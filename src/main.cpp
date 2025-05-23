#include <SoftwareSerial.h>

#include "Communication/NetworkManager.h"
#include "defines.h"
#include "gesture.h"
#include "input.h"
#include "networkconfig.h"

// #if COMMUNICATION == COMM_SERIAL
// #include "Communication/SerialCommunication.h"
// #elif COMMUNICATION == COMM_WIFISERIAL
#include "Communication/WiFiCommunication.h"
// #endif

#if ENCODING == ENCODING_ALPHA
#include "Encoder/Alpha.h"
AlphaEncoder Encoder;  // 实例化编码器对象
#elif ENCODING == ENCODING_LEGACY
#include "Encoder/Legacy.h"
LegacyEncoder Encoder;  // 实例化编码器对象
#endif

void WiFiConnect(char* ssid, char* password);
void handleSerialCommand(String cmd);
void CheckSerialCommand();

GloversInput gloversInput;
NetworkManager network;
ICommunication* comm;
NetWorkConfig netWorkConfig;
int loops = 0;
String serialCommand = "";

void WiFiConnect(char* ssid, char* password) {
	String _deviceName = DEVICE_NAME;
	network.configure(ssid, password,
					  _deviceName);  // 配置WiFi信息和设备名称

	Serial.println("[" + network.getSSID() + "] Connecting...");
	network.begin();  // 初始化网络连接
	int retries = 0;
	while (WiFi.status() != WL_CONNECTED && retries < 20) {
		delay(500);
		CheckSerialCommand();
		Serial.print(".");
		retries++;
	}

	if (WiFi.status() == WL_CONNECTED) {
		Serial.println("\n[" + _deviceName + "] WiFi connected.");
		Serial.print("[" + _deviceName + "] IP address: ");
		Serial.println(WiFi.localIP());

		network.scanForServer();
	} else {
		Serial.println("\n[" + _deviceName + "] Failed to connect to WiFi.");
		while (WiFi.status() != WL_CONNECTED) {
			digitalWrite(LED_BUILTIN, LOW);
			CheckSerialCommand();
			delay(500);
			digitalWrite(LED_BUILTIN, HIGH);
			CheckSerialCommand();
			delay(500);
		}
	}
}

void handleSerialCommand(String cmd) {
	if (cmd.startsWith("SET_WIFI ")) {
		digitalWrite(LED_BUILTIN, HIGH);
		WiFi.disconnect();

		// 提取双引号中的内容
		int firstQuote = cmd.indexOf('"');
		int secondQuote = cmd.indexOf('"', firstQuote + 1);
		int thirdQuote = cmd.indexOf('"', secondQuote + 1);
		int fourthQuote = cmd.indexOf('"', thirdQuote + 1);

		if (firstQuote != -1 && secondQuote != -1 && thirdQuote != -1
			&& fourthQuote != -1) {
			String newSsid = cmd.substring(firstQuote + 1, secondQuote);
			String newPass = cmd.substring(thirdQuote + 1, fourthQuote);

			netWorkConfig.saveWiFiConfig(newSsid, newPass);
			Serial.println("WiFi config saved.");

			char ssidChar[33];
			char passChar[65];
			netWorkConfig.loadWiFiConfig(ssidChar, passChar);
			WiFiConnect(ssidChar, passChar);
		} else {
			Serial.println("Invalid format. Use: SET_WIFI \"ssid\" \"password\"");
		}
	}
}

void CheckSerialCommand() {
	while (Serial.available()) {
		char c = Serial.read();
		if (c == '\n') {
			serialCommand.trim();  // 去除前后空白
			// Serial.print("Received command: ");
			// Serial.println(serialCommand);
			handleSerialCommand(serialCommand);
			serialCommand = "";
		} else {
			serialCommand += c;
		}
	}
}

void setup() {
	Serial.begin(SERIAL_BAUD_RATE);
	pinMode(LED_BUILTIN, OUTPUT);
	char ssidChar[33];  // 最多32字节 + null 终止符
	char passChar[65];  // 最多64字节 + null 终止符
	netWorkConfig.loadWiFiConfig(ssidChar, passChar);  // 从 EEPROM 中加载 WiFi 配置
	WiFiConnect(&ssidChar[0], &passChar[0]);  // 连接到新 WiFi

	// #if COMMUNICATION == COMM_SERIAL
	//	comm = new SerialCommunication();
	// #elif COMMUNICATION == COMM_WIFISERIAL
	comm = new WifiCommunication();
	// #endif
	comm->start(const_cast<char*>(network.getServer().c_str()));  // 启动通信
}

void loop() {
	// 监听串口输入命令（非阻塞）
	CheckSerialCommand();
	if (comm->isOpen()) {
#if USING_CALIB_PIN
		bool calibButton = getButton(PIN_CALIB) != INVERT_CALIB;
		if (calibButton) {
			loops = 0;
		}
#else
		bool calibButton = false;
#endif

		bool calibrate = false;
		if (loops < CALIBRATION_LOOPS || ALWAYS_CALIBRATING) {
			calibrate = true;
			loops++;
		}

		int* fingerPos = gloversInput.getFingerPosition(calibrate, calibButton);
		bool joyButton = false;

#if TRIGGER_GESTURE
		bool triggerButton = triggerGesture(fingerPos);
#else
		bool triggerButton = false;
#endif

		bool aButton = false;
		bool bButton = false;

#if GRAB_GESTURE
		bool grabButton = grabGesture(fingerPos);
#else
		bool grabButton = false;
#endif

#if PINCH_GESTURE
		bool pinchButton = pinchGesture(fingerPos);
#else
		bool pinchButton = false;

#endif

		bool menuButton = false;

		int JoyX = 0;
		int JoyY = 0;

		comm->output(Encoder.encode(
			fingerPos,
			JoyX,
			JoyY,
			joyButton,
			triggerButton,
			aButton,
			bButton,
			grabButton,
			pinchButton,
			calibButton,
			menuButton
		));
		delay(MAINTHREAD_DELAY);
	}
}

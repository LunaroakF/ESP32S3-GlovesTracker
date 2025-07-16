#include "NetworkManager.h"

NetworkManager::NetworkManager() {}

void NetworkManager::configure(
	const char* ssid,
	const char* password,
	const String& deviceName
) {
	_ssid = ssid;
	_password = password;
	_deviceName = deviceName;
}

void NetworkManager::begin() {
	WiFi.mode(WIFI_STA);
	WiFi.hostname(_deviceName);
	WiFi.begin(_ssid, _password);
	Serial.print("[" + _deviceName + "] Connecting to WiFi");
}

void NetworkManager::scanForServer() {
	WiFiUDP udp;
	udp.begin(2565);  // 本地监听端口

	IPAddress localIP = WiFi.localIP();
	IPAddress baseIP = localIP;
	baseIP[3] = 0;

	const char* message = "GloveMessageHello";
	const char* expectedResponse = "GloveMessageHelloBack";

	unsigned long startTime = millis();
	bool found = false;

	Serial.println("[" + _deviceName + "] Scanning local network for server...");

	for (int i = 1; i <= 255 && !found; i++) {
		IPAddress targetIP(baseIP[0], baseIP[1], baseIP[2], i);
		if (targetIP == localIP) {
			continue;
		}

		udp.beginPacket(targetIP, 2566);  // 向目标地址的端口2566发送消息
		udp.write((uint8_t*)message, strlen(message));
		udp.endPacket();
		delay(10);  // 避免过多拥塞

		// 等待回应
		unsigned long t0 = millis();
		while (millis() - t0 < 100 && !found) {
			int packetSize = udp.parsePacket();
			if (packetSize) {
				char buffer[64];
				int len = udp.read(buffer, sizeof(buffer) - 1);
				buffer[len] = '\0';  // 确保以 null 结尾

				// 检查回应内容
				if (strcmp(buffer, expectedResponse) == 0) {
					_server = udp.remoteIP().toString();
					found = true;

					Serial.println("[" + _deviceName + "] Found server at: " + _server);
				} else {
					Serial.println(
						"Received unexpected response from " + udp.remoteIP().toString()
						+ ": " + buffer
					);
				}
			}
		}
	}

	udp.stop();

	if (!found) {
		Serial.println(
			"[" + _deviceName + "] No matching server response found in local network."
		);
	}
}

bool NetworkManager::isConnected() { return WiFi.status() == WL_CONNECTED; }

String NetworkManager::getDeviceName() const { return _deviceName; }
String NetworkManager::getSSID() const { return _ssid; }
String NetworkManager::getPassword() const { return _password; }
String NetworkManager::getServer() { return _server; }
String NetworkManager::getServerPort() { return _serverPort; }

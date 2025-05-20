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
	udp.begin(2565);  // 监听端口

	IPAddress localIP = WiFi.localIP();
	IPAddress baseIP = localIP;
	baseIP[3] = 0;

	const char* message = "Hello";
	unsigned long startTime = millis();
	bool found = false;

	Serial.println("[" + _deviceName + "] Scanning local network for server...");

	for (int i = 1; i <= 255 && !found; i++) {
		IPAddress targetIP(baseIP[0], baseIP[1], baseIP[2], i);
		if (targetIP == localIP) {
			continue;
		}

		udp.beginPacket(targetIP, 2566);
		udp.write(message);
		udp.endPacket();
		delay(10);  // 避免过多拥塞

		// 检查回应（短等待）
		unsigned long t0 = millis();
		while (millis() - t0 < 100 && !found) {
			int packetSize = udp.parsePacket();
			if (packetSize) {
				char buffer[64];
				int len = udp.read(buffer, sizeof(buffer) - 1);
				buffer[len] = '\0';

				_server = udp.remoteIP().toString();
				found = true;

				Serial.println("[" + _deviceName + "] Found server at: " + _server);
			}
		}
	}

	udp.stop();

	if (!found) {
		Serial.println(
			"[" + _deviceName + "] No server response found in local network."
		);
	}
}

bool NetworkManager::isConnected() { return WiFi.status() == WL_CONNECTED; }

String NetworkManager::getDeviceName() const { return _deviceName; }
String NetworkManager::getSSID() const { return _ssid; }
String NetworkManager::getPassword() const { return _password; }
String NetworkManager::getServer() { return _server; }
String NetworkManager::getServerPort() { return _serverPort; }

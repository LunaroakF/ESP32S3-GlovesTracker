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

bool NetworkManager::begin() {
	WiFi.mode(WIFI_STA);
	WiFi.hostname(_deviceName);
	WiFi.begin(_ssid, _password);
	Serial.print("[" + _deviceName + "] Connecting to WiFi");

	int retries = 0;
	while (WiFi.status() != WL_CONNECTED && retries < 20) {
		delay(500);
		Serial.print(".");
		retries++;
	}

	if (WiFi.status() == WL_CONNECTED) {
		Serial.println("\n[" + _deviceName + "] WiFi connected.");
		Serial.print("[" + _deviceName + "] IP address: ");
		Serial.println(WiFi.localIP());
		return true;
	} else {
		Serial.println("\n[" + _deviceName + "] Failed to connect to WiFi.");
		return false;
	}
}

bool NetworkManager::isConnected() { return WiFi.status() == WL_CONNECTED; }

String NetworkManager::getDeviceName() const { return _deviceName; }
String NetworkManager::getSSID() const { return _ssid; }
String NetworkManager::getPassword() const { return _password; }
String NetworkManager::getServer() { return _server; }
String NetworkManager::getServerPort() { return _serverPort; }

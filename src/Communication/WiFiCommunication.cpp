#include "WiFiCommunication.h"

bool WifiCommunication::isOpen() { return m_isOpen; }

void WifiCommunication::start(char* additional) {
	_serverIP.fromString(additional);
	if (!_udp.begin(2565)) {  // 本地监听端口
		Serial.println("[WifiCommunication] UDP begin failed");
		m_isOpen = false;
		return;
	} else {
		m_isOpen = true;
	}
}

void WifiCommunication::output(char* data) {
	if (!m_isOpen) {
		return;
	}
	// Serial.println(String(data));  // Debug output to Serial
	_udp.beginPacket(_serverIP, _serverPort);
	_udp.write((uint8_t*)data, strlen(data));
	_udp.endPacket();
}

bool WifiCommunication::readData(char* input) {
	byte size = Serial.readBytesUntil('\n', input, 100);
	input[size] = NULL;
	return input != NULL && strlen(input) > 0;
}
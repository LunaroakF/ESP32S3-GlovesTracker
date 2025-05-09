#include "WiFiCommunication.h"

bool WifiCommunication::isOpen() { return m_isOpen; }

void WifiCommunication::start() {
	// Serial.begin(SERIAL_BAUD_RATE);
	m_isOpen = true;
}

void WifiCommunication::output(char* data) {
	Serial.print(data);
	Serial.flush();
}

bool WifiCommunication::readData(char* input) {
	byte size = Serial.readBytesUntil('\n', input, 100);
	input[size] = NULL;
	return input != NULL && strlen(input) > 0;
}
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#define EEPROM_SIZE 96

class NetWorkConfig {
public:
	NetWorkConfig() {
		// Initialize the network configuration
		// You can set default values here if needed
	}

	void loadWiFiConfig(char* ssid, char* password);

	void saveWiFiConfig(String ssid, String password);
};
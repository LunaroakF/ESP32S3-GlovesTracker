#include "networkconfig.h"

void NetWorkConfig::loadWiFiConfig(char* ssid, char* password) {
	EEPROM.begin(EEPROM_SIZE);

	for (int i = 0; i < 32; ++i) {
		ssid[i] = EEPROM.read(i);
	}
	ssid[32] = '\0';

	for (int i = 0; i < 64; ++i) {
		password[i] = EEPROM.read(32 + i);
	}
	password[64] = '\0';

	EEPROM.end();
}


void NetWorkConfig::saveWiFiConfig(String ssid, String password) {
	EEPROM.begin(EEPROM_SIZE);
	for (int i = 0; i < 32; ++i) {
		EEPROM.write(i, i < ssid.length() ? ssid[i] : 0);
	}
	for (int i = 0; i < 64; ++i) {
		EEPROM.write(32 + i, i < password.length() ? password[i] : 0);
	}
	EEPROM.commit();
	EEPROM.end();
}
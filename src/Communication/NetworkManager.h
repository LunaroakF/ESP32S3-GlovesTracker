#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

class NetworkManager {
public:
	NetworkManager();
	void configure(
		const char* ssid = "SSID",
		const char* password = "PASSWORD",
		const String& deviceName = "HOSTNAME"
	);
	bool begin();
	bool isConnected();
	String getDeviceName() const;
	String getSSID() const;
	String getPassword() const;
	String getServer();
	String getServerPort();

private:
	const char* _ssid = "SSID";
	const char* _password = "PASSWORD";
	String _deviceName = "HOSTNAME";
	String _server = "0.0.0.0";
	String _serverPort = "2566";
};

#endif

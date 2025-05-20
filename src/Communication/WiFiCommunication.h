#include <WiFiUdp.h>

#include "../GlobalVars.h"
#include "ICommunication.h"

class WifiCommunication : public ICommunication {
private:
	bool m_isOpen;
	String m_server = "";
	WiFiUDP _udp;
	IPAddress _serverIP;
	uint16_t _serverPort = 2566;  // 服务端端口

public:
	WifiCommunication() { m_isOpen = false; }

	bool isOpen();

	void start(char* additional);

	void output(char* data);

	bool readData(char* input);
};
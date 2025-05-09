#include "ICommunication.h"

class WifiCommunication : public ICommunication {
private:
	bool m_isOpen;
	String m_server = "";

public:
	WifiCommunication() { m_isOpen = false; }

	bool isOpen();

	void start();

	void output(char* data);

	bool readData(char* input);
};
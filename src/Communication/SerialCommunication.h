#include "ICommunication.h"

class SerialCommunication : public ICommunication {
private:
	bool m_isOpen;
	String m_server = "";

public:
	SerialCommunication() { m_isOpen = false; }

	bool isOpen();

	void start();

	void output(char* data);

	bool readData(char* input);
};
#include <Arduino.h>

#include "../defines.h"

class ICommunication {
public:
	virtual bool isOpen() = 0;

	virtual void start(char* additional) = 0;

	virtual void output(char* data) = 0;

	virtual bool readData(char* input) = 0;
};

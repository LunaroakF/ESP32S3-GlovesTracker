#include <M5Unified.h>

#include "defines.h"

class ScreenManager {
public:
	void begin();
	void update();
	void drawBackground();
	void drawIP(const String& ipAddress, const String& ServeripAddress = "0.0.0.0");
	void drawFingers(int thumb, int index, int middle, int ring, int pinky);
	void drawJoySticks(int JoyX, int JoyY);

private:
	void sleep();
	void wake();

	unsigned long lastInteractionTime = 0;
	bool sleeping = false;

	const unsigned long timeoutMs = 30 * 1000;  // 息屏时间：30秒
	const uint8_t brightnessOn = 70;  // 正常亮度
	const uint8_t brightnessOff = 0;  // 息屏亮度
};

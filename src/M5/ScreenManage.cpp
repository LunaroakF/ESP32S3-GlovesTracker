#include "ScreenManage.h"

void ScreenManager::begin() {
	M5.Lcd.setBrightness(brightnessOn);
	lastInteractionTime = millis();
	sleeping = false;
}

void ScreenManager::update() {
	M5.update();

	if (M5.BtnA.wasPressed()) {
		wake();  // 按键唤醒并重置计时
	}

	if (!sleeping && (millis() - lastInteractionTime > timeoutMs)) {
		sleep();
	}
}

void ScreenManager::sleep() {
	M5.Lcd.setBrightness(brightnessOff);
	sleeping = true;
}

void ScreenManager::wake() {
	if (sleeping) {
		M5.Lcd.setBrightness(brightnessOn);
		sleeping = false;
	}
	lastInteractionTime = millis();  // 重置计时器
}

void ScreenManager::drawBackground() {
	int screenWidth = M5.Lcd.width();
    int screenHeight = M5.Lcd.height();
	int topHeight = 15;
	M5.Lcd.fillRect(0, 0, screenWidth, topHeight, YELLOW);
	M5.Lcd.fillRect(0, topHeight, screenWidth, M5.Lcd.height() - topHeight, SKYBLUE);
    M5.Lcd.fillRect(0, screenHeight - topHeight, screenWidth, topHeight, GREEN);
}

void ScreenManager::drawIP(const String& ipAddress, const String& ServeripAddress) {
	int screenWidth = M5.Lcd.width();
    int screenHeight = M5.Lcd.height();
	int topHeight = 15;
	M5.Lcd.setTextColor(BLACK, YELLOW);
	M5.Lcd.setTextSize(1);
    String Text = "C: " + ipAddress;
	int textWidth = M5.Lcd.textWidth(Text);
	int x = (screenWidth - textWidth) / 2;
	M5.Lcd.fillRect(0, 0, screenWidth, topHeight, YELLOW);  // 擦除旧IP
	M5.Lcd.setCursor(x, 4);
	M5.Lcd.print(Text);
    M5.Lcd.setTextColor(BLACK, GREEN);
    M5.Lcd.setTextSize(1);
    Text = "S: " + ServeripAddress;
    textWidth = M5.Lcd.textWidth(Text);
	x = (screenWidth - textWidth) / 2;
    M5.Lcd.fillRect(0, screenHeight - topHeight, screenWidth, topHeight, GREEN);  // 擦除旧IP
	M5.Lcd.setCursor(x, screenHeight - topHeight + 4);
	M5.Lcd.print(Text);
}

void ScreenManager::drawFingers(int thumb, int index, int middle, int ring, int pinky) {
	int baseY = 15 + 2;
	int lineHeight = 10;
	int screenWidth = M5.Lcd.width();

	// 只清理数字显示行对应的区域
	// M5.Lcd.fillRect(0, baseY, screenWidth, lineHeight * 5, SKYBLUE);

	M5.Lcd.setTextColor(BLACK, SKYBLUE);
	M5.Lcd.setTextSize(1);
	M5.Lcd.setCursor(28, baseY + lineHeight * 0);
	M5.Lcd.printf("THUMB:  %04d", thumb);
	M5.Lcd.setCursor(28, baseY + lineHeight * 1);
	M5.Lcd.printf("INDEX:  %04d", index);
	M5.Lcd.setCursor(28, baseY + lineHeight * 2);
	M5.Lcd.printf("MIDDLE: %04d", middle);
	M5.Lcd.setCursor(28, baseY + lineHeight * 3);
	M5.Lcd.printf("RING:   %04d", ring);
	M5.Lcd.setCursor(28, baseY + lineHeight * 4);
	M5.Lcd.printf("PINKY:  %04d", pinky);
}

void ScreenManager::drawJoySticks(int JoyX, int JoyY) {
	if (JOYSTICK_BLANK) {
		return;  // 如果禁用摇杆，则不绘制
	}
	int lineHeight = 10;
	int baseY = 15 + 2 + lineHeight * 5 + 5;
	int screenWidth = M5.Lcd.width();

	// 只清理数字显示行对应的区域
	// M5.Lcd.fillRect(0, baseY, screenWidth, lineHeight * 5, SKYBLUE);

	M5.Lcd.setTextColor(BLACK, SKYBLUE);
	M5.Lcd.setTextSize(1);
	M5.Lcd.setCursor(28, baseY + lineHeight * 0);
	M5.Lcd.printf("JOYX:  %04d", JoyX);
	M5.Lcd.setCursor(28, baseY + lineHeight * 1);
	M5.Lcd.printf("JOYY:  %04d", JoyY);
}
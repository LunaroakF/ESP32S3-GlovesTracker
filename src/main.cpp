#include <SoftwareSerial.h>

#include "defines.h"
#include "input.h"

#if COMMUNICATION == COMM_SERIAL
#include "Communication/SerialCommunication.h"
#elif COMMUNICATION == COMM_WIFISERIAL
#include "Communication/WiFiCommunication.h"
#endif

#if ENCODING == ENCODING_ALPHA
#include "Encoder/Alpha.h"
AlphaEncoder Encoder;  // 实例化编码器对象
#elif ENCODING == ENCODING_LEGACY
#include "Encoder/Legacy.h"
LegacyEncoder Encoder;  // 实例化编码器对象
#endif
GloversInput gloversInput;

ICommunication* comm;
int loops = 0;

void setup() {
#if COMMUNICATION == COMM_SERIAL
	comm = new SerialCommunication();
#elif COMMUNICATION == COMM_BTSERIAL
	comm = new Communication();
#endif
	comm->start();
	Serial.begin(115200);  // 初始波特率115200
}

void loop() {
	if (comm->isOpen()) {
#if USING_CALIB_PIN
		bool calibButton = getButton(PIN_CALIB) != INVERT_CALIB;
		if (calibButton) {
			loops = 0;
		}
#else
		bool calibButton = false;
#endif

		bool calibrate = false;
		if (loops < CALIBRATION_LOOPS || ALWAYS_CALIBRATING) {
			calibrate = true;
			loops++;
		}

		int* fingerPos = gloversInput.getFingerPosition(calibrate, calibButton);
		bool joyButton = false;

#if TRIGGER_GESTURE
		bool triggerButton = triggerGesture(fingerPos);
#else
		bool triggerButton = false;
#endif

		bool aButton = false;
		bool bButton = false;

#if GRAB_GESTURE
		bool grabButton = grabGesture(fingerPos);
#else
		bool grabButton = false;
#endif

#if PINCH_GESTURE
		bool pinchButton = pinchGesture(fingerPos);
#else
		bool pinchButton = false;
#endif

		bool menuButton = false;

		int JoyX = 0;
		int JoyY = 0;

		comm->output(Encoder.encode(
			fingerPos,
			JoyX,
			JoyY,
			joyButton,
			triggerButton,
			aButton,
			bButton,
			grabButton,
			pinchButton,
			calibButton,
			menuButton
		));

		delay(MAINTHREAD_DELAY);
	}
}

#include <HardwareSerial.h>
#include <RunningMedian.h>  //中值滤波 https://github.com/RobTillaart/RunningMedian

#include "defines.h"

class GloversInput {
public:
	GloversInput() {
		pinMode(PIN_SA, OUTPUT);
		pinMode(PIN_SB, OUTPUT);
		pinMode(PIN_SC, OUTPUT);
	}
	int* getFingerPosition(bool calibrating, bool reset);
	int analogReadDeadzone(byte pin);
	int getJoyX();
	int getJoyY();

private:
	void setChannel(int channel);
#if ENABLE_MEDIAN_FILTER
#include <RunningMedian.h>
	RunningMedian rmSamples[5]
		= {RunningMedian(MEDIAN_SAMPLES),
		   RunningMedian(MEDIAN_SAMPLES),
		   RunningMedian(MEDIAN_SAMPLES),
		   RunningMedian(MEDIAN_SAMPLES),
		   RunningMedian(MEDIAN_SAMPLES)};
#endif
	int maxFingers[5] = {0, 0, 0, 0, 0};
	int minFingers[5] = {ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX};
};
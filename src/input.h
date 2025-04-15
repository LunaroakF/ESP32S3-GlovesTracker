#include <SoftwareSerial.h>
#include <RunningMedian.h>//中值滤波https://github.com/RobTillaart/RunningMedian
#include "defines.h"

class GloversInput {
  public:
    GloversInput() {
      pinMode(BIT_SA, OUTPUT);
      pinMode(BIT_SB, OUTPUT);
      pinMode(BIT_SC, OUTPUT);
    }
    int* getFingerPosition(bool reset, bool recalculate);

    private:
      void setChannel(int channel);
      int maxFingers[5] = {0, 0, 0, 0, 0};
      int minFingers[5] = {ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX};
};
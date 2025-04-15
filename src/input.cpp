#include <SoftwareSerial.h>

#include "defines.h"

struct fingerData
{
  int Thumb = 0;
  int Index = 0;
  int Middle = 0;
  int Ring = 0;
  int Pinky = 0; 
};

fingerData maxFingers = {0, 0, 0, 0, 0};
fingerData minFingers = {ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX, ANALOG_MAX};


int* getFingerPosition(bool reset, bool recalulate){
  
}

void setChannel(int channel) {
  digitalWrite(Bit_SA, bitRead(channel, 0));
  digitalWrite(Bit_SB, bitRead(channel, 1));
  digitalWrite(Bit_SC, bitRead(channel, 2));
  delay(1);
}
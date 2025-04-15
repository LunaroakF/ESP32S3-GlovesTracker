#include "input.h"

int* GloversInput::getFingerPosition(bool reset, bool recalCulate){
  static int fingerPosition[5] = {0, 0, 0, 0, 0};

  int ADC_Value = analogRead(PIN_ADC);
  for (size_t i = 0; i < 5; i++)
  {
    setChannel(i);
    delayMicroseconds(10);
    ADC_Value = analogRead(PIN_ADC) - PHASE;
    fingerPosition[i] = ADC_Value < 0 ? 0 : ADC_Value;
  }
  return &fingerPosition[0];
}

void GloversInput::setChannel(int channel) {
  digitalWrite(BIT_SA, bitRead(channel, 0));
  digitalWrite(BIT_SB, bitRead(channel, 1));
  digitalWrite(BIT_SC, bitRead(channel, 2));
}
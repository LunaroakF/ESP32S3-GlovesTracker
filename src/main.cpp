#include <SoftwareSerial.h>

#include "defines.h"
#include "input.h"
#include "Encoder/Alpha.h"

GloversInput gloversInput;
AlphaEncoder alphaEncoder; //实例化编码器对象

void setup() {
  Serial.begin(115200); //初始波特率115200
}

void output(char* data){
  Serial.print(data);
  Serial.flush();
}

void loop() {
  int* fingerPoition = gloversInput.getFingerPosition(false,false);
  // Serial.println(
  //   "A"+ String(fingerPoition[0]) +
  //   "B"+ String(fingerPoition[1]) +
  //   "C"+ String(fingerPoition[2]) +
  //   "D"+ String(fingerPoition[3]) +
  //   "E"+ String(fingerPoition[4]) +
  //   "F"+ANALOG_MAX+
  //   "G"+ANALOG_MAX+
  //   "P0HJN");
  Serial.println(alphaEncoder.encode(fingerPoition, 0, 0, false, false, false, false, false, false, false, false));
  delay(50);
}

#include <SoftwareSerial.h>

#include "defines.h"
#include "input.h"
#if ENCODING == ENCODING_ALPHA
  #include "Encoder/Alpha.h"
  AlphaEncoder Encoder; //实例化编码器对象
#elif ENCODING == ENCODING_LEGACY
  #include "Encoder/Legacy.h"
  LegacyEncoder Encoder; //实例化编码器对象
#endif

GloversInput gloversInput;

void setup() {
  Serial.begin(115200); //初始波特率115200
}

void output(char* data){
  Serial.print(data);
  Serial.flush();
}

void loop() {
  int* fingerPoition = gloversInput.getFingerPosition(false,false);
  Serial.println(Encoder.encode(fingerPoition, 0, 0, false, false, false, false, false, false, false, false));
  delay(MAINTHREAD_DELAY);
}
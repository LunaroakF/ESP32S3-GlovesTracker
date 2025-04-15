#include <SoftwareSerial.h>

#include "defines.h"

void setup() {
  Serial.begin(115200); //初始波特率115200
  pinMode(Bit_SA, OUTPUT);
  pinMode(Bit_SB, OUTPUT);
  pinMode(Bit_SC, OUTPUT);
}

void output(char* data){
  Serial.print(data);
  Serial.flush();
}

void loop() {
  int adcValue = analogRead(A0)-11;
  
  Serial.println("A"+ String(adcValue) +"B0C0D0E0F1023G1023P0HJN");
  delay(4);
}

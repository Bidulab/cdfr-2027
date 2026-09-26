#include <SoftwareSerial.h>

SoftwareSerial HC12(2, 3); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);            
  HC12.begin(9600);           
}

void loop() {
  while (HC12.available()) {
    Serial.write(HC12.read());
  }
  while (Serial.available()) { 
    HC12.write(Serial.read());
  }
}
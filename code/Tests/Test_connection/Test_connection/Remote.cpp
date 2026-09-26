#include "HardwareSerial.h"
#include "Arduino.h"
#include "Remote.h"

#include <SoftwareSerial.h>

//#define HC12 HC12
SoftwareSerial HC12(2, 3);
Remote::Remote(unsigned long baud, short int initCounter) {
  HC12.begin(baud);
  counter = initCounter;
}
static unsigned long i = 0;
static bool waiting = false;

static unsigned long lastSentTime = 0;



// Returns true if valid
bool Remote::updateValues() {
      //Serial.write("Debut");
  if (!waiting) {
    while (HC12.available() > 0)
      HC12.read();
    HC12.write('A');  // Send get message

    //Serial.write("A");

    //Serial.println("Robot: Sent A");
    delay(10);
    waiting = true;
    i = 0;
    lastSentTime = millis();
  }

  if (HC12.available() < 13) {
    //i++;
    if (millis() - lastSentTime > 500){//(i >= 40000) {
      //Serial.println("Robot: Timeout!");
      waiting = false;
      i = 0;
    }
    return false;
  }
  waiting = false;

  // read the incoming bytes
  HC12.readBytes(Mymessage, 13);
  /*Serial.println("Robot: Got 13 bytes!");
  Serial.write(Mymessage, 13);
  Serial.println();*/

  Joystick1_X = Mymessage[1];
  Joystick1_X = -2 * Joystick1_X + 255;
  Joystick1_Y = Mymessage[2];
  Joystick1_Y = -2 * Joystick1_Y + 255;

  Joystick2_X = Mymessage[3];
  Joystick2_X = -2 * Joystick2_X + 255;
  Joystick2_Y = Mymessage[4];
  Joystick2_Y = -2 * Joystick2_Y + 255;

  Button1 = !Mymessage[5];
  Button2 = !Mymessage[6];
  Button3 = !Mymessage[7];
  Button4 = !Mymessage[8];

  Joystick1_SW = !Mymessage[9];
  Joystick2_SW = !Mymessage[10];

  Encoder_SW = !Mymessage[11];

  Serial.println("Joystick1_X : ");
  Serial.println(Joystick1_X);

  HC12.flush();


  return true;
}

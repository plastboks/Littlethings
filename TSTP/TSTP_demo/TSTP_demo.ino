/* 
  
  Proof of concept of TSTP. A 400x240 display will be used to simplefy testing.

  @description: Tweeno small transport protocol is a simple and 
                stupid protocol for communication between Arduino and python.
                The reason for this protocol is for simplefy datatransmission.

  @date: 2012-10-09

  @filename: TSTP_demo.ino
  
  @author: Alexander Skjolden

*/

#include <UTFT.h>
#include <avr/pgmspace.h>
#include "tstp.h"

tstp t(Serial);

UTFT myGLCD(ITDB32WD,38,39,40,41);


void setup() {
  myGLCD.InitLCD(LANDSCAPE);
  Serial.begin(57600);
  Serial.flush();
}


void loop() {}


void serialEvent() {
  while (Serial.available()) {
  
    t.getData();   

  }
}

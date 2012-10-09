/* 
  
  Tweeno Small Transport Protocol

  @description: Tweeno small transport protocol is a simple and 
                stupid protocol for communication between Arduino and python.
                The reason for this protocol is for simplefy datatransmission.

  @date: 2012-10-09

  @filename: tstp.cpp
  
  @author: Alexander Skjolden

*/

#include "arduino.h"
#include "tstp.h"

tstp::tstp(HardwareSerial& serial) : _s(serial) {}

void tstp::readData() {
  while(_s.available()) {
    
    char inInt = (int)_s.read();
    
    if (inInt == 1) {
      Serial.write(0x01);  
    }
   
    if (inInt == 2) {
      Serial.write("STX is received");
    }
   
    if (inInt == 3) {
      Serial.write("ETX is received");
    }
    
    if (inInt == 4) {
      Serial.write("EOT is received");
    }
    
    if (inInt == 6) {
      Serial.write("ACK is received");
    }
    
    if (inInt == 30) {
      Serial.write("RS is received");
    }
    
  }
}

void tstp::checkSum() {
}

void tstp::response() {
}






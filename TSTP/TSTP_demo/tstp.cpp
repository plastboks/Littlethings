/* 
  
  Tweeno Small Transport Protocol

  @description: Tweeno small transport protocol is a simple and 
                stupid protocol for communication between Arduino and python.
                The reason for this protocol is for simplefy datatransmission.
                This protocol is inspired by ESPA 4.4.4.

  @date: 2012-10-09

  @filename: tstp.cpp
  
  @author: Alexander Skjolden

  @version: 0.0.1

*/

#include "arduino.h"
#include "tstp.h"




tstp::tstp(HardwareSerial& serial) : _s(serial) {}



void tstp::readData() {
  while(_s.available()) {
    
    char inInt = (int)_s.read();
    
    if (inInt == 1) {
      _s.write("SOH is received");
      tstp::hasSOH = true; 
    }
   
    if (inInt == 2) {
      _s.write("STX is received");
      tstp::hasSTX = true;
    }
   
    if (inInt == 3) {
      _s.write("ETX is received");
      tstp::hasETX = true;
    }
    
    if (inInt == 4) {
      _s.write("EOT is received");
      tstp::hasEOT = true;
    }
    
    if (inInt == 6) {
      _s.write("ACK is received");
    }
    
    if (inInt == 30) {
      _s.write("RS is received");
      tstp::hasRS = true;
    }



  }
}



int tstp::genCheckSum(char *string) {
  int i, XOR, c;
  
  for (XOR = 0, i = 0; i < strlen(string); i++) {
    c = (unsigned char)string[i];
    XOR ^= c;
  }
  
  return XOR;
}

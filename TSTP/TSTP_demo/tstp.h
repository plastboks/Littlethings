/* 
  
  Tweeno Small Transport Protocol

  @description: Tweeno small transport protocol is a simple and 
                stupid protocol for communication between Arduino and python.
                The reason for this protocol is for simplefy datatransmission.
                This protocol is inspired by ESPA 4.4.4.

  @date: 2012-10-09

  @filename: tstp.h 
  
  @author: Alexander Skjolden
  
  @version: 0.0.1

*/

#ifndef tstp_h
#define tstp_h
#include "arduino.h"
#include "HardwareSerial.h"


class tstp {
  
  public:
    tstp(HardwareSerial& serial);
    HardwareSerial& _s;
    void readData();
    void response();
 
  private:
    
    int genCheckSum(char *string);
    
    boolean hasSOH;
    boolean hasSTX;
    boolean hasETX;
    boolean hasEOT;
    boolean hasRS;

};

#endif


/* 
  
  Tweeno Small Transport Protocol

  @description: Tweeno small transport protocol is a simple and 
                stupid protocol for communication between Arduino and python.
                The reason for this protocol is for simplefy datatransmission.

  @date: 2012-10-09

  @filename: tstp.h 
  
  @author: Alexander Skjolden

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
    void checkSum();
    void response();
  
  private: 
    boolean hasSOH;
    boolean hasSTX;
    boolean hasETX;
    boolean hasEOT;

};

#endif


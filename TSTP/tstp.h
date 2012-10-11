/* 
  
  Tweeno Small Transport Protocol

  @description: Tweeno small transport protocol is a simple and 
                stupid protocol for communication between Arduino and python.
                The reason for this protocol is for simplefy datatransmission.

  @date: 2012-10-09

  @filename: tstp.h 
  
  @author: Alexander Skjolden

  @version: 0.0.2

*/

#ifndef tstp_h
#define tstp_h
#include "arduino.h"
#include "HardwareSerial.h"


class tstp {
  
  public:
    tstp(HardwareSerial& serial);
    HardwareSerial& _s;
    
    void getData();
    void response();
  


  private: 
    void readHeader(int input);
    void readData(int input);
    void string(int intput);
    void image(int intput);
    void checkSum();
    void nukeDataArray(int size);

    unsigned int byteCounter;
    unsigned int dataType;
    unsigned int dataSize;
    unsigned int dataArray[];

    boolean gotHeader;
    
};

#endif

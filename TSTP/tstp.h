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
    unsigned int dataArray[256];
    unsigned int imageInfoArray[6];


  private: 
    void readHeader(int input);
    void readData(int input);
    void string(int input);
    void image(int intput);   
    void verifyCheckSum(int input);
    void nukeDataArray();

    int genCheckSum(unsigned int dataArray[], unsigned int dataSize); 

    unsigned int byteCounter;
    unsigned int dataType;
    unsigned int dataSize;
    unsigned int loopSize;

    boolean gotHeader;
    boolean readyForChecksum;
    
};

#endif

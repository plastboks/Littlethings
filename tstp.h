/* 
  
  Tweeno Small Transport Protocol

  @description: Tweeno small transport protocol is a simple and 
                stupid protocol for communication between Arduino and python.
                The reason for this protocol is for simplefy datatransmission.

  @date: 2012-10-09

  @filename: tstp.h 
  
  @author: Alexander Skjolden

  @version: 0.0.4

*/

#ifndef tstp_h
#define tstp_h
#include "HardwareSerial.h"
#include <avr/pgmspace.h>

class tstp {
  
  public:
    tstp(HardwareSerial& serial);
    HardwareSerial& _s;
    
    void getData();
    void response();
    unsigned int dataArray[256];
    unsigned int imageInfo[6];
    unsigned int imagePos[2];

    prog_uint16_t generatedImage[64];

    bool imageReady;


  private: 
    void readHeader(int input);
    void readData(int input);
    void string(int input);
    void image(int intput);   
    void verifyCheckSum(int input);
    void makeRGB565();
    void calcImgPos();
    void cleanUp();

    int genCheckSum(); 
    int c24t16(int r, int g, int b);

    unsigned int byteCounter;
    unsigned int dataType;
    unsigned int dataSize;
    unsigned int loopSize;

    bool gotHeader;
    bool readyForChecksum;
    
};

#endif

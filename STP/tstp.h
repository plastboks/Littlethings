/* 
  
  Tweeno Small Transport Protocol

  @description: Tweeno small transport protocol is a simple and 
                stupid protocol for communication between Arduino and python.
                The reason for this protocol is for simplify datatransmission.

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
    unsigned int dataInfo[8];
    
    unsigned int stringPos[2];
    unsigned int position[2];

    prog_uint16_t generatedImage[64];
    char stringData[256];

    bool imageReady;
    bool stringReady;
    bool clearScr;


  private: 
    void readHeader(int input);
    void readData(int input);

    void string(int input);
    void image(int intput);

    void verifyCheckSum(int input);
    void makeString();
    void makeRGB565(); // for 24bit input
    void conRGB565(); // for 16bit input

    void calcPos();
    void cleanUp();

    int genCheckSum(); 
    int c24t16(int r, int g, int b);
    int c8t16(int a, int b);

    unsigned int byteCounter;
    unsigned int dataType;
    unsigned int dataSize;
    unsigned int loopSize;

    bool gotHeader;
    bool readyForChecksum;
    
};

#endif

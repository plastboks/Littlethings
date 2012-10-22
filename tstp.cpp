/* 
  
  Tweeno Small Transport Protocol

  @description: Tweeno small transport protocol is a simple and 
                stupid protocol for communication between Arduino and python.
                The reason for this protocol is for simplify datatransmission.

  @date: 2012-10-09

  @filename: tstp.cpp
  
  @author: Alexander Skjolden

  @version: 0.0.7

*/

#include "tstp.h"
#include <avr/pgmspace.h>


tstp::tstp(HardwareSerial& serial) : _s(serial) {
  tstp::byteCounter = 0;
}


void tstp::getData() {
  while(_s.available()) {
    tstp::byteCounter++;
    int inInt = (int)_s.read();
    
    if (tstp::readyForChecksum) {
      tstp::verifyCheckSum(inInt);
    } else if (tstp::gotHeader) {
      tstp::readData(inInt);
    } else {
      tstp::readHeader(inInt);
    }
  }
}


void tstp::readHeader(int input) {
  
  if (tstp::byteCounter == 1) {
    tstp::dataType = input;
  } else if (tstp::byteCounter == 2) {
    tstp::dataSize = input;
    tstp::loopSize = input;
    tstp::gotHeader = true;
  }
}


void tstp::readData(int input) {
  int data = input;
  
  switch (tstp::dataType) {
    case 1:
      tstp::string(data);
      break;
    case 2:
      tstp::image(data);
      break;
  }
}


void tstp::string(int input) {
  int stringCount = tstp::byteCounter - 3;
  int mainCount = tstp::dataSize - tstp::loopSize;

  if (tstp::byteCounter <= 8) {
    tstp::dataInfo[stringCount] = input;
  } else if (tstp::loopSize) {
    tstp::dataArray[mainCount] = input;
    tstp::loopSize--;
  } 

  if (input == 0x17 && !tstp::loopSize) {
    tstp::readyForChecksum = true;
  }
}


void tstp::image(int input) { 
  int imageCount = tstp::byteCounter - 3;
  int mainCount = tstp::dataSize - tstp::loopSize;

  if (tstp::byteCounter <= 10) {
    tstp::dataInfo[imageCount] = input;
  } else if (tstp::loopSize) {
    dataArray[mainCount] = input;
    tstp::loopSize--;
  }

  if (input == 0x17 && !tstp::loopSize) {
    tstp::readyForChecksum = true;
  }
}


void tstp::verifyCheckSum(int input) {
  
  if (input == genCheckSum()) {
    _s.write(0x06);
    tstp::cleanUp();
    if (tstp::dataType == 1) {
      tstp::makeString();
    } else if (tstp::dataType == 2) {
      switch (tstp::dataInfo[6]) {
        case 1:
          tstp::makeRGB565();
          break;
        case 2:
          tstp::conRGB565();
          break;
      } 
    }
  } else {
    _s.write(0x15);
    tstp::cleanUp();
  }
}


int tstp::genCheckSum() {
  int i, XOR, c;

  for (XOR = 0, i = 0; i < tstp::dataSize; i++) {
    c = tstp::dataArray[i];
    XOR ^= c;
  }
  return XOR;  
}


int tstp::c24t16(int r, int g, int b) {
  int R16 = r >> 3;
  int G16 = g >> 2;
  int B16 = b >> 3;

  return ((R16 << 11) + (G16 << 5)) + B16;
}


int tstp::c8t16(int a, int b) {
  int calc = (a << 8) + b;
  return calc;
}


void tstp::calcPos() {
  tstp::position[0] = (tstp::dataInfo[0] << 8) + (tstp::dataInfo[1]);
  tstp::position[1] = (tstp::dataInfo[2] << 8) + (tstp::dataInfo[3]);
}


void tstp::makeString() {
  for (int i = 0; i < tstp::dataSize; i++) {
    tstp::stringData[i] = tstp::dataArray[i];
  }
  tstp::calcPos();
  tstp::stringReady = true;
}


void tstp::makeRGB565() {
  // Split out the colors
  for (int i = 0; i < (tstp::dataSize/3); i++) {
    int y = i * 3;
    int RGB565 = tstp::c24t16(tstp::dataArray[y], tstp::dataArray[(y+1)], tstp::dataArray[(y+2)]);
    tstp::generatedImage[i] = RGB565;
  }
  tstp::calcPos();
  tstp::imageReady = true;
}


void tstp::conRGB565() {
  for (int i = 0; i < (tstp::dataSize/2); i++) {
    int y = i * 2;
    int RGB565 = tstp::c8t16(tstp::dataArray[y], tstp::dataArray[(y+1)]);
    tstp::generatedImage[i] = RGB565;
  }
  tstp::calcPos();
  tstp::imageReady = true;
}


void tstp::cleanUp() {
  tstp::byteCounter = 0;
  gotHeader = false;
  readyForChecksum = false;
}


void tstp::response() {}






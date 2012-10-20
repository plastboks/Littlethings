/* 
  
  Tweeno Small Transport Protocol

  @description: Tweeno small transport protocol is a simple and 
                stupid protocol for communication between Arduino and python.
                The reason for this protocol is for simplefy datatransmission.

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
  int mainCount = tstp::byteCounter - 2;

  if (tstp::loopSize) {
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

  if (tstp::byteCounter <= 8) {
    tstp::imageInfo[imageCount] = input;
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
    tstp::makeRGB565();
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


void tstp::calcImgPos() {
  tstp::imagePos[0] = (tstp::imageInfo[0] << 8) + (tstp::imageInfo[1]);
  tstp::imagePos[1] = (tstp::imageInfo[2] << 8) + (tstp::imageInfo[3]);
}


void tstp::makeRGB565() {

  // Split out the colors
  for (int i = 0; i < (tstp::dataSize/3); i++) {
    int y = i * 3;
    int RGB565 = tstp::c24t16(tstp::dataArray[y], tstp::dataArray[(y+1)], tstp::dataArray[(y+2)]);
    tstp::generatedImage[i] = RGB565;
  }

  tstp::calcImgPos();
  tstp::imageReady = true;
}


void tstp::cleanUp() {
  tstp::byteCounter = 0;
  gotHeader = false;
  readyForChecksum = false;
}


void tstp::response() {}






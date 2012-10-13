/* 
  
  Tweeno Small Transport Protocol

  @description: Tweeno small transport protocol is a simple and 
                stupid protocol for communication between Arduino and python.
                The reason for this protocol is for simplefy datatransmission.

  @date: 2012-10-09

  @filename: tstp.cpp
  
  @author: Alexander Skjolden

  @version: 0.0.2

*/

#include "arduino.h"
#include "tstp.h"

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

  if (input == 0x17) tstp::readyForChecksum = true;

}


void tstp::image(int input) { // NOT A WORKING EXAMPLE, DATA NEED TO BE PROCESSED.
  int imageCount = tstp::byteCounter - 2;
  int mainCount = tstp::dataSize - tstp::loopSize;

  if (tstp::byteCounter <= 8) {
    tstp::imageInfoArray[imageCount] = input;
  } else if (tstp::loopSize) {
    tstp::dataArray[mainCount] = input;
    tstp::loopSize--;
  }

  if (input == 0x17) tstp::readyForChecksum = true;

}


void tstp::verifyCheckSum(int input) {
  
  if (input == genCheckSum(tstp::dataArray, tstp::dataSize)) {
    _s.write(0x06);
    tstp::makeRGB565();
  } else {
    _s.write(0x15);
  }
}


int tstp::genCheckSum(unsigned int dataArray[], unsigned int dataSize) {
  int i, XOR, c;

  for (XOR = 0, i = 0; i < dataSize; i++) {
    c = dataArray[i];
    XOR ^= c;
  }
  return XOR;  
}

void tstp::response() {}

int tstp::c24t16(int part[]) {
  int R = part[0] >> 3;
  int G = part[1] >> 2;
  int B = part[2] >> 3;

  //_s.write("Yo Bitch");
  //_s.write(((R << 11) + (G << 5)) + B);
  return ((R << 11) + (G << 5)) + B;
}

void tstp::makeRGB565() {
  int part[3]; 
  bool R = true;
  bool G, B;

  for (int i = 0; i < tstp::dataSize; i++) {
    if (R) {
      part[0] = dataArray[i];
      R = false;
      G = true;
      continue;
    }
    if (G) {
      part[1] = dataArray[i];
      G = false;
      B = true;
      continue;
    }
    if (B) {
      part[2] = dataArray[i];
      B = false;
      R = true;
      int RGB565 = tstp::c24t16(part);
      tstp::generatedImage[i / 3] = RGB565;
    }
  }

  tstp::imageReady = true;

}










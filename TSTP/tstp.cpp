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
    
    if (tstp::gotHeader) {
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
  if (tstp::dataSize) {
    tstp::dataArray[byteCounter - 2] = input;
    tstp::dataSize--;
  } else {
    for (int i = 0; i < byteCounter - 2 ; i++) { // This is a bit fugly..
      _s.write(tstp::dataArray[i]);
    }
  }
}

void tstp::image(int input) {
  _s.write(tstp::dataSize);
}

void nukeDataArray() {
  memset(&tstp::dataArray[0], 0, sizeof(tstp::dataArray[0]) * 256); // Probably not working...
}

void tstp::checkSum() {}

void tstp::response() {}






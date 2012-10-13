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
  int mainCount = tstp::byteCounter - 8;

  if (tstp::byteCounter <= 8) {
    tstp::imageInfoArray[imageCount] = input;
    _s.write("POS");
  } else if (tstp::loopSize) {
    tstp::dataArray[mainCount] = input;
    _s.write(input);
    tstp::loopSize--;
  }

  if (input == 0x17) {
    tstp::readyForChecksum = true;
  }

}

void tstp::nukeDataArray() {
  memset(tstp::dataArray, 0, 256); // NOT TESTED !!!
}

void tstp::verifyCheckSum(int input) {
  
  if (input == genCheckSum(tstp::dataArray, tstp::dataSize)) {
    //_s.write(0x06);
    _s.write(genCheckSum(tstp::dataArray, tstp::dataSize));
    //_s.write("Arduino says yay!");
  } else {
    //_s.write(0x15);
    _s.write(input);
    //_s.write(genCheckSum(tstp::dataArray, tstp::dataSize));
    //_s.write("Arduino says nay!");
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






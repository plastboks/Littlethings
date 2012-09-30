/*
Screens.cpp - Library for outputting different screens for Bragi
Created by Alexander Skjolden - September 2012
Released into the public domain.
This library depends on u8glib
*/

#include "Arduino.h"
#include "gps.h"

GPS::GPS(HardwareSerial& serial) : _s(serial) { }

bool GPS::getData() {
  while(_s.available()) {
    char c = (char)_s.read();
    if (GPS::encode(c)) {
      return true;
    }
    
    return false; 
  }
}

void GPS::setData() {
}

void GPS::averageSpeed() {
}

void odoMeter() {
}





/*
gps.h - Library for fetching and calculating GPS data
Created by Alexander Skjolden - September 2012
Released into the public domain.
This library depends on tinyGPS
*/

#ifndef gps_h
#define gps_h
#include "arduino.h"
#include "HardwareSerial.h"
#include "TinyGPS.h"



class GPS : TinyGPS {
  
  public:
    GPS(HardwareSerial& serial);
    HardwareSerial& _s;
    
    void averageSpeed();
    void odoMeter();
  
  private: 
    void setData();
    void getData();

};
#endif

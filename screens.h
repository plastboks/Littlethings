/*
Screens.h - Library for outputting different screens for Bragi
Created by Alexander Skjolden - September 2012
Released into the public domain.
This library depends on u8glib
*/

#ifndef screens_h
#define screens_h
#include "arduino.h"
#include "U8glib.h"

class Screens {
  
  public:
    Screens(U8GLIB_ST7920_128X64& parent);
    U8GLIB_ST7920_128X64& _d;
    
    void speedoMeter(int number, int time);
    void geo();
    void noSignal();
    void writing();
    void shutdown();

};
#endif






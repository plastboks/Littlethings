/*
Screens.h - Library for outputting different screens for Bragi
Created by Alexander Skjolden - September 2012
Released into the public domain.
This library depends on u8glib
*/

#ifndef ir_h
#define ir_h
#include "arduino.h"


class IR {
  
  public:
    IR(int pin);
    boolean compareSignals(int numpulses, int Signal[]);
    int listenForSignals();
    
  private:
    int _pin;

};
#endif

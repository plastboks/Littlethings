/*
ir.cpp - Library for fetching ir signals
Created by Alexander Skjolden - September 2012
Released into the public domain.
*/

#include "Arduino.h"
#include "ir.h"

// IR settings
#define IRpin_PIN PIND
#define MAXPULSE 65000
#define NUMPULSES 50
#define RESOLUTION 20 
#define FUZZINESS 20

uint16_t pulses[NUMPULSES][2]; 
uint8_t currentpulse = 0;


IR::IR(int pin) {
  _pin = pin;
}

boolean IR::compareSignals(int numpulses, int Signal[]) {
  
  int refsize = sizeof(Signal) / 4;
  int count = min(numpulses,refsize);
  
  for (int i=0; i< count-1; i++) {
    int oncode = pulses[i][1] * RESOLUTION / 10;
    int offcode = pulses[i+1][0] * RESOLUTION / 10;
    if ( ! (abs(oncode - Signal[i*2 + 0]) <= (Signal[i*2 + 0] * FUZZINESS / 100)) ) {  return false; }
    if ( ! (abs(offcode - Signal[i*2 + 1]) <= (Signal[i*2 + 1] * FUZZINESS / 100)) ) { return false; }
  }
  
  return true;
}


int IR::listenForSignals() {
  currentpulse = 0;
  
  for ( unsigned long start = millis(); millis() - start < 800; ) {
    uint16_t highpulse, lowpulse; 
    highpulse = lowpulse = 0;
    
    if (IRpin_PIN & (1 << _pin)) {
      
       highpulse++;
       delayMicroseconds(RESOLUTION);
       if (((highpulse >= MAXPULSE) && (currentpulse != 0))|| currentpulse == NUMPULSES) {
         return currentpulse;
       }
       
    }
    pulses[currentpulse][0] = highpulse;
    
    if (! (IRpin_PIN & _BV(_pin))) {
       lowpulse++;
       delayMicroseconds(RESOLUTION);
        if (((lowpulse >= MAXPULSE)  && (currentpulse != 0))|| currentpulse == NUMPULSES) {
         return currentpulse;
       }
    }
    
    pulses[currentpulse][1] = lowpulse;
    currentpulse++;
  }
  
}

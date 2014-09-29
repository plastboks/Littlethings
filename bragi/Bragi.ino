#include "U8glib.h"
#include "screens.h"
#include "gps.h"
#include "ir.h"
#include "ircodes.h"


U8GLIB_ST7920_128X64 u8g(9, 10, 17, U8G_PIN_NONE); 
Screens display(u8g);
GPS g(Serial);
IR ir(2);

// Hardware pins.
const int mainsPower = 8;

// Global variables
long previousMillis = 0;
long screenInterval = 1000;
short unsigned int screenNumber = 1;

void setup() {
  Serial.begin(57600);
  pinMode(mainsPower, INPUT);
}


void screenRotator(void) {
  switch(screenNumber) {
    case 0: display.speedoMeter(5, 4); break;
    case 1: display.geo(); break;
  }
}


void loop(void) {
  //unsigned long currentMillis = millis();
  
  int numberPulses; 
  numberPulses = ir.listenForSignals();
  
  if (ir.compareSignals(numberPulses, irNext)) {
    screenNumber++;
  }
  if (ir.compareSignals(numberPulses, irPrev)) {
    screenNumber--;
  }
  
  if ( screenNumber >= 2 ) {
    screenNumber = 0;
  }
  
  //if(currentMillis - previousMillis > screenInterval) {
    if (digitalRead(mainsPower) == HIGH) {
      u8g.firstPage();
      if (true) {
        do {
          display.speedoMeter(numberPulses, millis()/100);
        } while(u8g.nextPage());
      } else {
        do {
          display.noSignal();
        } while(u8g.nextPage());
      }
    }
    if (digitalRead(mainsPower) == LOW) {
      u8g.firstPage();
      do {
        display.shutdown();
      } while(u8g.nextPage());
    }
  //}
  

  
}




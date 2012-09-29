#include "U8glib.h"
#include "screens.h"
#include "gps.h"

U8GLIB_ST7920_128X64 u8g(9, 10, 17, U8G_PIN_NONE); 
Screens display(u8g);
GPS g(Serial);


// Hardware pins.
const int mainsPower = 8;

// Global variables
long previousMillis = 0;
long screenInterval = 1000;


void setup() {
  Serial.begin(57600);
  pinMode(mainsPower, INPUT);
}


void loop(void) {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > screenInterval) {
    
    if (digitalRead(mainsPower) == HIGH) {
      u8g.firstPage();
      if (true) {
        do {
          display.speedoMeter();
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
    
  }
}




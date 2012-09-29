#include "U8glib.h"
#include <TinyGPS.h>
#include <EEPROM.h>
#include <stdarg.h>
#include "ircodes.h"
#include "screens.h"
#include "eeprom.h"
#include "gps.h"
#include <SoftwareSerial.h>
#include <OBD.h>

TinyGPS gps;
U8GLIB_ST7920_128X64 u8g(9, 10, 17, U8G_PIN_NONE); 
SoftwareSerial bluetoothSerial(3, 4); // RX, TX
COBD obd;

// IR settings
#define IRpin_PIN      PIND
#define IRpin          2
#define MAXPULSE 65000
#define NUMPULSES 50
#define RESOLUTION 20 
#define FUZZINESS 20
uint16_t pulses[NUMPULSES][2]; 
uint8_t currentpulse = 0;

// Hardware pins.
const int mainsPower = 8;

// Global variables.
uint8_t draw_state = 0;
int neverHadFix = 1;
int shutdownState = 0;
long faultCounter = 50;
bool newGpsData = false;
long previousMillis = 0;
long interval = 1000;
float flat, flon, fkmph, falt, fc, avgspeed, avgspeedH;
unsigned long age, fix_age, speed;
int year, satellites, hdop, i;
byte month, day, hour, minutes, second, hundredths;
float lastLat = 0.0;
float lastLon = 0.0;
float aDriven = 0.0;
float bDriven = 0.0;
float cDriven = 0.0;
float dDriven = 0.0;
float lastBDriven, lastCDriven, lastDDriven;
static FILE lcdout = {0} ;  // LCD FILE structure
char gpsFeedString;

// LCD character writer
static int lcd_putchar(char ch, FILE* stream) {
  u8g.write(ch);
  return (0);
}


// ir compare signals 
boolean IRcompare(int numpulses, int Signal[], int refsize) {
  int count = min(numpulses,refsize);
  for (int i=0; i< count-1; i++) {
    int oncode = pulses[i][1] * RESOLUTION / 10;
    int offcode = pulses[i+1][0] * RESOLUTION / 10;
    if ( ! (abs(oncode - Signal[i*2 + 0]) <= (Signal[i*2 + 0] * FUZZINESS / 100)) ) {  return false; }
    if ( ! (abs(offcode - Signal[i*2 + 1]) <= (Signal[i*2 + 1] * FUZZINESS / 100)) ) { return false; }
  }
  return true;
}


// listen for ir signals
int listenForIR(void) {
  currentpulse = 0;
  
  for ( unsigned long start = millis(); millis() - start < 200; ) {
    uint16_t highpulse, lowpulse; 
    highpulse = lowpulse = 0;
    if (IRpin_PIN & (1 << IRpin)) {
       highpulse++;
       delayMicroseconds(RESOLUTION);
       if (((highpulse >= MAXPULSE) && (currentpulse != 0))|| currentpulse == NUMPULSES) {
         return currentpulse;
       }
    }
    pulses[currentpulse][0] = highpulse;
    if (! (IRpin_PIN & _BV(IRpin))) {
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


// scan for gps data on serial input
bool gpsGetData(void) {
  faultCounter ++;
  for (unsigned long start = millis(); millis() - start < 50;) {
    if (Serial.available()) {
      char c = Serial.read();
      if (gps.encode(c)) {
        // reset faulcounter
        faultCounter = 0;
      }
    }
  }
  if (faultCounter < 10) {
    setGpsData();
    newGpsData = true;
  } else {
    newGpsData = false;
  }
}



// main screen rotator
void drawRotator(void) {
  switch(draw_state) {
    case 0: firstGpsScreen(); break;
    case 1: secondGpsScreen(); break;
  }
}


void noSignalGpsScreen(void) {
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(10, 28, "Wait for it");
  u8g.drawStr(48, 48, "...");
}


void setup() {
  Serial.begin(57600);
  bluetoothSerial.begin(9600);
  // setup digital pins.
  pinMode(mainsPower, INPUT);
  // fill in the LCD FILE structure
  fdev_setup_stream (&lcdout, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
  readFromEEprom();
}


void loop(void) {

  unsigned long currentMillis = millis();
  //gpsGetData();
  
  if(currentMillis - previousMillis > interval) {
    if (digitalRead(mainsPower) == HIGH) {
      shutdownState = 0;
      u8g.firstPage();
      if (newGpsData) {
        do {
          drawRotator();
        } while(u8g.nextPage());
      } else {
        do {
          noSignalGpsScreen();
        } while(u8g.nextPage());
      }
    }
    if (digitalRead(mainsPower) == LOW) {
      u8g.firstPage();
      do {
        powerLostScreen();
      } while(u8g.nextPage());
    }
  }

  int numberpulses;
  numberpulses = listenForIR();
  
  if (IRcompare(numberpulses, irNext,sizeof(irQuit)/4)) {
    draw_state++;
  }
  
  if (IRcompare(numberpulses, irPrev,sizeof(irQuit)/4)) {
    draw_state--;
  }
  
  if ( draw_state >= 2 ) {
    draw_state = 0;
  }
    

}


void serialEvent() {
  while (Serial.available()) {
    int c = Serial.read(); 

    if (gps.encode(c)) {
      //gpsFeedString = NULL;
      setGpsData();
      newGpsData = true;
    }
  }
}


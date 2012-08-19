#include "U8glib.h"
#include <TinyGPS.h>
#include <EEPROM.h>
#include <stdarg.h>
#include "ircodes.h"
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


// LCD character writer
static int lcd_putchar(char ch, FILE* stream) {
  u8g.write(ch);
  return (0);
}


// eeprom write float 
void EEPROM_writeDouble(int ee, double value) {
  byte* p = (byte*)(void*)&value;
  for (int i = 0; i < sizeof(value); i++)
	  EEPROM.write(ee++, *p++);
}


// eeprom read float 
double EEPROM_readDouble(int ee) {
  double value = 0.0;
  byte* p = (byte*)(void*)&value;
  for (int i = 0; i < sizeof(value); i++)
	  *p++ = EEPROM.read(ee++);
  return value;
} 


// read from eeprom 
void readFromEEprom(void) {
  bDriven = EEPROM_readDouble(10);
  cDriven = EEPROM_readDouble(20);
  dDriven = EEPROM_readDouble(30); 
}


// save to eeprom
void saveToEEprom(void) {
  EEPROM_writeDouble(10, bDriven);
  EEPROM_writeDouble(20, cDriven);
  EEPROM_writeDouble(30, dDriven);
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


// average Speed calculate 
void averageSpeed(void) {
  i++;
  avgspeedH = fkmph + avgspeedH;
  avgspeed = avgspeedH / i;
}


// odomoter 
void odoMeter(void) {
  if (neverHadFix == 1) { lastLat = flat; lastLon = flon; }
  if (fkmph > 1.0) { aDriven = aDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
  if (fkmph > 1.0) { bDriven = bDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
  if (fkmph > 1.0) { cDriven = cDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
  if (fkmph > 1.0) { dDriven = cDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
  lastLat = flat;
  lastLon = flon;
  lastBDriven = bDriven;
  lastCDriven = cDriven;
  lastDDriven = dDriven;
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


// setGpsData to variables
void setGpsData(void) {
  gps.f_get_position(&flat, &flon, &age);
  fkmph = gps.f_speed_kmph();
  falt = gps.f_altitude();
  fc = gps.f_course();
  const char *cardinal = gps.cardinal(fc);
  satellites = gps.satellites();
  hdop = gps.hdop();    
  gps.crack_datetime(&year, &month, &day, &hour, &minutes, &second, &hundredths, &fix_age);
  odoMeter();
  averageSpeed();
}


// main screen rotator
void drawRotator(void) {
  switch(draw_state) {
    case 0: firstGpsScreen(); break;
    case 1: secondGpsScreen(); break;
  }
}


void powerLostScreen(void) {
  if (shutdownState == 0) {
    saveToEEprom();
    shutdownState = 1;
    u8g.setFont(u8g_font_10x20);
    u8g.drawStr(10, 28, "Writing");
    u8g.drawStr(48, 48, "...");
  } else {
    u8g.setFont(u8g_font_10x20);
    u8g.drawStr(10, 28, "Shutdown");
    u8g.drawStr(48, 48, "...");
  }
}


void noSignalGpsScreen(void) {
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(10, 28, "Wait for it");
  u8g.drawStr(48, 48, "...");
}


void firstGpsScreen(void) {
    
  int timeZone = hour + 2;
  if (timeZone == 24) { timeZone = 0; }
  if (timeZone == 25) { timeZone = 1; }

  u8g.drawLine(0, 8, 128, 8);
  u8g.drawLine(0, 44, 128, 44);
  
  u8g.setFont(u8g_font_6x12);
  u8g.setPrintPos(4, 7);
  fprintf(&lcdout, "%d-%02d-%02d    %02d:%02d", year, month, day, timeZone, minutes);

  u8g.setFont(u8g_font_10x20);
  u8g.setPrintPos(6, 28);
  u8g.print(fkmph, 1);
  u8g.setPrintPos(58, 28);
  u8g.print("/");
  u8g.setPrintPos(70, 28);
  u8g.print(avgspeed, 1);

  u8g.setFont(u8g_font_6x12);
  
  u8g.setPrintPos(24, 43);
  u8g.print("Odometer (km)");
  
  u8g.setPrintPos(4, 54);
  u8g.print("A: ");
  u8g.setPrintPos(16, 54);
  u8g.print(aDriven/1000, 1);

  u8g.setPrintPos(4, 64);
  u8g.print("B: ");
  u8g.setPrintPos(16, 64);
  u8g.print(bDriven/1000, 1);

  u8g.setPrintPos(64, 54);
  u8g.print("C: ");
  u8g.setPrintPos(76, 54);
  u8g.print(cDriven/1000, 1);
  
  u8g.setPrintPos(64, 64);
  u8g.print("D: ");  
  u8g.setPrintPos(76, 64);
  u8g.print(dDriven/1000, 1);
  
  neverHadFix = 0;
}


void secondGpsScreen(void) {
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(4, 16, "LAT");
  u8g.setPrintPos(38, 16);
  u8g.print(flat, 5);
  u8g.drawStr(4, 32, "LON");
  u8g.setPrintPos(38, 32);
  u8g.print(flon, 5);
  
  u8g.setFont(u8g_font_6x12);
  u8g.drawStr(4, 46, "ALT");
  u8g.setPrintPos(24, 46);
  u8g.print(falt, 1);
  u8g.drawStr(64, 46, "COUR");
  u8g.setPrintPos(90, 46);
  u8g.print(fc, 1);

  u8g.drawStr(4, 60, "SAT");
  u8g.setPrintPos(24, 60);
  u8g.print(satellites);
  u8g.drawStr(64, 60, "HDOP");
  u8g.setPrintPos(90, 60);
  u8g.print(hdop);
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
  gpsGetData();
  
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

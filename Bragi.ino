#include "U8glib.h"
#include <TinyGPS.h>
#include <EEPROM.h>
#include <stdarg.h>

TinyGPS gps;
U8GLIB_ST7920_128X64 u8g(9, 8, 17, U8G_PIN_NONE); 

// Hardware pins.
const int ledPin = 13;
const int buttonPin = 5;

// Global variables.
int neverHadFix = 1;
long faultCounter = 50;
bool newData = false;
long previousMillis = 0;
long interval = 500;
int switchTemplate = EEPROM.read(1);
float flat, flon, fkmph, falt, fc;
unsigned long age, fix_age, speed;
int year, satellites, hdop;
byte month, day, hour, minutes, second, hundredths;
float lastLat = 0.0;
float lastLon = 0.0;
float aDriven = 0.0;
double bDriven, lastBDriven;
static FILE lcdout = {0} ;  // LCD FILE structure

// LCD character writer
static int lcd_putchar(char ch, FILE* stream) {
  u8g.write(ch);
  return (0);
}

void EEPROM_writeDouble(int ee, double value) {
  byte* p = (byte*)(void*)&value;
  for (int i = 0; i < sizeof(value); i++)
	  EEPROM.write(ee++, *p++);
}

double EEPROM_readDouble(int ee) {
  double value = 0.0;
  byte* p = (byte*)(void*)&value;
  for (int i = 0; i < sizeof(value); i++)
	  *p++ = EEPROM.read(ee++);
  return value;
} 


bool gpsGetData(void) {
  faultCounter ++;
  for (unsigned long start = millis(); millis() - start < 500;) {
    while (Serial.available()) {
      if (gps.encode(Serial.read()))
        faultCounter = 0;
    }
  }
  if (faultCounter < 2) {
    gps.f_get_position(&flat, &flon, &age);
    fkmph = gps.f_speed_kmph();
    falt = gps.f_altitude();
    fc = gps.f_course();
    const char *cardinal = gps.cardinal(fc);
    satellites = gps.satellites();
    hdop = gps.hdop();    
    gps.crack_datetime(&year, &month, &day, &hour, &minutes, &second, &hundredths, &fix_age);
    return true;
  } else {
    return false; 
  }
}


void noSignalGpsScreen(void) {
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(10, 32, "Wait for it");
}


void firstGpsScreen(void) {
    
  if (neverHadFix == 1) { lastLat = flat; lastLon = flon; }
  if (fkmph > 1.0) { aDriven = aDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
  if (fkmph > 1.0) { bDriven = bDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
  if (bDriven/1000 > lastBDriven/1000) { EEPROM_writeDouble(0, bDriven/1000); }

  
  int timeZone = hour + 2;
  if (timeZone == 24) { timeZone = 0; }
  if (timeZone == 25) { timeZone = 1; }
  lastLat = flat;
  lastLon = flon;
  lastBDriven = bDriven;   


  u8g.drawLine(0, 8, 128, 8);
  u8g.drawLine(0, 54, 128, 54);
  u8g.drawLine(64, 56, 64, 64);
  
  u8g.setFont(u8g_font_6x12);
  u8g.setPrintPos(4, 7);
  fprintf(&lcdout, "%d-%02d-%02d  %02d:%02d:%02d", year, month, day, timeZone, minutes, second);

  u8g.setFont(u8g_font_10x20);
  u8g.setPrintPos(32, 28);
  u8g.print(fkmph, 1);
  u8g.setFont(u8g_font_6x12);
  u8g.setPrintPos(96, 28);
  u8g.print("km/h");

  u8g.setFont(u8g_font_6x12);
  u8g.setPrintPos(12, 42);
  u8g.print("A: ");
  u8g.setPrintPos(26, 42);
  u8g.print(aDriven/1000, 1);
  u8g.setPrintPos(70, 42);
  u8g.print("km");

  u8g.setPrintPos(12, 52);
  u8g.print("B: ");
  u8g.setPrintPos(26, 52);
  u8g.print(bDriven/1000, 1);
  u8g.setPrintPos(70, 52);
  u8g.print("km");
  
  u8g.setFont(u8g_font_6x12);
  u8g.setPrintPos(8, 64);
  u8g.print(falt, 1);
  u8g.setPrintPos(48, 64);
  u8g.print("m");
  u8g.setPrintPos(80, 64);
  u8g.print(fc, 1);
  u8g.setFont(u8g_font_5x7);
  u8g.setPrintPos(112, 60);
  u8g.print("o");
  
  
  neverHadFix = 0;

}


void secondGpsScreen(void) {
    u8g.setFont(u8g_font_6x12);
    u8g.drawStr( 0, 6, "LA");
    u8g.setPrintPos(14, 6);
    u8g.print(flat, 6);
    u8g.drawStr( 66, 6, "LO");
    u8g.setPrintPos(80, 6);
    u8g.print(flon, 6);
}


void setup() {
  bDriven = EEPROM_readDouble(0);
  Serial.begin(57600); 
  // setup digital pins.
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  // fill in the LCD FILE structure
  fdev_setup_stream (&lcdout, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
}


void loop(void) {
  
  
  u8g.firstPage();
  if (gpsGetData()) {
    do {
      firstGpsScreen();
    } while(u8g.nextPage());
  } else {
    do {
      noSignalGpsScreen();
    } while(u8g.nextPage());
  }
}

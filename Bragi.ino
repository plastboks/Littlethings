#include "U8glib.h"
#include <TinyGPS.h>
#include <EEPROM.h>
#include <stdarg.h>

TinyGPS gps;
U8GLIB_ST7920_128X64 u8g(9, 10, 17, U8G_PIN_NONE); 

// Hardware pins.
const int mainsPower = 8;

// Global variables.
uint8_t draw_state = 0;
int neverHadFix = 1;
int shutdownState = 0;
long faultCounter = 50;
bool newData = false;
long previousMillis = 0;
long interval = 500;
float flat, flon, fkmph, falt, fc, avgspeed, avgspeedH;
unsigned long age, fix_age, speed;
int year, satellites, hdop, i;
byte month, day, hour, minutes, second, hundredths;
float lastLat = 0.0;
float lastLon = 0.0;
float aDriven = 0.0;
float bDriven = 0.0;
float lastBDriven;
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


void averageSpeed(void) {
  i++;
  avgspeedH = fkmph + avgspeedH;
  avgspeed = avgspeedH / i;
}


void odoMeter(void) {
  if (neverHadFix == 1) { lastLat = flat; lastLon = flon; }
  if (fkmph > 1.0) { aDriven = aDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
  if (fkmph > 1.0) { bDriven = bDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
  lastLat = flat;
  lastLon = flon;
  lastBDriven = bDriven;   
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
    odoMeter();
    averageSpeed();
    return true;
  } else {
    return false; 
  }
}


void drawRotator(void) {
  switch(draw_state >> 7) {
    case 0: firstGpsScreen(); break;
    case 1: secondGpsScreen(); break;
  }
}


void powerLostScreen(void) {
  if (shutdownState == 0) {
    EEPROM_writeDouble(10, bDriven);
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
  //u8g.drawLine(0, 54, 128, 54);
  
  u8g.setFont(u8g_font_6x12);
  u8g.setPrintPos(4, 7);
  fprintf(&lcdout, "%d-%02d-%02d  %02d:%02d:%02d", year, month, day, timeZone, minutes, second);

  u8g.setFont(u8g_font_10x20);
  u8g.setPrintPos(6, 28);
  u8g.print(fkmph, 1);
  u8g.setPrintPos(58, 28);
  u8g.print("/");
  u8g.setPrintPos(70, 28);
  u8g.print(avgspeed, 1);

  u8g.setFont(u8g_font_6x12);
  u8g.setPrintPos(4, 54);
  u8g.print("A: ");
  u8g.setPrintPos(18, 54);
  u8g.print(aDriven/1000, 1);

  u8g.setPrintPos(4, 64);
  u8g.print("B: ");
  u8g.setPrintPos(18, 64);
  u8g.print(bDriven/1000, 1);

  u8g.setPrintPos(64, 54);
  u8g.print("C: ");
  
  u8g.setPrintPos(64, 64);
  u8g.print("D: ");  
  
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
  // setup digital pins.
  pinMode(mainsPower, INPUT);
  // fill in the LCD FILE structure
  fdev_setup_stream (&lcdout, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
  bDriven = EEPROM_readDouble(10);
}


void loop(void) {
  if (digitalRead(mainsPower) == HIGH) {
    shutdownState = 0;
    u8g.firstPage();
    if (gpsGetData()) {
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
  
  draw_state++;
  if ( draw_state >= 32*8 ) {
    draw_state = 0;
  }
  
  delay(50);

}

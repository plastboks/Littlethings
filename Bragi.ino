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
float bDriven = 0.0;
static FILE lcdout = {0} ;  // LCD FILE structure

// LCD character writer
static int lcd_putchar(char ch, FILE* stream) {
  u8g.write(ch) ;
  return (0) ;
}

void setup() {
  Serial.begin(57600); 
  // setup digital pins.
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  // fill in the LCD FILE structure
  fdev_setup_stream (&lcdout, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
}


bool gpsGetData(void) {
  faultCounter ++;
  for (unsigned long start = millis(); millis() - start < 500;) {
    while (Serial.available()) {
      if (gps.encode(Serial.read()))
        faultCounter = 0;
    }
  }
  if (faultCounter < 50) {
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
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(4, 22, "Wait for it...");
}


void firstGpsScreen(void) {
  
    //if (neverHadFix == 1) { lastLat = flat; lastLon = flon; }
    //if (fkmph > 1.0) { aDriven = aDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
    u8g.setFont(u8g_font_5x7);
    u8g.drawStr( 0, 6, "LA");
    u8g.setPrintPos(14, 6);
    u8g.print(flat, 6);
    u8g.drawStr( 66, 6, "LO");
    u8g.setPrintPos(80, 6);
    u8g.print(flon, 6);

    u8g.drawLine(0, 8, 128, 8);

    u8g.drawLine(40, 8, 40, 56);
    
    u8g.setFont(u8g_font_5x7);
    u8g.setPrintPos(0, 18);
    u8g.print("Alt:");
    u8g.setPrintPos(0, 28);
    u8g.print(falt);
    u8g.drawLine(0, 30, 40, 30);
    u8g.setPrintPos(0, 40);
    u8g.print("Course:");
    u8g.setPrintPos(0, 50);
    u8g.print(fc);

    u8g.setFont(u8g_font_10x20);
    u8g.setPrintPos(48, 28);
    u8g.print(fkmph, 1);
    u8g.setFont(u8g_font_6x12);
    u8g.setPrintPos(104, 28);
    u8g.print("km/h");
  
    u8g.setFont(u8g_font_5x7);
    u8g.setPrintPos(44, 52);
    //fprintf(&lcdout, "A: %dkm | B: %dkm", aDriven/1000, bDriven);
    
    u8g.drawLine(0, 56, 128, 56);
    u8g.setFont(u8g_font_5x7);
    u8g.setPrintPos(14, 64);
    fprintf(&lcdout, "%d-%02d-%02d  %02d:%02d:%02d", year, month, day, hour, minutes, second);
}


// program loop
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

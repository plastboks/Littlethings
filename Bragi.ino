#include "U8glib.h"
#include <TinyGPS.h>
#include <EEPROM.h>

TinyGPS gps;
U8GLIB_ST7920_128X64 u8g(9, 8, 17, U8G_PIN_NONE); 


long faultCounter = 50;
bool newData = false;


void gpsData(void) {
  
  float flat, flon;
  unsigned long age, fix_age, speed;
  int year;
  byte month, day, hour, minutes, second, hundredths;
  
  
  // check the serialdata 10 times.
  for (unsigned long start = millis(); millis() - start < 10;) {
    if (Serial.available()) {
      char c = Serial.read();
      if (gps.encode(c)) {
        // deactivate faulcounter
        faultCounter = 0;
      }
    }
  }
  
  // check if faultcounter has exceeded 50 turns.
  if (faultCounter < 50) {
     newData = true;
  } else {
     newData = false; 
  }
  
  if (newData) {
    gps.f_get_position(&flat, &flon, &age);
    float fkmph = gps.f_speed_kmph();
    float falt = gps.f_altitude();
    float fc = gps.f_course();
    const char *cardinal = gps.cardinal(fc);
    int satellites = gps.satellites();
    int hdop = gps.hdop();    
    gps.crack_datetime(&year, &month, &day, &hour, &minutes, &second, &hundredths, &fix_age);
    if (month < 10) { month = printf("%02u", month); }
    
    // graphic commands to redraw the complete screen should be placed here  
    u8g.setFont(u8g_font_8x13);
    //u8g.setFont(u8g_font_osb21);
    u8g.drawStr( 0, 9, "LAT");
    u8g.setPrintPos(55, 9);
    u8g.print(flat, 6);
  
    u8g.drawStr( 0, 20, "LON");
    u8g.setPrintPos(55, 20);
    u8g.print(flon, 6);
  
    u8g.drawStr( 0, 31, "ALT");
    u8g.setPrintPos(55, 31);
    u8g.print(falt, 1);
    u8g.setPrintPos(100, 31);
    u8g.print("m");
  
    u8g.drawStr( 0, 42, "SPEED");
    u8g.setPrintPos(55, 42);
    u8g.print(fkmph, 1);

    u8g.drawStr( 0, 53, "COURSE");
    u8g.setPrintPos(55, 53);
    u8g.print(fc, 0);
    
    //this is a ugly one...
    u8g.setFont(u8g_font_6x12);
    u8g.drawStr(0, 64, "DATE");
    u8g.setPrintPos(30, 64);
    u8g.print(year);
    u8g.setPrintPos(54, 64);
    u8g.print("-");
    u8g.setPrintPos(60,64);
    u8g.print(month);
    
    
  } else {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(4, 22, "Wait for it...");
  }

}

void setup(void) {
  // set serial speeds.
  Serial.begin(57600); 
}

void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    gpsData();
  } while( u8g.nextPage() );
  
  delay(250);
}


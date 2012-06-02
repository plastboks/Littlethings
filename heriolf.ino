#include <LiquidCrystal.h>
#include <TinyGPS.h>
#include <EEPROM.h>

TinyGPS gps;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// the hardware pins.
const int ledPin = 13;
const int lcdLightPin = 6;
const int buttonPin = 5;

// global variables.
float i = 0.0;
int buttonState = 0;
long faultCounter = 50;
long previousMillis = 0;
long interval = 500;
bool newData = false;
int switchTemplate = EEPROM.read(1);
float droven = 0.0;
float lastLat = 0.0;
float lastLon = 0.0;


void setup() {
  // set serial speeds.
  Serial.begin(57600);  
  // setup lcd display.
  lcd.begin(16,2);
  // setup digital pins.
  pinMode(ledPin, OUTPUT);
  pinMode(lcdLightPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}


void loop() {
  
  // activate lcd light.
  digitalWrite(lcdLightPin, HIGH);
  // reset faultCounter.
  faultCounter ++;
  
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
  
  // to this twice pr second.
  unsigned long currentMillis = millis();
  if (millis() - previousMillis > interval) {
    previousMillis = currentMillis;
    
    if (newData) {
      if (i > 0) {
        lcd.clear();
      }
      i = 0;
      float flat, flon;
      unsigned long age, fix_age, speed;
      int year;
      byte month, day, hour, minutes, second, hundredths;
  
      // get gps data.
      gps.f_get_position(&flat, &flon, &age);
      float fkmph = gps.f_speed_kmph();
      float falt = gps.f_altitude();
      float fc = gps.f_course();
      const char *cardinal = gps.cardinal(fc);
      int satellites = gps.satellites();
      int hdop = gps.hdop();    
      gps.crack_datetime(&year, &month, &day, &hour, &minutes, &second, &hundredths, &fix_age);
      droven = droven + gps.distance_between(flat, flon, lastLat, lastLon);
      lastLat = flat;
      lastLon = flon;
      
      // switch between templates.
      switch (switchTemplate) {
        case 1:
          lcd.setCursor(0, 0);
          lcd.print("LAT ");
          lcd.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
          lcd.setCursor(0, 1);
          lcd.print("LON ");
          lcd.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
          break;
        case 2:
          lcd.setCursor(0, 0);
          lcd.print("SPEED ");
          lcd.print(fkmph);
          lcd.print("km/h");
          lcd.setCursor(0, 1);
          lcd.print("ALT ");
          lcd.print(falt);
          lcd.print("m");
          break;
        case 3:
          lcd.setCursor(0, 0);
          lcd.print("CARDINAL ");
          lcd.print(cardinal);
          lcd.setCursor(0, 1);
          lcd.print("COURSE ");
          lcd.print(fc);
          lcd.print((char)223);
          break;
        case 4:
          lcd.setCursor(0, 0);
          lcd.print("DATE ");
          lcd.print(year);
          lcd.print("-");
          lcd.print(month);
          lcd.print("-");
          lcd.print(day);
          lcd.setCursor(0, 1);
          lcd.print("TIME ");
          // set timezone.
          hour = hour +2;
          // check if hour exeeds 23.
          if (hour == 24) { hour = 0; }
          if (hour == 25) { hour = 1; }
          // prefix with zero if time is under 10.
          if (hour < 10 ) {
            lcd.print("0");
            lcd.print(hour);
          } else {
            lcd.print(hour); 
          }
          lcd.print(":");
          // prefix with zero if time is under 10.
          if (minutes < 10) { 
            lcd.print("0");
            lcd.print(minutes);
          } else {
            lcd.print(minutes);
          } 
          break;
        case 5:
          lcd.setCursor(0, 0);
          lcd.print("SATELLITES ");
          lcd.print(satellites);
          lcd.setCursor(0, 1);
          lcd.print("HDOP ");
          lcd.print(hdop);
          break;
        case 6:
          lcd.setCursor(0, 0);
          lcd.print("DROVEN ");
          lcd.print(droven);
          lcd.setCursor(0, 1);
          break;
      }
    } else {
      if (i == 0) {
        // clear display upon "wait for it" change.
        lcd.clear(); 
      }
      lcd.setCursor(0,0);
      lcd.print("Wait for it...");
      lcd.setCursor(0,1);
      lcd.print(i);
      i = i + 0.5;
    }
  }
  
  // a bit messy... this to prevent the buttonState incrementing more than one time.
  if (digitalRead(buttonPin) == LOW) {
     buttonState = 0; 
  }
  // increment template switcher.
  if (digitalRead(buttonPin) == HIGH) {
    buttonState ++;
    if (buttonState == 1) {
      switchTemplate ++;
      EEPROM.write(1, switchTemplate);
      lcd.clear();
    }
    // clear display upon template change.
    if (switchTemplate > 6) {
      switchTemplate = 1;
      EEPROM.write(1, switchTemplate);
    }
  }
  
} // this ends the loop function.



#include <LiquidCrystal.h>
#include <TinyGPS.h>

TinyGPS gps;
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const int ledPin = 13;
const int lcdLightPin = 6;
const int buttonPin = 5;

float i = 0.0;
int switchTemplate = 1;
int templateTurn = 0;

void setup() {
  // set serial speeds.
  Serial.begin(57600);
  // setup lcd display.
  lcd.begin(16,2);
  // setup digital pins
  pinMode(ledPin, OUTPUT);
  pinMode(lcdLightPin, OUTPUT);
  pinMode(buttonPin, INPUT);

}

void loop() {
  
  // activate lcd light.
  digitalWrite(lcdLightPin, HIGH);
  
  // set some variables
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  
  // for half a second we parse GPS data and report some key values.
  for (unsigned long start = millis(); millis() - start < 500;) {
    while (Serial.available()) {
      char c = Serial.read(); //we need to use the hardware serial for now.
      //Serial.write(c); // uncomment this line if you want to see the GPS data flowing.
      if (gps.encode(c)) { // Did a new valid sentence come in?
        newData = true;
      }
    }
  }
  
  if (newData) {
    if ( i > 0) {
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
    //char cardinal = gps.cardinal();
    int satellites = gps.satellites();
    int hdop = gps.hdop();    
    gps.crack_datetime(&year, &month, &day, &hour, &minutes, &second, &hundredths, &fix_age);
    flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6;
    flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6;
    
    // switch between templates.
    switch (switchTemplate) {
      case 1:
        lcdTemplate0("LAT: ", flat, "", "LON: ", flon, "");
        break;
      case 2:
        lcdTemplate0("SPEED: ", fkmph, "km/h", "CARDINAL: ", 0.0, "");
        break;
      case 3:
        lcdTemplate0("ALT: ", falt, "m", "COURSE: ", fc, "");
        break;
      case 4:
        lcd.setCursor(0, 0);
        lcd.print("DATE: ");
        lcd.print(year);
        lcd.print("-");
        lcd.print(month);
        lcd.print("-");
        lcd.print(day);
        lcd.setCursor(0, 1);
        lcd.print("TIME: ");
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
        lcdTemplate1("SATELLITES: ", satellites, "", "HDOP: ", hdop, "");
        break;
    }
    // increment template switcher.
    if (digitalRead(buttonPin) == HIGH) {
      switchTemplate ++;
      // clear display upon template change.
      lcd.clear();
      if (switchTemplate > 5) {
        switchTemplate = 1;
      }
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

void lcdTemplate0(char* prefix0, float value0, char* subfix0, char* prefix1, float value1, char* subfix1) {
  lcd.setCursor(0, 0);
  lcd.print(prefix0);
  lcd.print(value0);
  lcd.print(subfix0);
  lcd.setCursor(0, 1);
  lcd.print(prefix1);
  lcd.print(value1);
  lcd.print(subfix1);
}

void lcdTemplate1(char* prefix0, int value0, char* subfix0, char* prefix1, int value1, char* subfix1) {
  lcd.setCursor(0, 0);
  lcd.print(prefix0);
  lcd.print(value0);
  lcd.print(subfix0);
  lcd.setCursor(0, 1);
  lcd.print(prefix1);
  lcd.print(value1);
  lcd.print(subfix1);
}


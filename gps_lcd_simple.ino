#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(3, 4);
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup()
{
  // set serial speeds.
  Serial.begin(57600);
  ss.begin(57600);
  // setup lcd display.
  lcd.begin(16,2);
  // setup pin 6 for lcd light.
  pinMode(6, OUTPUT);
  
}

float i = 0.0;
int switchTemplate = 1;
int templateTurn = 0;

void loop() {
  // activate lcd light.
  digitalWrite(6, HIGH);
  
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // for one second we parse GPS data and report some key values.
  for (unsigned long start = millis(); millis() - start < 500;) {
    while (ss.available()) {
      char c = ss.read();
      //Serial.write(c); // uncomment this line if you want to see the GPS data flowing.
      if (gps.encode(c)) { // Did a new valid sentence come in?
        newData = true;
      }
    }
  }

  if (newData) {
    i = 0;
    float flat, flon;
    unsigned long age;
    int year;
    byte month, day, hour, minutes, second, hundredths;
    unsigned long fix_age, speed;
    // get gps data.
    gps.f_get_position(&flat, &flon, &age);
    speed = gps.speed();
    int alt = gps.f_altitude();
    float fc = gps.f_course();
    gps.crack_datetime(&year, &month, &day, &hour, &minutes, &second, &hundredths, &fix_age);

    // print to serial interface.
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    // switch between templates.
    switch (switchTemplate) {
      case 1:
        lcd.setCursor(0, 0);
        lcd.print("LAT: ");
        lcd.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
        lcd.setCursor(0, 1);
        lcd.print("LON: ");
        lcd.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
        break;
      case 2:
        lcd.setCursor(0, 0);
        lcd.print("ALT: ");
        lcd.print(alt);
        lcd.print("m");
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
    }
    // increment template switcher.
    templateTurn ++;
    // set interval time.
    if (templateTurn > 40) {
      switchTemplate ++;
      // clear display upon template change.
      lcd.clear();
      if (switchTemplate > 2) {
        switchTemplate = 1;
      }
      templateTurn = 0; 
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

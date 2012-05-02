#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(3, 4);
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup()
{
  Serial.begin(57600);
  ss.begin(57600);
  
  lcd.begin(16,2);
  pinMode(6, OUTPUT);
}
float count = 0.0;

void loop() {
  
  digitalWrite(6, HIGH);
  
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 500;) {
    while (ss.available()) {
      char c = ss.read();
      //Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) { // Did a new valid sentence come in?
        newData = true;
        count = 0.0;
      } else {
        count += 0.5; 
      }
    }
  }

  if (newData) {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    lcd.setCursor(0, 0);
    lcd.print("LAT: ");
    lcd.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    lcd.setCursor(0, 1);
    lcd.print("LON: ");
    lcd.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  } else {
    lcd.setCursor(0,0);
    lcd.print("Wait for it...");
    lcd.setCursor(0,1);
    lcd.print(count);
  }


}

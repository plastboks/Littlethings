#include <UTFT.h>
#include <avr/pgmspace.h>

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

UTFT lcd(ITDB32WD,38,39,40,41);

extern unsigned int TLtwitter[1024];
extern unsigned int TRtwitter[1024];
extern unsigned int BLtwitter[1024];
extern unsigned int BRtwitter[1024];



String inputString = "";
boolean stringComplete = false;
int line = 2;
boolean byLine = false;

void setup() {
  lcd.InitLCD(LANDSCAPE);
  lcd.setFont(BigFont);
  Serial.begin(57600);
}


void LCDclearScreen() {
  line = 2;
  lcd.clrScr();
}

void LCDsplash() {
  lcd.setFont(BigFont);
  lcd.print("Twitter Display", 70, 100);
  
  //lcd.drawBitmap (50, 50, 32, 32, TLtwitter);
  //lcd.drawBitmap (50, 100, 32, 32, TRtwitter);
  //lcd.drawBitmap (100, 50, 32, 32, BLtwitter);
  //lcd.drawBitmap (100, 100, 32, 32, BRtwitter);
  
  lcd.setFont(SmallFont);
  lcd.print("Version: 0.0.1 Alpha", 200, 200);
}


void LCDmainPage(String string) {
  lcd.setFont(BigFont);
  lcd.print(string, 4, line);
  
  line += 20;
  if (line > 200) {
    LCDclearScreen();
  }
}

/*
void LCDbyLine(String string) {
  lcd.cursor(4, 128);
  lcd.println(string);
}
*/

void loop() {
  if (millis() / 1000 < 2) {
    LCDsplash();
  }
  if (stringComplete) {
    LCDmainPage(inputString);
    inputString = "";
    stringComplete = false;
  }
  /*if (byLine) {
    LCDbyLine(inputString);
    inputString = "";
    byLine = false;
  }*/

}


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read(); 
    
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      inputString += inChar;
    }
    
    if (inputString == "TweenoLCD::CLEAR") {
      inputString = "";
      LCDclearScreen();
    }
    if (inputString == "TweenoLCD::BYLINE") {
      inputString = "";
      byLine = true;
    }
    if (inputString == "TweenoLCD::END") {
      inputString = "";
    }

  }
}


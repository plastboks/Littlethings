#include <GLCDI2C.h>
#include <Wire.h>

#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

int blueLED = 9;
int greenLED = 10;
int redLED = 11;

unsigned int maxX = 160;  // LCD x-resolution
unsigned int maxY = 128;  // LCD y-resolution
unsigned char i2cAddress = 0x46;  // LCD module I2C address

unsigned int line = 2;
String inputString = "";
boolean stringComplete = false;
boolean byLine = false;

GLCDI2C lcd = GLCDI2C(maxX, maxY, i2cAddress);

void setup() {
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  analogWrite(blueLED, 255);
  analogWrite(greenLED, 255);
  analogWrite(redLED, 255);
  Serial.begin(57600);
  delay(500);
  Wire.begin();  
  lcd.init();
}

void LEDon() {
  for ( int fadeValue = 255 ; fadeValue >= 200; fadeValue -=1 ) {
    analogWrite(blueLED, fadeValue);
    delay(15);
  }
}

void LEDoff() {
  for ( int fadeValue = 200 ; fadeValue <= 255; fadeValue +=1 ) {
    analogWrite(blueLED, fadeValue);
    delay(15);
  }
}

void LCDclearScreen() {
  line = 2;
  lcd.setColor(BLACK);
  lcd.clear();
}

void LCDsplash() {
  lcd.setColor(BLACK);
  lcd.fontType(FONT_MEDIUM);
  lcd.setColor(WHITE);
  lcd.cursor(15, 20);
  lcd.print("Twitter Display");
   
  lcd.fontType(FONT_SMALL);
  lcd.cursor(20, 100);
  lcd.print("Version: 0.0.4 Alpha");
}


void LCDmainPage(String string) {
  lcd.setColor(BLACK);
  lcd.fontType(FONT_SMALL);
  lcd.setColor(WHITE);
  lcd.fontType(FONT_SMALL);
  lcd.cursor(4, line);
  lcd.println(string);
  
  line += 12;
  if (line > 128) {
    LCDclearScreen();
  }
}

void LCDbyLine(String string) {
  lcd.cursor(4, 128);
  lcd.println(string);
}

void loop() {
  if (millis() / 1000 < 2) {
    LCDsplash();
  }
  if (stringComplete) {
    LCDmainPage(inputString);
    inputString = "";
    stringComplete = false;
  }
  if (byLine) {
    LCDbyLine(inputString);
    inputString = "";
    byLine = false;
  }
  delay(50);
}


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read(); 
    inputString += inChar;

    if (inputString == "TweenoLCD::CLEAR") {
      inputString = "";
      LEDon();
      LCDclearScreen();
    }
    if (inputString == "TweenoLCD::BYLINE") {
      inputString = "";
      byLine = true;
    }
    if (inputString == "TweenoLCD::END") {
      inputString = "";
      LEDoff();
    }
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}



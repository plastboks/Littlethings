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

unsigned int maxX = 160;  // LCD x-resolution
unsigned int maxY = 128;  // LCD y-resolution
unsigned char i2cAddress = 0x46;  // LCD module I2C address

unsigned int line = 2;
String inputString = "";
boolean stringComplete = false;

GLCDI2C lcd = GLCDI2C(maxX, maxY, i2cAddress);

void setup() {
  Serial.begin(9600);
  delay(500);
  Wire.begin();  
  lcd.init();
}

void clearScreen() {
  line = 2;
  lcd.setColor(BLACK);
  lcd.clear();
}


void splash() {
  lcd.setColor(BLACK);
  lcd.fontType(FONT_MEDIUM);
  lcd.setColor(WHITE);
  lcd.cursor(15, 20);
  lcd.print("Twitter Display");
   
  lcd.fontType(FONT_SMALL);
  lcd.cursor(20, 100);
  lcd.print("Version: 0.0.2 Alpha");
}


void mainPage(String string) {

  lcd.setColor(BLACK);
  lcd.fontType(FONT_SMALL);
  lcd.setColor(WHITE);
  lcd.fontType(FONT_SMALL);
  lcd.cursor(4, line);
  lcd.println(string);
  
  line += 12;
  if (line > 112) {
    clearScreen();
  }
  
}

void loop() {
  if (millis() / 1000 < 2) {
    splash();
  }
  if (stringComplete) {
    mainPage(inputString);
    inputString = "";
    stringComplete = false;
  }
  delay(50);
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inputString == "TweenoLCD:CLEAR") {
      inputString = "";
      clearScreen();
    }
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}



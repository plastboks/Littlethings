#include <GLCDI2C.h>
#include <Wire.h>

// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

#define DEMODELAY       1000

#define VERSION         0001

unsigned int maxX = 160;  // LCD x-resolution
unsigned int maxY = 128;  // LCD y-resolution
unsigned char i2cAddress = 0x46;  // LCD module I2C address
unsigned int counter;
unsigned int tmp;

GLCDI2C lcd = GLCDI2C(maxX, maxY, i2cAddress);


void setup() {  
  delay(500);
  Wire.begin();  
  lcd.init();
}

void splash() {
   lcd.setColor(BLACK);
   lcd.fontType(FONT_MEDIUM);
   lcd.setColor(WHITE);
   lcd.cursor(15, 20);
   lcd.print("Twitter Display");
   
   lcd.fontType(FONT_SMALL);
   lcd.cursor(20, 100);
   lcd.print("Version: 0.0.1 Alpha");
}

void loop() {
  
   splash();
   delay(50);

}



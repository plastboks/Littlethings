// IMAGE TRANSFER TEST

#include <UTFT.h>
#include <avr/pgmspace.h>


prog_uint16_t image[256] = {};

unsigned int count = 0;
boolean dataReceive = false;
boolean imageReady = false;
String inputString = ""; 

UTFT myGLCD(ITDB32WD,38,39,40,41);


void setup() {
  myGLCD.InitLCD(LANDSCAPE);
  Serial.begin(57600);
  Serial.flush();
}


void loop() {
  
  if (imageReady) {
    myGLCD.drawBitmap (20, 20, 16, 16, image);
  }

}


void serialEvent() {
  while (Serial.available()) {
  
    char inChar = Serial.read();
    if (inChar == '\n') {
      inputString = "";
    } else {
      inputString += inChar;
    }
    
    if (dataReceive) {
      image[count] = inputString;
      count++;
      Serial.print(inputString, BIN);
      Serial.print('\n');
      
      if (count >= 255) {
        Serial.println("dataReceive is now false");
        inputString = "";
        dataReceive = false;
        imageReady = true;     
      }
      
    } else if (inInt == '1') {
      Serial.println("Start received");
      inputString = "";
      dataReceive = true;
      
    }

  }
}

/* 
  
  Proof of concept of TSTP. A 400x240 display will be used to simplefy testing.

  @description: Tweeno small transport protocol is a simple and 
                stupid protocol for communication between Arduino and python.
                The reason for this protocol is for simplefy datatransmission.

  @date: 2012-10-09

  @filename: TSTP_demo.ino
  
  @author: Alexander Skjolden

*/

#include <UTFT.h>
#include <avr/pgmspace.h>
#include <tstp.h>

tstp t(Serial);

extern uint8_t BigFont[];
UTFT d(ITDB32WD,38,39,40,41);


void setup() {
  d.InitLCD(LANDSCAPE);
  d.setFont(BigFont);
  Serial.begin(115200);
  Serial.flush();
}


void loop() {

  if (t.imageReady) {
    d.drawBitmap8S(t.position[0],t.position[1],t.dataInfo[4],t.dataInfo[5], t.generatedImage);
    t.imageReady = false;
  }

  if (t.stringReady) {
    d.print(t.stringData, t.position[0], t.position[1]);
    t.stringReady = false;
  }

}


void serialEvent() {
  while (Serial.available()) {
    t.getData();   
  }
}

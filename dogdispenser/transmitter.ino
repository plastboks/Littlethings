// Simple receiver script

#include "lib/VirtualWire.h"

int RF_TX_PIN = 2;
const int button = 10;


void setup() {
  pinMode(button, INPUT);
  vw_set_tx_pin(RF_TX_PIN);
  vw_setup(2000);
}


void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState = HIGH) {
    const char *msg "reddog";
    vw_send((uint8_t *)msg, strlen(msg));
    delay(400);
  }
}


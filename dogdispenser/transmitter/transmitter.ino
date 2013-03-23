// Simple receiver script

#include <VirtualWire.h>

int RF_TX_PIN = 2;
const int buttonPin = 10;
int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  vw_set_tx_pin(RF_TX_PIN);
  vw_setup(2000);
}


void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    const char *msg = "r";
    vw_send((uint8_t *)msg, strlen(msg));
    delay(1000);
  }
}


// Simple receiver script

#include <VirtualWire.h>

int RF_RX_PIN = 2;
int out1 = 10;


void setup() {
  
  pinMode(out1, OUTPUT);
  vw_set_rx_pin(RF_RX_PIN);
  vw_setup(2000);
  vw_rx_start();
}


void loop () {
  
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    int i;
    for (i = 0; i < buflen; i ++) {
      if (buf[i] == 114) {
        digitalWrite(out1, HIGH);
        delay(1000);
        digitalWrite(out1, LOW);
      }
    }
  }
}

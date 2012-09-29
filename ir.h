/************* IR FUNCTIONS ***********/

// IR settings
#define IRpin_PIN      PIND
#define IRpin          2
#define MAXPULSE 65000
#define NUMPULSES 50
#define RESOLUTION 20 
#define FUZZINESS 20
uint16_t pulses[NUMPULSES][2]; 
uint8_t currentpulse = 0;

// ir compare signals 
boolean IRcompare(int numpulses, int Signal[], int refsize) {
  int count = min(numpulses,refsize);
  for (int i=0; i< count-1; i++) {
    int oncode = pulses[i][1] * RESOLUTION / 10;
    int offcode = pulses[i+1][0] * RESOLUTION / 10;
    if ( ! (abs(oncode - Signal[i*2 + 0]) <= (Signal[i*2 + 0] * FUZZINESS / 100)) ) {  return false; }
    if ( ! (abs(offcode - Signal[i*2 + 1]) <= (Signal[i*2 + 1] * FUZZINESS / 100)) ) { return false; }
  }
  return true;
}

// listen for ir signals
int listenForIR(void) {
  currentpulse = 0;
  
  for ( unsigned long start = millis(); millis() - start < 200; ) {
    uint16_t highpulse, lowpulse; 
    highpulse = lowpulse = 0;
    if (IRpin_PIN & (1 << IRpin)) {
       highpulse++;
       delayMicroseconds(RESOLUTION);
       if (((highpulse >= MAXPULSE) && (currentpulse != 0))|| currentpulse == NUMPULSES) {
         return currentpulse;
       }
    }
    pulses[currentpulse][0] = highpulse;
    if (! (IRpin_PIN & _BV(IRpin))) {
       lowpulse++;
       delayMicroseconds(RESOLUTION);
        if (((lowpulse >= MAXPULSE)  && (currentpulse != 0))|| currentpulse == NUMPULSES) {
         return currentpulse;
       }
    }
    pulses[currentpulse][1] = lowpulse;
    currentpulse++;
  }
  
}

/**************** EEPROM FUNCTIONS **************/

// eeprom write float 
void EEPROM_writeDouble(int ee, double value) {
  byte* p = (byte*)(void*)&value;
  for (int i = 0; i < sizeof(value); i++)
	  EEPROM.write(ee++, *p++);
}


// eeprom read float 
double EEPROM_readDouble(int ee) {
  double value = 0.0;
  byte* p = (byte*)(void*)&value;
  for (int i = 0; i < sizeof(value); i++)
	  *p++ = EEPROM.read(ee++);
  return value;
} 


// read from eeprom 
void readFromEEprom(void) {
  bDriven = EEPROM_readDouble(10);
  cDriven = EEPROM_readDouble(20);
  dDriven = EEPROM_readDouble(30); 
}


// save to eeprom
void saveToEEprom(void) {
  EEPROM_writeDouble(10, bDriven);
  EEPROM_writeDouble(20, cDriven);
  EEPROM_writeDouble(30, dDriven);
}

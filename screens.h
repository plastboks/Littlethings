/************** DIFFERENT SCREENS *************/
byte hour;

void firstGpsScreen(void) {
    
  int timeZone = hour + 2;
  if (timeZone == 24) { timeZone = 0; }
  if (timeZone == 25) { timeZone = 1; }

  u8g.drawLine(0, 8, 128, 8);
  u8g.drawLine(0, 44, 128, 44);
  
  u8g.setFont(u8g_font_6x12);
  u8g.setPrintPos(4, 7);
  fprintf(&lcdout, "%d-%02d-%02d    %02d:%02d", year, month, day, timeZone, minutes);

  u8g.setFont(u8g_font_10x20);
  u8g.setPrintPos(6, 28);
  u8g.print(fkmph, 1);
  u8g.setPrintPos(58, 28);
  u8g.print("/");
  u8g.setPrintPos(70, 28);
  u8g.print(avgspeed, 1);

  u8g.setFont(u8g_font_6x12);
  
  u8g.setPrintPos(24, 43);
  u8g.print("Odometer (km)");
  
  u8g.setPrintPos(4, 54);
  u8g.print("A: ");
  u8g.setPrintPos(16, 54);
  u8g.print(aDriven/1000, 1);

  u8g.setPrintPos(4, 64);
  u8g.print("B: ");
  u8g.setPrintPos(16, 64);
  u8g.print(bDriven/1000, 1);

  u8g.setPrintPos(64, 54);
  u8g.print("C: ");
  u8g.setPrintPos(76, 54);
  u8g.print(cDriven/1000, 1);
  
  u8g.setPrintPos(64, 64);
  u8g.print("D: ");  
  u8g.setPrintPos(76, 64);
  u8g.print(dDriven/1000, 1);
  
  neverHadFix = 0;
}


void secondGpsScreen(void) {
  u8g.setFont(u8g_font_10x20);
  u8g.drawStr(4, 16, "LAT");
  u8g.setPrintPos(38, 16);
  u8g.print(flat, 5);
  u8g.drawStr(4, 32, "LON");
  u8g.setPrintPos(38, 32);
  u8g.print(flon, 5);
  
  u8g.setFont(u8g_font_6x12);
  u8g.drawStr(4, 46, "ALT");
  u8g.setPrintPos(24, 46);
  u8g.print(falt, 1);
  u8g.drawStr(64, 46, "COUR");
  u8g.setPrintPos(90, 46);
  u8g.print(fc, 1);

  u8g.drawStr(4, 60, "SAT");
  u8g.setPrintPos(24, 60);
  u8g.print(satellites);
  u8g.drawStr(64, 60, "HDOP");
  u8g.setPrintPos(90, 60);
  u8g.print(hdop);
}



void powerLostScreen(void) {
  if (shutdownState == 0) {
    saveToEEprom();
    shutdownState = 1;
    u8g.setFont(u8g_font_10x20);
    u8g.drawStr(10, 28, "Writing");
    u8g.drawStr(48, 48, "...");
  } else {
    u8g.setFont(u8g_font_10x20);
    u8g.drawStr(10, 28, "Shutdown");
    u8g.drawStr(48, 48, "...");
  }
}

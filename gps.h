/***************** GPS FUNCTIONS ****************/

// average Speed calculate 
void averageSpeed(void) {
  i++;
  avgspeedH = fkmph + avgspeedH;
  avgspeed = avgspeedH / i;
}


// odomoter 
void odoMeter(void) {
  if (neverHadFix == 1) { lastLat = flat; lastLon = flon; }
  if (fkmph > 1.0) { aDriven = aDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
  if (fkmph > 1.0) { bDriven = bDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
  if (fkmph > 1.0) { cDriven = cDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
  if (fkmph > 1.0) { dDriven = cDriven + gps.distance_between(flat, flon, lastLat, lastLon); }
  lastLat = flat;
  lastLon = flon;
  lastBDriven = bDriven;
  lastCDriven = cDriven;
  lastDDriven = dDriven;
}

// setGpsData to variables
void setGpsData(void) {
  gps.f_get_position(&flat, &flon, &age);
  fkmph = gps.f_speed_kmph();
  falt = gps.f_altitude();
  fc = gps.f_course();
  const char *cardinal = gps.cardinal(fc);
  satellites = gps.satellites();
  hdop = gps.hdop();    
  gps.crack_datetime(&year, &month, &day, &hour, &minutes, &second, &hundredths, &fix_age);
  odoMeter();
  averageSpeed();
}

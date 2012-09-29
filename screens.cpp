/*
Screens.cpp - Library for outputting different screens for Bragi
Created by Alexander Skjolden - September 2012
Released into the public domain.
This file is heavily inspired by http://www.arduino.cc/en/Hacking/LibraryTutorial
This library depends on u8glib
*/

#include "Arduino.h"
#include "Screens.h"

Screens::Screens(U8GLIB_ST7920_128X64& parent) : _d(parent) { }

void Screens::speedoMeter() {
  
  _d.drawLine(0, 8, 128, 8);
  _d.drawLine(0, 44, 128, 44);
  
}

void Screens::geo() {
  _d.setFont(u8g_font_10x20);
  _d.drawStr(4, 16, "LAT");
  _d.setPrintPos(38, 16);
  //_d.print(flat, 5);
  _d.drawStr(4, 32, "LON");
  _d.setPrintPos(38, 32);
  //_d.print(flon, 5);
  //--
  _d.setFont(u8g_font_6x12);
  _d.drawStr(4, 46, "ALT");
  _d.setPrintPos(24, 46);
  //_d.print(falt, 1);
  _d.drawStr(64, 46, "COUR");
  _d.setPrintPos(90, 46);
  //_d.print(fc, 1);
  //--
  _d.drawStr(4, 60, "SAT");
  _d.setPrintPos(24, 60);
  //_d.print(satellites);
  _d.drawStr(64, 60, "HDOP");
  _d.setPrintPos(90, 60);
  //_d.print(hdop);
}

void Screens::noSignal() {
  _d.setFont(u8g_font_10x20);
  _d.drawStr(10, 28, "Wait for it");
  _d.drawStr(48, 48, "...");
}

void Screens::writing() {
  _d.setFont(u8g_font_10x20);
  _d.drawStr(10, 28, "Writing");
  _d.drawStr(48, 48, "...");
}

void Screens::shutdown() {
  _d.setFont(u8g_font_10x20);
  _d.drawStr(10, 28, "Shutdown");
  _d.drawStr(48, 48, "...");
}


#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Tweeno LCD communications file
#
# @name: LCD.py
# 
# @date: 2012-09-13
#
# @version: 0.0.1
#
# @description: Tweeno LCD communictions class
#

import serial
import time
import textwrap

# web4robot 160x128px display
class p160_128():

  def __init__(self, port, speed):
    self.s = serial.Serial(port, speed)
    self.speedCheck(speed)
    time.sleep(5)

  def speedCheck(self, speed):
    self.speed = False
    speeds = {
      9600 : 2,
      14400 : 1.8,
      19200 : 1.2,
      28800 : 1,
      38400 : 0.6,
      57600 : 0.1,
      115200 : 0,
    }
    self.speed = speeds[speed]

  def send(self, s):
    for line in textwrap.wrap(s, 24):
      self.s.write(line.strip() + "\n")
      time.sleep(self.speed)

  def byline(self, s):
    self.s.write(" \n")
    time.sleep(self.speed)
    self.s.write("    By @" + s + '\n')
    time.sleep(self.speed)

  def clear(self):
    self.s.write("TweenoLCD::CLEAR")
    time.sleep(2)

  def end(self):
    self.s.write("TweenoLCD::END")

  def close(self):
    self.s.close()

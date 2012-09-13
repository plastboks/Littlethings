#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Tweeno LCD communications file
#
# @name: tweeno.py
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

class p160_128():

  def __init__(self, port, speed):
    self.s = serial.Serial(port, speed)
    time.sleep(5)

  def send(self, s):
    for line in textwrap.wrap(s, 24):
      self.s.write(line.strip() + "\n")
      time.sleep(0.1)

  def byline(self, s):
    self.s.write(" \n")
    time.sleep(0.1)
    self.s.write("    By @" + s + '\n')
    time.sleep(0.1)

  def clear(self):
    self.s.write("TweenoLCD::CLEAR")
    time.sleep(2)

  def end(self):
    self.s.write("TweenoLCD::END")

  def close(self):
    self.s.close()

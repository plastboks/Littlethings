#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Serial send and receive demo file
#
# @name: serial.test.py
# 
# @date: 2012-10-07
#
# @version: 0.0.1
#
# @description: Serial send and receive test file
#

from tstp import tstp
from serial import Serial
from rgb565 import rgb565
from time import sleep

t = tstp(
  Serial(
    "/dev/tty.usbmodemfa1221", 
    57600, 
    timeout=0.01, # Very aggressive timeout because of recurring speed.
  ) 
)

r = rgb565()

r.setImage("8x8-blue.png")
try:
  t.image(100, 100, 8, 8, r.img24bitList())
except Exception,e:
  print(e)

sleep(1)
r.setImage("8x8-green.png")
try:
  t.image(50, 50, 8, 8, r.img24bitList())
except Exception,e:
  print(e)

#try:
#  t.string("Yo Bitch in tha House")
#except Exception,e:
#  print(e)

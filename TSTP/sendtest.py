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

import sys

from tstp import tstp
from serial import Serial
from rgb565 import rgb565
from time import sleep


t = tstp(
  Serial(
    "/dev/tty.usbmodemfa1221", 
    115200, 
    timeout=0.01, # Very aggressive timeout because of speed.
  ) 
)

r = rgb565()

r.set("64x64-green.png")
imgSize = r.size()

p = (imgSize[0] / 8) * (imgSize[1] / 8)
r.parts(p)

horPos = 168
vertPos = 88

for part in r.imageParts:
  try:
    t.image(
        part[0][0]+horPos, 
        part[0][1]+vertPos, 
        part[1][0], part[1][1], 
        r.img24bitList(part[2])
      )
  except Exception,e:
    print(e)

  sleep(0.0001)


#try:
#  t.string("Yo Bitch in tha House")
#except Exception,e:
#  print(e)

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

r.set("DemoImages/400x240-multi.png")
r.setMode("24bit")

imgSize = r.size()
p = (imgSize[0] / 8) * (imgSize[1] / 8)

imgParts = r.parts(p, random=True)

horPos = 4
vertPos = 0

for part in imgParts:
  try:
    t.image( part[0][0]+horPos, part[0][1]+vertPos, part[1][0], part[1][1], 1, r.imgList(part[2]) )
  except Exception,e:
    print(e)

  sleep(0.000001)


#try:
#  t.string("Hello world")
#except Exception,e:
#  print(e)

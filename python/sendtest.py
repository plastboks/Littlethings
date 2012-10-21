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


serialPort = "/dev/tty.usb0"
serialSpeed = 115200
serialTimeout = 0.01

demoImage = "img/128x128.png"
imageMode = "24bit"
drawRandom = True

horizontalPos = 136
verticalPos = 20



t = tstp(Serial(serialPort, serialSpeed, timeout=serialTimeout))
r = rgb565()

r.set(demoImage)
r.setMode(imageMode)

imgSize = r.size()
p = (imgSize[0] / 8) * (imgSize[1] / 8)

imgParts = r.parts(p, random=drawRandom)

for part in imgParts:
  try:
    t.image( part[0][0]+horizontalPos, part[0][1]+verticalPos, part[1][0], part[1][1], 1, r.imgList(part[2]) )
  except Exception,e:
    print(e)
  sleep(0.000001)


try:
  t.string("Hello world")
except Exception,e:
  print(e)

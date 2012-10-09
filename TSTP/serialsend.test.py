#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Serial send and receive test file
#
# @name: serial.test.py
# 
# @date: 2012-10-07
#
# @version: 0.0.1
#
# @description: Serial send and receive test file
#

import serial
import time
import sys
from operator import xor



def genCheckSum(string):
  bits = map(ord, string)
  return hex(reduce(xor, bits))



s = serial.Serial("/dev/tty.usbmodemfa131", 57600, timeout=2)

time.sleep(3)
s.flush()

print(genCheckSum("Hei verden"))


s.write(chr(0x06))
print(s.readline())
print(s.read())


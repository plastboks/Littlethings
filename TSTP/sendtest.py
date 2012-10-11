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

print("Sending type")
s.write(chr(0x01))
print("Sending size")
s.write(chr(0x04))

print("Sending data: ")
for i in range(0, 20):
  s.write(chr(0x43))
  print(chr(0x43))

print("Sending extra chr")
s.write(chr(0x01))
print(s.readline())


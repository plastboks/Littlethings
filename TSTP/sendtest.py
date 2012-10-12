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
from pprint import pprint


def genStringCheckSum(string):
  bits = map(ord, string)
  return reduce(xor, bits)

def genImageCheckSum(imageTuple):
  print("Some nice feature") #...

def genBytes(string):
  return map(ord, string)

def transferSting(string):
  strLen = len(string)
  # send over type definition
  s.write(chr(0x01))
  # send over string length
  s.write(chr(strLen + 1))
  # send the actual data
  for i in genBytes(string):
    s.write(chr(i))
  # send "End of Transmission Block"
  s.write(chr(0x17))
  # send over chekcsum for comparison
  s.write(chr(genStringCheckSum(string)))
  if (s.readline() == '\x06'):
    print("Data successfully transmitted")
  else:
    print("Data not successfully transmitted")

def transferImage(imageTuple):
  # send over type definition
  s.write(0x02)
  # send over image length
  s.write(0x04) #Bogus data for now...
  # send over image information (hor pos, vert pos, hor size, vertsize)
  print("Sending image info")
  for i in range(0, 6):
    s.write(chr(0x01)) #Bogus data for now...
  # send over actual image data
  for i in range(0, 4):
    s.write(chr(0x01)) #Bogus data for now...
  # send "End of transmission block"
  s.write(chr(0x17))
  # send over checksum for comparison
  s.write(chr(genImageCheckSum(imageTuple)))
  if (s.readline() == '\x06'):
    print("Data successfully transmitted")
  else:
    print("Data not successfully transmitted") 


s = serial.Serial("/dev/tty.usbmodemfa131", 57600, timeout=0.01) # Very aggressive timeout because of recurring speed.


time.sleep(3)
s.flush()

transferSting("Yo Bitch in tha House")


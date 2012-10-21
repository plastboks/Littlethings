#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Python interpertaion of Tweeno :: STP 
#
# @name: tstp.py
# 
# @date: 2012-10-13
#
# @version: 0.0.1
#
# @description: Python version of th Tweeno :: STP library.
#

from operator import xor
import time
import sys

class tstp:


  def __init__(self, serialObject):
    self.s = serialObject
    self.s.flush()
    time.sleep(2) # The microcontroller need some time to restore from reboot.


  def string(self, string):
    
    self.s.write(chr(0x01)) # type definition
    self.s.write(chr(len(self.genBytes(string)))) # string length
    
    for i in self.genBytes(string): # string data
      self.s.write(chr(i))
    
    self.s.write(chr(0x17)) # "End of transmission block"
    self.s.write(chr(self.genStringCheckSum(string))) # checksum for comparison
    
    if (self.s.readline() == '\x06'):
      return True
    else:
      raise Exception("Data not transmitted successfully")


  def image(self, horPos, vertPos, horSize, vertSize, imgType, imgList):
    
    self.s.write(chr(0x02)) # type definition
    self.s.write(chr(len(imgList))) # image length
    
    # calculate pos bytes
    hPosA = horPos >> 8
    hPosB = horPos & 0xff
    vPosA = vertPos >> 8
    vPosB = vertPos & 0xff

    # send over image info
    self.s.write(chr(hPosA)) # first horPos Byte
    self.s.write(chr(hPosB)) # second horPos Byte
    self.s.write(chr(vPosA)) # first vertPos Byte
    self.s.write(chr(vPosB)) # second vertPos Byte
    
    self.s.write(chr(horSize)) # horSize Byte
    self.s.write(chr(vertSize)) # vertSize Byte
    self.s.write(chr(imgType)) # 1 for 24 bit, 2 for 16bit
    self.s.write(chr(0x17)) # spare byte, not in use for now.

    for r, i in enumerate(imgList): # image data
      self.s.write(chr(i))
      #time.sleep(0.0000001)

    self.s.write(chr(0x17)) # "End of transmission block"
    self.s.write(chr(self.genImageCheckSum(imgList))) # checksum for comparison

    if (self.s.readline() == '\x06'):
      return True
    else:
      raise Exception("Data not transmitted successfully")


  def genStringCheckSum(self, string):
    bits = map(ord, string)
    return reduce(xor, bits)


  def genImageCheckSum(self, imgList):
    return reduce(xor, imgList)


  def genBytes(self, string):
    return map(ord, string)


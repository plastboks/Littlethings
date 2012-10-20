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
    time.sleep(3) # This sould not be done this way, but the microcontroller need some time to restore from reboot.


  def string(self, string):
    strLen = len(string)
    
    self.s.write(chr(0x01)) # type definition
   
    self.s.write(chr(strLen + 1)) # string length
    
    for i in self.genBytes(string): # string data
      self.s.write(chr(i))
    
    self.s.write(chr(0x17)) # ETB
    
    self.s.write(chr(self.genStringCheckSum(string))) # chekcsum
    
    if (self.s.readline() == '\x06'):
      return True
    else:
      raise Exception("Data not transmitted successfully")


  def image(self, horPos, vertPos, horSize, vertSize, imgList):
    
    self.s.write(chr(0x02)) # send over type definition
    self.s.write(chr(0xc0)) # send over image length. Hardcoded for now...192
    
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

    for r, i in enumerate(imgList): # send over actual image data
      self.s.write(chr(i))
      time.sleep(0.0001)

    self.s.write(chr(0x17)) # send "End of transmission block"
    #print( map(ord, self.s.read()) )
    self.s.write(chr(self.genImageCheckSum(imgList))) # send over checksum for comparison

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


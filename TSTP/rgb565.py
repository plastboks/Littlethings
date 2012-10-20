#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Python RGB565 tools for the Tweeno :: STP library. 
#
# @name: rgb565.py
# 
# @date: 2012-10-13
#
# @version: 0.0.1
#
# @description: Python RGB565 tools for the Tweeno :: STP library. 
#

# from 8bit to 5/6 bit = 255 >> 3 (5bit), org 255 >> 2 (6bit)

from PIL import Image
from random import shuffle
import time
import math
import sys


class rgb565:


  def __init__(self):
    self.outArray = {}
    self.mode = 0


  def set(self, image):
    self.img = Image.open(image)


  def setMode(self, string):
    if (string == "24bit"):
      self.mode = 1
    elif (string == "16bit"):
      self.mode = 2
    else:
      print("Unknown mode")
      sys.exit()


  def data(self):
    return self.img.getdata()


  def size(self):
    return self.img.size


  def toRGB565(self, data):
    toFiveSixFive = [
      data[0] >> 3,
      data[1] >> 2,
      data[2] >> 3,
      ]
    highColor = ((toFiveSixFive[0] << 11) + (toFiveSixFive[1] << 5)) + toFiveSixFive[2]
    return [(highColor >> 8), (highColor & 8)]


  def split(self, imgSize, splits):
    p = int(math.sqrt(splits))
    h = imgSize[0] / p
    v = imgSize[1] / p

    outDict = []
    for r in range(1, imgSize[1], v):
      if r != 1 : r = r - 1
      for c in range(1, imgSize[0], h):
        if c != 1 : c = c - 1
        w = c if c != 1 else 0
        x = r if r != 1 else 0
        y = c + h if c != 1 else (c + h) - 1
        z = r + v if r != 1 else (r + v) - 1
        outDict.append((w, x, y, z))
    return outDict


  def img24bitList(self, inputImage):
    outList = []

    for byte in inputImage:
      for bit in byte:
        outList.append(bit)
    return outList


  def c16List(self, inputImage):
    outList = []

    for byte in inputImage:
      c3t2 = self.toRGB565(byte)
      outList.append(c3t2[0])
      outList.append(c3t2[1])
    return outList



  def imgList(self, inputImage):
    if (self.mode == 1):
      return self.img24bitList(inputImage)
    elif (self.mode == 2):
      return self.c16List(inputImage)



  def parts(self, parts, random=False):
    imageParts = []
    for c in self.split(self.size(), parts):
      imageParts.append([c, self.img.crop(c).size, list(self.img.crop(c).getdata())])
      if (random):
        shuffle(imageParts)
    return imageParts




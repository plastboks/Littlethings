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
import time
import math


class rgb565:


  def __init__(self):
    self.imageParts = []
    self.outArray = {}


  def set(self, image):
    self.img = Image.open(image)


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
    return hex( ((toFiveSixFive[0] << 11) + (toFiveSixFive[1] << 5)) + toFiveSixFive[2] )


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


  def img24bitList(self, inputImage=False):
    outList = []
    if inputImage:
      pic = inputImage
    else:
      pic = self.data()
    for byte in pic:
      for bit in byte:
        outList.append(bit)
    
    return outList


  def parts(self, parts):
    for c in self.split(self.size(), parts):
      self.imageParts.append([c, self.img.crop(c).size, list(self.img.crop(c).getdata())])
    return True

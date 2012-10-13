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

  def setImage(self, image):
    self.img = Image.open(image)


  def imgData(self):
    return self.img.getdata()

  def toRGB565(self, data):
    toFiveSixFive = [
      data[0] >> 3,
      data[1] >> 2,
      data[2] >> 3,
      ]
    return hex( ((toFiveSixFive[0] << 11) + (toFiveSixFive[1] << 5)) + toFiveSixFive[2] )

  def imageSplit(self, img, splits):
    p = int(math.sqrt(splits))
    h = img[0] / p
    v = img[1] / p

    outDict = []
    for r in range(1, img[1], v):
      if r != 1 : r = r - 1
      for c in range(1, img[0], h):
        if c != 1 : c = c - 1
        w = c
        x = r
        y = c + h if c != 1 else (c + h) - 1
        z = r + v if r != 1 else (r + v) - 1
        outDict.append((w, x, y, z))

    return outDict

  def img24bitList(self):
    outList = []
    for byte in self.imgData():
      for bit in byte:
        outList.append(bit)
    return outList


  def imageParts(self):
    for cor in imageSplit(demoImage.size, 16):
      print(cor)
      imageParts.append(list(demoImage.crop(cor).getdata()))


  def imagePartsRGB565(self):
    for idx, part in enumerate(imageParts):
      outArray[idx] = []
      for entry in part:
        outArray[idx].append(toRBG565(entry))
      return outArray




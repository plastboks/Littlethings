#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Tweeno RGB565 file
#
# @name: img565.py
# 
# @date: 2012-09-30
#
# @version: 0.0.1
#
# @description: Tweeno img to RGB565 converter
#


# from 8bit to 5/6 bit = 255 >> 3 (5bit), org 255 >> 2 (6bit)

from PIL import Image
import time
import math


def toRBG565(data):
  toFiveSixFive = [
    data[0] >> 3,
    data[1] >> 2,
    data[2] >> 3,
    ]

  return hex(
      ((toFiveSixFive[0] << 11) + (toFiveSixFive[1] << 5)) + toFiveSixFive[2]
    )



def imageSplit(img, splits):
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



demoImage = Image.open("128x96.png")


imageParts = []
outArray = {}

for cor in imageSplit(demoImage.size, 16):
  print(cor)
  imageParts.append(list(demoImage.crop(cor).getdata()))


for idx, part in enumerate(imageParts):
  outArray[idx] = []
  for entry in part:
    outArray[idx].append(toRBG565(entry))

print outArray

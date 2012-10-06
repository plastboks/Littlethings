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

start = time.time()


def toRBG565(data):
  toFiveSixFive = [
    data[0] >> 3,
    data[1] >> 2,
    data[2] >> 3,
    ]

  return hex(
      ((toFiveSixFive[0] << 11) + (toFiveSixFive[1] << 5)) + toFiveSixFive[2]
    )


demoImage = Image.open("2560x1600.png")
imgsize = demoImage.size[0]
split = imgsize / 2

imageParts = [
  list(demoImage.crop([0, 0, split, split]).getdata()),
  list(demoImage.crop([split, 0, imgsize, split]).getdata()),
  list(demoImage.crop([0, split, split, imgsize]).getdata()),
  list(demoImage.crop([split, split, imgsize, imgsize]).getdata()),
]

outArray = {}

for idx, part in enumerate(imageParts):
  outArray[idx] = []
  for entry in part:
    outArray[idx].append(toRBG565(entry))

stop = time.time()

print (stop - start)


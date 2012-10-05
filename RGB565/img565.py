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

demoImage = Image.open("demo300.png")
imgsize = demoImage.size[0]
split = imgsize / 2

imageParts = [
  list(demoImage.crop([0, 0, split, split]).getdata()),
  list(demoImage.crop([split, 0, imgsize, split]).getdata()),
  list(demoImage.crop([0, split, split, imgsize]).getdata()),
  list(demoImage.crop([split, split, imgsize, imgsize]).getdata()),
]


for part in imageParts:
  for entry in part:
    print(hex(((entry[0] >> 3) << 11) + ((entry[1] >> 2) << 5) + (entry[2] >> 3)))

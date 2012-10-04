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

iUL = demoImage.crop([0, 0, split, split]) # upper left
iUR = demoImage.crop([split, 0, imgsize, split]) # upper right
iLF = demoImage.crop([0, split, split, imgsize]) # lower left
iLR = demoImage.crop([split, split, imgsize, imgsize]) # lower right

iULData = list(iUL.getdata())


for entry in iULData:
  print entry

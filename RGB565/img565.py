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


from PIL import Image

im = Image.open("demo300.png")

imgsize = im.size[0]

split = imgsize / 2

im.crop([0, 0, split, split]).show() # upper left
im.crop([split, 0, imgsize, split]).show() # upper right
im.crop([0, split, split, imgsize]).show() # lower left
im.crop([split, split, imgsize, imgsize]).show() # lower right
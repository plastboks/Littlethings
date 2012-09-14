#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Tweeno functions file
#
# @name: functions.py
# 
# @date: 2012-09-13
#
# @version: 0.0.1
#
# @description: Tweeno generic functions
#

#- A simple custom replace UTF characther in string function
def replaceUTF(s):
  notAscii = [  ["Æ","AE"], 
                ["æ","ae"], 
                ["Ø","O"], 
                ["ø","o"], 
                ["Å","å"], 
                ["å","a"], 
                ["è", "e"], 
                ["č", "c"], 
                ["í", "i"], 
                ["ů", "u"],
                ["“", "'"],
                ["”", "'"],
                ]
  out = s
  for letters in notAscii:
    out = out.replace(letters[0], letters[1])
  return out
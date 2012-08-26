#!/usr/bin/python
# -*- coding: utf-8 -*-


import serial
import twitter
import time
import textwrap


def replaceUTF(s):
  notAscii = [ ["Æ","AE"], ["æ","ae"], ["Ø","O"], ["ø","o"], ["Å","å"], ["å","a"], ]
  tmp = s
  for letters in notAscii:
    tmp = tmp.replace(letters[0], letters[1])
  return tmp

ser = serial.Serial('/dev/tty.usbserial-A1016455', 9600)
api = twitter.Api()

statuses = api.GetUserTimeline("oslopolitiops", count="1")
lastStatus = [s.text for s in statuses][0].encode("utf-8", "ignore")

time.sleep(5)
ser.write("TweenoLCD::CLEAR")

print replaceUTF(lastStatus)

for line in textwrap.wrap(replaceUTF(lastStatus), 24):
  time.sleep(3)
  ser.write(line.strip() + "\n")

time.sleep(3)
ser.write("TweenoLCD::END")
time.sleep(3)
ser.close()
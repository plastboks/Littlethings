#!/usr/bin/python
# -*- coding: utf-8 -*-


import serial
import twitter
import time
import textwrap
import json

f = open("config.json", "r")
config = json.loads(f.read())

api = twitter.Api(
  consumer_key=config["oauth"]["consumer_key"],
  consumer_secret=config["oauth"]["consumer_secret"], 
  access_token_key=config["oauth"]["access_token_key"], 
  access_token_secret=config["oauth"]["access_token_secret"])

ser = serial.Serial(config["serial"]["port"], 57600)

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
                ]
  tmp = s
  for letters in notAscii:
    tmp = tmp.replace(letters[0], letters[1])
  return tmp

time.sleep(5)
oldMessage = None

while True:
  statuses = api.GetFriendsTimeline(user="skjoldenfrilans", count=1)

  lastMessage = [s.text for s in statuses][0].encode("utf-8", "ignore")
  user = [s.user.screen_name for s in statuses]


  if not lastMessage == oldMessage:
    print replaceUTF(lastMessage)
    oldMessage = lastMessage
    ser.write("TweenoLCD::CLEAR")
    time.sleep(2)
    for line in textwrap.wrap(replaceUTF(lastMessage), 24):
      ser.write(line.strip() + "\n")
      time.sleep(0.1)
    ser.write(" \n")
    time.sleep(0.1)
    ser.write("    By @" + user[0] + '\n')
    time.sleep(0.1)
    ser.write("TweenoLCD::END")
  time.sleep(10)


ser.close()


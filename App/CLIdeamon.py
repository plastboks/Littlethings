#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Tweeno deamon file
#
# @name: deamon.py
# 
# @date: 2012-09-13
#
# @version: 0.0.1
#
# @description: Tweeno deamon functions
#

import twitter
import time

# - project spesifict import
import config
import functions
import LCD
import fetch


c = config.Config()
t = fetch.tweet(c)
d = LCD.p160_128(c.s_port, 57600)

oldMessage = None

while True:
  data = t.fetchNewMessage()

  asciiMessage = t.asciiMe(data[0])

  if not asciiMessage == oldMessage:
    print asciiMessage + "\nBy @:" +data[1]
    oldMessage = asciiMessage
    d.clear()
    d.send(asciiMessage)
    d.byline(data[1])
    d.end()
  time.sleep(15)

d.close()


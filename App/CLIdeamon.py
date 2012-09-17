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


c = config.Config()
t = twitter.Api(
  consumer_key=c.o_ck,
  consumer_secret=c.o_cs, 
  access_token_key=c.o_atk, 
  access_token_secret=c.o_ats,
  input_encoding="utf-8")

d = LCD.p160_128(c.s_port, 57600)

oldMessage = None

while True:
  statuses = t.GetFriendsTimeline(user="skjoldenfrilans", count=1, retweets=True)
  message = [s.text for s in statuses][0].encode("utf-8", "replace")
  user = [s.user.screen_name for s in statuses]

  if not message == oldMessage:
    #print message + "   By: @" + user[0]
    print functions.replaceUTF(message) + "   @" + user[0]
    oldMessage = message
    d.clear()
    #d.send(message)
    d.send(functions.replaceUTF(message))
    d.byline(user[0])
    d.end()
  time.sleep(10)

d.close()


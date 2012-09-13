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
api = twitter.Api(
  consumer_key=c.o_ck,
  consumer_secret=c.o_cs, 
  access_token_key=c.o_atk, 
  access_token_secret=c.o_ats)

t = LCD.p160_128(c.s_port, 57600)

oldMessage = None

while True:
  statuses = api.GetFriendsTimeline(user="skjoldenfrilans", count=1)
  message = [s.text for s in statuses][0].encode("utf-8", "ignore")
  user = [s.user.screen_name for s in statuses]

  if not message == oldMessage:
    print functions.replaceUTF(message)
    oldMessage = message
    t.clear()
    t.send(functions.replaceUTF(message))
    t.byline(user[0])
    t.end()
  time.sleep(10)

t.close()


#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Tweeno fether file
#
# @name: fetch.py
#
# @date: 2012-09-30
#
# @version: 0.0.1
#
# @description: Tweeno deamon functions
#

import twitter
import unicodedata


class tweet():

    def __init__(self, config):
        self.config = config
        self.setup()

    def setup(self):
        self.t = twitter.Api(
            consumer_key=self.config.o_ck,
            consumer_secret=self.config.o_cs,
            access_token_key=self.config.o_atk,
            access_token_secret=self.config.o_ats,
            input_encoding="utf-8"
            )

    def fetchNewMessage(self):
        statuses = self.t.GetFriendsTimeline(self.config.u_name,
                                             count=1,
                                             retweets=True)
        message = [s.text for s in statuses][0]
        user = [s.user.screen_name for s in statuses][0]
        userdata = self.t.GetUser(user)
        userimg = userdata.profile_image_url

        data = [message, user, userdata, userimg]
        return data

    def asciiMe(self, string):
        return unicodedata.normalize("NFKD", string).encode("ascii", "ignore")

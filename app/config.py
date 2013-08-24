#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Tweeno config file
#
# @name: config.py
#
# @date: 2012-09-03
#
# @version: 0.0.1
#
# @description: Config read write
#

# standard libraries
import os
import json


class Config():

    def __init__(self):
        self.path = os.path.abspath(".") + "/"
        self.read()

    def myFile(self):
        return self.path + 'config.json'

    def check(self):
        if not os.path.exists(self.myFile()):
            self.createNew()
            return False
        else:
            return True

    def layout(self):
        return {
            "oauth": {
                "consumer_secret": "",
                "consumer_key": "",
                "access_token_secret": "",
                "access_token_key": "",
            },
            "serial": {
                "port": "",
            },
            "user": {
                "name": "",
            }
        }

    def read(self):
        if self.check():
            cFile = open(self.myFile(), "r")
            c = json.load(cFile)
            cFile.close()
            self.o_cs = c["oauth"]["consumer_secret"]
            self.o_ck = c["oauth"]["consumer_key"]
            self.o_ats = c["oauth"]["access_token_secret"]
            self.o_atk = c["oauth"]["access_token_key"]
            self.s_port = c["serial"]["port"]
            self.u_name = c["user"]["name"]
            return True
        else:
            return False

    def write(self):
        if self.check():
            cFile = open(self.myFile(), "r+")
            c = json.load(cFile)
            c["oauth"]["consumer_secret"] = self.o_cs
            c["oauth"]["consumer_key"] = self.o_ck
            c["oauth"]["access_token_secret"] = self.o_ats
            c["oauth"]["access_token_key"] = self.o_atk
            c["serial"]["port"] = self.s_port
            c["user"]["name"] = self.u_name
            cFile.seek(0)
            cFile.write(json.dumps(c))
            cFile.truncate()
            cFile.close()
        else:
            return False

    def createNew(self):
        try:
            cFile = open(self.myFile(), 'w+')
            cFile.write(json.dumps(self.layout()))
            cFile.close()
        except:
            return False

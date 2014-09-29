#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Tweeno LCD communications file
#
# @name: LCD.py
#
# @date: 2012-09-13
#
# @version: 0.0.1
#
# @description: Tweeno LCD communictions class
#

import serial
import time
import textwrap
import time
import sys
from operator import xor


class serialTools():

    def speedCheck(self, speed):
        self.speed = False
        speeds = {
            9600: 2,
            14400: 1.8,
            19200: 1.2,
            28800: 1,
            38400: 0.6,
            57600: 0.1,
            115200: 0.00001,
        }
        return = speeds[speed]


# web4robot 160x128px display
class p160_128():

    def __init__(self, port, speed):
        self.s = serial.Serial(port, speed)
        sT = serialTools
        self.speed = sT.speedCheck(speed)
        time.sleep(4)

    def send(self, s):
        for line in textwrap.wrap(s, 24):
            self.s.write(line.strip() + "\n")
            time.sleep(self.speed)

    def byline(self, s):
        self.s.write(" \n")
        time.sleep(self.speed)
        self.s.write("     @" + s + '\n')
        time.sleep(self.speed)

    def clear(self):
        self.s.write("TweenoLCD::CLEAR")
        time.sleep(2)

    def end(self):
        self.s.write("TweenoLCD::END")

    def close(self):
        self.s.close()


# iteadStudio 400x240px display
class p400_240():

    def __init__(self, port, speed):
        self.s = serial.Serial(port, speed)
        sT = serialTools
        self.speed = sT.speedCheck(speed)
        self.s.flush()
        #The microcontroller need some time to restore from reboot.
        time.sleep(2)

    def clearScr(self):
        self.s.write(chr(0xff))  # type definition
        self.s.write(chr(0x00))  # zero length
        self.s.write(chr(0x00))  # zero data
        time.sleep(1)  # this takes some time...

    def string(self, horPos, vertPos, stringType, string):
        self.s.write(chr(0x01))  # type definition
        self.s.write(chr(len(self.genBytes(string))))  # string length
        # calculate pos bytes
        hPosA = horPos >> 8
        hPosB = horPos & 0xff
        vPosA = vertPos >> 8
        vPosB = vertPos & 0xff

        # send over image info
        self.s.write(chr(hPosA))  # first horPos Byte
        self.s.write(chr(hPosB))  # second horPos Byte
        self.s.write(chr(vPosA))  # first vertPos Byte
        self.s.write(chr(vPosB))  # second vertPos Byte

        self.s.write(chr(stringType))  # Not in use atm
        self.s.write(chr(0x17))  # spare byte, not in use for now.

        for i in self.genBytes(string):  # string data
            self.s.write(chr(i))

        #"End of transmission block"
        self.s.write(chr(0x17))
        # checksum for comparison
        self.s.write(chr(self.genStringCheckSum(string)))

        if (self.s.readline() == '\x06'):
            return True
        else:
            raise Exception("Data not transmitted successfully")

    def image(self, horPos, vertPos, horSize, vertSize, imgType, imgList):
        self.s.write(chr(0x02))  # type definition
        self.s.write(chr(len(imgList)))  # image length

        # calculate pos bytes
        hPosA = horPos >> 8
        hPosB = horPos & 0xff
        vPosA = vertPos >> 8
        vPosB = vertPos & 0xff

        # send over image info
        self.s.write(chr(hPosA))  # first horPos Byte
        self.s.write(chr(hPosB))  # second horPos Byte
        self.s.write(chr(vPosA))  # first vertPos Byte
        self.s.write(chr(vPosB))  # second vertPos Byte

        self.s.write(chr(horSize))  # horSize Byte
        self.s.write(chr(vertSize))  # vertSize Byte
        self.s.write(chr(imgType))  # 1 for 24 bit, 2 for 16bit
        self.s.write(chr(0x17))  # spare byte, not in use for now.

        for r, i in enumerate(imgList):  # image data
            self.s.write(chr(i))
            #time.sleep(0.0000001)

        # "End of transmission block"
        self.s.write(chr(0x17))
        # checksum for comparison
        self.s.write(chr(self.genImageCheckSum(imgList)))

        if (self.s.readline() == '\x06'):
            return True
        else:
            raise Exception("Data not transmitted successfully")

    def genStringCheckSum(self, string):
        bits = map(ord, string)
        return reduce(xor, bits)

    def genImageCheckSum(self, imgList):
        return reduce(xor, imgList)

    def genBytes(self, string):
        return map(ord, string)

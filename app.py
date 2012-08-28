#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Tweeno App main file 
#
# @name: app.py
# 
# @date: 2012-08-28
#
# @version: 0.0.1
#
# @description: Launch Tweeno app
#

# special library
import wx

class Tweeno(wx.Frame):
  def __init__(self, *args, **kwargs):
    super(Tweeno, self).__init__(*args, **kwargs)
    self.InitUI()


  def InitUI(self):

    self.SetSize((300, 700))
    self.SetTitle('Tweeno')
    self.Centre()
    self.Show(True)




if __name__ == '__main__':
  ex = wx.App()
  Tweeno(None)
  ex.MainLoop()
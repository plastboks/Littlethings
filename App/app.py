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

import sys
import wx

#import Tweeno
import config
import configDialog

class App(wx.Frame):
  def __init__(self, *args, **kwargs):
    super(App, self).__init__(*args, **kwargs)
    self.c = config.Config()

    self.InitUI()



  def InitUI(self):

    menuBar = wx.MenuBar()

    self.fileMenu = wx.Menu()
    configFileMenu = self.fileMenu.Append(wx.ID_NEW,    "Config\tCtrl-O", "Open Configuration")
    closeFileMenu = self.fileMenu.Append(wx.ID_CLOSE,  "Close\tCtrl-W")

    menuBar.Append(self.fileMenu, "File")
    self.SetMenuBar(menuBar)

    self.Bind(wx.EVT_TOOL, self.onConfig, configFileMenu)
    self.Bind(wx.EVT_TOOL, self.onClose, closeFileMenu)


    self.SetSize((300, 700))
    self.SetTitle('Tweeno')
    self.Centre()
    self.Show(True)


  def onConfig(self, event): 
    config = configDialog.Dialog(self, title='Config')
    config.ShowModal()
    config.Destroy()

  def onClose(self, event):
    self.Destroy()
    sys.exit()



if __name__ == '__main__':
  ex = wx.App()
  App(None)
  ex.MainLoop()
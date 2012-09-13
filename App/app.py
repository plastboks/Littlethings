#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# Tweeno App main file 
#
# @name: app.py
# 
# @date: 2012-08-28
#
# @version: 0.0.2
#
# @description: Launch Tweeno app
#

import sys
import wx
import textwrap

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

    
    pnl = wx.Panel(self)
    vbox = wx.BoxSizer(wx.VERTICAL)
    vbox.Add((-1, 15))

    for count in range(1, 20):

      tmp1 = "WordPress hack: Easily get post content by ID http://t.co/0mpCWRxc"
      for line in textwrap.wrap(tmp1, 45):
        vbox.Add(wx.StaticText(pnl, label=line, style=wx.ALIGN_LEFT), flag=wx.LEFT, border=10)
      vbox.Add(wx.StaticLine(pnl, -1, size=(1,2), style=wx.LI_VERTICAL), flag=wx.EXPAND|wx.ALL, border=10)

    pnl.SetSizer(vbox)

    self.Bind(wx.EVT_TOOL, self.onConfig, configFileMenu)
    self.Bind(wx.EVT_TOOL, self.onClose, closeFileMenu)

    #self.scroll = wx.ScrolledWindow(self, -1)
    #self.scroll.SetScrollbars(1, 1, 600, 400)

    self.SetSize((300, 700))
    self.SetMaxSize((300, 700))
    self.SetMinSize((300, 700))
    self.SetTitle('Tweeno')
    self.Centre()
    self.Show(True)




  def onConfig(self, event): 
    configDlg = configDialog.Dialog(self, title='Config')
    configDlg.ShowModal()
    configDlg.Destroy()

  def onClose(self, event):
    self.Destroy()
    sys.exit()



if __name__ == '__main__':
  ex = wx.App()
  App(None)
  ex.MainLoop()
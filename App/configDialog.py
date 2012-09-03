#!/usr/bin/python
# -*- coding: utf-8 -*-


#
# Tweeno config dialog file
#
# @name: configDialog.py
# 
# @date: 2012-09-03
#
# @version: 0.0.1
#
# @description: Tweeno config dialog
#

import wx

from config import Config

class Dialog(wx.Dialog):

  def __init__(self, parent, title):
    super(Dialog, self).__init__(parent=parent, title=title, size=(565, 450))

    self.parent = parent

    panel = wx.Panel(self)
    vbox = wx.BoxSizer(wx.VERTICAL)

    sb = wx.StaticBox(panel, label='Config')
    sbs = wx.StaticBoxSizer(sb, orient=wx.VERTICAL)        


    hbSTconsumerSecret = wx.BoxSizer(wx.HORIZONTAL)
    hbSTconsumerSecret.Add(wx.StaticText(panel, -1, 'Consumer Secret'), flag=wx.LEFT|wx.TOP, border=3)
    sbs.Add(hbSTconsumerSecret)
    sbs.Add((-1, 2))

    hbTCconsumerSecret = wx.BoxSizer(wx.HORIZONTAL)
    self.o_cs = wx.TextCtrl(panel, -1, self.parent.c.o_cs, size=(500,23))
    hbTCconsumerSecret.Add(self.o_cs, flag=wx.LEFT|wx.TOP, border=3)
    sbs.Add(hbTCconsumerSecret)
    sbs.Add((-1, 15))

    # --

    hbSTconsumerKey = wx.BoxSizer(wx.HORIZONTAL)
    hbSTconsumerKey.Add(wx.StaticText(panel, -1, 'Consumer Key'), flag=wx.LEFT|wx.TOP, border=3)
    sbs.Add(hbSTconsumerKey)
    sbs.Add((-1, 2))

    hbTCconsumerKey = wx.BoxSizer(wx.HORIZONTAL)
    self.o_ck = wx.TextCtrl(panel, -1, self.parent.c.o_ck, size=(500,23))
    hbTCconsumerKey.Add(self.o_ck, flag=wx.LEFT|wx.TOP, border=3)
    sbs.Add(hbTCconsumerKey)
    sbs.Add((-1, 15))

    # --

    hbSTaccessTokenSecret = wx.BoxSizer(wx.HORIZONTAL)
    hbSTaccessTokenSecret.Add(wx.StaticText(panel, -1, 'Access Token Secret'), flag=wx.LEFT|wx.TOP, border=3)
    sbs.Add(hbSTaccessTokenSecret)
    sbs.Add((-1, 2))

    hbTCaccessTokenSecret = wx.BoxSizer(wx.HORIZONTAL)
    self.o_ats = wx.TextCtrl(panel, -1, self.parent.c.o_ats, size=(500,23))
    hbTCaccessTokenSecret.Add(self.o_ats, flag=wx.LEFT|wx.TOP, border=3)
    sbs.Add(hbTCaccessTokenSecret)
    sbs.Add((-1, 15))

    # --

    hbSTaccessTokenKey = wx.BoxSizer(wx.HORIZONTAL)
    hbSTaccessTokenKey.Add(wx.StaticText(panel, -1, 'Access Token Key'), flag=wx.LEFT|wx.TOP, border=3)
    sbs.Add(hbSTaccessTokenKey)
    sbs.Add((-1, 2))

    hbTCaccessTokenKey = wx.BoxSizer(wx.HORIZONTAL)
    self.o_atk = wx.TextCtrl(panel, -1, self.parent.c.o_atk, size=(500,23))
    hbTCaccessTokenKey.Add(self.o_atk, flag=wx.LEFT|wx.TOP, border=3)
    sbs.Add(hbTCaccessTokenKey)
    sbs.Add((-1, 15))

    #--

    hbSTserialPort = wx.BoxSizer(wx.HORIZONTAL)
    hbSTserialPort.Add(wx.StaticText(panel, -1, 'Serial Port'), flag=wx.LEFT|wx.TOP, border=3)
    sbs.Add(hbSTserialPort)
    sbs.Add((-1, 2))

    hbTCserialPort = wx.BoxSizer(wx.HORIZONTAL)
    self.s_port = wx.TextCtrl(panel, -1, self.parent.c.s_port, size=(500,23))
    hbTCserialPort.Add(self.s_port, flag=wx.LEFT|wx.TOP, border=3)
    sbs.Add(hbTCserialPort)
    sbs.Add((-1, 15))

    # --


    panel.SetSizer(sbs)

    buttons = wx.BoxSizer(wx.HORIZONTAL)
    saveCloseButton = wx.Button(self, label='Save & Close')
    buttons.Add(saveCloseButton, flag=wx.LEFT, border=5)

    vbox.Add(panel, proportion=1, flag=wx.ALL|wx.EXPAND, border=5)
    vbox.Add(buttons, flag=wx.ALIGN_CENTER|wx.TOP|wx.BOTTOM, border=10)

    self.SetSizer(vbox)

    saveCloseButton.Bind(wx.EVT_BUTTON, self.onSave)


  def onSave(self, event):
    print "tjohei"


  def onClose(self, event):
    self.Destroy()


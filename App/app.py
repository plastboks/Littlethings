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
      
    self.TabPane1 = wx.Panel(self)
    self.column = wx.ScrolledWindow(self.TabPane1, -1, style=wx.TAB_TRAVERSAL)


    self.menu()
    self.properties()
    self.layout()
    
    self.demoMode(self)


  def menu(self):

    menuBar = wx.MenuBar()

    self.fileMenu = wx.Menu()
    configFileMenu = self.fileMenu.Append(wx.ID_NEW,    "Config\tCtrl-O", "Open Configuration")
    closeFileMenu = self.fileMenu.Append(wx.ID_CLOSE,  "Close\tCtrl-W")

    menuBar.Append(self.fileMenu, "File")
    self.SetMenuBar(menuBar)

    self.Bind(wx.EVT_TOOL, self.onConfig, configFileMenu)
    self.Bind(wx.EVT_TOOL, self.onClose, closeFileMenu)



  def properties(self):
      self.SetTitle("Tweeno")
      self.SetSize((300, 600))
      self.column.SetScrollRate(10, 10)

  def layout(self):
      wrapperSizer = wx.BoxSizer(wx.HORIZONTAL)
      columnSizer = wx.BoxSizer(wx.HORIZONTAL)
      columnSizer.Add(self.column, 1, wx.RIGHT|wx.EXPAND, 3)
      self.TabPane1.SetSizer(columnSizer)
      wrapperSizer.Add(self.TabPane1, 1, wx.EXPAND, 0)
      self.SetSizer(wrapperSizer)
      self.Layout()


  def demoMode(self, event):
      tweet = "WordPress hack: Easily get post content by ID http://t.co/0mpCWRxc"
      fromText = "Fromline"
      self.tweetGridSizer = wx.FlexGridSizer(82, 1, 0, 0)
      self.column.SetSizer(self.tweetGridSizer)
      self.tweetGridSizer.Add((1,5), 0, 0, 0)
      for i in range(10):
          self.newSizer = wx.FlexGridSizer(1, 2, 0, 5)
          self.tweetGridSizer.Add(self.newSizer)
          self.tweetPic = wx.StaticBitmap(self.column, -1)
          self.newSizer.Add(self.tweetPic)
          self.tweetBox = wx.TextCtrl(self.column, -1, tweet, style=wx.TE_MULTILINE|wx.TE_READONLY|wx.TE_RICH|wx.TE_WORDWRAP|wx.NO_BORDER, size=(200, 65))
          self.newSizer.Add(self.tweetBox)
          self.fromBox = wx.TextCtrl(self.column, -1, fromText, style=wx.TE_READONLY|wx.NO_BORDER, size=(240,-1))
          self.tweetGridSizer.Add(self.fromBox)
          self.myLine = wx.StaticLine(self.column, -1, size=(240,-1))
          self.tweetGridSizer.Add(self.myLine)
          self.tweetGridSizer.Add((1,5), 0, 0, 0)
      self.tweetGridSizer.Layout()
      self.column.FitInside()


  def onConfig(self, event): 
    configDlg = configDialog.Dialog(self, title='Config')
    configDlg.ShowModal()
    configDlg.Destroy()

  def onClose(self, event):
    self.Destroy()
    sys.exit()

if __name__ == "__main__":
  app = wx.PySimpleApp(0)
  #wx.InitAllImageHandlers()
  mainFrame = App(None, -1, "")
  app.SetTopWindow(mainFrame)
  mainFrame.Show()
  app.MainLoop()

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
import time

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
        self.column = wx.ScrolledWindow(self.TabPane1,
                                        -1,
                                        style=wx.TAB_TRAVERSAL
                                        )
        self.menu()
        self.properties()
        self.layout()
        self.tweetsDict()
        self.drawTweets(self)

    def menu(self):
        menuBar = wx.MenuBar()
        self.fileMenu = wx.Menu()
        configFileMenu = self.fileMenu.Append(wx.ID_NEW,
                                              "Config\tCtrl-O",
                                              "Open Configuration")
        closeFileMenu = self.fileMenu.Append(wx.ID_CLOSE,
                                             "Close\tCtrl-W")
        self.addMenu = wx.Menu()
        addSome = self.addMenu.Append(20, "Add", "Add Tweet")
        menuBar.Append(self.fileMenu, "File")
        menuBar.Append(self.addMenu, "Add")
        self.SetMenuBar(menuBar)
        self.Bind(wx.EVT_TOOL, self.onConfig, configFileMenu)
        self.Bind(wx.EVT_TOOL, self.onClose, closeFileMenu)
        self.Bind(wx.EVT_TOOL, self.drawTweets, addSome)

    def properties(self):
        self.SetTitle("Tweeno")
        self.SetSize((300, 600))
        self.SetMaxSize((300, 600))
        self.SetMinSize((300, 600))
        self.column.SetScrollRate(25, 25)

    def layout(self):
        columnSizer = wx.BoxSizer(wx.HORIZONTAL)
        columnSizer.Add(self.column, 1, wx.RIGHT | wx.EXPAND, 3)
        self.TabPane1.SetSizer(columnSizer)

        wrapperSizer = wx.BoxSizer(wx.HORIZONTAL)
        wrapperSizer.Add(self.TabPane1, 1, wx.EXPAND, 0)
        self.SetSizer(wrapperSizer)

        self.tweetGS = wx.BoxSizer(wx.VERTICAL)
        self.column.SetSizer(self.tweetGS)
        self.Layout()

    def tweetsDict(self):
        self.tweets = []

    def addTweet(self, event, tweet):
        newTweet = self.tweets.append(
            {
                "timestamp": str(time.time()),
                "pic": tweet["pic"],
                "text": tweet["text"],
                "from": tweet["from"],
            })
        return self.drawTweets(newTweet)

    def drawTweets(self, event):
        tweetText = "Heia"
        fromText = "God"

        for i in range(1, 5):
            # Sizer for the tweet
            self.newSizer = wx.BoxSizer(wx.VERTICAL)
            self.tweetGS.Add(self.newSizer)
            # Tweet picture
            self.pic = wx.BoxSizer(wx.VERTICAL)
            self.newSizer.Add(self.pic)
            # Tweet text
            for line in textwrap.wrap(tweetText, 40):
                tmp = wx.StaticText(self.column, -1, line)
                self.newSizer.Add(tmp, flag=wx.LEFT | wx.TOP, border=3)
            # Tweet byLine
            self.by = wx.StaticText(self.column, -1, str(time.time()))
            self.tweetGS.Add(self.by, flag=wx.LEFT | wx.TOP, border=3)
            # Tweet seperator
            self.myLine = wx.StaticLine(self.column, -1, size=(280, -1))
            self.tweetGS.Add(self.myLine)
            # Some padding
            self.tweetGS.Add((1, 5), 0, 0, 0)
            self.tweetGS.Layout()

        self.tweetGS.Layout()

    def onConfig(self, event):
        configDlg = configDialog.Dialog(self, title='Config')
        configDlg.ShowModal()
        configDlg.Destroy()

    def onClose(self, event):
        self.Destroy()
        sys.exit()

if __name__ == "__main__":
    app = wx.App()
    mainFrame = App(None)
    mainFrame.Show()
    app.MainLoop()

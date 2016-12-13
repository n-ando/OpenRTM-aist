#!/usr/bin/env python

import sys
sys.path.append("../../swig/python/")

import RTM

                
arg = ["-f", "./rtc.conf"]
mgr = RTM.RtcManager(arg)
mgr.initManager()
mgr.activateManager()

uuid = mgr.bindInOutByName("TkMotor0","pos","2ch_slider0","slider")
print uuid

mgr.runManager()

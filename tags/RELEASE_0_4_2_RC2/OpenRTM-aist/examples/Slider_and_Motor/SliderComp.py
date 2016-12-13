#!/usr/bin/env python

import sys
sys.path.append("../../swig/python/")

import RTM

import slider
import thread
import time

channels = (
        ("motor0", -360, 360, 0.1, 200),
        ("motor1", -360, 360, 0.1, 200),
        ("motor2", -360, 360, 0.1, 200),
        ("motor3", -360, 360, 0.1, 200),
        ("motor4", -360, 360, 0.1, 200),
        ("motor5", -360, 360, 0.1, 200))

mod_spec = { 
        RTM.RTC_MODULE_NAME:      "slider", 
        RTM.RTC_MODULE_DESC:      "slider component", 
        RTM.RTC_MODULE_VERSION:   "1.0", 
        RTM.RTC_MODULE_AUTHOR:    "Noriaki Ando", 
        RTM.RTC_MODULE_COMPANY:   "AIST: Japan", 
        RTM.RTC_MODULE_CATEGORY:  "Generic", 
        RTM.RTC_MODULE_COMP_TYPE: "COMMUTATIVE", 
        RTM.RTC_MODULE_ACT_TYPE:  "SPORADIC", 
        RTM.RTC_MODULE_MAX_INST:  "10", 
        RTM.RTC_MODULE_LANG:      "Python", 
        RTM.RTC_MODULE_LANG_TYPE: "SCRIPT",
        RTM.RTC_MODULE_SPEC_END:  ""
        }

sl = slider.SliderMulti(channels)
thread.start_new_thread(sl.mainloop, ())

class MyComponent(RTM.RtcBase):
        def __init__(self, mgr):
                RTM.RtcBase.__init__(self, mgr)
                self.outport = RTM.TimedFloatSeqOut("slider")
                return

        def rtc_init_entry(self):
                self.registerOutPort(self.outport)
                print "init"
                return 0
        
        def rtc_ready_do(self):
                print sl.get()
                time.sleep(1)
                return 0

        def rtc_active_do(self):
                self.outport.write(sl.get())
                time.sleep(0.01)
                return 0

        def rtc_active_exit(self):
                print "active exit"
                return 0
               
                
arg = ["-f", "./rtc.conf"]
mgr = RTM.RtcManager(arg)
mgr.initManager()
mgr.activateManager()
prof = RTM.RtcModuleProfile(mod_spec)
mgr.registerComponent((prof, MyComponent))
time.sleep(3)
s = mgr.create_component("slider", "Generic")
mgr.runManager()

#!/usr/bin/env python

import sys
sys.path.append("../../swig/python/")

import RTM

import tkmotor
import thread
import time


mod_spec = { 
	RTM.RTC_MODULE_NAME:      "TkMotor", 
	RTM.RTC_MODULE_DESC:      "Tk Motor component (position control)", 
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


tkm = tkmotor.TkMotor(6, 40)
thread.start_new_thread(tkm.mainloop, ())

class MyComponent(RTM.RtcBase):
	def __init__(self, mgr):
		try:
			RTM.RtcBase.__init__(self, mgr)
			self.inport = RTM.TimedFloatSeqIn("pos")
			self.registerInPort(self.inport)
			self.cnt = 0
			self.num = 6
		except:
			pass
		return
	
	def rtc_init_entry(self):
		try:
			print "init"

			time.sleep(0.1)
		except:
			pass
		return 0
	
	def rtc_ready_do(self):
		try:
			val = [self.cnt] * self.num
			tkm.set_angle(val)
			time.sleep(0.01)
			self.cnt= self.cnt + 1
			self.v = [0] * 6
		except:
			pass

		return 0
	
	def rtc_active_do(self):
		try:
			val = self.inport.read()
			if len(val.data) == 6:
				for i in range(6):
					self.v[i] = val.data[i]*10
				tkm.set_angle(self.v)

		except:
			pass
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
s = mgr.create_component("TkMotor", "Generic")
mgr.runManager()


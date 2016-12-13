#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  @file README_src.py
#  @brief rtc-template RTComponent's README & specification file generator class
#  @date $Date: 2005-05-12 09:06:18 $
#  @author Noriaki Ando <n-ando@aist.go.jp>
# 
#  Copyright (C) 2004-2005
#      Task-intelligence Research Group,
#      Intelligent Systems Research Institute,
#      National Institute of
#          Advanced Industrial Science and Technology (AIST), Japan
#      All rights reserved.
# 
#  $Id: README_src.py,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
# 

#
#  $Log: not supported by cvs2svn $
#

import re
import os
import time

class README_src:
	def __init__(self, fname, spec):
		self.fname = "README." + fname
		self.spec = spec
		self.version = os.popen("rtm-config --version", "r").read()
		
	def print_readme(self):
		if (not self.check_overwrite(self.fname)):
			return
		readme = file(self.fname, "w")

		print >> readme, """======================================================================
  RTComponent: %s specificatioin

  OpenRTM-%s
  Date: %s
======================================================================
""" % (self.spec["module-name"][1],
	   self.version,
	   time.asctime())
		
		print >> readme, """Module Name: %s
Description: %s
Version:     %s
Author:      %s
Category:    %s
Comp. Type:  %s
Act. Type:   %s
MAX Inst.:   %s
Lang:        %s
Lang Type:   %s
""" % (self.spec["module-name"][1],
	   self.spec["module-desc"][1],
	   self.spec["module-version"][1],
	   self.spec["module-author"][1],
	   self.spec["module-category"][1],
	   self.spec["module-comp-type"][1],
	   self.spec["module-act-type"][1],
	   self.spec["module-max-inst"][1],
	   self.spec["module-lang"][1],
	   self.spec["module-lang"][1])


		print >> readme, """======================================================================"""
		print >> readme, """    Activity definition"""
		print >> readme, """======================================================================"""

		print >> readme, """
[Initializing]

[Ready]
	[Entry]
	[Do]
	[Exit]

[Starting]

[Active]
	[Entry]
	[Do]
	[Exit]

[Stopping]

[Error]
	[Entry]
	[Do]
	[Exit]


[Fatal Error]
	[Entry]
	[Do]
	[Exit]

[Exiting]

"""

		print >> readme, """======================================================================"""
		print >> readme, """    InPorts definition"""
		print >> readme, """======================================================================"""
		i = 0
		for inpname in self.spec["module-inport"][1]:
			inp = self.spec["module-inport"][1][inpname]
			print >> readme, """[InPort]
	Name:        %s
	PortNumber:  %d
	Description:
	PortType: 
	DataType:    %s
	MaxOut: 
	[Data Elements]
		Number:
		Name:
		Type:
		Unit:
		RangeLow:
		RangeHigh:
		DefaultValue:

		""" % (inpname, i, inp)
			i += 1

		print >> readme, """======================================================================"""
		print >> readme, """    OutPorts definition"""
		print >> readme, """======================================================================"""
		i = 0
		for outpname in self.spec["module-outport"][1]:
			outp = self.spec["module-outport"][1][outpname]
			print >> readme, """[OutPort]
	Name:        %s
	PortNumber:  %d
	Description:
	PortType: 
	DataType:    %s
	MaxOut: 
	[Data Elements]
		Number:
		Name:
		Type:
		Unit:
		RangeLow:
		RangeHigh:
		DefaultValue:

		""" % (inpname, i, inp)
			i += 1

		print >> readme, """======================================================================"""
		print >> readme, """    Configuration definition"""
		print >> readme, """======================================================================"""
		print >> readme, """This area is reserved for future OpenRTM."""
		
		print self.fname, "was generated"

	def check_overwrite(self, fname):
		if (os.access(fname, os.F_OK)):
			ans = raw_input("\"" + fname + "\" already exists. Overwrite? (y/n) ")
			if (ans == "y" or ans == "Y"):
				return True
			else:
				return False
		else:
			return True

def main():
	module_spec = {"module-name":["RTC_MODULE_NAME","Hoge"],
			   "module-desc":["RTC_MODULE_DESC","Hoge component"],
			   "module-version":["RTC_MODULE_VERSION","0.1"],
			   "module-author":["RTC_MODULE_AUTHOR","Hoge"],
			   "module-category":["RTC_MODULE_CATEGORY","Generic"],
			   "module-comp-type":["RTC_MODULE_COMP_TYPE","COMMUTATIVE"],
			   "module-act-type":["RTC_MODULE_ACT_TYPE","SPORADIC"],
			   "module-max-inst":["RTC_MODULE_MAX_INST","10"],
			   "module-lang":["RTC_MODULE_LANG","C++"],
			   "module-inport":["", {"Ref":"TimedFloat", \
									"Sens":"TimedDouble"}],
			   "module-outport":["", {"Ctrl":"TimedFloat", \
									 "Monitor":"TimedShort"}]
			   }

	readme = README_src("HogeTest", module_spec)
	readme.print_readme()


if __name__ == "__main__":
	main()

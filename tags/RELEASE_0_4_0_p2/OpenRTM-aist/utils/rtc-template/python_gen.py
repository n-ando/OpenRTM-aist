#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  @file Py_src.py
#  @brief rtc-template Python soruce code generator class
#  @date $Date: 2005-08-26 12:02:37 $
#  @author Noriaki Ando <n-ando@aist.go.jp>
# 
#  Copyright (C) 2004-2005
#      Task-intelligence Research Group,
#      Intelligent Systems Research Institute,
#      National Institute of
#          Advanced Industrial Science and Technology (AIST), Japan
#      All rights reserved.
# 
#  $Id: python_gen.py,v 1.1 2005-08-26 12:02:37 n-ando Exp $
# 

#
#  $Log: not supported by cvs2svn $
#  Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
#  Public release.
#
#

import re
import os
import ezt
import gen_base

def description():
	return "Python component code generator"

def usage():
	"""
	C++ generator specific usage
	"""
	return """
----------------------------------
  Help for Python code generator
----------------------------------
Python code generator generates the following files.
    [Component name].py............Component class and executable
    README.[Component name]........Specification template of the component

No additional options are available for Python code generator.

"""

def get_opt_fmt():
	return []

#------------------------------------------------------------
# Python component source code template
#------------------------------------------------------------
py_source = """#!/usr/bin/env python
# -*- Python -*-

import sys
import time
sys.path.append(".")

# Inport RTM module
import RTM

# This module's spesification
mod_spec = { 
        RTM.RTC_MODULE_NAME:      "[module.name]", 
        RTM.RTC_MODULE_DESC:      "[module.desc]", 
        RTM.RTC_MODULE_VERSION:   "[module.version]", 
        RTM.RTC_MODULE_AUTHOR:    "[module.author]", 
        RTM.RTC_MODULE_COMPANY:   "[module.author]", 
        RTM.RTC_MODULE_CATEGORY:  "[module.category]", 
        RTM.RTC_MODULE_COMP_TYPE: "[module.comp_type]", 
        RTM.RTC_MODULE_ACT_TYPE:  "[module.act_type]", 
        RTM.RTC_MODULE_MAX_INST:  "[module.max_inst]", 
        RTM.RTC_MODULE_LANG:      "Python", 
        RTM.RTC_MODULE_LANG_TYPE: "SCRIPT",
        RTM.RTC_MODULE_SPEC_END:  " "
        }

class [module.name](RTM.RtcBase):
	def __init__(self, mgr):
		try:
			RTM.RtcBase.__init__(self, mgr)
			
			[for inport]self.[inport.name] = RTM.[inport.type]In("[inport.name]")
			[end][for outport]self.[outport.name] = RTM.[outport.type]Out("[outport.name]")
			[end]
			[for inport]self.registerInPort(self.[inport.name])
			[end][for outport]self.registerOutPort(self.[outport.name])
			[end]
		except:
			pass
		return

	[for activity]
	#def [activity](self):
	#	try:
	#		# do something
	#		pass
	#	except:
	#		pass
	#	return 0
	[end]


def main():
	arg = ["-f", "./rtc.conf"]
	mgr = RTM.RtcManager(arg)
	mgr.initManager()
	mgr.activateManager()
	prof = RTM.RtcModuleProfile(mod_spec)
	mgr.registerComponent((prof, [module.name]))
	time.sleep(3)
	s = mgr.create_component("[module.name]", "[module.category]")
	mgr.runManager()

if __name__ == "__main__":
	main()
"""



class python_gen(gen_base.gen_base):
	"""
	Python component source code generation class
	"""
	def __init__(self, data, opts):
		self.data = data.copy()
		self.data['fname_py'] = self.data['fname'] + ".py"
		self.data["activity"] = [\
						   "rtc_init_entry",\
						   "rtc_ready_entry",\
						   "rtc_ready_do",\
						   "rtc_ready_exit",\
						   "rtc_starting_entry",\
						   "rtc_active_entry",\
						   "rtc_active_do",\
						   "rtc_active_exit",\
						   "rtc_stopping_entry",\
						   "rtc_aborting_entry",\
						   "rtc_error_entry",\
						   "rtc_error_do",\
						   "rtc_error_exit",\
						   "rtc_fatal_entry",\
						   "rtc_fatal_do",\
						   "rtc_fatal_exit",\
						   "rtc_exiting_entry"]
		return


	def print_pysrc(self):
		"""
		Generate component class script
		"""
		f = self.check_overwrite(self.data["fname_py"])
		if (not f):
			return
		t = ezt.Template(compress_whitespace = 0)
		t.parse(py_source)
		t.generate(f, self.data)
		print self.data["fname_py"], " was generated."
		return


	def print_all(self):
		self.print_pysrc()
		return

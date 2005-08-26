#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  @file cxx_gen.py
#  @brief rtc-template C++ source code generator class
#  @date $Date: 2005-08-26 12:02:14 $
#  @author Noriaki Ando <n-ando@aist.go.jp>
# 
#  Copyright (C) 2004-2005
#      Task-intelligence Research Group,
#      Intelligent Systems Research Institute,
#      National Institute of
#          Advanced Industrial Science and Technology (AIST), Japan
#      All rights reserved.
# 
#  $Id: cxx_gen.py,v 1.1 2005-08-26 12:02:14 n-ando Exp $
# 

#
#  $Log: not supported by cvs2svn $
#  Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
#  Public release.
#
#

import re
import os
import sys
import ezt
import gen_base

def description():
	return "C++ component code generator"

def usage():
	"""
	C++ generator specific usage
	"""
	return """
-------------------------------
  Help for C++ code geenrator
-------------------------------
C++ code generator generates the following files.
    [Component name].h.............Component class header
    [Component name].cpp...........Component class soruce code
    [Component name]Comp.cpp.......Component startup code
    Makefile.[Component name]......Makefile to compile this codes
    README.[Component name]........Specification template of the component

No additional options are available for C++ code generator.

"""

def get_opt_fmt():
	return []

	
#------------------------------------------------------------
# Component header template code
#------------------------------------------------------------
comp_header = """// -*- C++ -*-
/*!
 * @file  [fname_h]
 * @brief [module.desc]
 * @date  [rcs_date]
 *
 * [rcs_id]
 */

#ifndef [u_name]_H
#define [u_name]_H

#include <rtm/RtcBase.h>
#include <rtm/RtcManager.h>
#include <rtm/RtcInPort.h>
#include <rtm/RtcOutPort.h>

using namespace RTM;

static RtcModuleProfSpec [l_name]_spec[] =
  {
    {RTC_MODULE_NAME,      "[module.name]"},
    {RTC_MODULE_DESC,      "[module.desc]"},
    {RTC_MODULE_VERSION,   "[module.version]"},
    {RTC_MODULE_AUTHOR,    "[module.author]"},
    {RTC_MODULE_CATEGORY,  "[module.category]"},
    {RTC_MODULE_COMP_TYPE, "[module.comp_type]"},
    {RTC_MODULE_ACT_TYPE,  "[module.act_type]"},
    {RTC_MODULE_MAX_INST,  "[module.max_inst]"},
    {RTC_MODULE_LANG,      "C++"},
    {RTC_MODULE_LANG_TYPE, "COMPILE"},
    {RTC_MODULE_SPEC_END,  NULL}
  };

	
class [module.name]
  : public RTM::RtcBase
{
 public:
  [module.name](RtcManager* manager);

  // Initializing state
  //  virtual RtmRes rtc_init_entry();

  // Ready state
  //  virtual RtmRes rtc_ready_entry();
  //  virtual RtmRes rtc_ready_do();
  //  virtual RtmRes rtc_ready_exit();

  // Starting state
  //  virtual RtmRes rtc_starting_entry();
  
  // Active state
  //  virtual RtmRes rtc_active_entry();
  //  virtual RtmRes rtc_active_do();
  //  virtual RtmRes rtc_active_exit();

  // Stopping state
  //  virtual RtmRes rtc_stopping_entry();

  // Aborting state
  //  virtual RtmRes rtc_aborting_entry();
  
  // Error state
  //  virtual RtmRes rtc_error_entry();
  //  virtual RtmRes rtc_error_do();
  //  virtual RtmRes rtc_error_exit();

  // Fatal Error state
  //  virtual RtmRes rtc_fatal_entry();
  //  virtual RtmRes rtc_fatal_do();
  //  virtual RtmRes rtc_fatal_exit();
  
  // Exiting state
  //  virtual RtmRes rtc_exiting_entry();

  // InPort definition
  [for inport][inport.type] m_[inport.name];
  InPortAny<[inport.type]> m_[inport.name]In;
  [end]

  // OutPort definition
  [for outport][outport.type] m_[outport.name];
  OutPortAny<[outport.type]> m_[outport.name]Out;
  [end]

};


extern "C"
{
  RtcBase* [module.name]New(RtcManager* manager);
  void [module.name]Delete(RtcBase* p);
  void [module.name]Init(RtcManager* manager);
};

#endif // [u_name]_H
"""


#------------------------------------------------------------
# Component source template code
#------------------------------------------------------------
comp_soruce = """// -*- C++ -*-
/*!
 * @file  [fname_cpp]
 * @brief [module.desc]
 * [rcs_date]
 *
 * [rcs_id]
 */

#include "[fname_h]"

using namespace std;

[module.name]::[module.name](RtcManager* manager)
  : RtcBase(manager),
    [for inport]m_[inport.name]In("[inport.name]", m_[inport.name])[if-index inport last][if-any outport],[else][end][else],[end]
    [end][for outport]m_[outport.name]Out("[outport.name]", m_[outport.name])[if-index outport last][else],[end]
    [end]
{
  [for inport]registerInPort(m_[inport.name]In);
  [end][for outport]registerOutPort(m_[outport.name]Out);
  [end]
}


[for activity]
/*
RtmRes [module.name]::[activity]()
{
  return RTM_OK;
}
*/
[end]


extern "C"
{
 
  RtcBase* [module.name]New(RtcManager* manager)
  {
	return new [module.name](manager);
  }
  
  
  void [module.name]Delete(RtcBase* p)
  {
	delete ([module.name] *)p;
	return;
  }
  
  
  void [module.name]Init(RtcManager* manager)
  {
	RtcModuleProfile profile([l_name]_spec);
	manager->registerComponent(profile, [module.name]New, [module.name]Delete);
  }
  
};


"""


#------------------------------------------------------------
# Component soruce template
#------------------------------------------------------------
comp_compsrc = """// -*- C++ -*-
/*!
 * @file [module.name]Comp.cpp
 * @brief Standalone component
 * @date [rcs_date]
 *
 * [rcs_id]
 */

#include <rtm/RtcManager.h>
#include <iostream>
#include <string>
#include "[fname_h]"


void MyModuleInit(RtcManager* manager)
{
  [module.name]Init(manager);

  std::string name;
  RtcBase* comp;
  comp = manager->createComponent("[module.name]", "[module.category]", name);

  std::cout << "RTComponent: " << name << " was created." << std::endl;

  return;
}

int main (int argc, char** argv)
{
  RTM::RtcManager manager(argc, argv);
  // Initialize manager
  manager.initManager();
  // Activate manager and register to naming service
  manager.activateManager();
  // Initialize my module on this maneger
  manager.initModuleProc(MyModuleInit);
  // Main loop
  manager.runManager();
  return 0;
}
"""


#------------------------------------------------------------
# Makefile template
#------------------------------------------------------------
makefile = """
# -*- Makefile -*-

CXXFLAGS = `rtm-config --cflags`
LDFLAGS  = `rtm-config --libs`
SHFLAGS  = -shared
.SUFFIXES: .cpp .o .so

all: [module.name]Comp [module.name].so

.cpp.o:
\trm -f $@
\t$(CXX) $(CXXFLAGS) -c -o $@ $<

.o.so:
\trm -f $@
\t$(CXX) $(SHFLAGS) -o $@ $< $(LDFLAGS)

[module.name]Comp: [module.name].o [module.name]Comp.o
\t$(CXX) -o $@ [module.name].o [module.name]Comp.o $(LDFLAGS) 

clean:
\trm -f *~ *.o *.so *Comp

"""




class cxx_gen(gen_base.gen_base):
	"""
	C++ component source code generator
	"""
	def __init__(self, data, opts):
		self.data = data.copy()
		self.data["rcs_date"] = "$" + "Date" + "$"
		self.data["rcs_id"] = "$" + "Id" + "$"
		self.data["fname_h"] = self.data["fname"] + ".h"
		self.data["fname_cpp"] = self.data["fname"] + ".cpp"
		self.data["fname_comp"] = self.data["fname"] + "Comp.cpp"
		self.data["makefile"] = "Makefile." + self.data["fname"]
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
		self.data["u_name"] = self.data["module"].name.upper()
		self.data["l_name"] = self.data["module"].name.lower()
		return


#	def check_overwrite(self, fname):
#		"""
#		Check file exist or not.
#		"""
#		msg = " already exists. Overwrite? (y/n)"
#		if (os.access(fname, os.F_OK)):
#			ans = raw_input("\"" + fname + "\"" + msg)
#			if (ans == "y" or ans == "Y"):
#				return file(fname, "w")
#			else:
#				return None
#		else:
#			return file(fname, "w")
#		return


	def print_header(self):
		"""
		Generate component class header
		"""
		f = self.check_overwrite(self.data["fname_h"])
		if (not f):
			return
		t = ezt.Template(compress_whitespace = 0)
		t.parse(comp_header)
		t.generate(f, self.data)
		print self.data["fname_h"], " was generated."
		return


	def print_source(self):
		"""
		Generate component class source code
		"""
		f = self.check_overwrite(self.data["fname_cpp"])
		if (not f):
			return
		t = ezt.Template(compress_whitespace = 0)
		t.parse(comp_soruce)
		t.generate(f, self.data)
		print self.data["fname_cpp"], " was generated."
		return


	def print_compsrc(self):
		"""
		Generate component source code
		"""
		f = self.check_overwrite(self.data["fname_comp"])
		if (not f):
			return
		t = ezt.Template(compress_whitespace = 0)
		t.parse(comp_compsrc)
		t.generate(f, self.data)
		print self.data["fname_comp"], " was generated."
		return


	def print_makefile(self):
		"""
		Generate Makefile
		"""
		f = self.check_overwrite(self.data["makefile"])
		if (not f):
			return
		t = ezt.Template(compress_whitespace = 0)
		t.parse(makefile)
		t.generate(f, self.data)
		print self.data["makefile"], " was generated."
		return


	def print_all(self):
		self.print_header()
		self.print_source()
		self.print_compsrc()
		self.print_makefile()
		return


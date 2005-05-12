#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  @file CXX_src.py
#  @brief rtc-template C++ source code generator class
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
#  $Id: CXX_src.py,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
# 

#
#  $Log: not supported by cvs2svn $
#

import re
import os

class CXX_src:
	def __init__(self, fname, spec):
		self.fname = fname
		self.fname_h = fname + ".h"
		self.fname_cpp = fname + ".cpp"
		
		self.spec = spec
		_name = re.sub("\.", "_", self.spec["module-name"][1])
		self.include_guard = "__" + _name.upper() + "_h__"
		self.lcase_name = self.spec["module-name"][1].lower()
		self.state_funcs = (
			"rtc_init_entry",
			"rtc_ready_entry",
			"rtc_ready_do",
			"rtc_ready_exit",
			"rtc_starting_entry",
			"rtc_active_entry",
			"rtc_active_do",
			"rtc_active_exit",
			"rtc_stopping_entry",
			"rtc_aborting_entry",
			"rtc_error_entry",
			"rtc_error_do",
			"rtc_error_exit",
			"rtc_fatal_entry",
			"rtc_fatal_do",
			"rtc_fatal_exit",
			"rtc_exiting_entry")

	def print_header(self):
		if (not self.check_overwrite(self.fname_h)):
			return
		header = file(self.fname_h, "w")
		print >> header, """// -*- C++ -*-
/*!
 * @file %s
 * @brief %s
 * @date $Date: 2005-05-12 09:06:18 $
 *
 * $Id: CXX_src.py,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 */

#ifndef %s
#define %s
""" % (self.fname_h, self.spec["module-desc"][1], 
		self.include_guard, self.include_guard)

		print >> header, """
#include <rtm/RtcBase.h>
#include <rtm/RtcManager.h>
#include <rtm/RtcInPort.h>
#include <rtm/RtcOutPort.h>

using namespace RTM;

static RtcModuleProfSpec %s_spec[] =
  {
  """ % self.lcase_name

		spec_list = ("module-name", "module-desc", "module-version",
					 "module-author", "module-category", "module-comp-type",
					 "module-act-type", "module-max-inst")
		for key in spec_list:
			print >> header, "  {%s, \"%s\"}," % \
				  (self.spec[key][0], self.spec[key][1])

		# End of module spec
		print >> header, """  {RTC_MODULE_LANG, "C++"},
  {RTC_MODULE_LANG_TYPE, "COMPILE"},
  {RTC_MODULE_SPEC_END, NULL}
  };
"""
		# class definition
		print >> header, """
	
class %s
  : public RTM::RtcBase
{
 public:
  %s(RtcManager* manager);

  // [Initializing state]
  //  virtual RtmRes rtc_init_entry();

  // [Ready state]
  //  virtual RtmRes rtc_ready_entry();
  //  virtual RtmRes rtc_ready_do();
  //  virtual RtmRes rtc_ready_exit();

  // [Starting state]
  //  virtual RtmRes rtc_starting_entry();
  
  // [Active state]
  //  virtual RtmRes rtc_active_entry();
  //  virtual RtmRes rtc_active_do();
  //  virtual RtmRes rtc_active_exit();

  // [Stopping state]
  //  virtual RtmRes rtc_stopping_entry();

  // [Aborting state]
  //  virtual RtmRes rtc_aborting_entry();
  
  // [Error state]
  //  virtual RtmRes rtc_error_entry();
  //  virtual RtmRes rtc_error_do();
  //  virtual RtmRes rtc_error_exit();

  // [Fatal Error state]
  //  virtual RtmRes rtc_fatal_entry();
  //  virtual RtmRes rtc_fatal_do();
  //  virtual RtmRes rtc_fatal_exit();
  
  // [Exiting state]
  //  virtual RtmRes rtc_exiting_entry();
""" % (self.spec["module-name"][1], self.spec["module-name"][1])


		# print >> header, InPort and OutPort definition
		for inpname in self.spec["module-inport"][1]:
			inp = self.spec["module-inport"][1][inpname]
			print >> header, "  %s m_%s;" % (inp, inpname)
			print >> header, "  InPortAny<%s> m_%sIn;" % (inp, inpname)
		for outpname in self.spec["module-outport"][1]:
			outp = self.spec["module-outport"][1][outpname]
			print >> header, "  %s m_%s;" % (outp, outpname)
			print >> header, "  OutPortAny<%s> m_%sOut;" % (outp, outpname)
		print >> header, """
};
"""
		# print shared object export functions
		print >> header, """
extern "C" {
  RtcBase* %sNew(RtcManager* manager);
  void %sDelete(RtcBase* p);
  void %sInit(RtcManager* manager);
};
#endif // %s
""" % (self.spec["module-name"][1],
		self.spec["module-name"][1],
		self.spec["module-name"][1],
		self.include_guard)

		header.close()
		print self.fname_h, "was generated."


	def print_source(self):
		if (not self.check_overwrite(self.fname_cpp)):
			return
		source = file(self.fname_cpp, "w")
		# print beginning part of source
		print >> source, """// -*- C++ -*-
/*!
 * @file %s
 * @brief %s
 * @date $Date: 2005-05-12 09:06:18 $
 *
 * $Id: CXX_src.py,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 */

""" % (self.fname_cpp, self.spec["module-desc"][1]) 

		# print include directive and class constructor
		print >> source, """
#include "%s"

using namespace std;

%s::%s(RtcManager* manager)""" % (self.fname_h,
self.spec["module-name"][1],
self.spec["module-name"][1])


		# print InPort and OutPort initializer
		inp_num = len(self.spec["module-inport"][1])
		outp_num = len(self.spec["module-outport"][1])

		print >> source, "  : RtcBase(manager)",
		if inp_num != 0 or outp_num != 0:
			print >> source, ","

		# InPort initializer
		inp_init = ""
		for inpname in self.spec["module-inport"][1]:
			inp = self.spec["module-inport"][1][inpname]
			inp_init = inp_init + "    m_%sIn(\"%s\", m_%s),\n" % \
					  (inpname, inpname, inpname) 
		if outp_num == 0: 
			inp_init = inp_init[0:(len(inp_init) - 2)]
			print >> source, inp_init
		else:
			print >> source, inp_init,

		# OutPort initializer
		outp_init = ""
		for outpname in self.spec["module-outport"][1]:
			outp = self.spec["module-outport"][1][outpname]
			outp_init = outp_init + "    m_%sOut(\"%s\", m_%s),\n" % \
				  (outpname, outpname, outpname) 

		outp_init = outp_init[0:(len(outp_init) - 2)]
		print >> source, outp_init

		# begeinning of constructor
		print >> source, "{"

		# InPort registration
		for inpname in self.spec["module-inport"][1]:
			print >> source, "  registerInPort(m_%sIn);" % inpname

		# OutPort initializer
		for outpname in self.spec["module-outport"][1]:
			print >> source, "  registerOutPort(m_%sOut);" % outpname


		# end of constructor
		print >> source, "}"

		for funcname in self.state_funcs:
			# beginning of rtc_active_do()
			print >> source, """
/*
RtmRes %s::%s()
{
  return RTM_OK;
}
*/

""" % (self.spec["module-name"][1], funcname)
			

		print >> source, """
extern "C" {
  
  RtcBase* %sNew(RtcManager* manager)
  {
	return new %s(manager);
  }
  
  
  void %sDelete(RtcBase* p)
  {
	delete (%s *)p;
	return;
  }
  
  
  void %sInit(RtcManager* manager)
  {
	RtcModuleProfile profile(%s_spec);
	manager->registerComponent(profile, %sNew, %sDelete);
  }
};
""" % (self.spec["module-name"][1],
		self.spec["module-name"][1],
		self.spec["module-name"][1],
		self.spec["module-name"][1],
		self.spec["module-name"][1],
		self.lcase_name,
		self.spec["module-name"][1],
		self.spec["module-name"][1])

		source.close()
		print self.fname_cpp, "was generated."

	def print_compsrc(self):
		compfname = self.fname + "Comp.cpp"
		if (not self.check_overwrite(compfname)):
			return
		compsrc = file(compfname, "w")
		
		print >> compsrc, """// -*- C++ -*-
/*!
 * @file %sComp.h
 * @brief %s
 * @date $Date: 2005-05-12 09:06:18 $
 *
 * $Id: CXX_src.py,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 */

""" % (self.fname, self.spec["module-desc"][1]) 

		print >> compsrc, """
#include <rtm/RtcManager.h>
#include <iostream>
#include <string>
#include "%s"


void MyModuleInit(RtcManager* manager)
{
  %sInit(manager);

  std::string name;
  RtcBase* comp;
  comp = manager->createComponent("%s", "%s", name);

  std::cout << "RTComponent: " << name << " was created." << std::endl;

  return;
}
""" % (self.fname_h,
self.spec["module-name"][1],
self.spec["module-name"][1],
self.spec["module-category"][1])


		print >> compsrc, """
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
		compsrc.close()
		print compfname, "was generated."


	def print_makefile(self):
		mkname = "Makefile." + self.fname
		if (not self.check_overwrite(mkname)):
			return
		makefile = file(mkname, "w")

		print >> makefile, """# -*- Makefile -*-

CXXFLAGS = `rtm-config --cflags`
LDFLAGS  = `rtm-config --libs`
SHFLAGS  = -shared
.SUFFIXES: .cpp .o .so

all: %sComp %s.so

.cpp.o:
\trm -f $@
\t$(CXX) $(CXXFLAGS) -c -o $@ $<

.o.so:
\trm -f $@
\t$(CXX) $(SHFLAGS) -o $@ $< $(LDFLAGS)

%sComp: %s.o %sComp.o
\t$(CXX) -o $@ %s.o %sComp.o $(LDFLAGS) 

clean:
\trm -f *~ *.o *.so *Comp

""" %  (self.fname,
		self.fname,
		self.fname,
		self.fname,
		self.fname,
		self.fname,
		self.fname)

		makefile.close()
		print mkname, "was generated."

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

	cxx = CXX_src("HogeTest", module_spec)
	cxx.print_header()
	cxx.print_source()
	cxx.print_compsrc()
	cxx.print_makefile()


if __name__ == "__main__":
	main()

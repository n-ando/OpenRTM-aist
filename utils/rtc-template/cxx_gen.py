#!/usr/bin/env python
# -*- python -*-
#
#  @file cxx_gen.py
#  @brief rtc-template C++ source code generator class
#  @date $Date: 2005-09-06 14:37:03 $
#  @author Noriaki Ando <n-ando@aist.go.jp>
# 
#  Copyright (C) 2004-2005
#      Task-intelligence Research Group,
#      Intelligent Systems Research Institute,
#      National Institute of
#          Advanced Industrial Science and Technology (AIST), Japan
#      All rights reserved.
# 
#  $Id: cxx_gen.py,v 1.2 2005-09-06 14:37:03 n-ando Exp $
# 

#
#  $Log: not supported by cvs2svn $
#  Revision 1.1  2005/08/26 12:02:14  n-ando
#  This code generator module uses ezt (Easy Template).
#
#  Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
#  Public release.
#
#

import re
import os
import sys
import ezt
import gen_base
import cxx_svc_impl

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

// Service implementation headers
// <rtc-template block="service_impl_h">
// </rtc-template>

using namespace RTM;

// Module specification
// <rtc-template block="module_spec">
// </rtc-template>
	
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


 protected:
  // InPort declaration
  // <rtc-template block="inport_declar">
  // </rtc-template>


  // OutPort declaration
  // <rtc-template block="outport_declar">
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declar">
  // </rtc-template>


 private:
  int dummy;

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
    // <rtc-template block="initializer">
    // </rtc-template>
	dummy(0)
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // </rtc-template>

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
makefile = """# -*- Makefile -*-
#
# @file  Makefile.[module.name]
# @brief RTComponent makefile for "[module.name] component"
# @date  [rcs_date]
#
# This file is generated by rtc-template with the following argments.
#
[for fmtd_args]#  [fmtd_args]
[end]#
#
# [rcs_id]
#
CXXFLAGS = `rtm-config --cflags`
LDFLAGS  = `rtm-config --libs`
SHFLAGS  = -shared

IDLC     = `rtm-config --idlc`
IDLFLAGS = `rtm-config --idlflags` -I`rtm-config --prefix`/include/rtm/idl
WRAPPER  = ./rtm-skelwrapper
WRAPPER_FLAGS = --include-dir="" --skel-suffix=Skel --stub-suffix=Stub

SKEL_OBJ = [for service_idl][service_idl.skel_basename].o[end]
STUB_OBJ = [for service_idl][service_idl.stub_basename].o[end]
IMPL_OBJ = [for service_idl][service_idl.impl_basename].o[end]
OBJS     = [module.name].o $(SKEL_OBJ) $(IMPL_OBJ)

.SUFFIXES : .so

all: [module.name].so [module.name]Comp


.cpp.o:
	rm -f $@
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.o.so:
	rm -f $@
	$(CXX) $(SHFLAGS) -o $@ $(OBJS) $(LDFLAGS)

[module.name]Comp: [module.name]Comp.o $(OBJS)
	$(CXX) -o $@ $(OBJS) [module.name]Comp.o $(LDFLAGS) 


clean: clean_objs clean_skelstub
	rm -f *~

clean_objs:
	rm -f $(OBJS) [module.name].so [module.name]Comp

clean_skelstub:
	rm -f *[skel_suffix].h *[skel_suffix].cpp
	rm -f *[stub_suffix].h *[stub_suffix].cpp



[for service_idl]
[service_idl.skel_basename].cpp : [service_idl.idl_fname]
	$(IDLC) $(IDLFLAGS) [service_idl.idl_fname]
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=[service_idl.idl_fname]
[service_idl.skel_basename].h : [service_idl.idl_fname]
	$(IDLC) $(IDLFLAGS) [service_idl.idl_fname]
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=[service_idl.idl_fname]
[service_idl.stub_basename].cpp : [service_idl.idl_fname]
	$(IDLC) $(IDLFLAGS) [service_idl.idl_fname]
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=[service_idl.idl_fname]
[service_idl.stub_basename].h : [service_idl.idl_fname]
	$(IDLC) $(IDLFLAGS) [service_idl.idl_fname]
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=[service_idl.idl_fname]
[end]


[module.name].so: $(OBJS)
[module.name].o: [for service_idl][service_idl.skel_basename].h [service_idl.impl_basename].h[end]
[module.name]Comp.o: [module.name]Comp.cpp [module.name].cpp [module.name].h [for service_idl][service_idl.skel_basename].h [service_idl.impl_basename].h[end]

[for service_idl]
[service_idl.impl_basename].o: [service_idl.impl_basename].cpp [service_idl.impl_basename].h [service_idl.skel_basename].h [service_idl.stub_basename].h
[service_idl.skel_basename].o: [service_idl.skel_basename].cpp [service_idl.skel_basename].h [service_idl.stub_basename].h
[service_idl.stub_basename].o: [service_idl.stub_basename].cpp [service_idl.stub_basename].h
[end]

# end of Makefile
"""


#============================================================
# Replaced strings definition for <rtc-template> tags
#============================================================
service_impl_h = """[for service_idl]#include "[service_idl.impl_h]"[end]"""

module_spec = """static RtcModuleProfSpec [l_name]_spec[] =
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
  };"""

inport_declar = \
"""  [for inport][inport.type] m_[inport.name];
  InPortAny<[inport.type]> m_[inport.name]In;
  [end]"""

outport_declar = \
"""  [for outport][outport.type] m_[outport.name];
  OutPortAny<[outport.type]> m_[outport.name]Out;
  [end]"""

service_declar = \
"""  [for service][service.class_impl] m_[service.name];
  RtcServiceProfile m_[service.profile];
  [end]"""

initializer = \
"""    [for inport]m_[inport.name]In("[inport.name]", m_[inport.name]),
    [end][for outport]m_[outport.name]Out("[outport.name]", m_[outport.name]),
    [end][for service]m_[service.profile]("[service.name]", "[service.type]", ""),[end]"""


registration = \
"""  [for inport]registerInPort(m_[inport.name]In);
  [end][for outport]registerOutPort(m_[outport.name]Out);
  [end][for service]registerService(m_[service.name], m_[service.profile]);[end]"""



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
		self.data["impl_suffix"] = self.data["service_idl"][0].impl_suffix
		self.data["skel_suffix"] = self.data["service_idl"][0].skel_suffix
		self.data["stub_suffix"] = self.data["service_idl"][0].stub_suffix

		self.tags = {}
		self.tags["service_impl_h"] = service_impl_h
		self.tags["module_spec"]    = module_spec
		self.tags["inport_declar"]  = inport_declar
		self.tags["outport_declar"] = outport_declar
		self.tags["service_declar"] = service_declar
		self.tags["initializer"]    = initializer
		self.tags["registration"]   = registration
		return


	def print_header(self):
		"""
		Generate component class header
		"""
		f, lines = self.check_overwrite(self.data["fname_h"])
		if not f:  # overwrite: No
			return

		if not lines:  # overwrite: Yes
			temp_txt = comp_header.splitlines()
		else:      # overwrite: Merge mode
			temp_txt = lines

		# replace tags
		temp_txt = self.replace_tags(temp_txt, self.tags)			

		t = ezt.Template(compress_whitespace = 0)
		t.parse(temp_txt)
		t.generate(f, self.data)
		print self.data["fname_h"], " was generated."
		return


	def print_source(self):
		"""
		Generate component class source code
		"""
		f, lines = self.check_overwrite(self.data["fname_cpp"])
		if not f:  # overwrite: No
			return

		if not lines:  # overwrite: Yes
			temp_txt = comp_soruce.splitlines()
		else:      # overwrite: Merge mode
			temp_txt = lines

		# replace tags
		temp_txt = self.replace_tags(temp_txt, self.tags)
		
		t = ezt.Template(compress_whitespace = 0)
		t.parse(temp_txt)
		t.generate(f, self.data)
		print self.data["fname_cpp"], " was generated."
		return


	def print_compsrc(self):
		"""
		Generate component source code
		"""
		f, lines = self.check_overwrite(self.data["fname_comp"])
		if not f:  # overwrite: No
			return

		if not lines:  # overwrite: Yes
			temp_txt = comp_compsrc.splitlines()
		else:      # overwrite: Merge mode
			temp_txt = lines

		# replace tags
		temp_txt = self.replace_tags(temp_txt, self.tags)

		t = ezt.Template(compress_whitespace = 0)
		t.parse(temp_txt)
		t.generate(f, self.data)
		print self.data["fname_comp"], " was generated."
		return


	def print_makefile(self):
		"""
		Generate Makefile
		"""
		f,line = self.check_overwrite(self.data["makefile"])
		if not f:  # overwrite: No
			return

		if not line:  # overwrite: Yes
			temp_txt = makefile.splitlines()
		else:     # overwrite: Merge mode
			temp_txt = lines

		# replace tags
		temp_txt = self.replace_tags(temp_txt, self.tags)
		
		t = ezt.Template(compress_whitespace = 0)
		t.parse(temp_txt)
		t.generate(f, self.data)
		print self.data["makefile"], " was generated."
		return

	def print_impl(self):
		for svc_idl in self.data["service_idl"]:
			if not os.access(svc_idl.idl_fname, os.F_OK):
				sys.stderr.write("Error: IDL file \"" \
								 + svc_idl.idl_fname \
								 + "\" not found.\n")
				sys.exit(1)
			fd_h, lines_h      = self.check_overwrite(svc_idl.impl_h)
			fd_cpp, lines_cpp = self.check_overwrite(svc_idl.impl_cpp)

			if not fd_h or not fd_cpp:
				return
			if lines_h or lines_cpp:
				sys.stderr.write("Merge of service impl. code is not supported.\n")
				return

			try:
				ifs = cxx_svc_impl.generate(svc_idl.idl_fname,
											self.data["idl_include"],
											svc_idl.impl_suffix,
											svc_idl.skel_suffix,
											fd_h, fd_cpp)
				print svc_idl.impl_h, " was generated."
				print svc_idl.impl_cpp, " was generated."
			except:
				sys.stderr.write("Error: " \
								 + svc_idl.impl_h + svc_idl.impl_cpp + "\n")

	def print_all(self):
		self.print_impl()
		self.print_header()
		self.print_source()
		self.print_compsrc()
		self.print_makefile()
		return


class idl2char:
	def __init__(self, filename = None):
		self.lines = ""
		self.inComment = False
		if filename:
			f = open(filename)
			l = f.readlines()
			self.erase_comments(l)
			f.close()

			#		while 1:
			#			l = f.readline()
			#			if not l:
			#				break


	def open_file(self, filename):
		f = open(filename)
		l = f.readlines()
		self.erase_comments(l)
		f.close()

	def cleanup():
		self.lines = ""

	def erase_comments(self, lines):
		for l in lines:
			m = re.search("/\*.*\*/", l)
			if m:
				l = l.replace(m.group(), "")
				
			m = re.search(".*\*/", l)
			if m:
				l = l.replace(m.group(), "")
				if self.inComment == True:
					self.inComment = False

			m = re.search("/\*.*$", l)
			if m:
				l = l.replace(m.group(), "")
				if self.inComment == False:
					self.inComment = True

			m = re.search("//.*$", l)
			if m:
				l = l.replace(m.group(), "")

			m = re.search("\s+$", l)
			if m:
				l = l.replace(m.group(), "")
				l = l + "\n"

			m = re.search("\S", l)
			if m:
				if not self.inComment:
					self.lines += l

					
	def get_lines(self):
		return self.lines

	def make_chardata(self, var_name):
		self.lines = self.lines.replace("\n","\\n\\\n")
		self.lines = self.lines.replace("\"","\\\"")
		self.lines = "static char* " + var_name + " = \"\\\n" + self.lines
		self.lines += "\";\n"
		return self.lines

	def add_slash(self):
		self.lines = self.lines.replace("\n","\\\n")
		return self.lines

	def write_file(self, filename):
		f = open(filename, "w")
		f.write(self.lines)
		f.close()



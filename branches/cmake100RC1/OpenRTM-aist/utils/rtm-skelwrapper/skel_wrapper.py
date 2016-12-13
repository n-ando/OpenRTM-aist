#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  @file skel_wrapper.py
#  @brief CORBA skelton/stub wrapper generator module
#  @date $Date: 2008-03-06 06:51:10 $
#  @author Noriaki Ando <n-ando@aist.go.jp>
# 
#  Copyright (C) 2004-2007
#      Task-intelligence Research Group,
#      Intelligent Systems Research Institute,
#      National Institute of
#          Advanced Industrial Science and Technology (AIST), Japan
#      All rights reserved.
# 
#  $Id$
# 

import yat
import re
import sys
import os
import os.path
import time


#------------------------------------------------------------
# Server Skelton header template
#------------------------------------------------------------
skel_h = """// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file [skel_h]
 
 * @brief [basename] server skeleton header wrapper code
 * @date [date]
 
 *
 */

#ifndef [skel_h_inc_guard]

#define [skel_h_inc_guard]



[config_inc]

#if   defined ORB_IS_TAO
#  include "[include_dir][basename]C.h"
#  include "[include_dir][basename]S.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "[include_dir][basename].hh"
#elif defined ORB_IS_MICO
#  include "[include_dir][basename].h"
#elif defined ORB_IS_ORBIT2
#  include "[include_dir]/[basename]-cpp-stubs.h"
#  include "[include_dir]/[basename]-cpp-skels.h"
#else
#  error "NO ORB defined"
#endif

#endif // [skel_h_inc_guard]

"""


#------------------------------------------------------------
# Server Skelton source template
#------------------------------------------------------------
skel_cpp = """// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file [skel_cpp]
 
 * @brief [basename] server skeleton wrapper
 * @date [date]
 
 *
 */

#include "[include_dir][skel_h]"

#if defined ORB_IS_TAO
#  include "[include_dir][basename]C.cpp"
#  include "[include_dir][basename]S.cpp"
#elif defined ORB_IS_OMNIORB
#  include "[include_dir][basename]SK.cc"
#  include "[include_dir][basename]DynSK.cc"
#elif defined ORB_IS_MICO
#  include "[include_dir][basename].cc"
#  include "[include_dir][basename]_skel.cc"
#elif defined ORB_IS_ORBIT2
#  include "[include_dir][basename]-cpp-stubs.cc"
#  include "[include_dir][basename]-cpp-skels.cc"
#else
#  error "NO ORB defined"
#endif

// end of [skel_cpp]

"""

#------------------------------------------------------------
# Client Stub header template
#------------------------------------------------------------
stub_h = """// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file [stub_h]
 
 * @brief [basename] client stub header wrapper code
 * @date [date]
 
 *
 */

#ifndef [stub_h_inc_guard]

#define [stub_h_inc_guard]



[config_inc]

#if   defined ORB_IS_TAO
#  include "[include_dir][basename]C.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "[include_dir][basename].hh"
#elif defined ORB_IS_MICO
#  include "[include_dir][basename].h"
#elif defined ORB_IS_ORBIT2
#  include "[include_dir][basename]-cpp-stubs.h"
#else
#  error "NO ORB defined"
#endif

#endif // [stub_h_inc_guard]

"""
 
#------------------------------------------------------------
# Client Stub soruce template
#------------------------------------------------------------
stub_cpp = """// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file [stub_cpp]
 
 * @brief [basename] client stub wrapper code
 * @date [date]
 
 *
 */

#include "[include_dir][stub_h]"

#if   defined ORB_IS_TAO
#  include "[include_dir][basename]C.cpp"
#elif defined ORB_IS_OMNIORB
#  include "[include_dir][basename]SK.cc"
#  include "[include_dir][basename]DynSK.cc"
#elif defined ORB_IS_MICO
#  include "[include_dir][basename].cc"
#elif defined ORB_IS_ORBIT2
#  include "[include_dir][basename]-cpp-stubs.cc"
#else
#  error "NO ORB defined"
#endif

// end of [stub_cpp]

"""


config_inc = """
#include <[rtm_dir]config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
"""

class skel_wrapper:
	def __init__(self, idl_fname, skel_suffix = "Skel", stub_suffix = "Stub",
				 include_dir = "", output_dir = "", config_inc = ""):
		self.data = {}
		self.data["include_dir"] = include_dir
		self.data["idl_fname"] = idl_fname
		m = re.search("\.[iI][dD][lL]$", idl_fname)
		if m:
			basename = os.path.split(idl_fname.replace(m.group(0), ""))[1]
		else:
			sys.stderr.write("Invalid IDL file name specified.\n")
			sys.exit(1)
		if output_dir != "":
			if not os.path.isdir(output_dir):
				sys.stderr.write("Specified output directory does not exist.")
				sys.exit(1)
		self.output_dir = output_dir

		self.data["basename"] = basename
		self.data["skel_h"]   = basename + skel_suffix + ".h"
		self.data["skel_cpp"] = basename + skel_suffix + ".cpp"
		self.data["stub_h"]   = basename + stub_suffix + ".h"
		self.data["stub_cpp"] = basename + stub_suffix + ".cpp"

		skel_h_guard = self.data["skel_h"].replace(".","_").upper()
		stub_h_guard = self.data["stub_h"].replace(".","_").upper()
		self.data["skel_h_inc_guard"] = skel_h_guard
		self.data["stub_h_inc_guard"] = stub_h_guard

		self.data["date"] = time.ctime()
		self.data["config_inc"] = config_inc
		return

	def print_skel_h(self):
		f = file(os.path.join(self.output_dir, self.data["skel_h"]), "w")
		t = yat.Template(skel_h)
		text=t.generate(self.data)
		f.write(text)
		f.close()
		print self.data["skel_h"], " was generated."
		return

	def print_skel_cpp(self):
		f = file(os.path.join(self.output_dir, self.data["skel_cpp"]), "w")
		t = yat.Template(skel_cpp)
		text=t.generate(self.data)
                f.write(text)
                f.close()
		print self.data["skel_cpp"], " was generated."
		return

	def print_stub_h(self):
		f = file(os.path.join(self.output_dir, self.data["stub_h"]), "w")
		t = yat.Template(stub_h)
		text=t.generate(self.data)
                f.write(text)
                f.close()
		print self.data["stub_h"], " was generated."
		return

	def print_stub_cpp(self):
		f = file(os.path.join(self.output_dir, self.data["stub_cpp"]), "w")
		t = yat.Template(stub_cpp)
		text=t.generate(self.data)
                f.write(text)
                f.close()
		print self.data["stub_cpp"], " was generated."
		return

	def print_all(self):
		self.print_skel_h()
		self.print_skel_cpp()
		self.print_stub_h()
		self.print_stub_cpp()
		return

	def generate(self):
		self.print_all()


if __name__ == "__main__":
	w = skel_wrapper("Hoge.idl", "_Skel", "_Stub", "rtm/idl/", "")
	w.generate()

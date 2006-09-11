#!/usr/bin/env python
#
# @brief CORBA stub and skelton wrapper generator
# @date $Date: 2006-09-11 18:33:14 $
# @author Norkai Ando <n-ando@aist.go.jp>
#
# Copyright (C) 2005
#     Task-intelligence Research Group,
#     Intelligent Systems Research Institute,
#     National Institute of
#         Advanced Industrial Science and Technology (AIST), Japan
#     All rights reserved.
#
# $Id: makewrapper.py,v 1.3 2006-09-11 18:33:14 n-ando Exp $
#

# $Log: not supported by cvs2svn $
# Revision 1.2  2006/03/31 05:26:34  n-ando
# - Almost all functions are rewritten to use ezt.py (Easy Template module).
# - Now makewrapper.py uses ezt.py (Easy Template module).
#
# Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
# Public release.
#
#
#
import sys
import re
import time
import ezt

skel_cpp_temp = """// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file  [skel_cpp]
 * @brief [basename] server skeleton wrapper code
 * @date  [date]
 *
 */

#include "[skel_dir]/[basename]Skel.h"

#if   defined ORB_IS_TAO
#include "[skel_dir]/[basename]S.cpp"
#elif defined ORB_IS_OMNIORB
#include "[skel_dir]/[basename]SK.cc"
#include "[skel_dir]/[basename]DynSK.cc"
#elif defined ORB_IS_MICO
#include "[skel_dir]/[basename]_skel.cc"
#elif defined ORB_IS_ORBIT2
#include "[skel_dir]/[basename]-cpp-skels.cc"
#else
#error "NO ORB defined"
#endif
"""

skel_h_temp = """// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file  [skel_h]
 * @brief [basename] server skeleton wrapper code
 * @date  [date]
 *
 */

#ifndef __[BASENAME]SKEL_H__
#define __[BASENAME]SKEL_H__

#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#include "[skel_dir]/[basename]S.h"
#elif defined ORB_IS_OMNIORB
#include "[skel_dir]/[basename].hh"
#elif defined ORB_IS_MICO
#include "[skel_dir]/[basename].h"
#elif defined ORB_IS_ORBIT2
#include "[skel_dir]/[basename]-cpp-skels.h"
#else
#error "NO ORB defined"
#endif

#endif // end of __[BASENAME]SKEL_H__
"""

stub_cpp_temp = """// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file  [stub_cpp]
 * @brief [basename] server skeleton wrapper code
 * @date  [date]
 *
 */

#include "[skel_dir]/[basename]Stub.h"

#if   defined ORB_IS_TAO
#include "[skel_dir]/[basename]C.cpp"
#elif defined ORB_IS_OMNIORB
#include "[skel_dir]/[basename]SK.cc"
#include "[skel_dir]/[basename]DynSK.cc"
#elif defined ORB_IS_MICO
#include "[skel_dir]/[basename].cc"
#elif defined ORB_IS_ORBIT2
#include "[skel_dir]/[basename]-cpp-stubs.cc"
#else
#error "NO ORB defined"
#endif
"""

stub_h_temp = """// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file  [stub_h]
 * @brief [basename] server skeleton wrapper code
 * @date  [date]
 *
 */

#ifndef __[BASENAME]STUB_H__
#define __[BASENAME]STUB_H__

#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#include "[skel_dir]/[basename]C.h"
#elif defined ORB_IS_OMNIORB
#include "[skel_dir]/[basename].hh"
#elif defined ORB_IS_MICO
#include "[skel_dir]/[basename].h"
#elif defined ORB_IS_ORBIT2
#include "[skel_dir]/[basename]-cpp-stubs.h"
#else
#error "NO ORB defined"
#endif

#endif // end of __[BASENAME]STUB_H__
"""

class wrapper_data:
	def __init__(self, basename, dir_name):
		self.data = {}
		self.data["basename"] = basename
		self.data["BASENAME"] = basename.upper()
		self.data["idl_name"] = basename + ".idl"
		self.data["skel_dir"] = dir_name
		self.data["date"]     = time.ctime()
		self.data["skel_cpp"] = basename + "Skel.cpp"
		self.data["skel_h"]   = basename + "Skel.h"
		self.data["stub_cpp"] = basename + "Stub.cpp"
		self.data["stub_h"]   = basename + "Stub.h"

	def get_dict(self):
		return self.data
		

class wrapper_gen:
	def __init__(self, data):
		self.data = data

	def gen(self, fname, temp_txt, data):
		f = file(fname, "w")
		#		s = StringIO.StringIO()
		t = ezt.Template(compress_whitespace = 0)
		t.parse(temp_txt)
		t.generate(f, data)
		#		gen_txt = s.getvalue().splitlines()
		#		f.write(gen_txt)
		f.close()
		print "\"", fname, "\"" " was generated."
		return

	def gen_all(self):
		self.write_skel()
		self.write_skelh()
		self.write_stub()
		self.write_stubh()
		return

	def write_skel(self):
		self.gen(self.data["skel_cpp"], skel_cpp_temp, self.data)

	def write_skelh(self):
		self.gen(self.data["skel_h"], skel_h_temp, self.data)
		return

	def write_stub(self):
		self.gen(self.data["stub_cpp"], stub_cpp_temp, self.data)
		return

	def write_stubh(self):
		self.gen(self.data["stub_h"], stub_h_temp, self.data)
		return


idl_file = sys.argv[1]
if len(sys.argv) > 2:
	skel_dir = sys.argv[2]
else:
	skel_dir = "rtm/idl"

basename = re.sub(".idl", "", idl_file);

data = wrapper_data(basename, skel_dir)
gen  = wrapper_gen(data.get_dict())
gen.gen_all()



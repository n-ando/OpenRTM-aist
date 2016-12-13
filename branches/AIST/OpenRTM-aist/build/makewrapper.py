#!/usr/bin/env python
#
# @brief CORBA stub and skelton wrapper generator
# @date $Date: 2005-05-12 09:06:18 $
# @author Norkai Ando <n-ando@aist.go.jp>
#
# Copyright (C) 2005
#     Task-intelligence Research Group,
#     Intelligent Systems Research Institute,
#     National Institute of
#         Advanced Industrial Science and Technology (AIST), Japan
#     All rights reserved.
#
# $Id: makewrapper.py,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
#

# $Log: not supported by cvs2svn $
#
#

import time
import sys
import re

class MakeWrapper:
	def __init__(self, basename):
		self.basename = basename
		self.date = time.asctime()
		self.skel_dir = "rtm/idl/";
		self.rtc_dir = "rtm/";

	def write_skel(self):
		"""
		write_skel()
		
		Writing server skeleton wrapper code
		"""
	
		skel_cpp_name = self.basename + "Skel.cpp"
		skel_cpp = file(skel_cpp_name, "w")
		
		# Skelton
		print >> skel_cpp, """// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file %s
 * @brief %s server skeleton wrapper code
 * @date %s
 *
 */

#include "%s%sSkel.h"
""" % (skel_cpp_name,
	   self.basename,
	   self.date,
	   self.skel_dir,
	   self.basename)

		print >> skel_cpp, """#if   defined ORB_IS_TAO
#include "%s%sS.cpp"
#elif defined ORB_IS_OMNIORB
#include "%s%sSK.cc"
#include "%s%sDynSK.cc"
#elif defined ORB_IS_MICO
#include "%s%s_skel.cc"
#else
#error "NO ORB defined"
#endif
""" % (self.skel_dir, self.basename,
	   self.skel_dir, self.basename,
	   self.skel_dir, self.basename,
	   self.skel_dir, self.basename)

		skel_cpp.close()

		print skel_cpp_name + " generated"


	def write_skelh(self):
		"""------------------------------------------------------------
		write_skelh()
		
		Writing server skeleton header wrapper code
		------------------------------------------------------------"""
		skel_h_name = self.basename + "Skel.h"
		hdefine  = self.basename.upper()

		skel_h = file(skel_h_name, "w")

		# Header
		print >> skel_h, """// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file %s
 * @brief %s server skeleton header wrapper code
 * @date %s
 *
 */

#ifndef __%sSKEL_H__
#define __%sSKEL_H__

#include <%sconfig_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
""" % (skel_h_name,
	   self.basename,
	   self.date,
	   hdefine,
	   hdefine,
	   self.rtc_dir)

		print >> skel_h, """#if   defined ORB_IS_TAO
#include "%s%sS.h"
#elif defined ORB_IS_OMNIORB
#include "%s%s.hh"
#elif defined ORB_IS_MICO
#include "%s%s.h"
#else
#error "NO ORB defined"
#endif

#endif // end of __%sSKEL_H__
""" % (self.skel_dir, self.basename,
	   self.skel_dir, self.basename,
	   self.skel_dir, self.basename,
	   hdefine)

		skel_h.close()
		print skel_h_name + " generated"

		
	def write_stub(self):
		"""
		write_stub()
		
		Writing stub wrapper code
		"""
		stub_cpp_name = self.basename + "Stub.cpp"
		stub_cpp = file(stub_cpp_name, "w")

		print >> stub_cpp, """// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file %s
 * @brief %s client stub wrapper code
 * @date %s
 *
 */

#include "%s%sStub.h"
""" % (stub_cpp_name,
	   self.basename,
	   self.date,
	   self.skel_dir,
	   self.basename)

		print >> stub_cpp, """#if   defined ORB_IS_TAO
#include "%s%sC.cpp"
#elif defined ORB_IS_OMNIORB
#include "%s%sSK.cc"
#include "%s%sSynSK.cc"
#elif defined ORB_IS_MICO
#include "%s%s.cc"
#else
#error "NO ORB defined"
#endif
""" % (self.skel_dir, self.basename,
	   self.skel_dir, self.basename,
	   self.skel_dir, self.basename,
	   self.skel_dir, self.basename)

		stub_cpp.close()
		print stub_cpp_name + " generated"


	def write_stubh(self):
		stub_h_name = self.basename + "Stub.h"
		hdefine  = self.basename.upper()

		stub_h = file(stub_h_name, "w")

		# Header
		print >> stub_h, """// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file %s
 * @brief %s client stub header wrapper code
 * @date %s
 *
 */

#ifndef __%sSTUB_H__
#define __%sSTUB_H__

#include <%sconfig_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
""" % (stub_h_name,
	   self.basename,
	   self.date,
	   hdefine,
	   hdefine,
	   self.rtc_dir)

		# Body
		print >> stub_h, """#if   defined ORB_IS_TAO
#include "%s%sC.h"
#elif defined ORB_IS_OMNIORB
#include "%s%s.hh"
#elif defined ORB_IS_MICO
#include "%s%s.h"
#else
#error "NO ORB defined"
#endif

#endif // end of __%sSTUB_H__
""" % (self.skel_dir, self.basename,
	   self.skel_dir, self.basename,
	   self.skel_dir, self.basename,
	   hdefine)

		stub_h.close()
		print stub_h_name + " generated"


idl_file = sys.argv[1]
idl_name = re.sub(".idl", "", idl_file);

mkw = MakeWrapper(idl_name)
mkw.write_skel()
mkw.write_stub()
mkw.write_skelh()
mkw.write_stubh()




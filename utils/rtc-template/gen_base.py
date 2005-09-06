#!/usr/bin/env python
# -*- python -*-
#
#  @file gen_base.py
#  @brief rtc-template source code generator base class
#  @date $Date: 2005-09-06 14:37:29 $
#  @author Noriaki Ando <n-ando@aist.go.jp>
# 
#  Copyright (C) 2005
#      Task-intelligence Research Group,
#      Intelligent Systems Research Institute,
#      National Institute of
#          Advanced Industrial Science and Technology (AIST), Japan
#      All rights reserved.
# 
#  $Id: gen_base.py,v 1.2 2005-09-06 14:37:29 n-ando Exp $
# 

#
#  $Log: not supported by cvs2svn $
#

import os
import re
import time

class gen_base:
	
	def check_overwrite(self, fname):
		"""
		Check file exist or not.
		"""
		msg = " already exists. Overwrite or merge? (y/n/m)"
		if (os.access(fname, os.F_OK)):
			ans = raw_input("\"" + fname + "\"" + msg)
			if (ans == "y" or ans == "Y"):
				return file(fname, "w"), None
			elif (ans == "m" or ans == "M"):
				f = file(fname, "r")
				lines = f.readlines()
				f.close()
				oldfname = fname + ".old." + time.strftime("%y%m%d%H%M%S")
				os.rename(fname, oldfname)
				return file(fname, "w"), lines
			else:
				return None, None
		else:
			return file(fname, "w"), None
		return
	
	def replace_tags(self, lines, data):
		in_tag = False
		tag_name = ""
		ret_lines = ""
		
		for l in lines:
			m = re.search("<rtc-template block=\"(.*?)\">", l)
			if m:
				inside_tag = True
				tag_name   = m.group(1)
				ret_lines += l + "\n"
				continue

			m = re.search("</rtc-template>", l)
			if m:
				inside_tag = False
				if data.has_key(tag_name):
					ret_lines += data[tag_name] + "\n"
				ret_lines += l + "\n"
				tag_name = ""
				continue

			ret_lines += l + "\n"

		return ret_lines


if __name__ == "__main__":
	hoge = """
 protected:
  // <rtc-template block="inport_declar">
  // </rtc-template>

  // <rtc-template block="outport_declar">
  // </rtc-template>
"""
	data = {"inport_declar": "  hoge;\n  dara;\n  munya;",
			"outport_declar": "  1;\n  2;\n  3;"}
	g = gen_base()
	print g.replace_tags(hoge.splitlines(), data)

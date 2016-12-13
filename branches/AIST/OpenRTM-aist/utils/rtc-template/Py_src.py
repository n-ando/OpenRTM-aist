#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  @file Py_src.py
#  @brief rtc-template Python soruce code generator class
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
#  $Id: Py_src.py,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
# 

#
#  $Log: not supported by cvs2svn $
#

import re
import os

class Py_src:
	def __init__(self, fname, spec):
		self.fname = fname
		self.fname_py = fname + ".py"
		
		self.spec = spec
		_name = re.sub("\.", "_", self.spec["module-name"][1])
		self.include_guard = "__" + _name.upper() + "_h__"
		self.lcase_name = self.spec["module-name"][1].lower()

	def print_pysrc(self):
		if (not self.check_overwrite(self.fname_py)):
			return
		pyscript = file(self.fname_py, "w")
		print >> pyscript, """#!/usr/bin/env python
# -*- Python -*-
import sys
sys.path.append(".")

# Inport RTM module
import RTM

# This module's spesification
mod_spec = {
"""
		spec_list = ("module-name", "module-desc", "module-version",
					 "module-author", "module-category", "module-comp-type",
					 "module-act-type", "module-max-inst")
		for key in spec_list:
			print >> pyscript, "\tRTM.%s: \"%s\"," % \
				  (self.spec[key][0], self.spec[key][1])

		# End of module spec
		print >> pyscript, """\tRTM.RTC_MODULE_LANG: "Python",
\tRTM.RTC_MODULE_LANG_TYPE: "SCRIPT",
\tRTM.RTC_MODULE_SPEC_END: ""
  }
"""
		# class definition
		print >> pyscript, """
	
class %s(RTM.RtcBase):
\tdef __init__(self, mgr):
\t\ttry:
\t\t\tRTM.RtcBase.__init__(self, mgr)
""" % (self.spec["module-name"][1])
		print >> pyscript, "\t\t\t# Initialize InPorts and OutPorts"
		for inpname in self.spec["module-inport"][1]:
			inp = self.spec["module-inport"][1][inpname]
			print >> pyscript, "\t\t\tself.%s = RTM.%sIn(\"%s\")" % (inpname, inp, inpname)
			print >> pyscript, "\t\t\tself.registerInPort(self.%s)" % (inpname)
		for outpname in self.spec["module-outport"][1]:
			outp = self.spec["module-outport"][1][outpname]
			print >> pyscript, "\t\t\tself.%s = RTM.%sOut(\"%s\")" % (outpname, outp, outpname)
			print >> pyscript, "\t\t\tself.registerOutPort(self.%s)" % (outpname)
		print >> pyscript, """\t\texcept:
\t\t\tpass
\t\treturn
"""
		# print shared object export functions
		print >> pyscript, """
\tdef rtc_init_entry(self):
\t\ttry:
\t\t\t# do something
\t\t\tpass
\t\texcept:
\t\t\tpass
\t\treturn 0
"""

		print >> pyscript, """
\tdef rtc_active_do(self):
\t\ttry:
\t\t\t# do something
\t\t\tpass
\t\texcept:
\t\t\tpass
\t\treturn 0
"""

		print >> pyscript, """
arg = [\"-f\", \"./rtc.conf\"]
mgr = RTM.RtcManager(arg)
prof = RTM.RtcModuleProfile(mod_spec)
mgr.registerComponent((prof, %s))
""" % (self.spec["module-name"][1])

		print >> pyscript, """
def main():
\targ = ["-f", "./rtc.conf"]
\tmgr = RTM.RtcManager(arg)
\tmgr.initManager()
\tmgr.activateManager()
\ts = mgr.create_component("%s")
\tmgr.runManager()

if __name__ == "__main__":
\tmain()
""" % (self.spec["module-name"][1])
		pyscript.close()
		print self.fname_py, "was generated."

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
	pys = Py_src("HogeTest", module_spec)
	pys.print_pysrc()


if __name__ == "__main__":
	main()

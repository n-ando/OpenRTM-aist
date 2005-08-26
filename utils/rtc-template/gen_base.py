#!/usr/bin/env python

import os

class gen_base:
	
	def check_overwrite(self, fname):
		"""
		Check file exist or not.
		"""
		msg = " already exists. Overwrite? (y/n)"
		if (os.access(fname, os.F_OK)):
			ans = raw_input("\"" + fname + "\"" + msg)
			if (ans == "y" or ans == "Y"):
				return file(fname, "w")
			else:
				return None
		else:
			return file(fname, "w")
		return
	

#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  @file README_src.py
#  @brief rtc-template RTComponent's README & specification file generator class
#  @date $Date: 2005-08-26 12:01:15 $
#  @author Noriaki Ando <n-ando@aist.go.jp>
# 
#  Copyright (C) 2004-2005
#      Task-intelligence Research Group,
#      Intelligent Systems Research Institute,
#      National Institute of
#          Advanced Industrial Science and Technology (AIST), Japan
#      All rights reserved.
# 
#  $Id: README_src.py,v 1.2 2005-08-26 12:01:15 n-ando Exp $
# 

#
#  $Log: not supported by cvs2svn $
#  Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
#  Public release.
#
#

import re
import os
import time
import ezt
import gen_base

readme = """======================================================================
  RTComponent: [module.name] specificatioin

  OpenRTM-[version]
  Date: [date]
======================================================================

Description: [module.desc]
Version:     [module.version]
Author:      [module.author]
Category:    [module.category]
Comp. Type:  [module.comp_type]
Act. Type:   [module.act_type]
MAX Inst.:   [module.max_inst]
Lang:        
Lang Type:   


======================================================================
    Activity definition
======================================================================

[b]Initializing[e]

[b]Ready[e]
	[b]Entry[e]
	[b]Do[e]
	[b]Exit[e]

[b]Starting[e]

[b]Active[e]
	[b]Entry[e]
	[b]Do[e]
	[b]Exit[e]

[b]Stopping[e]

[b]Error[e]
	[b]Entry[e]
	[b]Do[e]
	[b]Exit[e]


[b]Fatal Error[e]
	[b]Entry[e]
	[b]Do[e]
	[b]Exit[e]

[b]Exiting[e]

======================================================================
    InPorts definition
======================================================================
[for inport]
	Name:        [inport.name]
	PortNumber:  [inport.num]
	Description:
	PortType: 
	DataType:    [inport.type]
	MaxOut: 
	[b]Data Elements[e]
		Number:
		Name:
		Type:
		Unit:
		RangeLow:
		RangeHigh:
		DefaultValue:
[end]

======================================================================
    OutPorts definition
======================================================================
[for outport]
	Name:        [outport.name]
	PortNumber:  [outport.num]
	Description:
	PortType: 
	DataType:    [outport.type]
	MaxOut: 
	[b]Data Elements[e]
		Number:
		Name:
		Type:
		Unit:
		RangeLow:
		RangeHigh:
		DefaultValue:
[end]

======================================================================
    Configuration definition
======================================================================
This area is reserved for future OpenRTM.

"""



class README_src(gen_base.gen_base):
	def __init__(self, data):
		self.data = data.copy()
		self.data['fname'] = "README." + self.data['fname']
		self.data['version'] = os.popen("rtm-config --version", "r").read()
		self.data['date'] = time.asctime()
		self.data['b'] = "["
		self.data['e'] = "]"
		return

	def print_readme(self):
		f = self.check_overwrite(self.data["fname"])
		if (not f):
			return
		t = ezt.Template(compress_whitespace = 0)
		t.parse(readme)
		t.generate(f, self.data)
		print self.data["fname"], " was generated."

	def print_all(self):
		self.print_readme()
	

#!/usr/bin/env python
# -*- coding: shift_jis -*-
# -*- python -*-
#
# @file omniidl_be/doil/corba/__init__.py
# @brief corba servant/adapter code generator for doil backend
# @date $Date$
# @author Norkai Ando <n-ando@aist.go.jp>
#
#  Copyright (C) 2008
#      Task-intelligence Research Group,
#      Intelligent Systems Research Institute,
#      National Institute of
#          Advanced Industrial Science and Technology (AIST), Japan
#      All rights reserved.
#
# $Id$
#

import os

from omniidl_be.doil.corba import template
import omniidl_be.doil.yat as yat

def generate_servant(dict):
    for d in dict['interfaces']:
        t = yat.Template(template.servant_h)
        f = open(d['servant_h'], "w")
        text = t.generate(d)
        f.write(text)
        f.close()

        t = yat.Template(template.servant_cpp)
        f = open(d['servant_cpp'], "w")
        text = t.generate(d)
        f.write(text)
        f.close()

def generate_adapter(dict):
    for d in dict['interfaces']:
        t = yat.Template(template.adapter_h)
        f = open(d['adapter_h'], "w")
        text = t.generate(d)
        f.write(text)
        f.close()

        t = yat.Template(template.adapter_cpp)
        f = open(d['adapter_cpp'], "w")
        text = t.generate(d)
        f.write(text)
        f.close()


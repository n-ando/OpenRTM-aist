#!/usr/bin/env python
# -*- python -*-
#
# @file omniidl_be/doil/servant/__init__.py
# @brief servant code generator for doil backend
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

from omniidl_be.doil.servant import main
from omniidl_be.doil import util

def run(tree, config):
    main.__init__(config)
    try:
        main.run(tree)
    except Exception, inst:
        print dir(inst)
        import traceback
        print traceback.print_stack()
        print "exception", inst.args
        print inst.message

#!/usr/bin/env python
# -*- python -*-
#
# @file omniidl_be/doil/config.py
# @brief configuration module for doil backend
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

import string
import config

class ConfigurationState:
    def __init__(self):
        self._config = {
            # Name of this program
            'Program Name':          'omniidl (doil adapter backend)',
            # Useful data from CVS
            'CVS ID':                '$Id$',
            # Relevant omniORB C++ library version
            'Library Version':       'omniORB_4_0',
            # Debug mode
            'Debug':                 False,
            #
            # generated classes for doil
            # - Servant
            # - Adapter
            # - Ice slice
            # - Ice servant
            # - Ice adapter
            #
            'Servant':               False,
            'Adapter':               False,
            'IceSlice':              False,
            'IceServant':            False,
            'IceAdapter':            False,    
            #
            # Type mapping
            #
            'MappingFile':           '',
            #
            # Servant stuff
            #
            # Suffix of generated servant class
            'ServantSuffix':         'Servant',
            # Prefix of generated servant class
            'ServantPrefix':         '',
            # Namespace of servant class
            'ServantNs':             [],
            # servant class header directory
            'ServantDir':            [],
            #
            # Adapter stuff
            #
            # Suffix of generated servant class
            'AdapterSuffix':         'Adapter',
            # Prefix of generated servant class
            'AdapterPrefix':          '',
            # Namespace of servant class
            'AdapterNs':             [],
            # servant class header directory
            'AdapterDir':            [],
            #
            # Interface stuff
            #
            # Suffix of generated servant class
            'IfaceSuffix':           '',
            # Prefix of generated servant class
            'IfacePrefix':           'I',
            # Namespace of delegated interface class
            'IfaceNs':               [],
            # interface class header directory
            'IfaceDir':              "",
            # Base name of file being processed
            'Basename':              None,
            # Directory name of file being processed
            'Directory':             None
            }

    def __getitem__(self, key):
        if self._config.has_key(key):
            return self._config[key]
        util.fatalError("Configuration key not found (" + key + ")")

    def __setitem__(self, key, value):
        if self._config.has_key(key):
            self._config[key] = value
            return
        util.fatalError("Configuration key not found (" + key + ")")

    def dump(self):
        # find the longest key string
        max = 0
        for key in self._config.keys():
            if len(key) > max: max = len(key)
        # display the table
        for key in self._config.keys():
            print string.ljust(key, max), ":  ", repr(self._config[key])

# Create state-holding singleton object
if not hasattr(config, "state"):
    config.state = ConfigurationState()

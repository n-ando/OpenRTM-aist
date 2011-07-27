#!/usr/bin/env python
#
# @brief CMake Config file generator
# @date $Date$
# @author Norkai Ando <n-ando@aist.go.jp>
#
# Copyright (C) 2011
#     Noriaki Ando
#     Intelligent Systems Research Institute,
#     National Institute of
#         Advanced Industrial Science and Technology (AIST), Japan
#     All rights reserved.
#
# $Id$
#
# Usage:
#   cmakeconfgen.py rtm_config.vsprops
#
# This command create OpenRTMConfig.cmake to the current directory
#

from xml.dom import minidom, Node
import sys
import re
import os
import yat
import time

template="""
# -*- cmake -*-
#
# @file OpenRTMConfig.cmake
# @brief cmake-config file for OpenRTM-aist on Windows
# @date [date] 
#
# This file is used for cmake config-mode.
# The following variables are defined.
#
# Basic compiler/linker options
# - OPENRTM_CFLAGS: cflags 
# - OPENRTM_INCLUDE_DIRS: include directories
# - OPENRTM_LDFLAGS: linker options
# - OPENRTM_LIBRARY_DIRS: library directories
# - OPENRTM_LIBRARIES: libraries
# - OPENRTM_LIB_DIR: OpenRTM's lib directory
#
# OpenRTM-aist specific directory
# - COIL_INCLUDE_DIR: coil include dir
# - OPENRTM_INCLUDE_DIR: OpenRTM's include directory
# - OPENRTM_LIB_DIR: OpenRTM's lib directory
# - OPENRTM_DATA_DIR: OpenRTM's shared directory
#
# OpenRTM-aist version
# - OPENRTM_VERSION: x.y.z version
# - OPENRTM_VERSION_MAJOR: major version number
# - OPENRTM_VERSION_MINOR: minor version number
# - OPENRTM_VERSION_PATCH: revision number
# - OPENRTM_SHORT_VERSION: short version number 1.1.0->110
#
# OpenRTM-aist's CORBA related settings
# - OPENRTM_ORB: CORBA implementation
# - OPENRTM_IDL_WRAPPER: rtm-skelwrapper command
# - OPENRTM_IDL_WRAPPER_FLAGS: rtm-skelwrapper flag
# - OPENRTM_IDLC: IDL command
# - OPENRTM_IDLFLAGS: IDL optins

message(STATUS "OpenRTMConfig.cmake found.")
message(STATUS "Configrued by configuration mode.")

string(REPLACE "\\\\" "/" OMNIORB_DIR "$ENV{OMNI_ROOT}")
string(REPLACE "\\\\" "/" OPENRTM_DIR "$ENV{RTM_ROOT}")
string(REGEX REPLACE "/$" "" OMNIORB_DIR "${OMNIORB_DIR}")
string(REGEX REPLACE "/$" "" OPENRTM_DIR "${OPENRTM_DIR}")

# omniORB options
file(GLOB _vers RELATIVE "${OMNIORB_DIR}" "${OMNIORB_DIR}/THIS_IS_OMNIORB*")
if("${_vers}" STREQUAL "")
  message(FATAL_ERROR "omniORB version file not found.")
endif()
string(REGEX REPLACE "[[]^0-9]+([[]0-9]+)_([[]0-9]+)_([[]0-9]+)"
  "\\\\1.\\\\2.\\\\3" OMNIORB_VERSION "${_vers}")
set(OMNIORB_CFLAGS [omniorb_cflags])
set(OMNIORB_INCLUDE_DIRS [omniorb_include_dirs])
set(OMNIORB_LDFLAGS [omniorb_ldflags])
set(OMNIORB_LIBRARY_DIRS [omniorb_library_dirs])
set(OMNIORB_LIBRARIES [omniorb_libraries])

# Basic compiler/linker options
set(OPENRTM_CFLAGS [openrtm_cflags])
set(OPENRTM_INCLUDE_DIRS [openrtm_include_dirs])
set(OPENRTM_LDFLAGS [openrtm_ldflags])
set(OPENRTM_LIBRARY_DIRS [openrtm_lib_dirs])
set(OPENRTM_LIBRARIES [openrtm_libs])

# OpenRTM-aist specific directory
set(COIL_INCLUDE_DIR [coil_include_dir])
set(OPENRTM_INCLUDE_DIR [openrtm_include_dir])
set(OPENRTM_LIB_DIR [openrtm_libdir])
set(OPENRTM_DATA_DIR [openrtm_data_dir])

# OpenRTM-aist version
set(OPENRTM_VERSION [openrtm_version])
set(OPENRTM_VERSION_MAJOR [openrtm_version_major])
set(OPENRTM_VERSION_MINOR [openrtm_version_minor])
set(OPENRTM_VERSION_PATCH [openrtm_version_patch])
set(OPENRTM_SHORT_VERSION [openrtm_short_version])

# OpenRTM-aist's CORBA related settings
set(OPENRTM_ORB [openrtm_orb])
set(OPENRTM_IDL_WRAPPER [openrtm_idl_wrapper])
set(OPENRTM_IDL_WRAPPER_FLAGS [openrtm_idl_wrapper_flags])
set(OPENRTM_IDLC [openrtm_idlc])
set(OPENRTM_IDLFLAGS [openrtm_idlflags])

message(STATUS "OpenRTM-aist configuration done")

message(STATUS "  OMNIORB_DIR=${OMNIORB_DIR}")
message(STATUS "  OMNIORB_VERSION=${OMNIORB_VERSION}")
message(STATUS "  OMNIORB_CFLAGS=${OMNIORB_CFLAGS}")
message(STATUS "  OMNIORB_INCLUDE_DIRS=${OMNIORB_INCLUDE_DIRS}")
message(STATUS "  OMNIORB_LDFLAGS=${OMNIORB_LDFLAGS}")
message(STATUS "  OMNIORB_LIBRARY_DIRS=${OMNIORB_LIBRARY_DIRS}")
message(STATUS "  OMNIORB_LIBRARIES=${OMNIORB_LIBRARIES}")

message(STATUS "  OPENRTM_DIR=${OPENRTM_DIR}")
message(STATUS "  OPENRTM_VERSION=${OPENRTM_VERSION}")
message(STATUS "  OPENRTM_VERSION_MAJOR=${OPENRTM_VERSION_MAJOR}")
message(STATUS "  OPENRTM_VERSION_MINOR=${OPENRTM_VERSION_MINOR}")
message(STATUS "  OPENRTM_VERSION_PATCH=${OPENRTM_VERSION_PATCH}")
message(STATUS "  OPENRTM_CFLAGS=${OPENRTM_CFLAGS}")
message(STATUS "  OPENRTM_INCLUDE_DIRS=${OPENRTM_INCLUDE_DIRS}")
message(STATUS "  OPENRTM_LDFLAGS=${OPENRTM_LDFLAGS}")
message(STATUS "  OPENRTM_LIBRARY_DIRS=${OPENRTM_LIBRARY_DIRS}")
message(STATUS "  OPENRTM_LIBRARIES=${OPENRTM_LIBRARIES}")

message(STATUS "  OPENRTM_IDLC=${OPENRTM_IDLC}")
message(STATUS "  OPENRTM_IDLFLAGS=${OPENRTM_IDLFLAGS}")
message(STATUS "  OPENRTM_IDL_WRAPPER=${OPENRTM_IDL_WRAPPER}")
message(STATUS "  OPENRTM_IDL_WRAPPER_FLAGS=${OPENRTM_IDL_WRAPPER_FLAGS}")

# end of OpenRTMConfig.cmake

"""


def process_lib(libs, type):
    liblist = libs.split(" ")
    results = ""
    for l in liblist:
        if re.match(".*.[lL][iI][bB]", l):
            results += type + ";" + re.sub(".[lL][iI][bB]", "", l) + ";"
    return results[:-1]


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print "please specify vsprops file"
        sys.exit(1)

    fname = sys.argv[1]
    if fname.split(".")[-1] != "vsprops":
        print "please specify vsprops file"
        sys.exit(1)

    f = file(sys.argv[1], "r")
    text = f.read().replace("shift_jis", "utf-8")
    f.close()

    doc = minidom.parseString(text)

    dict = {}
    for node in doc.getElementsByTagName('UserMacro'):
        name = node.getAttribute("Name")
        value = node.getAttribute("Value")
        # backslash -> slash
        value = value.replace("\\", "/")
        value = value.replace("\"", "")
        value = re.sub("(SolutionDir)", "%RTM_ROOT%", value)
        dict[name] = value
    dict["user_lib"] = ""
    dict["user_libd"] = ""
    dict["omni_root"] = "${OMNIORB_DIR}"
    dict["rtm_root"] = "${OPENRTM_DIR}"
    dict["date"] = time.ctime()

    # replace variables in actual values
    for key in dict:
        for varname in dict:
            varexp = "$(" + varname + ")"
            dict[key] = str(dict[key].replace(varexp, dict[varname]))

    # cflags
    omni_cflags  = "-D__WIN32__;-D__x86__;-D__NT__;-D__OSVERSION__=4"
    omni_cflags += ";-D_CRT_SECURE_NO_DEPRECATE"

    rtm_cflags = omni_cflags + ";-DINCLUDE_stub_in_nt_dll"
    if re.match("^41", dict["omni_dllver"]):
        rtm_cflags += ";-DRTC_CORBA_CXXMAPPING11;-D_WIN32_WINNT=0x0500"
    else:
        rtm_cflags += ";-D_WIN32_WINNT=0x0400"

    # libs
    omni_libs  = process_lib(dict["omni_lib"], "optimized")
    omni_libs += ";" + process_lib(dict["omni_libd"], "debug")
    rtm_libs   = process_lib(dict["rtm_lib"], "optimized")
    rtm_libs  += ";" + process_lib(dict["rtm_libd"], "debug")



    dict["omniorb_cflags"] = omni_cflags
    dict["omniorb_include_dirs"] = dict["omni_includes"] 
    dict["omniorb_ldflags"] = ""
    dict["omniorb_library_dirs"] = dict["omni_libdir"]
    dict["omniorb_libraries"] = omni_libs

    dict["openrtm_cflags"] = rtm_cflags
    dict["openrtm_include_dirs"] = str(dict["rtm_includes"])
    dict["openrtm_ldflags"] = ""
    dict["openrtm_lib_dirs"] = str(dict["rtm_libdir"] + ";" + dict["omni_libdir"])
    dict["openrtm_libs"] = str(rtm_libs)
    dict["coil_include_dir"] = str(dict["rtm_libdir"])
    dict["openrtm_include_dir"] = "%RTM_ROOT%"
    dict["openrtm_libdir"] = "%RTM_ROOT%"
    dict["openrtm_data_dir"] = "%RTM_ROOT%"
    dict["openrtm_version"] = str(dict["rtm_version"])
    dict["openrtm_version_major"] = str(dict["rtm_version"].split(".")[0])
    dict["openrtm_version_minor"] = str(dict["rtm_version"].split(".")[1])
    dict["openrtm_version_patch"] = str(dict["rtm_version"].split(".")[2])
    dict["openrtm_short_version"] = str(dict["rtm_version"].replace(".",""))
    dict["openrtm_orb"] = "omniORB"
    dict["openrtm_idl_wrapper"] = "rtm-skelwrapper.py"
    dict["openrtm_idl_wrapper_flags"] = '--include-dir="";--skel-suffix=Skel;--stub-suffix=Stub'
    dict["openrtm_idlc"] = "omniidl"
    dict["openrtm_idlflags"] =  "-bcxx;-Wba;-nf;-I${OPENRTM_DIR}/rtm/idl"

    t = yat.Template(template)
    f = file("OpenRTMConfig.cmake", "w")
    f.write(t.generate(dict))
    f.close()

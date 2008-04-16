## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for ConsoleIn/ConsoleOut components
##
## $Id$
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.2  2008/02/29 04:56:04  n-ando
## A trivial fix.
##
## Revision 1.1.2.1  2008/02/26 14:13:25  n-ando
## Visual Studio project file generation
##
## Revision 1.1  2007/04/23 07:26:43  n-ando
## ConfigSample example.
##
## Revision 1.3  2007/01/21 13:35:17  n-ando
## A trivial fix.
##
## Revision 1.2  2007/01/14 22:52:23  n-ando
## Updated for OpenRTM-aist-0.4.0.
##
## Revision 1.1.1.1  2005/05/12 09:06:20  n-ando
## Public release.
##
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/rtm -L$(top_builddir)/rtm/idl

noinst_LTLIBRARIES = libConfigSample.la
libConfigSample_la_SOURCES = ConfigSample.cpp ConfigSample.h
libConfigSample_la_LIBADD = $(top_builddir)/rtm/libRTC.la
libConfigSample_la_FLAGS = -L$(top_builddir)/rtm/.lib

noinst_PROGRAMS = ConfigSampleComp
ConfigSampleComp_SOURCES = ConfigSampleComp.cpp 
ConfigSampleComp_LDADD = $(top_builddir)/rtm/libRTC.la ConfigSample.o
ConfigSampleComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

EXTRA_DIST =                  \
	gen.sh                \
	rtc.conf              \
	configsample.conf     \
	VectorConvert.h       \
	Makefile.ConfigSample \
	README.ConfigSample

ALL_SRC =                    \
	ConfigSampleComp.cpp \
	ConfigSample.cpp     \
	ConfigSample.h

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(ALL_SRC) > src.lst
	echo $(EXTRA_DIST) > other.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/examples/ConfigSample/

vcproj: vc8proj vc9proj

vc8proj:
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type EXE                                      \
		--vcversion "8.00"                              \
		--projectname "ConfigSampleComp"                \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/ConfigSample_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                       \
		--source ConfigSample.cpp ConfigSampleComp.cpp  \
		--header ConfigSample.h VectorConvert.h
	qkc -sm $(win32_builddir)/ConfigSample_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj                 \
		--type DLL                                         \
		--vcversion "8.00"                                 \
		--projectname "ConfigSample"                       \
		--version $(RTM_VERSION)                           \
		--out $(win32_builddir)/ConfigSampleDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                       \
		--source ConfigSample.cpp                          \
		--header ConfigSample.h VectorConvert.h
	qkc -sm $(win32_builddir)/ConfigSampleDll_vc8.vcproj

vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type EXE                                      \
		--vcversion "9.00"                              \
		--projectname "ConfigSampleComp"                \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/ConfigSample_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                       \
		--source ConfigSample.cpp ConfigSampleComp.cpp  \
		--header ConfigSample.h VectorConvert.h
	qkc -sm $(win32_builddir)/ConfigSample_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj                 \
		--type DLL                                         \
		--vcversion "9.00"                                 \
		--projectname "ConfigSample"                       \
		--version $(RTM_VERSION)                           \
		--out $(win32_builddir)/ConfigSampleDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                       \
		--source ConfigSample.cpp                          \
		--header ConfigSample.h VectorConvert.h
	qkc -sm $(win32_builddir)/ConfigSampleDll_vc9.vcproj


dist-hook: lst vcproj


clean-local:
	rm -f \
	*.gch *.bak *.rpo *.sym lib*.*_pure_* *.lst \
	Makefile.old *core *~ *.so *.log


## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for ConsoleIn/ConsoleOut components
##
## $Id: Makefile.am 2086 2011-05-09 04:46:15Z fsi-katami $
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS=-I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/coil/include -I$(top_srcdir)/src/lib/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/src/lib/rtm -L$(top_builddir)/src/lib/rtm/idl

all-local:
	mkdir -p idl
	cp -p $(top_srcdir)/src/lib/rtm/idl/SDOPackage.idl idl/
	cp -p $(top_srcdir)/src/lib/rtm/idl/RTC.idl idl/
	cp -p ../LogicalTimeTriggeredEC.idl idl/

#------------------------------------------------------------
# Targets
#------------------------------------------------------------
# Targets directories
exampledir = $(rtm_exampledir)
socompdir  = $(exampledir)/rtc
sourcedir  = $(exampledir)/src/ExtTrigger

# Standalone RTCs
example_PROGRAMS = LTTSampleComp
example_DATA = rtc.conf

LTTSampleComp_SOURCES = LTTSampleComp.cpp LTTSample.cpp LTTSample.h
LTTSampleComp_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la \
	../libLogicalTimeTriggeredECSkel.la
LTTSampleComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs

# Example sources
source_DATA = $(ALL_SRC) $(EXTRA_DIST)

#------------------------------------------------------------
# Extra distributed files
#------------------------------------------------------------
EXTRA_DIST =            \
	TickApp.py          \
	run.sh              \
	rtc.conf

ALL_SRC = $(LTTSampleComp_SOURCES)

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
#lst:
#	echo $(ALL_SRC) > src.lst
#	echo $(EXTRA_DIST) > other.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/examples/LTTSample

vcproj: vc8proj vc9proj vc10proj

vc8proj: 
	$(top_builddir)/build/vcprojtool.py vcproj       \
		--type EXE                                   \
		--vcversion "8.00"                           \
		--projectname "LTTSampleComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/LTTSample_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source LTTSample.cpp LTTSampleComp.cpp     \
		--header LTTSample.h
	qkc -sm $(win32_builddir)/LTTSample_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj          \
		--type DLL                                      \
		--vcversion "8.00"                              \
		--projectname "LTTSample"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/LTTSampleDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source LTTSample.cpp                          \
		--header LTTSample.h
	qkc -sm $(win32_builddir)/LTTSampleDll_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj        \
		--type EXE                                    \
		--vcversion "8.00"                            \
		--projectname "TriggerApp"                    \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/TriggerApp_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source TriggerApp.cpp
	qkc -sm $(win32_builddir)/TriggerApp_vc8.vcproj

vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj       \
		--type EXE                                   \
		--vcversion "9.00"                           \
		--projectname "LTTSampleComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/LTTSample_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source LTTSample.cpp LTTSampleComp.cpp     \
		--header LTTSample.h
	qkc -sm $(win32_builddir)/LTTSample_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj          \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "LTTSample"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/LTTSampleDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source LTTSample.cpp                          \
		--header LTTSample.h
	qkc -sm $(win32_builddir)/LTTSampleDll_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj        \
		--type EXE                                    \
		--vcversion "9.00"                            \
		--projectname "TriggerAppComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/TriggerApp_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source TriggerApp.cpp
	qkc -sm $(win32_builddir)/TriggerApp_vc9.vcproj

vc10proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj       \
		--type EXE                                     \
		--vcversion "10.00"                            \
		--projectname "LTTSampleComp"                  \
		--version $(RTM_VERSION)                       \
		--out $(win32_builddir)/LTTSample_vc10.vcxproj \
		--yaml ../rtc.vcxproj.yaml                     \
		--source LTTSample.cpp LTTSampleComp.cpp       \
		--header LTTSample.h
	qkc -sm $(win32_builddir)/LTTSample_vc10.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj          \
		--type DLL                                        \
		--vcversion "10.00"                               \
		--projectname "LTTSample"                         \
		--version $(RTM_VERSION)                          \
		--out $(win32_builddir)/LTTSampleDll_vc10.vcxproj \
		--yaml ../rtcdll.vcxproj.yaml                     \
		--source LTTSample.cpp                            \
		--header LTTSample.h
	qkc -sm $(win32_builddir)/LTTSampleDll_vc10.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj        \
		--type EXE                                      \
		--vcversion "10.00"                             \
		--projectname "TriggerAppComp"                  \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/TriggerApp_vc10.vcxproj \
		--yaml ../rtc.vcxproj.yaml                      \
		--source TriggerApp.cpp
	qkc -sm $(win32_builddir)/TriggerApp_vc10.vcxproj

dist-hook: lst

clean-local:
	rm -f \
	*.bak *.rpo *.sym lib*.*_pure_* *.lst \
	Makefile.old *core *~ *.so *.log
	rm -f $(example_PROGRAMS)

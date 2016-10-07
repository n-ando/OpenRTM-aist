## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for Fsm component
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

AM_CPPFLAGS=-std=c++11 -Wunused-local-typedefs -I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/coil/include -I$(top_srcdir)/src/lib/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/src/lib/rtm -L$(top_builddir)/src/lib/rtm/idl

#------------------------------------------------------------
# Targets
#------------------------------------------------------------
# Targets directories
exampledir = $(rtm_exampledir)
socompdir  = $(exampledir)/rtc
sourcedir  = $(exampledir)/src/SimpleIO

# Loadable RTCs
socomp_LTLIBRARIES = Fsm.la

Fsm_la_SOURCES = Fsm.cc Fsm.h camera.cc camera.h camera_functions.cc camera_functions.h
Fsm_la_LDFLAGS = -module
Fsm_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Fsm_la_LIBADD  = -lPocoFoundation \
	$(top_builddir)/src/lib/hrtm/libHRTM.la \
	$(top_builddir)/src/lib/rtm/libRTC.la  \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

# Standalone RTCs
example_PROGRAMS = FsmComp
example_DATA = rtc.conf

FsmComp_SOURCES = FsmMain.cc
FsmComp_DEPENDENCIES = Fsm.la
FsmComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
FsmComp_LDADD   =  Fsm.o camera.o camera_functions.o \
	-lPocoFoundation \
	$(top_builddir)/src/lib/hrtm/libHRTM.la \
	$(top_builddir)/src/lib/rtm/libRTC.la  \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

# Example sources
source_DATA = $(ALL_SRC) $(EXTRA_DIST)

#------------------------------------------------------------
# Extra distributed files
#------------------------------------------------------------
EXTRA_DIST =                \
	README.Fsm    \
	rtc.conf            \
	fsm.conf

ALL_SRC =               \
	FsmMain.cc          \
	Fsm.cc              \
	Fsm.h               \
	camera.cc           \
	camera.h            \
	camera_functions.cc \
	camera_functions.h

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(ALL_SRC) > src.lst
	echo $(EXTRA_DIST) > other.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/examples/Fsm

vcproj: vc8proj vc9proj vc10proj vc11proj vc12proj vc14proj

vc8proj: 
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "8.00"                           \
		--projectname "FsmComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Fsm_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Fsm.cpp FsmComp.cpp     \
		--header Fsm.h
	qkc -O- -sm $(win32_builddir)/Fsm_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "8.00"                              \
		--projectname "Fsm"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/FsmDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Fsm.cpp                          \
		--header Fsm.h
	qkc -O- -sm $(win32_builddir)/FsmDll_vc8.vcproj


vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "9.00"                           \
		--projectname "FsmComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Fsm_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Fsm.cpp FsmComp.cpp     \
		--header Fsm.h
	qkc -O- -sm $(win32_builddir)/Fsm_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "Fsm"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/FsmDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Fsm.cpp                          \
		--header Fsm.h
	qkc -O- -sm $(win32_builddir)/FsmDll_vc9.vcproj


vc10proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj           \
		--type EXE                                   \
		--vcversion "10.00"                           \
		--projectname "FsmComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Fsm_vc10.vcxproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Fsm.cpp FsmComp.cpp     \
		--header Fsm.h
	qkc -O- -sm $(win32_builddir)/Fsm_vc10.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj              \
		--type DLL                                      \
		--vcversion "10.00"                              \
		--projectname "Fsm"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/FsmDll_vc10.vcxproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Fsm.cpp                          \
		--header Fsm.h
	qkc -O- -sm $(win32_builddir)/FsmDll_vc10.vcxproj


vc11proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj           \
		--type EXE                                   \
		--vcversion "11.00"                           \
		--projectname "FsmComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Fsm_vc11.vcxproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Fsm.cpp FsmComp.cpp     \
		--header Fsm.h
	qkc -O- -sm $(win32_builddir)/Fsm_vc11.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj              \
		--type DLL                                      \
		--vcversion "11.00"                              \
		--projectname "Fsm"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/FsmDll_vc11.vcxproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Fsm.cpp                          \
		--header Fsm.h
	qkc -O- -sm $(win32_builddir)/FsmDll_vc11.vcxproj


vc12proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj           \
		--type EXE                                   \
		--vcversion "12.00"                           \
		--projectname "FsmComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Fsm_vc12.vcxproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Fsm.cpp FsmComp.cpp     \
		--header Fsm.h
	qkc -O- -sm $(win32_builddir)/Fsm_vc12.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj              \
		--type DLL                                      \
		--vcversion "12.00"                              \
		--projectname "Fsm"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/FsmDll_vc12.vcxproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Fsm.cpp                          \
		--header Fsm.h
	qkc -O- -sm $(win32_builddir)/FsmDll_vc12.vcxproj


vc14proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj           \
		--type EXE                                   \
		--vcversion "14.00"                           \
		--projectname "FsmComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Fsm_vc14.vcxproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Fsm.cpp FsmComp.cpp     \
		--header Fsm.h
	qkc -O- -sm $(win32_builddir)/Fsm_vc14.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj              \
		--type DLL                                      \
		--vcversion "14.00"                              \
		--projectname "Fsm"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/FsmDll_vc14.vcxproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Fsm.cpp                          \
		--header Fsm.h
	qkc -O- -sm $(win32_builddir)/FsmDll_vc14.vcxproj


dist-hook: lst vcproj

clean-local:
	rm -f *.bak *.rpo *.sym lib*.*_pure_* 
	rm -f *.lst *.core *~ *.so *.log
	rm -f Makefile.old 

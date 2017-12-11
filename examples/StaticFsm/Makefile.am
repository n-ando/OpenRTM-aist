## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for Inputbutton/Microwave components
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

AM_CPPFLAGS=-I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/coil/include -I$(top_srcdir)/src/lib/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/src/lib/rtm -L$(top_builddir)/src/lib/rtm/idl

#------------------------------------------------------------
# Targets
#------------------------------------------------------------
# Targets directories
exampledir = $(rtm_exampledir)
socompdir  = $(exampledir)/rtc
sourcedir  = $(exampledir)/src/StaticFsm

# Loadable RTCs
socomp_LTLIBRARIES = Inputbutton.la Microwave.la Display.la

Inputbutton_la_SOURCES = Inputbutton.cpp Inputbutton.h
Inputbutton_la_LDFLAGS = -module
Inputbutton_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Inputbutton_la_LIBADD  = \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

Microwave_la_SOURCES = \
	MicrowaveFsm.cpp MicrowaveFsm.h \
	Microwave.cpp Microwave.h
Microwave_la_LDFLAGS = -module
Microwave_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Microwave_la_LIBADD  = \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

Display_la_SOURCES = Display.cpp Display.h
Display_la_LDFLAGS = -module
Display_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Display_la_LIBADD  = \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

# Standalone RTCs
example_PROGRAMS = InputbuttonComp MicrowaveComp DisplayComp
example_DATA = rtc.conf inputbutton.conf microwave.conf display.conf

InputbuttonComp_SOURCES = InputbuttonComp.cpp
#InputbuttonComp_DEPENDENCIES = Inputbutton.la
InputbuttonComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
InputbuttonComp_LDADD   =  Inputbutton.o \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

MicrowaveComp_SOURCES = MicrowaveComp.cpp
#MicrowaveComp_DEPENDENCIES = Microwave.la MicrowaveFsm.la
MicrowaveComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
MicrowaveComp_LDADD   = Microwave.o MicrowaveFsm.o \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

DisplayComp_SOURCES = DisplayComp.cpp
DisplayComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
DisplayComp_LDADD   = Display.o \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

# Example sources
source_DATA = $(ALL_SRC) $(EXTRA_DIST)

#------------------------------------------------------------
# Extra distributed files
#------------------------------------------------------------
EXTRA_DIST =            \
	run.sh              \
	rtc.conf            \
	inputbutton.conf    \
	microwave.conf      \
	display.conf

ALL_SRC =                \
	InputbuttonComp.cpp  \
	Inputbutton.cpp      \
	Inputbutton.h        \
	MicrowaveComp.cpp    \
	Microwave.cpp        \
	Microwave.h          \
	DisplayComp.cpp      \
	Display.cpp          \
	Display.h

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(ALL_SRC) > src.lst
	echo $(EXTRA_DIST) > other.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/examples/SimpleIO

vcproj: vc8proj vc9proj vc10proj vc11proj vc12proj vc14proj

vc8proj: 
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "8.00"                           \
		--projectname "InputbuttonComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Inputbutton_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Inputbutton.cpp InputbuttonComp.cpp     \
		--header Inputbutton.h
	qkc -O- -sm $(win32_builddir)/Inputbutton_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "8.00"                              \
		--projectname "Inputbutton"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/InputbuttonDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Inputbutton.cpp                          \
		--header Inputbutton.h
	qkc -O- -sm $(win32_builddir)/InputbuttonDll_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj            \
		--type EXE                                    \
		--vcversion "8.00"                            \
		--projectname "MicrowaveComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/Microwave_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source Microwave.cpp MicrowaveComp.cpp    \
		--header Microwave.h
	qkc -O- -sm $(win32_builddir)/Microwave_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj               \
		--type DLL                                       \
		--vcversion "8.00"                               \
		--projectname "Microwave"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/MicrowaveDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source Microwave.cpp                          \
		--header Microwave.h
	qkc -O- -sm $(win32_builddir)/MicrowaveDll_vc8.vcproj

vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "9.00"                           \
		--projectname "InputbuttonComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Inputbutton_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Inputbutton.cpp InputbuttonComp.cpp     \
		--header Inputbutton.h
	qkc -O- -sm $(win32_builddir)/Inputbutton_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "Inputbutton"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/InputbuttonDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Inputbutton.cpp                          \
		--header Inputbutton.h
	qkc -O- -sm $(win32_builddir)/InputbuttonDll_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj            \
		--type EXE                                    \
		--vcversion "9.00"                            \
		--projectname "MicrowaveComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/Microwave_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source Microwave.cpp MicrowaveComp.cpp    \
		--header Microwave.h
	qkc -O- -sm $(win32_builddir)/Microwave_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj               \
		--type DLL                                       \
		--vcversion "9.00"                               \
		--projectname "Microwave"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/MicrowaveDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source Microwave.cpp                          \
		--header Microwave.h
	qkc -O- -sm $(win32_builddir)/MicrowaveDll_vc9.vcproj

vc10proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj           \
		--type EXE                                   \
		--vcversion "10.00"                           \
		--projectname "InputbuttonComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Inputbutton_vc10.vcxproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Inputbutton.cpp InputbuttonComp.cpp     \
		--header Inputbutton.h
	qkc -O- -sm $(win32_builddir)/Inputbutton_vc10.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj              \
		--type DLL                                      \
		--vcversion "10.00"                              \
		--projectname "Inputbutton"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/InputbuttonDll_vc10.vcxproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Inputbutton.cpp                          \
		--header Inputbutton.h
	qkc -O- -sm $(win32_builddir)/InputbuttonDll_vc10.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj            \
		--type EXE                                    \
		--vcversion "10.00"                            \
		--projectname "MicrowaveComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/Microwave_vc10.vcxproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source Microwave.cpp MicrowaveComp.cpp    \
		--header Microwave.h
	qkc -O- -sm $(win32_builddir)/Microwave_vc10.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj               \
		--type DLL                                       \
		--vcversion "10.00"                               \
		--projectname "Microwave"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/MicrowaveDll_vc10.vcxproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source Microwave.cpp                          \
		--header Microwave.h
	qkc -O- -sm $(win32_builddir)/MicrowaveDll_vc10.vcxproj

vc11proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj           \
		--type EXE                                   \
		--vcversion "11.00"                           \
		--projectname "InputbuttonComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Inputbutton_vc11.vcxproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Inputbutton.cpp InputbuttonComp.cpp     \
		--header Inputbutton.h
	qkc -O- -sm $(win32_builddir)/Inputbutton_vc11.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj              \
		--type DLL                                      \
		--vcversion "11.00"                              \
		--projectname "Inputbutton"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/InputbuttonDll_vc11.vcxproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Inputbutton.cpp                          \
		--header Inputbutton.h
	qkc -O- -sm $(win32_builddir)/InputbuttonDll_vc11.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj            \
		--type EXE                                    \
		--vcversion "11.00"                            \
		--projectname "MicrowaveComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/Microwave_vc11.vcxproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source Microwave.cpp MicrowaveComp.cpp    \
		--header Microwave.h
	qkc -O- -sm $(win32_builddir)/Microwave_vc11.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj               \
		--type DLL                                       \
		--vcversion "11.00"                               \
		--projectname "Microwave"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/MicrowaveDll_vc11.vcxproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source Microwave.cpp                          \
		--header Microwave.h
	qkc -O- -sm $(win32_builddir)/MicrowaveDll_vc11.vcxproj

vc12proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj           \
		--type EXE                                   \
		--vcversion "12.00"                           \
		--projectname "InputbuttonComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Inputbutton_vc12.vcxproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Inputbutton.cpp InputbuttonComp.cpp     \
		--header Inputbutton.h
	qkc -O- -sm $(win32_builddir)/Inputbutton_vc12.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj              \
		--type DLL                                      \
		--vcversion "12.00"                              \
		--projectname "Inputbutton"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/InputbuttonDll_vc12.vcxproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Inputbutton.cpp                          \
		--header Inputbutton.h
	qkc -O- -sm $(win32_builddir)/InputbuttonDll_vc12.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj            \
		--type EXE                                    \
		--vcversion "12.00"                            \
		--projectname "MicrowaveComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/Microwave_vc12.vcxproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source Microwave.cpp MicrowaveComp.cpp    \
		--header Microwave.h
	qkc -O- -sm $(win32_builddir)/Microwave_vc12.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj               \
		--type DLL                                       \
		--vcversion "12.00"                               \
		--projectname "Microwave"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/MicrowaveDll_vc12.vcxproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source Microwave.cpp                          \
		--header Microwave.h
	qkc -O- -sm $(win32_builddir)/MicrowaveDll_vc12.vcxproj

vc14proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj           \
		--type EXE                                   \
		--vcversion "14.00"                           \
		--projectname "InputbuttonComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Inputbutton_vc14.vcxproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Inputbutton.cpp InputbuttonComp.cpp     \
		--header Inputbutton.h
	qkc -O- -sm $(win32_builddir)/Inputbutton_vc14.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj              \
		--type DLL                                      \
		--vcversion "14.00"                              \
		--projectname "Inputbutton"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/InputbuttonDll_vc14.vcxproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Inputbutton.cpp                          \
		--header Inputbutton.h
	qkc -O- -sm $(win32_builddir)/InputbuttonDll_vc14.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj            \
		--type EXE                                    \
		--vcversion "14.00"                            \
		--projectname "MicrowaveComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/Microwave_vc14.vcxproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source Microwave.cpp MicrowaveComp.cpp    \
		--header Microwave.h
	qkc -O- -sm $(win32_builddir)/Microwave_vc14.vcxproj
	$(top_builddir)/build/vcxprojtool.py vcxproj               \
		--type DLL                                       \
		--vcversion "14.00"                               \
		--projectname "Microwave"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/MicrowaveDll_vc14.vcxproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source Microwave.cpp                          \
		--header Microwave.h
	qkc -O- -sm $(win32_builddir)/MicrowaveDll_vc14.vcxproj

dist-hook: lst vcproj

clean-local:
	rm -f *.bak *.rpo *.sym lib*.*_pure_* 
	rm -f *.lst *.core *~ *.so *.log
	rm -f Makefile.old 

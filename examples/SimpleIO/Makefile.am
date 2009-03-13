## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for ConsoleIn/ConsoleOut components
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
exampledir = $(pkgdatadir)/examples
socompdir  = $(exampledir)/rtcs
sourcedir  = $(exampledir)/src/SimpleIO

# Loadable RTCs
socomp_LTLIBRARIES = ConsoleIn.la ConsoleOut.la

ConsoleIn_la_SOURCES = ConsoleIn.cpp ConsoleIn.h
ConsoleIn_la_LDFLAGS = -module
ConsoleIn_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
ConsoleIn_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la

ConsoleOut_la_SOURCES = ConsoleOut.cpp ConsoleOut.h
ConsoleOut_la_LDFLAGS = -module
ConsoleOut_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
ConsoleOut_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la

# Standalone RTCs
example_PROGRAMS = ConsoleInComp ConsoleOutComp
noinst_PROGRAMS = ConnectorComp
example_DATA = rtc.conf consin.conf consout.conf

ConsoleInComp_SOURCES = ConsoleInComp.cpp 
ConsoleInComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
ConsoleInComp_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la ConsoleIn.o

ConsoleOutComp_SOURCES = ConsoleOutComp.cpp 
ConsoleOutComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
ConsoleOutComp_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la ConsoleOut.o

ConnectorComp_SOURCES = ConnectorComp.cpp
ConnectorComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
ConnectorComp_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la

# Example sources
source_DATA = $(ALL_SRC) $(EXTRA_DIST)

#------------------------------------------------------------
# Extra distributed files
#------------------------------------------------------------
EXTRA_DIST =                \
	run.sh              \
	gen.sh              \
	Makefile.ConsoleIn  \
	Makefile.ConsoleOut \
	README.ConsoleIn    \
	README.ConsoleOut   \
	rtc.conf            \
	consin.conf         \
	consout.conf

ALL_SRC =                  \
	ConsoleInComp.cpp  \
	ConsoleIn.cpp      \
	ConsoleIn.h        \
	ConsoleOutComp.cpp \
	ConsoleOut.cpp     \
	ConsoleOut.h       \
	ConnectorComp.cpp

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

vcproj: vc8proj vc9proj

vc8proj: 
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "8.00"                           \
		--projectname "ConsoleInComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/ConsoleIn_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source ConsoleIn.cpp ConsoleInComp.cpp     \
		--header ConsoleIn.h
	qkc -sm $(win32_builddir)/ConsoleIn_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "8.00"                              \
		--projectname "ConsoleIn"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/ConsoleInDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source ConsoleIn.cpp                          \
		--header ConsoleIn.h
	qkc -sm $(win32_builddir)/ConsoleInDll_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj            \
		--type EXE                                    \
		--vcversion "8.00"                            \
		--projectname "ConsoleOutComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/ConsoleOut_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source ConsoleOut.cpp ConsoleOutComp.cpp    \
		--header ConsoleOut.h
	qkc -sm $(win32_builddir)/ConsoleOut_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj               \
		--type DLL                                       \
		--vcversion "8.00"                               \
		--projectname "ConsoleOut"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/ConsoleOutDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source ConsoleOut.cpp                          \
		--header ConsoleOut.h
	qkc -sm $(win32_builddir)/ConsoleOutDll_vc8.vcproj

vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "9.00"                           \
		--projectname "ConsoleInComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/ConsoleIn_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source ConsoleIn.cpp ConsoleInComp.cpp     \
		--header ConsoleIn.h
	qkc -sm $(win32_builddir)/ConsoleIn_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "ConsoleIn"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/ConsoleInDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source ConsoleIn.cpp                          \
		--header ConsoleIn.h
	qkc -sm $(win32_builddir)/ConsoleInDll_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj            \
		--type EXE                                    \
		--vcversion "9.00"                            \
		--projectname "ConsoleOutComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/ConsoleOut_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source ConsoleOut.cpp ConsoleOutComp.cpp    \
		--header ConsoleOut.h
	qkc -sm $(win32_builddir)/ConsoleOut_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj               \
		--type DLL                                       \
		--vcversion "9.00"                               \
		--projectname "ConsoleOut"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/ConsoleOutDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source ConsoleOut.cpp                          \
		--header ConsoleOut.h
	qkc -sm $(win32_builddir)/ConsoleOutDll_vc9.vcproj

dist-hook: lst vcproj

clean-local:
	rm -f \
	*.bak *.rpo *.sym lib*.*_pure_* *.lst \
	Makefile.old *core *~ *.so *.log

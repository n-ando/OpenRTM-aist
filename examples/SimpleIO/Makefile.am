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
exampledir = $(rtm_exampledir)
socompdir  = $(exampledir)/rtc
sourcedir  = $(exampledir)/src/SimpleIO

# Loadable RTCs
socomp_LTLIBRARIES = ConsoleIn.la ConsoleOut.la

ConsoleIn_la_SOURCES = ConsoleIn.cpp ConsoleIn.h
ConsoleIn_la_LDFLAGS = -module
ConsoleIn_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
ConsoleIn_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

ConsoleOut_la_SOURCES = ConsoleOut.cpp ConsoleOut.h
ConsoleOut_la_LDFLAGS = -module
ConsoleOut_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
ConsoleOut_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

# Standalone RTCs
example_PROGRAMS = ConsoleInComp ConsoleOutComp
noinst_PROGRAMS = ConnectorComp
example_DATA = rtc.conf consin.conf consout.conf component.conf

ConsoleInComp_SOURCES = ConsoleInComp.cpp 
ConsoleInComp_DEPENDENCIES = ConsoleIn.la
ConsoleInComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
ConsoleInComp_LDADD   =  ConsoleIn.o \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

ConsoleOutComp_SOURCES = ConsoleOutComp.cpp 
ConsoleOutComp_DEPENDENCIES = ConsoleOut.la
ConsoleOutComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
ConsoleOutComp_LDADD   =  ConsoleOut.o \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

ConnectorComp_SOURCES = ConnectorComp.cpp
ConnectorComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
ConnectorComp_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

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
	consout.conf        \
	component.conf      

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

vcproj: vc9proj vcxproj

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
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "ConsoleIn"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/ConsoleInDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source ConsoleIn.cpp                          \
		--header ConsoleIn.h
	$(top_builddir)/build/vcprojtool.py vcproj            \
		--type EXE                                    \
		--vcversion "9.00"                            \
		--projectname "ConsoleOutComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/ConsoleOut_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source ConsoleOut.cpp ConsoleOutComp.cpp    \
		--header ConsoleOut.h
	$(top_builddir)/build/vcprojtool.py vcproj               \
		--type DLL                                       \
		--vcversion "9.00"                               \
		--projectname "ConsoleOut"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/ConsoleOutDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source ConsoleOut.cpp                          \
		--header ConsoleOut.h

vcxproj:
	for ver in $(VC_VERSION); do \
		$(top_builddir)/build/vcxprojtool.py vcxproj           \
			--type EXE                                   \
			--vcversion "$${ver}.00"                           \
			--projectname "ConsoleInComp"                \
			--version $(RTM_VERSION)                     \
			--out $(win32_builddir)/ConsoleIn_vc$${ver}.vcxproj \
			--yaml ../rtc.vcproj.yaml                    \
			--source ConsoleIn.cpp ConsoleInComp.cpp     \
			--header ConsoleIn.h ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj              \
			--type DLL                                      \
			--vcversion "$${ver}.00"                              \
			--projectname "ConsoleIn"                       \
			--version $(RTM_VERSION)                        \
			--out $(win32_builddir)/ConsoleInDll_vc$${ver}.vcxproj \
			--yaml ../rtcdll.vcproj.yaml                    \
			--source ConsoleIn.cpp                          \
			--header ConsoleIn.h ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj            \
			--type EXE                                    \
			--vcversion "$${ver}.00"                            \
			--projectname "ConsoleOutComp"                \
			--version $(RTM_VERSION)                      \
			--out $(win32_builddir)/ConsoleOut_vc$${ver}.vcxproj \
			--yaml ../rtc.vcproj.yaml                     \
			--source ConsoleOut.cpp ConsoleOutComp.cpp    \
			--header ConsoleOut.h ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj               \
			--type DLL                                       \
			--vcversion "$${ver}.00"                               \
			--projectname "ConsoleOut"                       \
			--version $(RTM_VERSION)                         \
			--out $(win32_builddir)/ConsoleOutDll_vc$${ver}.vcxproj \
			--yaml ../rtcdll.vcproj.yaml                     \
			--source ConsoleOut.cpp                          \
			--header ConsoleOut.h ; \
	done

dist-hook: lst vcproj

clean-local:
	rm -f *.bak *.rpo *.sym lib*.*_pure_* 
	rm -f *.lst *.core *~ *.so *.log
	rm -f Makefile.old 

## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for ConsoleIn/ConsoleOut components
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS=-I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/coil/include -I$(top_srcdir)/src/lib/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/src/lib/rtm -L$(top_builddir)/src/lib/rtm/idl

#------------------------------------------------------------
# Targets
#------------------------------------------------------------
# Targets directories
exampledir = $(rtm_exampledir)
socompdir  = $(exampledir)/rtc
sourcedir  = $(exampledir)/src/ExtTrigger

# Standalone RTCs
example_PROGRAMS = ExtConsoleInComp ExtConsoleOutComp ExtConnectorComp
example_DATA = rtc.conf

ExtConsoleInComp_SOURCES = ConsoleInComp.cpp ConsoleIn.cpp ConsoleIn.h
ExtConsoleInComp_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la
ExtConsoleInComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs

ExtConsoleOutComp_SOURCES = ConsoleOutComp.cpp ConsoleOut.cpp ConsoleOut.h
ExtConsoleOutComp_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la
ExtConsoleOutComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs

ExtConnectorComp_SOURCES = ConnectorComp.cpp
ExtConnectorComp_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la
ExtConnectorComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs

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
	rtc.conf            

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
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/examples/ExtTrigger

vcproj: vc9proj vcxproj

vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "9.00"                           \
		--projectname "ExtConsoleInComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/ConsoleIn_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source ConsoleIn.cpp ConsoleInComp.cpp     \
		--header ConsoleIn.h
	qkc -O- -sm $(win32_builddir)/ConsoleIn_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "ExtConsoleIn"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/ConsoleInDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source ConsoleIn.cpp                          \
		--header ConsoleIn.h
	qkc -O- -sm $(win32_builddir)/ConsoleInDll_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj            \
		--type EXE                                    \
		--vcversion "9.00"                            \
		--projectname "ExtConsoleOutComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/ConsoleOut_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source ConsoleOut.cpp ConsoleOutComp.cpp    \
		--header ConsoleOut.h
	qkc -O- -sm $(win32_builddir)/ConsoleOut_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj               \
		--type DLL                                       \
		--vcversion "9.00"                               \
		--projectname "ExtConsoleOut"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/ConsoleOutDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source ConsoleOut.cpp                          \
		--header ConsoleOut.h
	qkc -O- -sm $(win32_builddir)/ConsoleOutDll_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj               \
		--type EXE                                       \
		--vcversion "9.00"                               \
		--projectname "ExtConnectorComp"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/ConnectorComp_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source ConnectorComp.cpp

vcxproj:
	for ver in $(VC_VERSION); do \
		$(top_builddir)/build/vcxprojtool.py vcxproj           \
			--type EXE                                   \
			--vcversion "$${ver}.00"                           \
			--projectname "ExtConsoleInComp"                \
			--version $(RTM_VERSION)                     \
			--out $(win32_builddir)/ConsoleIn_vc$${ver}.vcxproj \
			--yaml ../rtc.vcproj.yaml                    \
			--source ConsoleIn.cpp ConsoleInComp.cpp     \
			--header ConsoleIn.h ; \
		qkc -O- -sm $(win32_builddir)/ConsoleIn_vc$${ver}.vcxproj ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj              \
			--type DLL                                      \
			--vcversion "$${ver}.00"                              \
			--projectname "ExtConsoleIn"                       \
			--version $(RTM_VERSION)                        \
			--out $(win32_builddir)/ConsoleInDll_vc$${ver}.vcxproj \
			--yaml ../rtcdll.vcproj.yaml                    \
			--source ConsoleIn.cpp                          \
			--header ConsoleIn.h ; \
		qkc -O- -sm $(win32_builddir)/ConsoleInDll_vc$${ver}.vcxproj ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj            \
			--type EXE                                    \
			--vcversion "$${ver}.00"                            \
			--projectname "ExtConsoleOutComp"                \
			--version $(RTM_VERSION)                      \
			--out $(win32_builddir)/ConsoleOut_vc$${ver}.vcxproj \
			--yaml ../rtc.vcproj.yaml                     \
			--source ConsoleOut.cpp ConsoleOutComp.cpp    \
			--header ConsoleOut.h ; \
		qkc -O- -sm $(win32_builddir)/ConsoleOut_vc$${ver}.vcxproj ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj               \
			--type DLL                                       \
			--vcversion "$${ver}.00"                               \
			--projectname "ExtConsoleOut"                       \
			--version $(RTM_VERSION)                         \
			--out $(win32_builddir)/ConsoleOutDll_vc$${ver}.vcxproj \
			--yaml ../rtcdll.vcproj.yaml                     \
			--source ConsoleOut.cpp                          \
			--header ConsoleOut.h ; \
		qkc -O- -sm $(win32_builddir)/ConsoleOutDll_vc$${ver}.vcxproj ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj               \
			--type EXE                                       \
			--vcversion "$${ver}.00"                               \
			--projectname "ExtConnectorComp"                       \
			--version $(RTM_VERSION)                         \
			--out $(win32_builddir)/ConnectorComp_vc$${ver}.vcxproj \
			--yaml ../rtc.vcproj.yaml                     \
			--source ConnectorComp.cpp ; \
	done

dist-hook: lst vcproj

clean-local:
	rm -f \
	*.bak *.rpo *.sym lib*.*_pure_* *.lst \
	Makefile.old *core *~ *.so *.log
	rm -f $(example_PROGRAMS)

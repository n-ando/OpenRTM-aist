## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for performance Analyzer components
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
sourcedir  = $(exampledir)/src/Analyzer

# Loadable RTCs
socomp_LTLIBRARIES = Analyzer.la Analyzer_test.la

Analyzer_la_SOURCES = Analyzer.cpp Analyzer.h
Analyzer_la_LDFLAGS = -module
Analyzer_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Analyzer_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

Analyzer_test_la_SOURCES = Analyzer_test.cpp Analyzer_test.h
Analyzer_test_la_LDFLAGS = -module
Analyzer_test_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Analyzer_test_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

# Standalone RTCs
example_PROGRAMS = AnalyzerComp Analyzer_testComp
noinst_PROGRAMS = ConnectorComp
example_DATA = rtc.conf consin.conf consout.conf component.conf

AnalyzerComp_SOURCES = AnalyzerComp.cpp 
AnalyzerComp_DEPENDENCIES = Analyzer.la
AnalyzerComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
AnalyzerComp_LDADD   =  Analyzer.o \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

Analyzer_testComp_SOURCES = Analyzer_testComp.cpp 
Analyzer_testComp_DEPENDENCIES = Analyzer_test.la
Analyzer_testComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
Analyzer_testComp_LDADD   =  Analyzer_test.o \
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
	Makefile.Analyzer  \
	Makefile.Analyzer_test \
	README.Analyzer    \
	README.Analyzer_test   \
	rtc.conf            \
	consin.conf         \
	consout.conf        \
	component.conf      

ALL_SRC =                  \
	AnalyzerComp.cpp  \
	Analyzer.cpp      \
	Analyzer.h        \
	Analyzer_testComp.cpp \
	Analyzer_test.cpp     \
	Analyzer_test.h       \
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
		--projectname "AnalyzerComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Analyzer_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Analyzer.cpp AnalyzerComp.cpp     \
		--header Analyzer.h
	qkc -O- -sm $(win32_builddir)/Analyzer_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "Analyzer"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/AnalyzerDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Analyzer.cpp                          \
		--header Analyzer.h
	qkc -O- -sm $(win32_builddir)/AnalyzerDll_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj            \
		--type EXE                                    \
		--vcversion "9.00"                            \
		--projectname "Analyzer_testComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/Analyzer_test_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source Analyzer_test.cpp Analyzer_testComp.cpp    \
		--header Analyzer_test.h
	qkc -O- -sm $(win32_builddir)/Analyzer_test_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj               \
		--type DLL                                       \
		--vcversion "9.00"                               \
		--projectname "Analyzer_test"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/Analyzer_testDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source Analyzer_test.cpp                          \
		--header Analyzer_test.h
	qkc -O- -sm $(win32_builddir)/Analyzer_testDll_vc9.vcproj

vcxproj:
	for ver in $(VC_VERSION); do \
		$(top_builddir)/build/vcxprojtool.py vcxproj           \
			--type EXE                                   \
			--vcversion "$${ver}.00"                           \
			--projectname "AnalyzerComp"                \
			--version $(RTM_VERSION)                     \
			--out $(win32_builddir)/Analyzer_vc$${ver}.vcxproj \
			--yaml ../rtc.vcproj.yaml                    \
			--source Analyzer.cpp AnalyzerComp.cpp     \
			--header Analyzer.h ; \
		qkc -O- -sm $(win32_builddir)/Analyzer_vc$${ver}.vcxproj ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj              \
			--type DLL                                      \
			--vcversion "$${ver}.00"                              \
			--projectname "Analyzer"                       \
			--version $(RTM_VERSION)                        \
			--out $(win32_builddir)/AnalyzerDll_vc$${ver}.vcxproj \
			--yaml ../rtcdll.vcproj.yaml                    \
			--source Analyzer.cpp                          \
			--header Analyzer.h ; \
		qkc -O- -sm $(win32_builddir)/AnalyzerDll_vc$${ver}.vcxproj ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj            \
			--type EXE                                    \
			--vcversion "$${ver}.00"                            \
			--projectname "Analyzer_testComp"                \
			--version $(RTM_VERSION)                      \
			--out $(win32_builddir)/Analyzer_test_vc$${ver}.vcxproj \
			--yaml ../rtc.vcproj.yaml                     \
			--source Analyzer_test.cpp Analyzer_testComp.cpp    \
			--header Analyzer_test.h ; \
		qkc -O- -sm $(win32_builddir)/Analyzer_test_vc$${ver}.vcxproj ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj               \
			--type DLL                                       \
			--vcversion "$${ver}.00"                               \
			--projectname "Analyzer_test"                       \
			--version $(RTM_VERSION)                         \
			--out $(win32_builddir)/Analyzer_testDll_vc$${ver}.vcxproj \
			--yaml ../rtcdll.vcproj.yaml                     \
			--source Analyzer_test.cpp                          \
			--header Analyzer_test.h ; \
		qkc -O- -sm $(win32_builddir)/Analyzer_testDll_vc$${ver}.vcxproj ; \
	done

dist-hook: lst vcproj

clean-local:
	rm -f *.bak *.rpo *.sym lib*.*_pure_* 
	rm -f *.lst *.core *~ *.so *.log
	rm -f Makefile.old 

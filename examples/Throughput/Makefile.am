## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for performance Throughput components
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
sourcedir  = $(exampledir)/src/Throughput

# Loadable RTCs
socomp_LTLIBRARIES = Throughput.la

Throughput_la_SOURCES = Throughput.cpp Throughput.h
Throughput_la_LDFLAGS = -module
Throughput_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Throughput_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

# Standalone RTCs
example_PROGRAMS = ThroughputComp
example_DATA = rtc.conf

ThroughputComp_SOURCES = ThroughputComp.cpp 
ThroughputComp_DEPENDENCIES = Throughput.la
ThroughputComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
ThroughputComp_LDADD   =  Throughput.o \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

# Example sources
source_DATA = $(ALL_SRC) $(EXTRA_DIST)

#------------------------------------------------------------
# Extra distributed files
#------------------------------------------------------------
EXTRA_DIST =                \
	CMakeLists.txt      \
	run.sh              \
	direct.sh           \
	cdr_samecomp.sh     \
	cdr_sameproc.sh     \
	rtc.conf

ALL_SRC =                   \
	ThroughputComp.cpp  \
	Throughput.cpp      \
	Throughput.h


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
		--projectname "ThroughputComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Throughput_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Throughput.cpp ThroughputComp.cpp     \
		--header Throughput.h
	qkc -O- -sm $(win32_builddir)/Throughput_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "Throughput"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/ThroughputDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Throughput.cpp                          \
		--header Throughput.h
	qkc -O- -sm $(win32_builddir)/ThroughputDll_vc9.vcproj

vcxproj:
	for ver in $(VC_VERSION); do \
		$(top_builddir)/build/vcxprojtool.py vcxproj           \
			--type EXE                                   \
			--vcversion "$${ver}.00"                           \
			--projectname "ThroughputComp"                \
			--version $(RTM_VERSION)                     \
			--out $(win32_builddir)/Throughput_vc$${ver}.vcxproj \
			--yaml ../rtc.vcproj.yaml                    \
			--source Throughput.cpp ThroughputComp.cpp     \
			--header Throughput.h ; \
		qkc -O- -sm $(win32_builddir)/Throughput_vc$${ver}.vcxproj ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj              \
			--type DLL                                      \
			--vcversion "$${ver}.00"                              \
			--projectname "Throughput"                       \
			--version $(RTM_VERSION)                        \
			--out $(win32_builddir)/ThroughputDll_vc$${ver}.vcxproj \
			--yaml ../rtcdll.vcproj.yaml                    \
			--source Throughput.cpp                          \
			--header Throughput.h ; \
		qkc -O- -sm $(win32_builddir)/ThroughputDll_vc$${ver}.vcxproj ; \
	done

dist-hook: lst vcproj

clean-local:
	rm -f *.bak *.rpo *.sym lib*.*_pure_* 
	rm -f *.dat *.lst *.core *~ *.so *.log
	rm -f Makefile.old 

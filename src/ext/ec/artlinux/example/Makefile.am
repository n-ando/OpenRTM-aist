## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for ConsoleIn/ConsoleOut components
##
## $Id: Makefile.am 2086 2011-05-09 04:46:15Z fsi-katami $
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
sourcedir  = $(exampledir)/src/ARTSample

# Standalone RTCs
example_PROGRAMS = ARTSampleComp
example_DATA = rtc.conf

ARTSampleComp_SOURCES = ARTSampleComp.cpp ARTSample.cpp ARTSample.h
ARTSampleComp_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la
ARTSampleComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs

# Example sources
source_DATA = $(ALL_SRC) $(EXTRA_DIST)

#------------------------------------------------------------
# Extra distributed files
#------------------------------------------------------------
EXTRA_DIST = rtc.conf

ALL_SRC = $(ARTSampleComp_SOURCES)

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
#lst:
#	echo $(ALL_SRC) > src.lst
#	echo $(EXTRA_DIST) > other.lst

clean-local:
	rm -f *.bak *.rpo *.sym lib*.*_pure_* *.lst
	rm -f Makefile.old *core *~ *.so *.log
	rm -f $(example_PROGRAMS)
	rm -rf idl

## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for ConsoleIn/ConsoleOut components
##
## $Id: Makefile.am,v 1.1 2007-04-23 07:26:43 n-ando Exp $
##
## $Log: not supported by cvs2svn $
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

clean-local:
	rm -f \
	*.gch *.bak *.rpo *.sym lib*.*_pure_* \
	Makefile.old *core *~ *.so *.log


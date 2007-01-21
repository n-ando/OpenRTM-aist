## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for ConsoleIn/ConsoleOut components
##
## $Id: Makefile.am,v 1.3 2007-01-21 13:35:17 n-ando Exp $
##
## $Log: not supported by cvs2svn $
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

noinst_LTLIBRARIES = libConsoleIn.la libConsoleOut.la
libConsoleIn_la_SOURCES = ConsoleIn.cpp ConsoleIn.h
libConsoleIn_la_LIBADD = $(top_builddir)/rtm/libRTC.la
libConsoleIn_la_FLAGS = -L$(top_builddir)/rtm/.lib

libConsoleOut_la_SOURCES = ConsoleOut.cpp ConsoleOut.h
libConsoleOut_la_LIBADD = $(top_builddir)/rtm/libRTC.la
libConsoleOut_la_FLAGS = -L$(top_builddir)/rtm/.lib

noinst_PROGRAMS = ConsoleInComp ConsoleOutComp ConnectorComp
ConsoleInComp_SOURCES = ConsoleInComp.cpp 
ConsoleInComp_LDADD = $(top_builddir)/rtm/libRTC.la ConsoleIn.o
ConsoleInComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

ConsoleOutComp_SOURCES = ConsoleOutComp.cpp 
ConsoleOutComp_LDADD = $(top_builddir)/rtm/libRTC.la ConsoleOut.o
ConsoleOutComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

ConnectorComp_SOURCES = ConnectorComp.cpp
ConnectorComp_LDADD = $(top_builddir)/rtm/libRTC.la
ConnectorComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

EXTRA_DIST =                \
	run.sh              \
	gen.sh              \
	Makefile.ConsoleIn  \
	Makefile.ConsoleOut \
	README.ConsoleIn    \
	README.ConsoleOut

clean-local:
	rm -f \
	*.bak *.rpo *.sym lib*.*_pure_* \
	Makefile.old *core *~ *.so *.log\
	rtc.conf

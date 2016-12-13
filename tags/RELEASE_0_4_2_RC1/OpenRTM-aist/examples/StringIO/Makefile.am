## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for StringIn/StringOut components
##
## $Id: Makefile.am,v 1.1.1.1 2005-05-12 09:06:20 n-ando Exp $
##
## $Log: not supported by cvs2svn $
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/rtm -L$(top_builddir)/rtm/idl

noinst_LTLIBRARIES = libStringIn.la libStringOut.la
libStringIn_la_SOURCES = StringIn.cpp StringIn.h
libStringIn_la_LIBADD = $(top_builddir)/rtm/libRTC.la
libStringIn_la_FLAGS = -L$(top_builddir)/rtm/.lib

libStringOut_la_SOURCES = StringOut.cpp StringOut.h
libStringOut_la_LIBADD = $(top_builddir)/rtm/libRTC.la
libStringOut_la_FLAGS = -L$(top_builddir)/rtm/.lib

noinst_PROGRAMS = StringInComp StringOutComp
StringInComp_SOURCES = StringInComp.cpp 
StringInComp_LDADD = $(top_builddir)/rtm/libRTC.la StringIn.o
StringInComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

StringOutComp_SOURCES = StringOutComp.cpp 
StringOutComp_LDADD = $(top_builddir)/rtm/libRTC.la StringOut.o
StringOutComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

EXTRA_DIST = \
	Makefile.StringIn \
	Makefile.StringOut

clean-local:
	rm -f *.bak *.rpo *.sym lib*.*_pure_* Makefile.old *core *~

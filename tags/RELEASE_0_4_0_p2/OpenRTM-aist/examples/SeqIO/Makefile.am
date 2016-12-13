## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for SeqIn/SeqOut components
##
## $Id: Makefile.am,v 1.2.2.1 2007-07-22 14:26:32 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.2  2007/02/04 16:47:25  n-ando
## Updated for 0.4.0.
##
## Revision 1.1.1.1  2005/05/12 09:06:20  n-ando
## Public release.
##
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/rtm -L$(top_builddir)/rtm/idl

noinst_LTLIBRARIES = libSeqIn.la libSeqOut.la
libSeqIn_la_SOURCES = SeqIn.cpp SeqIn.h
libSeqIn_la_LIBADD = $(top_builddir)/rtm/libRTC.la
libSeqIn_la_FLAGS = -L$(top_builddir)/rtm/.lib

libSeqOut_la_SOURCES = SeqOut.cpp SeqOut.h
libSeqOut_la_LIBADD = $(top_builddir)/rtm/libRTC.la
libSeqOut_la_FLAGS = -L$(top_builddir)/rtm/.lib

noinst_PROGRAMS = SeqInComp SeqOutComp
SeqInComp_SOURCES = SeqInComp.cpp 
SeqInComp_LDADD = $(top_builddir)/rtm/libRTC.la SeqIn.o
SeqInComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

SeqOutComp_SOURCES = SeqOutComp.cpp 
SeqOutComp_LDADD = $(top_builddir)/rtm/libRTC.la SeqOut.o
SeqOutComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

EXTRA_DIST =            \
	Makefile.SeqIn  \
	Makefile.SeqOut \
	README.SeqIn    \
	README.SeqOut   \
	gen.sh          \
	rtc.conf

clean-local:
	rm -f *.bak *.rpo *.sym lib*.*_pure_* Makefile.old *core *~

## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile for rtcd
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_buiddir)/rtm -L$(top_builddir)/rtm/idl

bin_PROGRAMS = rtcd

rtcd_SOURCES = rtcd.cpp

rtcd_LDADD = $(top_builddir)/rtm/libRTC.la

rtcd_LDFLAGS = -L$(top_builddir)/rtm

clean-local:
	rm -rf rtcd *.o *~ *core .libs

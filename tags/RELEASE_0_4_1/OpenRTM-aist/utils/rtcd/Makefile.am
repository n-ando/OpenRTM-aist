## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile for rtcd
##
## $Id: Makefile.am,v 1.1.1.1 2005-05-12 09:06:19 n-ando Exp $
##
## $Log: not supported by cvs2svn $
##---------------------------------------------------------------------------

##
##  Process this file with automake to create Makefile.in
##

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_buiddir)/rtm -L$(top_builddir)/rtm/idl

bin_PROGRAMS = rtcd

rtcd_SOURCES = rtcd.cpp

rtcd_LDADD = $(top_builddir)/rtm/libRTC.la

rtcd_LDFLAGS = -L$(top_builddir)/rtm

clean-local:
	rm -rf rtcd *.o *~ *core .libs

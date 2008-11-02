## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for libOpenRTM_CORBA
##
## $Id$
##---------------------------------------------------------------------------

SUBDIRS = idl
AM_CPPFLAGS=-I$(top_srcdir)/include -I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/coil/include -I$(top_srcdir)/src/lib/rtm_corba -I$(top_srcdir)/src/lib/rtm_corba/idl -I$(top_srcdir)/src/lib/coil/include
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/rtm -L$(top_builddir)/src/lib/rtm_corba/idl -L$(top_builddir)/src/lib/coil/lib


lib_LTLIBRARIES = librtmcorba.la

librtmcorba_la_SOURCES =    \
	CorbaManager.cpp
#	RTObjectServant.cpp


librtmcorba_la_LIBADD = \
	$(top_builddir)/src/lib/rtm_corba/idl/libRTCSkel.la

librtmcorba_la_LDFLAGS =                 \
	-no-undefined               \
	-L$(top_builddir)/src/lib/rtm_corba/idl   \
	-release $(PACKAGE_VERSION) \
	-version-info 0:4:0
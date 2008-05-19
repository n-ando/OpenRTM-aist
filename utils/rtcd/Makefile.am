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

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(RTC_SRC) > src.lst
	echo $(rtmheader_HEADERS) > header.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir = $(top_builddir)/win32/OpenRTM-aist/

vcproj: vc8proj vc9proj

vc8proj: rtcd.yaml
	$(top_builddir)/build/vcprojtool.py vcproj                 \
		--type RTCEXE                                      \
		--vcversion "8.00"                                 \
		--projectname "rtcd"                               \
		--version $(RTM_VERSION)                           \
		--out $(win32_builddir)/utils/rtcd/rtcd_vc8.vcproj \
		--yaml rtcd.yaml                                   \
		--source $(rtcd_SOURCES)
#	qkc -sm $(win32_builddir)/rtm/libRTC_vc8.vcproj

vc9proj: rtcd.yaml
	$(top_builddir)/build/vcprojtool.py vcproj                 \
		--type RTCEXE                                      \
		--vcversion "9.00"                                 \
		--projectname "rtcd"                               \
		--version $(RTM_VERSION)                           \
		--out $(win32_builddir)/utils/rtcd/rtcd_vc9.vcproj \
		--yaml rtcd.yaml                                   \
		--source $(rtcd_SOURCES)
#	qkc -sm $(win32_builddir)/rtm/rtcd_vc9.vcproj
#------------------------------------------------------------
# for wxs file
#------------------------------------------------------------
wxs:
	$(top_srcdir)/build/makewxs.py flist \
		-c Rtcd \
		-o $(win32_builddir)installer/rtcd.yaml \
		-p ..\\bin \
		$(bin_PROGRAMS).exe

dist-hook: lst vcproj wxs

clean-local:
	rm -rf rtcd *.o *~ *core .libs *.lst

EXTRA_DIST = rtcd.yaml
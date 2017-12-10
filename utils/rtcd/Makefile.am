## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile for rtcd
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/coil/include -I$(top_srcdir)/src/lib/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_buiddir)/src/lib/rtm -L$(top_builddir)/src/lib/rtm/idl

bin_PROGRAMS = rtcd

rtcd_SOURCES = rtcd.cpp
rtcd_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la
rtcd_LDFLAGS = -L$(top_builddir)/src/lib/rtm

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

vcproj: vc9proj vcxproj

vc9proj: rtcd.yaml
	$(top_builddir)/build/vcprojtool.py vcproj             \
		--type RTCEXE                                      \
		--vcversion "9.00"                                 \
		--projectname "rtcd"                               \
		--version $(RTM_VERSION)                           \
		--out $(win32_builddir)/utils/rtcd/rtcd_vc9.vcproj \
		--yaml rtcd.yaml                                   \
		--source $(rtcd_SOURCES)

vcxproj: rtcd.yaml
	for ver in $(VC_VERSION); do \
		$(top_builddir)/build/vcxprojtool.py vcxproj             \
			--type RTCEXE                                        \
			--vcversion "$${ver}.00"                                  \
			--projectname "rtcd"                                 \
			--version $(RTM_VERSION)                             \
			--out $(win32_builddir)/utils/rtcd/rtcd_vc$${ver}.vcxproj \
			--yaml rtcd.yaml                                     \
			--source $(rtcd_SOURCES) ; \
	done

dist-hook: lst vcproj

clean-local:
	rm -rf rtcd
	rm -rf *.o *~ *.core *.lst *.log
	rm -rf .libs 

EXTRA_DIST = rtcd.yaml


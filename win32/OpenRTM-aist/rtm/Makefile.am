## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/rtm
##
## $Id$
##---------------------------------------------------------------------------
SUBDIRS = idl .

RTM_VERSION = @RTM_VERSION@
RTM_SHORT_VERSION = @RTM_SHORT_VERSION@

clean-local:
	rm -rf Debug Release
	rm -f *~ *.cpp *.h *.cc *.hh *.sln *.suo *.ncb *.user *.vcproj

src:
	cp -p $(top_srcdir)/src/lib/rtm/*.cpp .
	cp -p $(top_srcdir)/src/lib/rtm/*.h .
	cp -p config_rtc.h.in config_rtc.h
	qkc -ms *.cpp
	qkc -ms *.h

dist-hook: src

EXTRA_DIST = config_rtc.h.in
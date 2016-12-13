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
	rm -f *~ *.cpp *.h *.cc *.hh
	rm -f *.sln *.suo *.ncb *.user *.vcproj *.def

config_rtc.h:
	sed -e 's/__RTM_VERSION__/$(RTM_VERSION)/g' config_rtc.h.in > temp.1
	sed -e 's/__RTM_SHORT_VERSION__/$(RTM_SHORT_VERSION)/g' temp.1 > temp.2
	mv temp.2 config_rtc.h
	rm -f temp.1

src:
	cp -p $(top_srcdir)/src/lib/rtm/*.cpp .
	cp -p $(top_srcdir)/src/lib/rtm/*.h .
	qkc -ms *.cpp
	qkc -ms *.h

dist-hook: src config_rtc.h

EXTRA_DIST = config_rtc.h.in
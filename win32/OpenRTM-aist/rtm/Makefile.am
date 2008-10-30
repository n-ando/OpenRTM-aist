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
	cp $(top_srcdir)/src/lib/rtm/*.cpp .
	cp $(top_srcdir)/src/lib/rtm/*.h .
	qkc -ms *.cpp
	qkc -ms *.h

dist-hook: src

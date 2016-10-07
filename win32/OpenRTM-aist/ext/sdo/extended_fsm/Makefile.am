## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/ext/sdo/extended_fsm
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.hh *.cc *.idl rtc.conf
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo
	rm -rf ExtendedFsmServiceProvider

src:
	cp -p $(top_srcdir)/src/ext/sdo/extended_fsm/*.cpp .
	cp -p $(top_srcdir)/src/ext/sdo/extended_fsm/*.h .
	cp -p $(top_srcdir)/src/ext/sdo/extended_fsm/*.idl .
	qkc -O- -ms *.cpp
	qkc -O- -ms *.h
	qkc -O- -ms *.idl

dist-hook: src

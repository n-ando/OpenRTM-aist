## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/ext/ec/local_time
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.hh *.cc *.idl rtc.conf
	rm -rf *.user *.ncb *.suo
	rm -rf LogicalTimeTriggeredEC

src:
	cp -p $(top_srcdir)/src/ext/ec/logical_time/*.cpp .
	cp -p $(top_srcdir)/src/ext/ec/logical_time/*.h .
	cp -p $(top_srcdir)/src/ext/ec/logical_time/*.idl .
	qkc -ms *.cpp
	qkc -ms *.h
	qkc -ms *.idl

dist-hook: src

## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/ext/sdo/observer
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.hh *.cc *.idl rtc.conf
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo
	rm -rf ComponentObserverConsumer

src:
	cp -p $(top_srcdir)/src/ext/sdo/observer/ComponentObserverConsumer.cpp .
	cp -p $(top_srcdir)/src/ext/sdo/observer/ComponentObserverConsumer.h .
	cp -p $(top_srcdir)/src/ext/sdo/observer/*.idl .
	qkc -O- -ms *.cpp
	qkc -O- -ms *.h
	qkc -O- -ms *.idl

dist-hook: src

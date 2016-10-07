## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/Fsm
##
## $Id: Makefile.am 2556 2014-04-09 17:05:15Z n-ando $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.idl rtc.conf
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo
	rm -rf FsmComp

src:
	cp -p $(top_srcdir)/examples/Fsm/*.cpp .
	cp -p $(top_srcdir)/examples/Fsm/*.cc .
	cp -p $(top_srcdir)/examples/Fsm/*.h .
	cp -p $(top_srcdir)/examples/Fsm/*.hpp .
	cp -p $(top_srcdir)/examples/Fsm/rtc.conf .
	qkc -O- -ms *.cpp
	qkc -O- -ms *.cc
	qkc -O- -ms *.h
	qkc -O- -ms *.hpp

dist-hook: src

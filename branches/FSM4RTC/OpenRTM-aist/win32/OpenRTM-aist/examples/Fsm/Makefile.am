## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/Fsm
##
## $Id: Makefile.am 2556 2014-04-09 17:05:15Z n-ando $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cc *.cpp *.h *.idl *.conf 
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo
	rm -rf FsmComp

src:
	cp -p $(top_srcdir)/examples/Fsm/*.cc .
	cp -p $(top_srcdir)/examples/Fsm/*.h .
	cp -p $(top_srcdir)/examples/Fsm/CMakeLists.txt .
	cp -p $(top_srcdir)/examples/Fsm/*.conf .
	qkc -O- -ms *.cc
	qkc -O- -ms *.h

dist-hook: src

## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/ext/ec/rtpreempt
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf *~ *.cpp *.h rtc.conf.sample *.conf Makefile.in

src:
	cp -p $(top_srcdir)/src/ext/ec/rtpreempt/rtc.conf.sample .
	cp -p $(top_srcdir)/src/ext/ec/rtpreempt/*.cpp .
	cp -p $(top_srcdir)/src/ext/ec/rtpreempt/*.h .
	qkc -O- -ms *.cpp
	qkc -O- -ms *.h

dist-hook: src

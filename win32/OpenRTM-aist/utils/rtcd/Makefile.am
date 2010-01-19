## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtcd
##
## $Id$
##---------------------------------------------------------------------------

clean-local:
	rm -rf *~ *core *.cpp *.vcproj *.user *.exe
	rm -rf rtc.conf
	rm -rf rtcd

src:
	cp -p $(top_srcdir)/utils/rtcd/*.cpp .
	qkc -ms *.cpp

dist-hook: src

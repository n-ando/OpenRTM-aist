## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/ext/sdo/logger
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.hh *.cc *.idl
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo

src:
	cp -p $(top_srcdir)/src/ext/sdo/logger/*.cpp .
	cp -p $(top_srcdir)/src/ext/sdo/logger/*.h .
	cp -p $(top_srcdir)/src/ext/sdo/logger/*.idl .
	qkc -O- -ms *.cpp
	qkc -O- -ms *.h
	qkc -O- -ms *.idl

dist-hook: src

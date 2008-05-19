## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtcd
##
## $Id$
##---------------------------------------------------------------------------

clean-local:
	rm -rf *~ *core *.cpp *.vcproj

src:
	cp $(top_srcdir)/utils/rtcd/*.cpp .
	qkc -ms *.cpp

dist-hook: src

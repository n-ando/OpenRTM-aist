## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/coil
##
## $Id: Makefile.am 725 2008-10-27 16:49:04Z h-Kojima $
##---------------------------------------------------------------------------
all: src

clean-local:
	rm -rf Debug Release
	rm -f *~ *.idl *.cpp *.h *.cc *.hh *.sln *.suo *.ncb *.user *.vcproj

src:
	cp $(top_srcdir)/src/lib/coil/win32/coil/*.h .
	qkc -ms *.h


dist-hook: src

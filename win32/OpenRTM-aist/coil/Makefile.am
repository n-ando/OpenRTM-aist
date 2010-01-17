## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/coil
##
## $Id: Makefile.am 725 2008-10-27 16:49:04Z h-Kojima $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -f *~ *.idl *.cpp *.h *.cc *.hh *.sln *.suo *.ncb *.user *.vcproj

src:
	cp -p $(top_srcdir)/src/lib/coil/win32/coil/*.cpp .
	cp -p $(top_srcdir)/src/lib/coil/win32/coil/*.h .
	cp -p $(top_srcdir)/src/lib/coil/win32/coil/*.vcproj .


dist-hook: src

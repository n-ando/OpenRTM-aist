## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/hrtm/idls
##
## $Id: Makefile.am 2720 2016-05-20 10:35:25Z n-ando $
##---------------------------------------------------------------------------

clean-local:
	rm -rf Debug Release
	rm -f *~ *.cpp *.h *.cc *.hh version.txt
	rm -f *.sln *.suo *.ncb *.user *.vcproj *.vcxproj *.def

src:
	cp -p $(top_srcdir)/src/lib/hrtm/idls/*.cpp .
	cp -p $(top_srcdir)/src/lib/hrtm/idls/*.h .
	qkc -O- -ms *.cpp
	qkc -O- -ms *.h

dist-hook: src


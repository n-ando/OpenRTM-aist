## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/Composite
##
## $Id: Makefile.am 725 2008-05-13 16:49:04Z n-ando $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.idl *.conf
	rm -rf *.vcproj *.user *.ncb *.suo

src:
	cp $(top_srcdir)/examples/Composite/*.cpp .
	cp $(top_srcdir)/examples/Composite/*.h .
	cp $(top_srcdir)/examples/Composite/*.conf .
	qkc -ms *.cpp
	qkc -ms *.h
	qkc -ms *.conf

dist-hook: src

## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/ext/ssl
##
## $Id: Makefile.am 1680 2018-01-24 15:12:59Z n-miyamoto $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo
	rm -rf SSLTransport

src:
	cp -p $(top_srcdir)/src/ext/ssl/*.cpp .
	qkc -O- -ms *.cpp

dist-hook: src

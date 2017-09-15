## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/Analyzer
##
## $Id: Makefile.am 3041 2017-09-15 14:49:04Z n-ando $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.idl *.conf
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo
	rm -rf Analyzer AnalyzerComp Analyzer_test Analyzer_testComp

src:
	cp -p $(top_srcdir)/examples/Analyzer/*.cpp .
	cp -p $(top_srcdir)/examples/Analyzer/*.h .
	cp -p $(top_srcdir)/examples/Analyzer/*.conf .
	qkc -O- -ms *.cpp
	qkc -O- -ms *.h
	qkc -O- -ms *.conf

dist-hook: src

## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/Throughput
##
## $Id: Makefile.am 3041 2017-09-15 14:49:04Z n-ando $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.idl *.conf
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo
	rm -rf Throughput ThroughputComp

src:
	cp -p $(top_srcdir)/examples/Throughput/*.cpp .
	cp -p $(top_srcdir)/examples/Throughput/*.h .
	cp -p $(top_srcdir)/examples/Throughput/*.conf .
	qkc -O- -ms *.cpp
	qkc -O- -ms *.h
	qkc -O- -ms *.conf

dist-hook: src

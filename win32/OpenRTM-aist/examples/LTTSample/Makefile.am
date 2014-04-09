## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/LTTSample
##
## $Id: Makefile.am 2107 2011-05-23 02:54:49Z n-ando $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.h *.idl *.cpp LTTSample.conf TickApp.py
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo
	rm -rf LTTSampleComp

src:
	cp -p $(top_srcdir)/src/ext/ec/logical_time/example/*.cpp .
	cp -p $(top_srcdir)/src/ext/ec/logical_time/example/*.h .
	cp -p $(top_srcdir)/src/ext/ec/logical_time/example/TickApp.py .
	cp -p $(top_srcdir)/src/ext/ec/logical_time/example/LTTSample.conf .
	cp -p $(top_srcdir)/src/ext/ec/logical_time/example/idl/*.idl .
	cp -p $(top_srcdir)/src/ext/ec/logical_time/example/idl/*.idl .
	qkc -O- -ms *.cpp
	qkc -O- -ms *.h
	qkc -O- -ms *.conf
	qkc -O- -ms *.py
	qkc -O- -ms *.idl

dist-hook: src

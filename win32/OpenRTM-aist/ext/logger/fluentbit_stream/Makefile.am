## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/ext/logger/fluentbit_stream
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf *~ *.cpp *.h *.conf Makefile.in

src:
	cp -p $(top_srcdir)/src/ext/logger/fluentbit_stream/*.conf .
	cp -p $(top_srcdir)/src/ext/logger/fluentbit_stream/*.cpp .
	cp -p $(top_srcdir)/src/ext/logger/fluentbit_stream/*.h .
	qkc -O- -ms *.cpp
	qkc -O- -ms *.h

dist-hook: src

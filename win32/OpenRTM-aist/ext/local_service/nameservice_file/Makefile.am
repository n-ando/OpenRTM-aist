## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for FileNameservice
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h
	rm -rf *.user *.ncb *.suo
	rm -rf FileNameservice

src: 
	cp -p $(top_srcdir)/src/ext/local_service/nameservice_file/*.cpp .
	cp -p $(top_srcdir)/src/ext/local_service/nameservice_file/*.h .
	qkc -ms *.cpp
	qkc -ms *.h

dist-hook: src

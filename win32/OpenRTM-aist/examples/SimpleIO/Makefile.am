## Makefile.am for win32/OpenRTM-aist/examples/SimpleIO
##
## $Id: Makefile.am,v 1.1.2.1 2007-07-20 16:26:56 n-ando Exp $
##
## $Log: not supported by cvs2svn $
##
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.user

vcprojs: ConsoleInvc8.vcproj ConsoleOutvc8.vcproj


src:
	cp $(top_srcdir)/examples/SimpleIO/*.cpp .
	cp $(top_srcdir)/examples/SimpleIO/*.h .
	qkc -ms *.cpp
	qkc -ms *.h


ConsoleInvc8.vcproj:
	$(top_srcdir)/build/makevcproj.py   \
		-i ConsoleInvc8.vcproj.in   \
		-d ConsoleInvc8.vcproj.yaml \
		-o ConsoleInvc8.vcproj
	qkc -ms ConsoleInvc8.vcproj


ConsoleOutvc8.vcproj:
	$(top_srcdir)/build/makevcproj.py    \
		-i ConsoleOutvc8.vcproj.in   \
		-d ConsoleOutvc8.vcproj.yaml \
		-o ConsoleOutvc8.vcproj
	qkc -ms ConsoleOutvc8.vcproj


dist-hook: clean-local src vcprojs

EXTRA_DIST =                      \
	ConsoleInvc8.vcproj.in    \
	ConsoleOutvc8.vcproj.in   \
	ConsoleInvc8.vcproj.yaml  \
	ConsoleOutvc8.vcproj.yaml

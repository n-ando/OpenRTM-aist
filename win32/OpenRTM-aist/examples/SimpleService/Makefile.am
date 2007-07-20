## Makefile.am for win32/OpenRTM-aist/examples/SimpleService
##
## $Id: Makefile.am,v 1.1.2.2 2007-07-20 16:56:55 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.1  2007/07/20 16:26:59  n-ando
## Makefile for Win32 source tree management.
##
##
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.idl *.user

vcprojs: MyServiceProvidervc8.vcproj MyServiceConsumervc8.vcproj


src:
	cp $(top_srcdir)/examples/SimpleService/*.cpp .
	cp $(top_srcdir)/examples/SimpleService/*.h .
	cp $(top_srcdir)/examples/SimpleService/*.idl .
	qkc -ms *.cpp
	qkc -ms *.h
	qkc -ms *.idl


MyServiceProvidervc8.vcproj:
	$(top_srcdir)/build/makevcproj.py            \
		-i MyServiceProvidervc8.vcproj.in    \
		-d MyServiceProvidervc8.vcproj.yaml  \
		-o MyServiceProvidervc8.vcproj
	qkc -ms MyServiceProvidervc8.vcproj


MyServiceConsumervc8.vcproj:
	$(top_srcdir)/build/makevcproj.py            \
		-i MyServiceConsumervc8.vcproj.in    \
		-d MyServiceConsumervc8.vcproj.yaml  \
		-o MyServiceConsumervc8.vcproj
	qkc -ms MyServiceConsumervc8.vcproj


dist-hook: clean-local src vcprojs

EXTRA_DIST=                              \
	MyServiceProvidervc8.vcproj.in   \
	MyServiceConsumervc8.vcproj.in   \
	MyServiceConsumervc8.vcproj.yaml \
	MyServiceProvidervc8.vcproj.yaml


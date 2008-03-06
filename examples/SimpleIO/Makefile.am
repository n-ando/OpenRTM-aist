## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for ConsoleIn/ConsoleOut components
##
## $Id: Makefile.am,v 1.3.4.7 2008-03-06 06:48:45 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.3.4.6  2008/02/29 11:04:58  n-ando
## A trivial fix.
##
## Revision 1.3.4.5  2008/02/29 04:56:46  n-ando
## A trivial fix.
##
## Revision 1.3.4.4  2008/02/26 14:13:35  n-ando
## Visual Studio project file generation
##
## Revision 1.3.4.3  2007/10/09 07:33:15  n-ando
## Modification for TCP socket data port.
##
## Revision 1.3.4.2  2007/09/21 09:21:04  n-ando
## Now rtc.conf is not deleted in clean.
##
## Revision 1.3.4.1  2007/07/22 14:26:35  n-ando
## *** empty log message ***
##
## Revision 1.3  2007/01/21 13:35:17  n-ando
## A trivial fix.
##
## Revision 1.2  2007/01/14 22:52:23  n-ando
## Updated for OpenRTM-aist-0.4.0.
##
## Revision 1.1.1.1  2005/05/12 09:06:20  n-ando
## Public release.
##
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/rtm -L$(top_builddir)/rtm/idl

noinst_LTLIBRARIES = libConsoleIn.la libConsoleOut.la
libConsoleIn_la_SOURCES = ConsoleIn.cpp ConsoleIn.h
libConsoleIn_la_LIBADD = $(top_builddir)/rtm/libRTC.la
libConsoleIn_la_FLAGS = -L$(top_builddir)/rtm/.lib

libConsoleOut_la_SOURCES = ConsoleOut.cpp ConsoleOut.h
libConsoleOut_la_LIBADD = $(top_builddir)/rtm/libRTC.la
libConsoleOut_la_FLAGS = -L$(top_builddir)/rtm/.lib

noinst_PROGRAMS = ConsoleInComp ConsoleOutComp ConnectorComp
ConsoleInComp_SOURCES = ConsoleInComp.cpp 
ConsoleInComp_LDADD = $(top_builddir)/rtm/libRTC.la ConsoleIn.o
ConsoleInComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

ConsoleOutComp_SOURCES = ConsoleOutComp.cpp 
ConsoleOutComp_LDADD = $(top_builddir)/rtm/libRTC.la ConsoleOut.o
ConsoleOutComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

ConnectorComp_SOURCES = ConnectorComp.cpp
ConnectorComp_LDADD = $(top_builddir)/rtm/libRTC.la
ConnectorComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

EXTRA_DIST =                \
	run.sh              \
	gen.sh              \
	Makefile.ConsoleIn  \
	Makefile.ConsoleOut \
	README.ConsoleIn    \
	README.ConsoleOut   \
	rtc.conf            \
	consin.conf         \
	consout.conf

ALL_SRC =                  \
	ConsoleInComp.cpp  \
	ConsoleIn.cpp      \
	ConsoleIn.h        \
	ConsoleOutComp.cpp \
	ConsoleOut.cpp     \
	ConsoleOut.h       \
	ConnectorComp.cpp

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(ALL_SRC) > src.lst
	echo $(EXTRA_DIST) > other.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/examples/SimpleIO

vcproj: vc8proj vc9proj

vc8proj: 
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "8.00"                           \
		--projectname "ConsoleInComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/ConsoleIn_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source ConsoleIn.cpp ConsoleInComp.cpp     \
		--header ConsoleIn.h
	qkc -sm $(win32_builddir)/ConsoleIn_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "8.00"                              \
		--projectname "ConsoleIn"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/ConsoleInDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source ConsoleIn.cpp                          \
		--header ConsoleIn.h
	qkc -sm $(win32_builddir)/ConsoleInDll_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj            \
		--type EXE                                    \
		--vcversion "8.00"                            \
		--projectname "ConsoleOutComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/ConsoleOut_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source ConsoleOut.cpp ConsoleOutComp.cpp    \
		--header ConsoleOut.h
	qkc -sm $(win32_builddir)/ConsoleOut_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj               \
		--type DLL                                       \
		--vcversion "8.00"                               \
		--projectname "ConsoleOut"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/ConsoleOutDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source ConsoleOut.cpp                          \
		--header ConsoleOut.h
	qkc -sm $(win32_builddir)/ConsoleOutDll_vc8.vcproj

vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "9.00"                           \
		--projectname "ConsoleInComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/ConsoleIn_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source ConsoleIn.cpp ConsoleInComp.cpp     \
		--header ConsoleIn.h
	qkc -sm $(win32_builddir)/ConsoleIn_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "ConsoleIn"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/ConsoleInDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source ConsoleIn.cpp                          \
		--header ConsoleIn.h
	qkc -sm $(win32_builddir)/ConsoleInDll_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj            \
		--type EXE                                    \
		--vcversion "9.00"                            \
		--projectname "ConsoleOutComp"                \
		--version $(RTM_VERSION)                      \
		--out $(win32_builddir)/ConsoleOut_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                     \
		--source ConsoleOut.cpp ConsoleOutComp.cpp    \
		--header ConsoleOut.h
	qkc -sm $(win32_builddir)/ConsoleOut_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj               \
		--type DLL                                       \
		--vcversion "9.00"                               \
		--projectname "ConsoleOut"                       \
		--version $(RTM_VERSION)                         \
		--out $(win32_builddir)/ConsoleOutDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                     \
		--source ConsoleOut.cpp                          \
		--header ConsoleOut.h
	qkc -sm $(win32_builddir)/ConsoleOutDll_vc9.vcproj

dist-hook: lst vcproj

clean-local:
	rm -f \
	*.bak *.rpo *.sym lib*.*_pure_* *.lst \
	Makefile.old *core *~ *.so *.log

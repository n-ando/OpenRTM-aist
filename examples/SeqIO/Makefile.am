## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for SeqIn/SeqOut components
##
## $Id$
##
## $Log: not supported by cvs2svn $
## Revision 1.2.2.3  2008/02/26 14:13:32  n-ando
## Visual Studio project file generation
##
## Revision 1.2.2.2  2007/09/26 07:43:40  n-ando
## Some modification for version 0.4.1.
##
## Revision 1.2.2.1  2007/07/22 14:26:32  n-ando
## *** empty log message ***
##
## Revision 1.2  2007/02/04 16:47:25  n-ando
## Updated for 0.4.0.
##
## Revision 1.1.1.1  2005/05/12 09:06:20  n-ando
## Public release.
##
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/rtm -L$(top_builddir)/rtm/idl

noinst_LTLIBRARIES = libSeqIn.la libSeqOut.la
libSeqIn_la_SOURCES = SeqIn.cpp SeqIn.h
libSeqIn_la_LIBADD = $(top_builddir)/rtm/libRTC.la
libSeqIn_la_FLAGS = -L$(top_builddir)/rtm/.lib

libSeqOut_la_SOURCES = SeqOut.cpp SeqOut.h
libSeqOut_la_LIBADD = $(top_builddir)/rtm/libRTC.la
libSeqOut_la_FLAGS = -L$(top_builddir)/rtm/.lib

noinst_PROGRAMS = SeqInComp SeqOutComp
SeqInComp_SOURCES = SeqInComp.cpp 
SeqInComp_LDADD = $(top_builddir)/rtm/libRTC.la SeqIn.o
SeqInComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

SeqOutComp_SOURCES = SeqOutComp.cpp 
SeqOutComp_LDADD = $(top_builddir)/rtm/libRTC.la SeqOut.o
SeqOutComp_LDFLAGS = -L$(top_builddir)/rtm/.libs

EXTRA_DIST =            \
	Makefile.SeqIn  \
	Makefile.SeqOut \
	README.SeqIn    \
	README.SeqOut   \
	gen.sh          \
	rtc.conf

ALL_SRC =              \
	SeqInComp.cpp  \
	SeqIn.cpp      \
	SeqIn.h        \
	SeqOutComp.cpp \
	SeqOut.cpp     \
	SeqOut.h

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(ALL_SRC) > src.lst
	echo $(EXTRA_DIST) > other.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/examples/SeqIO

vcproj: vc8proj vc9proj

vc8proj: 
	$(top_builddir)/build/vcprojtool.py vcproj       \
		--type EXE                               \
		--vcversion "8.00"                       \
		--projectname "SeqInComp"                \
		--version $(RTM_VERSION)                 \
		--out $(win32_builddir)/SeqIn_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                \
		--source SeqIn.cpp SeqInComp.cpp         \
		--header SeqIn.h
	qkc -sm $(win32_builddir)/SeqIn_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj          \
		--type DLL                                  \
		--vcversion "8.00"                          \
		--projectname "SeqIn"                       \
		--version $(RTM_VERSION)                    \
		--out $(win32_builddir)/SeqInDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                \
		--source SeqIn.cpp                          \
		--header SeqIn.h
	qkc -sm $(win32_builddir)/SeqInDll_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj        \
		--type EXE                                \
		--vcversion "8.00"                        \
		--projectname "SeqOutComp"                \
		--version $(RTM_VERSION)                  \
		--out $(win32_builddir)/SeqOut_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                 \
		--source SeqOut.cpp SeqOutComp.cpp        \
		--header SeqOut.h
	qkc -sm $(win32_builddir)/SeqOut_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type DLL                                   \
		--vcversion "8.00"                           \
		--projectname "SeqOut"                       \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/SeqOutDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                 \
		--source SeqOut.cpp                          \
		--header SeqOut.h
	qkc -sm $(win32_builddir)/SeqOutDll_vc8.vcproj

vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj       \
		--type EXE                               \
		--vcversion "9.00"                       \
		--projectname "SeqInComp"                \
		--version $(RTM_VERSION)                 \
		--out $(win32_builddir)/SeqIn_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                \
		--source SeqIn.cpp SeqInComp.cpp         \
		--header SeqIn.h
	qkc -sm $(win32_builddir)/SeqIn_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj          \
		--type DLL                                  \
		--vcversion "9.00"                          \
		--projectname "SeqIn"                       \
		--version $(RTM_VERSION)                    \
		--out $(win32_builddir)/SeqInDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                \
		--source SeqIn.cpp                          \
		--header SeqIn.h
	qkc -sm $(win32_builddir)/SeqInDll_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj        \
		--type EXE                                \
		--vcversion "9.00"                        \
		--projectname "SeqOutComp"                \
		--version $(RTM_VERSION)                  \
		--out $(win32_builddir)/SeqOut_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                 \
		--source SeqOut.cpp SeqOutComp.cpp        \
		--header SeqOut.h
	qkc -sm $(win32_builddir)/SeqOut_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type DLL                                   \
		--vcversion "9.00"                           \
		--projectname "SeqOut"                       \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/SeqOutDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                 \
		--source SeqOut.cpp                          \
		--header SeqOut.h
	qkc -sm $(win32_builddir)/SeqOutDll_vc9.vcproj

dist-hook: lst vcproj

clean-local:
	rm -f \
	*.bak *.rpo *.sym lib*.*_pure_* *.lst \
	Makefile.old *core *~ *.log

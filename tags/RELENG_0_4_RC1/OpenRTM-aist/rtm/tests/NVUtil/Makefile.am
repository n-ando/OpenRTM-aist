# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for NVUtil unit test
# @date   $Date: 2007-01-21 06:52:23 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.3 2007-01-21 06:52:23 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.2  2007/01/12 14:44:00  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/11/27 08:30:12  n-ando
# TestSuites are devided into each directory.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =                    \
	 -I.                      \
	-I$(top_builddir)         \
	-I$(top_builddir)/rtm/idl \
	-I$(includedir)

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir)


IDL_SOURCES =                                \
	$(top_srcdir)/rtm/idl/RTC.idl        \
	$(top_srcdir)/rtm/idl/SDOPackage.idl 

noinst_PROGRAMS = NVUtilTests

nodist_NVUtilTests_SOURCES =             \
	../TestRunner.cpp                \
	$(IDL_SOURCES:.idl=Skel.cpp)     \
	$(top_srcdir)/rtm/StringUtil.cpp \
	$(top_srcdir)/rtm/Properties.cpp \
	$(top_srcdir)/rtm/NVUtil.cpp     \
	NVUtilTests.cpp

NVUtilTests_LDFLAGS = -L$(libdir)
NVUtilTests_LDADD   = -lcppunit

EXTRA_DIST =        \
	NVUtilTests.cpp

# all
all: do-test

# do tests
do-test:
	./NVUtilTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

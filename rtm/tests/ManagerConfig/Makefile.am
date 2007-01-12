# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for ManagerConfig unit test
# @date   $Date: 2007-01-12 14:43:47 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.2 2007-01-12 14:43:47 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.1  2006/11/27 08:30:00  n-ando
# TestSuites are devided into each directory.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =         \
	 -I.              \
	-I$(includedir)   \
	-I$(top_builddir)

AM_LDFLAGS =          \
	 -L.              \
	-L$(top_builddir)


noinst_PROGRAMS = ManagerConfigTests

nodist_ManagerConfigTests_SOURCES =       \
	../TestRunner.cpp                     \
	$(top_builddir)/rtm/StringUtil.cpp    \
	$(top_builddir)/rtm/Properties.cpp    \
	$(top_builddir)/rtm/ManagerConfig.cpp \
	ManagerConfigTests.cpp

ManagerConfigTests_LDFLAGS = -L$(libdir)
ManagerConfigTests_LDADD   = -lcppunit

EXTRA_DIST =               \
	ManagerConfigTests.cpp \
	rtc.conf

# all
all: do-test

# do tests
do-test:
	./ManagerConfigTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

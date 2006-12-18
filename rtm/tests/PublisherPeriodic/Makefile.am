# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PublisherPeriodic unit test
# @date   $Date: 2006-12-18 06:51:50 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.1 2006-12-18 06:51:50 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS= -I.                  \
	-I$(includedir)           \
	-I$(top_builddir)

AM_LDFLAGS= -L.                   \
	-L$(top_builddir)


noinst_PROGRAMS = PublisherPeriodicTests

PublisherPeriodicTests_SOURCES = \
	../TestRunner.cpp \
	PublisherPeriodicTests.cpp \
	$(top_builddir)/rtm/Properties.cpp \
	$(top_builddir)/rtm/PublisherPeriodic.cpp \
	$(top_builddir)/rtm/StringUtil.cpp

PublisherPeriodicTests_LDFLAGS = -L$(libdir)
PublisherPeriodicTests_LDADD   = -lcppunit

# all
all: do-test

# do tests
do-test:
	./PublisherPeriodicTests

# clean-up
clean-local:
	rm -f PublisherPeriodicTests        \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PublisherFactory unit test
# @date   $Date: 2007-01-21 06:53:04 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.3 2007-01-21 06:53:04 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.2  2007/01/12 14:44:55  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/12/18 06:50:53  n-ando
# The first commitment.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =             \
	-I.               \
	-I$(top_builddir) \
	-I$(includedir)


AM_LDFLAGS =              \
	 -L.              \
	-L$(top_builddir)


noinst_PROGRAMS = PublisherFactoryTests

nodist_PublisherFactoryTests_SOURCES =            \
	../TestRunner.cpp                         \
	$(top_builddir)/rtm/Properties.cpp        \
	$(top_builddir)/rtm/StringUtil.cpp        \
	$(top_builddir)/rtm/PublisherFactory.cpp  \
	$(top_builddir)/rtm/PublisherNew.cpp      \
	$(top_builddir)/rtm/PublisherPeriodic.cpp \
	$(top_builddir)/rtm/PublisherFlush.cpp    \
	PublisherFactoryTests.cpp

PublisherFactoryTests_LDFLAGS = -L$(libdir)
PublisherFactoryTests_LDADD   = -lcppunit

EXTRA_DIST =                  \
	PublisherFactoryTests.cpp

# all
all: do-test

# do tests
do-test:
	./PublisherFactoryTests

# clean-up
clean-local:
	rm -f PublisherFactoryTests         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PublisherFlush unit test
# @date   $Date: 2007-01-12 14:45:00 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.2 2007-01-12 14:45:00 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.1  2006/12/18 06:51:03  n-ando
# The first commitment.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =         \
	-I.               \
	-I$(includedir)   \
	-I$(top_builddir)

AM_LDFLAGS =          \
	 -L.              \
	-L$(top_builddir)


noinst_PROGRAMS = PublisherFlushTests

nodist_PublisherFlushTests_SOURCES =       \
	../TestRunner.cpp                      \
	$(top_builddir)/rtm/Properties.cpp     \
	$(top_builddir)/rtm/PublisherFlush.cpp \
	$(top_builddir)/rtm/StringUtil.cpp     \
	PublisherFlushTests.cpp

PublisherFlushTests_LDFLAGS = -L$(libdir)
PublisherFlushTests_LDADD   = -lcppunit

EXTRA_DIST =                \
	PublisherFlushTests.cpp

# all
all: do-test

# do tests
do-test:
	./PublisherFlushTests

# clean-up
clean-local:
	rm -f PublisherFlushTests           \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PublisherNew unit test
# @date   $Date: 2007-01-21 06:53:14 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.3 2007-01-21 06:53:14 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.2  2007/01/12 14:45:06  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/12/18 06:51:38  n-ando
# The first commitment.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =         \
	-I.               \
	-I$(top_builddir) \
	-I$(includedir)

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir)


noinst_PROGRAMS = PublisherNewTests

nodist_PublisherNewTests_SOURCES =           \
	../TestRunner.cpp                    \
	$(top_builddir)/rtm/Properties.cpp   \
	$(top_builddir)/rtm/PublisherNew.cpp \
	$(top_builddir)/rtm/StringUtil.cpp   \
	PublisherNewTests.cpp

PublisherNewTests_LDFLAGS = -L$(libdir)
PublisherNewTests_LDADD   = -lcppunit

EXTRA_DIST =              \
	PublisherNewTests.cpp

# all
all: do-test

# do tests
do-test:
	./PublisherNewTests

# clean-up
clean-local:
	rm -f PublisherNewTests             \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

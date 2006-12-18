# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PublisherNew unit test
# @date   $Date: 2006-12-18 06:51:38 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.1 2006-12-18 06:51:38 n-ando Exp $
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


noinst_PROGRAMS = PublisherNewTests

PublisherNewTests_SOURCES = \
	../TestRunner.cpp \
	PublisherNewTests.cpp \
	$(top_builddir)/rtm/Properties.cpp \
	$(top_builddir)/rtm/PublisherNew.cpp \
	$(top_builddir)/rtm/StringUtil.cpp



PublisherNewTests_LDFLAGS = -L$(libdir)
PublisherNewTests_LDADD   = -lcppunit

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

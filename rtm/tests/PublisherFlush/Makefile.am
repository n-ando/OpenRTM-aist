# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PublisherFlush unit test
# @date   $Date: 2006-12-18 06:51:03 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.1 2006-12-18 06:51:03 n-ando Exp $
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


noinst_PROGRAMS = PublisherFlushTests

PublisherFlushTests_SOURCES = \
	../TestRunner.cpp \
	PublisherFlushTests.cpp \
	$(top_builddir)/rtm/Properties.cpp \
	$(top_builddir)/rtm/PublisherFlush.cpp \
	$(top_builddir)/rtm/StringUtil.cpp

PublisherFlushTests_LDFLAGS = -L$(libdir)
PublisherFlushTests_LDADD   = -lcppunit

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

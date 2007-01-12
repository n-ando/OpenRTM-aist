# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for RingBuffer unit test
# @date   $Date: 2007-01-12 14:45:19 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.2 2007-01-12 14:45:19 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.1  2006/11/27 08:36:59  n-ando
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

noinst_PROGRAMS = RingBufferTests

nodist_RingBufferTests_SOURCES = \
	../TestRunner.cpp            \
	RingBufferTests.cpp

RingBufferTests_LDFLAGS = -L$(libdir)
RingBufferTests_LDADD   = -lcppunit

EXTRA_DIST =            \
	RingBufferTests.cpp

# all
all: do-test

# do tests
do-test:
	./RingBufferTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

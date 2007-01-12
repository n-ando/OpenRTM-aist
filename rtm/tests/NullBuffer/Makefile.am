# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for NullBuffer unit test
# @date   $Date: 2007-01-12 14:44:07 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.3 2007-01-12 14:44:07 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.2  2006/12/18 06:54:47  n-ando
# clean-local target NullBuffer was added.
#
# Revision 1.1  2006/12/02 18:54:43  n-ando
# *** empty log message ***
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

noinst_PROGRAMS = NullBufferTests

nodist_NullBufferTests_SOURCES = \
	../TestRunner.cpp            \
	NullBufferTests.cpp

NullBufferTests_LDFLAGS = -L$(libdir)
NullBufferTests_LDADD   = -lcppunit

EXTRA_DIST =            \
	NullBufferTests.cpp

# all
all: do-test

# do tests
do-test:
	./NullBufferTests

# clean-up
clean-local:
	rm -f NullBufferTests               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

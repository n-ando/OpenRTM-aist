# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for InPort unit test
# @date   $Date: 2007-01-12 14:43:41 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.2 2007-01-12 14:43:41 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.1  2006/11/27 08:32:45  n-ando
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


noinst_PROGRAMS = InPortTests

nodist_InPortTests_SOURCES = \
	../TestRunner.cpp        \
	InPortTests.cpp
InPortTests_LDFLAGS = -L$(libdir)
InPortTests_LDADD   = -lcppunit

EXTRA_DIST =        \
	InPortTests.cpp

# all
all: do-test

# do tests
do-test:
	./InPortTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for Factory unit test
# @date   $Date: 2007-01-21 06:51:58 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.2  2007/01/12 14:43:33  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/11/27 08:32:07  n-ando
# TestSuites are devided into each directory.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =             \
	 -I.              \
	-I$(top_builddir) \
	-I$(includedir)


AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir)

noinst_PROGRAMS = FactoryTests

nodist_FactoryTests_SOURCES =     \
	../TestRunner.cpp         \
	FactoryTests.cpp

FactoryTests_LDFLAGS = -L$(libdir)
FactoryTests_LDADD   = -lcppunit

EXTRA_DIST =         \
	FactoryTests.cpp

# all
all: do-test

# do tests
do-test:
	./FactoryTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

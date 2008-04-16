# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for StateMachine unit test
# @date   $Date: 2007-01-21 06:53:49 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.2  2007/01/12 14:45:43  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/11/27 08:30:04  n-ando
# TestSuites are devided into each directory.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS=              \
	-I.               \
	-I$(top_builddir) \
	-I$(includedir)

AM_LDFLAGS=               \
	-L.               \
	-L$(top_builddir)


noinst_PROGRAMS = StateMachineTests

nodist_StateMachineTests_SOURCES =     \
	../TestRunner.cpp              \
	StateMachineTests.cpp

StateMachineTests_LDFLAGS = -L$(libdir)
StateMachineTests_LDADD   = -lcppunit

EXTRA_DIST = \
	StateMachineTests.cpp

# all
all: do-test

# do tests
do-test:
	./StateMachineTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

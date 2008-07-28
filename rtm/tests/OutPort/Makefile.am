# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for OutPort unit test
# @date   $Date: 2007-01-21 06:52:40 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

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


noinst_PROGRAMS = OutPortTests

nodist_OutPortTests_SOURCES =               \
	../TestRunner.cpp                   \
	$(top_builddir)/rtm/OutPortBase.cpp \
	OutPortTests.cpp

OutPortTests_LDFLAGS = -L$(libdir)
OutPortTests_LDADD   = -lcppunit

EXTRA_DIST =         \
	OutPortTests.cpp

# all
all: do-test

# do tests
do-test:
	./OutPortTests

# clean-up
clean-local:
	rm -f OutPortTests                  \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for OutPortBase unit test
# @date   $Date: 2007-01-12 14:44:30 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

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


noinst_PROGRAMS = OutPortBaseTests

nodist_OutPortBaseTests_SOURCES =       \
	../TestRunner.cpp                   \
	$(top_builddir)/rtm/OutPortBase.cpp \
	OutPortBaseTests.cpp

OutPortBaseTests_LDFLAGS = -L$(libdir)
OutPortBaseTests_LDADD   = -lcppunit

EXTRA_DIST =       \
	OutPortBaseTests.cpp

# all
all: do-test

# do tests
do-test:
	./OutPortBaseTests

# clean-up
clean-local:
	rm -f OutPortBaseTests              \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

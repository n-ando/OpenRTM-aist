# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for SdoService unit test
# @date   $Date: 2007-01-21 06:53:43 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

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


noinst_PROGRAMS = SdoServiceTests

nodist_SdoServiceTests_SOURCES =     \
	../TestRunner.cpp            \
	SdoServiceTests.cpp

SdoServiceTests_LDFLAGS = -L$(libdir)
SdoServiceTests_LDADD   = -lcppunit

EXTRA_DIST =            \
	SdoServiceTests.cpp

# all
all: do-test

# do tests
do-test:
	./SdoServiceTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl


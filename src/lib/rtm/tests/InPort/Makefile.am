# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for InPort unit test
# @date   $Date: 2007/01/21 06:52:04 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS = \
	 -I. \
	-I$(top_builddir) \
	-I$(top_builddir)/src/lib/ \
	-I$(top_builddir)/src/lib/rtm \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(includedir)

AM_LDFLAGS =              \
	 -L.              \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib

noinst_PROGRAMS = InPortTests

nodist_InPortTests_SOURCES =     \
	../TestRunner.cpp        \
	InPortTests.cpp

InPortTests_LDFLAGS = -L$(libdir) -L$(AM_LDFLAGS)
InPortTests_LDADD   = -lcppunit -lcoil

EXTRA_DIST =        \
	InPortTests.cpp

# all
all: do-test

# do tests
do-test:
	./InPortTests --xml inporttests.xml --xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

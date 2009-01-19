# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for NullBuffer unit test
# @date   $Date: 2007/01/21 06:52:28 $
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
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(top_builddir)/src/lib/rtm \
	-I$(includedir)


AM_LDFLAGS =              \
	 -L.              \
	-L$(top_builddir)

noinst_PROGRAMS = NullBufferTests

nodist_NullBufferTests_SOURCES =     \
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
	./NullBufferTests --xml nullbuffertests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f NullBufferTests               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

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

#
# $Log: Makefile.am,v $
# Revision 1.4  2007/01/21 06:52:28  n-ando
# The include search path option order in AM_CPPFLAGS was changed.
#
# Revision 1.3  2007/01/12 14:44:07  n-ando
# Some fixes for distribution control.
#
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

AM_CPPFLAGS =             \
	 -I.              \
	-I$(top_builddir) \
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
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

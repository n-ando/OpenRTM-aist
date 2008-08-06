# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for SdoService unit test
# @date   $Date: 2007/01/21 06:53:43 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.3  2007/01/21 06:53:43  n-ando
# The include search path option order in AM_CPPFLAGS was changed.
#
# Revision 1.2  2007/01/12 14:45:37  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/11/27 08:38:07  n-ando
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
	-I$(top_builddir)/rtm/idl \
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
	./SdoServiceTests --xml sdoservicetests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl


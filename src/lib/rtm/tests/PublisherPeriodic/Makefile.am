# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PublisherPeriodic unit test
# @date   $Date: 2007/01/21 06:53:20 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.3  2007/01/21 06:53:20  n-ando
# The include search path option order in AM_CPPFLAGS was changed.
#
# Revision 1.2  2007/01/12 14:45:13  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/12/18 06:51:50  n-ando
# The first commitment.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =         \
	-I.               \
	-I$(top_builddir) \
	-I$(top_builddir)/src/lib/ \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(includedir)


AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib


noinst_PROGRAMS = PublisherPeriodicTests

nodist_PublisherPeriodicTests_SOURCES =           \
	../TestRunner.cpp                         \
	$(top_builddir)/src/lib/coil/common/Properties.cpp        \
	$(top_builddir)/src/lib/rtm/PublisherPeriodic.cpp \
	$(top_builddir)/src/lib/coil/common/stringutil.cpp        \
	PublisherPeriodicTests.cpp

PublisherPeriodicTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
PublisherPeriodicTests_LDADD   = -lcppunit -lcoil

EXTRA_DIST =                  \
	PublisherPeriodicTests.cpp

# all
all: do-test

# do tests
do-test:
	./PublisherPeriodicTests --xml publisherperiodictests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f PublisherPeriodicTests        \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PublisherFlush unit test
# @date   $Date: 2007/01/21 06:53:09 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.3  2007/01/21 06:53:09  n-ando
# The include search path option order in AM_CPPFLAGS was changed.
#
# Revision 1.2  2007/01/12 14:45:00  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/12/18 06:51:03  n-ando
# The first commitment.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =             \
	-I.               \
	-I$(top_builddir) \
	-I$(top_builddir)/rtm/idl \
	-I$(includedir)


AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir)


noinst_PROGRAMS = PublisherFlushTests

nodist_PublisherFlushTests_SOURCES =           \
	../TestRunner.cpp                      \
	$(top_builddir)/rtm/Properties.cpp     \
	$(top_builddir)/rtm/PublisherFlush.cpp \
	$(top_builddir)/rtm/StringUtil.cpp     \
	PublisherFlushTests.cpp

PublisherFlushTests_LDFLAGS = -L$(libdir)
PublisherFlushTests_LDADD   = -lcppunit

EXTRA_DIST =                \
	PublisherFlushTests.cpp

# all
all: do-test

# do tests
do-test:
	./PublisherFlushTests --xml publisherflushtests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f PublisherFlushTests           \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

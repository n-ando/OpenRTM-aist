# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PublisherFactory unit test
# @date   $Date: 2007/01/21 06:53:04 $
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
	-I.               \
	-I$(top_builddir) \
	-I$(top_builddir)         \
	-I$(top_builddir)/src/lib/ \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(top_builddir)/src/lib/rtm \
	-I$(includedir)


AM_LDFLAGS =              \
	 -L.              \
	-L$(top_builddir) \
        -L$(top_builddir)/src/lib/coil/lib/ 


noinst_PROGRAMS = PublisherFactoryTests

nodist_PublisherFactoryTests_SOURCES =            \
	../TestRunner.cpp                         \
	$(top_builddir)/src/lib/coil/common/Properties.cpp        \
	$(top_builddir)/src/lib/coil/common/stringutil.cpp        \
	$(top_builddir)/src/lib/rtm/PublisherFactory.cpp  \
	$(top_builddir)/src/lib/rtm/PublisherNew.cpp      \
	$(top_builddir)/src/lib/rtm/PublisherPeriodic.cpp \
	$(top_builddir)/src/lib/rtm/PublisherFlush.cpp    \
	PublisherFactoryTests.cpp

PublisherFactoryTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
PublisherFactoryTests_LDADD   = -lcppunit -lcoil

EXTRA_DIST =                  \
	PublisherFactoryTests.cpp

# all
all: do-test

# do tests
do-test:
	./PublisherFactoryTests --xml publisherfactortests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f PublisherFactoryTests         \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

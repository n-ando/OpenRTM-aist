# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for SdoConfiguration unit test
# @date   $Date: 2007/01/21 06:53:31 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS= \
	-I. \
	-I$(top_builddir) \
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(includedir)


AM_LDFLAGS= \
	-L. \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib



IDL_SOURCES = $(top_builddir)/src/lib/rtm/idl/SDOPackage.idl

noinst_PROGRAMS = SdoConfigurationTests

nodist_SdoConfigurationTests_SOURCES = \
	../TestRunner.cpp \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	$(top_builddir)/src/lib/rtm/NVUtil.cpp \
	$(top_builddir)/src/lib/coil/common/stringutil.cpp \
	$(top_builddir)/src/lib/coil/common/Properties.cpp \
	$(top_builddir)/src/lib/rtm/ConfigAdmin.cpp \
	$(top_builddir)/src/lib/rtm/SdoConfiguration.cpp \
	SdoConfigurationTests.cpp

SdoConfigurationTests_LDFLAGS = -L$(libdir) -L$(AM_LDFLAGS)
SdoConfigurationTests_LDADD   = -lcppunit -lcoil -luuid

EXTRA_DIST =                  \
	SdoConfigurationTests.cpp

# all
all: do-test

# do tests
do-test:
	./SdoConfigurationTests --xml sdoconfigurationotests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

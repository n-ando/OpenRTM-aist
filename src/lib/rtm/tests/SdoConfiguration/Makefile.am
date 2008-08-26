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

#
# $Log: Makefile.am,v $
# Revision 1.3  2007/01/21 06:53:31  n-ando
# The include search path option order in AM_CPPFLAGS was changed.
#
# Revision 1.2  2007/01/12 14:45:25  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/11/27 08:30:08  n-ando
# TestSuites are devided into each directory.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS= \
	-I. \
	-I$(top_builddir) \
	-I$(top_builddir)/rtm/idl \
	-I$(includedir)


AM_LDFLAGS= \
	-L. \
	-L$(top_builddir)


IDL_SOURCES = $(top_builddir)/rtm/idl/SDOPackage.idl

noinst_PROGRAMS = SdoConfigurationTests

nodist_SdoConfigurationTests_SOURCES = \
	../TestRunner.cpp \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	$(top_builddir)/rtm/NVUtil.cpp \
	$(top_builddir)/rtm/StringUtil.cpp \
	$(top_builddir)/rtm/Properties.cpp \
	$(top_builddir)/rtm/ConfigAdmin.cpp \
	$(top_builddir)/rtm/SdoConfiguration.cpp \
	SdoConfigurationTests.cpp

SdoConfigurationTests_LDFLAGS = -L$(libdir)
SdoConfigurationTests_LDADD   = -lcppunit

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
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

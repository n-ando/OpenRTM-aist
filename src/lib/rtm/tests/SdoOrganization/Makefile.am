# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for SdoOrganization unit test
# @date   $Date: 2007/01/21 06:53:36 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.3  2007/01/21 06:53:36  n-ando
# The include search path option order in AM_CPPFLAGS was changed.
#
# Revision 1.2  2007/01/12 14:45:30  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/11/27 08:30:06  n-ando
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
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm \
	-I$(top_builddir)/src/lib/rtm_corba \
	-I$(top_builddir)/src/lib/rtm_corba/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(includedir)


AM_LDFLAGS=               \
	-L.               \
	-L$(top_builddir)


IDL_SOURCES = $(top_builddir)/src/lib/rtm_corba/idl/SDOPackage.idl

noinst_PROGRAMS = SdoOrganizationTests

nodist_SdoOrganizationTests_SOURCES =              \
	../TestRunner.cpp                          \
	$(IDL_SOURCES:.idl=Skel.cpp)               \
	$(top_builddir)/src/lib/rtm/SdoOrganization.cpp    \
	SdoOrganizationTests.cpp

SdoOrganizationTests_LDFLAGS = -L$(libdir)
SdoOrganizationTests_LDADD   = -lcppunit -lcoil -luuid

EXTRA_DIST =                 \
	SdoOrganizationTests.cpp

# all
all: do-test

# do tests
do-test:
	./SdoOrganizationTests --xml sdoorganizationtests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

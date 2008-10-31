# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for ManagerConfig unit test
# @date   $Date: 2007/01/21 06:52:12 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.3  2007/01/21 06:52:12  n-ando
# The include search path option order in AM_CPPFLAGS was changed.
#
# Revision 1.2  2007/01/12 14:43:47  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/11/27 08:30:00  n-ando
# TestSuites are devided into each directory.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =\
	-I. \
	-I$(top_builddir) \
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm_corba/idl \
	-I$(top_builddir)/src/lib/rtm_corba \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(top_builddir)/src/lib/rtm \
	-I$(includedir)

AM_LDFLAGS = \
	-L. \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib

noinst_PROGRAMS = ManagerConfigTests

nodist_ManagerConfigTests_SOURCES =\
	../TestRunner.cpp\
	$(top_builddir)/src/lib/coil/common/stringutil.cpp \
	$(top_builddir)/src/lib/coil/common/Properties.cpp \
	$(top_builddir)/src/lib/rtm/ManagerConfig.cpp \
	ManagerConfigTests.cpp

ManagerConfigTests_LDFLAGS = -L$(libdir)
ManagerConfigTests_LDADD   = -lcppunit -lcoil

EXTRA_DIST =               \
	ManagerConfigTests.cpp \
	rtc.conf

# all
all: do-test

# do tests
do-test:
	./ManagerConfigTests --xml managerconfigtests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

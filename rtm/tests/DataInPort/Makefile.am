# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for DataInPort unit test
# @date   $Date: 2007-01-21 06:51:47 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =                     \
	 -I.                      \
	-I$(top_builddir)         \
	-I$(top_builddir)/rtm/idl \
	-I$(includedir)           \
	-DORB_IS_OMNIORB

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir)

IDL_SOURCES =                                   \
	$(top_srcdir)/rtm/idl/RTC.idl           \
	$(top_srcdir)/rtm/idl/SDOPackage.idl    \
	$(top_srcdir)/rtm/idl/DataPort.idl      \
	$(top_srcdir)/rtm/idl/BasicDataType.idl

noinst_PROGRAMS = DataInPortTests

nodist_DataInPortTests_SOURCES =               \
	../TestRunner.cpp                      \
	$(IDL_SOURCES:.idl=Skel.cpp)           \
	$(top_srcdir)/rtm/StringUtil.cpp       \
	$(top_srcdir)/rtm/Properties.cpp       \
	$(top_srcdir)/rtm/NVUtil.cpp           \
	$(top_srcdir)/rtm/PortBase.cpp         \
	$(top_srcdir)/rtm/InPortProvider.cpp   \
	$(top_srcdir)/rtm/DataInPort.cpp       \
	DataInPortTests.cpp

DataInPortTests_LDFLAGS = -L$(libdir)
DataInPortTests_LDADD   = -lcppunit

EXTRA_DIST =            \
	DataInPortTests.cpp

# all
all: do-test

# do tests
do-test:
	./DataInPortTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

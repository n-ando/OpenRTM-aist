# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for DataInPort unit test
# @date   $Date: 2007-01-12 14:43:21 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.4 2007-01-12 14:43:21 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.3  2006/12/02 18:53:58  n-ando
# *** empty log message ***
#
# Revision 1.2  2006/11/28 02:40:04  n-ando
# IDL source entries were added.
#
# Revision 1.1  2006/11/27 08:30:16  n-ando
# TestSuites are devided into each directory.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =                 \
	 -I.                      \
	-I$(includedir)           \
	-I$(top_builddir)         \
	-I$(top_builddir)/rtm/idl \
	-DORB_IS_OMNIORB

AM_LDFLAGS =          \
	-L.               \
	-L$(top_builddir)

IDL_SOURCES =                               \
	$(top_srcdir)/rtm/idl/RTC.idl           \
	$(top_srcdir)/rtm/idl/SDOPackage.idl    \
	$(top_srcdir)/rtm/idl/DataPort.idl      \
	$(top_srcdir)/rtm/idl/BasicDataType.idl

noinst_PROGRAMS = DataInPortTests

nodist_DataInPortTests_SOURCES =           \
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

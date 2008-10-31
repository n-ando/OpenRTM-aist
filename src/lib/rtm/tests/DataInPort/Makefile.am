# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for DataInPort unit test
# @date   $Date: 2007/01/21 06:51:47 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.5  2007/01/21 06:51:47  n-ando
# The include search path option order in AM_CPPFLAGS was changed.
#
# Revision 1.4  2007/01/12 14:43:21  n-ando
# Some fixes for distribution control.
#
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

AM_CPPFLAGS =                     \
	 -I.                      \
	-I$(top_builddir)         \
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm_corba \
	-I$(top_builddir)/src/lib/rtm_corba/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(includedir)

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib

IDL_SOURCES = \
	$(top_srcdir)/src/lib/rtm_corba/idl/RTC.idl \
	$(top_srcdir)/src/lib/rtm_corba/idl/OpenRTM.idl \
	$(top_srcdir)/src/lib/rtm_corba/idl/SDOPackage.idl \
	$(top_srcdir)/src/lib/rtm_corba/idl/BasicDataType.idl \
	$(top_srcdir)/src/lib/rtm_corba/idl/DataPort.idl

noinst_PROGRAMS = DataInPortTests

nodist_DataInPortTests_SOURCES =               \
	../TestRunner.cpp                      \
	$(IDL_SOURCES:.idl=Skel.cpp)           \
	$(top_srcdir)/src/lib/coil/common/stringutil.cpp       \
	$(top_srcdir)/src/lib/coil/common/Properties.cpp       \
	$(top_srcdir)/src/lib/rtm/DataInPort.cpp       \
	$(top_srcdir)/src/lib/rtm/NVUtil.cpp           \
	$(top_srcdir)/src/lib/rtm/PortBase.cpp         \
	$(top_srcdir)/src/lib/rtm/InPortProvider.cpp   \
	DataInPortTests.cpp

DataInPortTests_LDFLAGS = -L$(libdir)
DataInPortTests_LDADD   = -lcppunit -lcoil -luuid

EXTRA_DIST =            \
	DataInPortTests.cpp

# all
all: do-test

# do tests
do-test:
	./DataInPortTests --xml datainporttests.xml --xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

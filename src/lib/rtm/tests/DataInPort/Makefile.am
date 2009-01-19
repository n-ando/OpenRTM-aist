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

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =                     \
	 -I.                      \
	-I$(top_builddir)         \
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(includedir)

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib

IDL_SOURCES = \
	$(top_srcdir)/src/lib/rtm/idl/RTC.idl \
	$(top_srcdir)/src/lib/rtm/idl/OpenRTM.idl \
	$(top_srcdir)/src/lib/rtm/idl/SDOPackage.idl \
	$(top_srcdir)/src/lib/rtm/idl/BasicDataType.idl \
	$(top_srcdir)/src/lib/rtm/idl/DataPort.idl

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

DataInPortTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
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
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

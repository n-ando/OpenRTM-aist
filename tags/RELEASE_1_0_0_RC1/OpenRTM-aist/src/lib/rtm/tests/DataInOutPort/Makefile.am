# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for DataInOutPort unit test
# @date   $Date: 2007/01/21 06:51:41 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.3  2007/01/21 06:51:41  n-ando
# The include search path option order in AM_CPPFLAGS was changed.
#
# Revision 1.2  2007/01/12 14:43:13  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2007/01/06 18:05:13  n-ando
# *** empty log message ***
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =                     \
	 -I.                      \
	-I$(top_builddir)         \
	-I$(top_builddir)/src/lib/ \
	-I$(top_builddir)/src/lib/rtm \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(includedir)
#	-DORB_IS_OMNIORB

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib

IDL_SOURCES = \
	$(top_srcdir)/src/lib/rtm/idl/SDOPackage.idl    \
	$(top_srcdir)/src/lib/rtm/idl/RTC.idl           \
	$(top_srcdir)/src/lib/rtm/idl/BasicDataType.idl \
	$(top_srcdir)/src/lib/rtm/idl/DataPort.idl

noinst_PROGRAMS = DataInOutPortTests

nodist_DataInOutPortTests_SOURCES =                 \
	../TestRunner.cpp                           \
	$(IDL_SOURCES:.idl=Skel.cpp)                \
	$(top_srcdir)/src/lib/coil/common/stringutil.cpp            \
	$(top_srcdir)/src/lib/coil/common/Properties.cpp            \
	$(top_srcdir)/src/lib/rtm/NVUtil.cpp                \
	$(top_srcdir)/src/lib/rtm/PortBase.cpp              \
	$(top_srcdir)/src/lib/rtm/DataInPort.cpp            \
	$(top_srcdir)/src/lib/rtm/OutPortBase.cpp           \
	$(top_srcdir)/src/lib/rtm/DataOutPort.cpp           \
	$(top_srcdir)/src/lib/rtm/InPortProvider.cpp        \
	$(top_srcdir)/src/lib/rtm/OutPortProvider.cpp       \
	$(top_srcdir)/src/lib/rtm/PublisherFactory.cpp      \
	$(top_srcdir)/src/lib/rtm/PublisherNew.cpp          \
	$(top_srcdir)/src/lib/rtm/PublisherPeriodic.cpp     \
	$(top_srcdir)/src/lib/rtm/PublisherFlush.cpp        \
	DataInOutPortTests.cpp

DataInOutPortTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
DataInOutPortTests_LDADD   = -lcppunit -lcoil -luuid

# Extra sources included distribution
EXTRA_DIST =               \
	DataInOutPortTests.cpp


# all
all: do-test

# do tests
do-test:
	./DataInOutPortTests --xml datainoutporttests.xml --xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for DataOutPort unit test
# @date   $Date: 2007/01/21 06:51:52 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =                             \
	-I.                               \
	-I$(top_builddir)/src/lib         \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(includedir)                   \
	-I$(top_builddir)/src/lib/coil/include \
	-DORB_IS_OMNIORB

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib


SUFFIXES = .idl Skel.cpp Stub.cpp Stub.o Skel.o
.idlSkel.cpp:
	$(top_srcdir)/build/makewrapper.py $< rtm/tests
	$(IDLC) $(IDLFLAGS) $<

IDL_SOURCES =             \
	$(top_srcdir)/src/lib/rtm/idl/RTC.idl           \
	$(top_srcdir)/src/lib/rtm/idl/SDOPackage.idl    \
	$(top_srcdir)/src/lib/rtm/idl/DataPort.idl      \
	$(top_srcdir)/src/lib/rtm/idl/BasicDataType.idl

noinst_PROGRAMS = DataOutPortTests

nodist_DataOutPortTests_SOURCES =               \
	../TestRunner.cpp                       \
	$(IDL_SOURCES:.idl=Skel.cpp)            \
	$(top_srcdir)/src/lib/rtm/Properties.cpp        \
	$(top_srcdir)/src/lib/rtm/NVUtil.cpp            \
	$(top_srcdir)/src/lib/rtm/PortBase.cpp          \
	$(top_srcdir)/src/lib/rtm/OutPortBase.cpp       \
	$(top_srcdir)/src/lib/rtm/OutPortProvider.cpp   \
	$(top_srcdir)/src/lib/rtm/DataOutPort.cpp       \
	$(top_srcdir)/src/lib/rtm/PublisherFactory.cpp  \
	$(top_srcdir)/src/lib/rtm/PublisherNew.cpp      \
	$(top_srcdir)/src/lib/rtm/PublisherPeriodic.cpp \
	$(top_srcdir)/src/lib/rtm/PublisherFlush.cpp    \
	DataOutPortTests.cpp

DataOutPortTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
DataOutPortTests_LDADD   = -lcppunit -lcoil

EXTRA_DIST =             \
	DataOutPortTests.cpp

# all
all: do-test

# do tests
do-test:
	./DataOutPortTests --xml dataoutporttests.xml --xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

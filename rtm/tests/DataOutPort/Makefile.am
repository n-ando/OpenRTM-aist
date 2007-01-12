# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for DataOutPort unit test
# @date   $Date: 2007-01-12 14:43:27 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.2 2007-01-12 14:43:27 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.1  2006/11/27 08:30:18  n-ando
# TestSuites are devided into each directory.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =                 \
	-I.                       \
	-I$(includedir)           \
	-I$(top_builddir)         \
	-I$(top_builddir)/rtm/idl \
	-DORB_IS_OMNIORB

AM_LDFLAGS =          \
	-L.               \
	-L$(top_builddir)


SUFFIXES = .idl Skel.cpp Stub.cpp Stub.o Skel.o
.idlSkel.cpp:
	$(top_srcdir)/build/makewrapper.py $< rtm/tests
	$(IDLC) $(IDLFLAGS) $<

IDL_SOURCES =                               \
	$(top_srcdir)/rtm/idl/RTC.idl           \
	$(top_srcdir)/rtm/idl/SDOPackage.idl    \
	$(top_srcdir)/rtm/idl/DataPort.idl      \
	$(top_srcdir)/rtm/idl/BasicDataType.idl

noinst_PROGRAMS = DataOutPortTests

nodist_DataOutPortTests_SOURCES =           \
	../TestRunner.cpp                       \
	$(IDL_SOURCES:.idl=Skel.cpp)            \
	$(top_srcdir)/rtm/StringUtil.cpp        \
	$(top_srcdir)/rtm/Properties.cpp        \
	$(top_srcdir)/rtm/NVUtil.cpp            \
	$(top_srcdir)/rtm/PortBase.cpp          \
	$(top_srcdir)/rtm/OutPortBase.cpp       \
	$(top_srcdir)/rtm/OutPortProvider.cpp   \
	$(top_srcdir)/rtm/DataOutPort.cpp       \
	$(top_srcdir)/rtm/PublisherFactory.cpp  \
	$(top_srcdir)/rtm/PublisherNew.cpp      \
	$(top_srcdir)/rtm/PublisherPeriodic.cpp \
	$(top_srcdir)/rtm/PublisherFlush.cpp    \
	DataOutPortTests.cpp

DataOutPortTests_LDFLAGS = -L$(libdir)
DataOutPortTests_LDADD   = -lcppunit

EXTRA_DIST =             \
	DataOutPortTests.cpp

# all
all: do-test

# do tests
do-test:
	./DataOutPortTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

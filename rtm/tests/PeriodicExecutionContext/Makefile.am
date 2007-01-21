# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PeriodicExecutionContext unit test
# @date   $Date: 2007-01-21 13:07:15 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.1 2007-01-21 13:07:15 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =                     \
	-I.                       \
	-I$(top_builddir)         \
	-I$(top_builddir)/rtm/idl \
	-I$(top_builddir)/rtm     \
	-I$(includedir)

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir)


IDL_SOURCES =                                \
	$(top_srcdir)/rtm/idl/SDOPackage.idl \
	$(top_srcdir)/rtm/idl/RTC.idl


noinst_PROGRAMS = PeriodicExecutionContextTests

nodist_PeriodicExecutionContextTests_SOURCES =         \
	../TestRunner.cpp                              \
	$(IDL_SOURCES:.idl=Skel.cpp)                   \
	$(top_srcdir)/rtm/PeriodicExecutionContext.cpp \
	PeriodicExecutionContextTests.cpp

PeriodicExecutionContextTests_LDFLAGS = -L$(libdir)
PeriodicExecutionContextTests_LDADD   = -lcppunit

EXTRA_DIST = \
	PeriodicExecutionContextTests.cpp

# all
all: do-test

# do tests
do-test:
	./PeriodicExecutionContextTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

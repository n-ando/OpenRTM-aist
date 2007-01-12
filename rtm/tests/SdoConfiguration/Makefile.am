# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for SdoConfiguration unit test
# @date   $Date: 2007-01-12 14:45:25 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.2 2007-01-12 14:45:25 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.1  2006/11/27 08:30:08  n-ando
# TestSuites are devided into each directory.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS=          \
	-I.               \
	-I$(includedir)   \
	-I$(top_builddir)

AM_LDFLAGS=           \
	-L.               \
	-L$(top_builddir)


IDL_SOURCES = $(top_builddir)/rtm/idl/SDOPackage.idl

noinst_PROGRAMS = SdoConfigurationTests

nodist_SdoConfigurationTests_SOURCES =       \
	../TestRunner.cpp                        \
	$(IDL_SOURCES:.idl=Skel.cpp)             \
	$(top_builddir)/rtm/SdoConfiguration.cpp \
	SdoConfigurationTests.cpp

SdoConfigurationTests_LDFLAGS = -L$(libdir)
SdoConfigurationTests_LDADD   = -lcppunit

EXTRA_DIST =                  \
	SdoConfigurationTests.cpp

# all
all: do-test

# do tests
do-test:
	./SdoConfigurationTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for SdoConfiguration unit test
# @date   $Date: 2007-01-21 06:53:31 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS=              \
	-I.               \
	-I$(top_builddir) \
	-I$(includedir)


AM_LDFLAGS=               \
	-L.               \
	-L$(top_builddir)


IDL_SOURCES = $(top_builddir)/rtm/idl/SDOPackage.idl

noinst_PROGRAMS = SdoConfigurationTests

nodist_SdoConfigurationTests_SOURCES =           \
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

# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for SdoOrganization unit test
# @date   $Date: 2006-11-27 08:30:06 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.1 2006-11-27 08:30:06 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS= -I.                  \
	-I$(includedir)           \
	-I$(top_builddir)

AM_LDFLAGS= -L.                   \
	-L$(top_builddir)


SUFFIXES = .idl Skel.cpp Stub.cpp Stub.o Skel.o
.idlSkel.cpp:
	$(top_srcdir)/build/makewrapper.py $< rtm/tests
	$(IDLC) $(IDLFLAGS) $<

IDL_SOURCES = $(top_builddir)/rtm/idl/SDOPackage.idl

noinst_PROGRAMS = SdoOrganizationTests

SdoOrganizationTests_SOURCES =                     \
	../TestRunner.cpp                          \
	$(IDL_SOURCES:.idl=Skel.cpp)               \
	$(top_builddir)/rtm/SdoOrganization.cpp    \
	SdoOrganizationTests.cpp
SdoOrganizationTests_LDFLAGS = -L$(libdir)
SdoOrganizationTests_LDADD   = -lcppunit

# all
all: do-test

# do tests
do-test:
	./SdoOrganizationTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

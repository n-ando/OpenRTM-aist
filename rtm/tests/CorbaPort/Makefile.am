# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for CorbaPort unit test
# @date   $Date: 2007-01-04 00:50:44 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.1 2007-01-04 00:50:44 n-ando Exp $
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
	-I$(top_builddir)         \
	-I$(top_builddir)/rtm/idl


AM_LDFLAGS= -L.                   \
	-L$(top_builddir)

SUFFIXES = .idl Skel.cpp Stub.cpp Stub.o Skel.o
.idlSkel.cpp:
	$(top_srcdir)/build/makewrapper.py $< rtm/tests/CorbaPort
	$(IDLC) $(IDLFLAGS) $<

IDL_SOURCES =                                \
	$(top_srcdir)/rtm/idl/SDOPackage.idl \
	$(top_srcdir)/rtm/idl/RTC.idl        \
	MyService.idl

noinst_PROGRAMS = CorbaPortTests

CorbaPortTests_SOURCES =                \
	../TestRunner.cpp               \
	$(IDL_SOURCES:.idl=Skel.cpp)    \
	CorbaPortTests.cpp              \
	$(top_srcdir)/rtm/StringUtil.cpp\
	$(top_srcdir)/rtm/Properties.cpp\
	$(top_srcdir)/rtm/NVUtil.cpp    \
	$(top_srcdir)/rtm/PortBase.cpp  \
	$(top_srcdir)/rtm/CorbaPort.cpp

CorbaPortTests_LDFLAGS = -L$(libdir)
CorbaPortTests_LDADD   = -lcppunit

# all
all: do-test

# do tests
do-test:
	./CorbaPortTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for CorbaConsumer unit test
# @date   $Date: 2007-01-12 14:42:59 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.2 2007-01-12 14:42:59 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.1  2006/11/27 08:30:14  n-ando
# TestSuites are devided into each directory.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS=           \
	-I.                \
	-I$(includedir)    \
	-I$(top_builddir)

AM_LDFLAGS=           \
	-L.               \
	-L$(top_builddir)


SUFFIXES = .idl Skel.cpp Stub.cpp Stub.o Skel.o
.idlSkel.cpp:
	$(top_srcdir)/build/makewrapper.py $< rtm/tests/CorbaConsumer/
	$(IDLC) $(IDLFLAGS) $<

IDL_SOURCES = Hello.idl

noinst_PROGRAMS = CorbaConsumerTests

nodist_CorbaConsumerTests_SOURCES = \
	../TestRunner.cpp               \
	$(IDL_SOURCES:.idl=Skel.cpp)    \
	CorbaConsumerTests.cpp

CorbaConsumerTests_LDFLAGS = -L$(libdir)
CorbaConsumerTests_LDADD   = -lcppunit

EXTRA_DIST =               \
	CorbaConsumerTests.cpp \
	$(IDL_SOURCES)

# all
all: do-test

# do tests
do-test:
	./CorbaConsumerTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

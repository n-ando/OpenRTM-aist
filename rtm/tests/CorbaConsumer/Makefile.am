# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for CorbaConsumer unit test
# @date   $Date: 2006-11-27 08:30:14 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.1 2006-11-27 08:30:14 n-ando Exp $
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
	$(top_srcdir)/build/makewrapper.py $< rtm/tests/CorbaConsumer/
	$(IDLC) $(IDLFLAGS) $<

IDL_SOURCES = Hello.idl

noinst_PROGRAMS = CorbaConsumerTests

CorbaConsumerTests_SOURCES =         \
	../TestRunner.cpp            \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	CorbaConsumerTests.cpp
CorbaConsumerTests_LDFLAGS = -L$(libdir)
CorbaConsumerTests_LDADD   = -lcppunit

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

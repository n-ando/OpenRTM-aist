# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for SyncLIFO unit test
# @date   $Date: 2007-09-19 02:37:12 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.1.2.1 2007-09-19 02:37:12 n-ando Exp $
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


#SUFFIXES = .idl Skel.cpp Stub.cpp Stub.o Skel.o
#.idlSkel.cpp:
#	$(top_srcdir)/build/makewrapper.py $< rtm/tests
#	$(IDLC) $(IDLFLAGS) $<

# if this test uses other lib libHogeSkel.a or libHogeSkel.so
#
#noinst_LTLIBRARIES = libHogeSkel.la

#IDL_SOURCES = hoge.idl
#libHogeSkel_la_SOURCES =            \
#	$(IDL_SOURCES:.idl=Skel.cpp) \
#	$(IDL_SOURCES:.idl=Stub.cpp) \
#	$(IDL_SOURCES:.idl=Skel.h)   \
#	$(IDL_SOURCES:.idl=Stub.h)
#libHogeSkel_la_LIBADD = $(LIBS)

noinst_PROGRAMS = SyncLIFOTests

SyncLIFOTests_SOURCES = ../TestRunner.cpp SyncLIFOTests.cpp
SyncLIFOTests_LDFLAGS = -L$(libdir)
SyncLIFOTests_LDADD   = -lcppunit

# all
all: do-test

# do tests
do-test:
	./SyncLIFOTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl


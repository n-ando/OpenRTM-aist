# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for CORBA_SeqUtil unit test
# @date   $Date: 2007-01-12 14:42:45 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.2 2007-01-12 14:42:45 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.1  2006/11/27 08:30:10  n-ando
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

if ORB_IS_ORBIT2
OIDLC = $(IDLC) -DORBIT2_IDL
else
OIDLC = echo
endif

SUFFIXES = .idl Skel.cpp Stub.cpp Stub.o Skel.o
.idlSkel.cpp:
	$(top_srcdir)/build/makewrapper.py $< rtm/tests/CORBA_SeqUtil
	$(OIDLC) $<
	$(IDLC) $(IDLFLAGS) $<

IDL_SOURCES = SeqUtilTests.idl

noinst_PROGRAMS = CORBA_SeqUtilTests

nodist_CORBA_SeqUtilTests_SOURCES =  \
	../TestRunner.cpp                \
	$(IDL_SOURCES:.idl=Skel.cpp)     \
	CORBA_SeqUtilTests.cpp

CORBA_SeqUtilTests_LDFLAGS = -L$(libdir)
CORBA_SeqUtilTests_LDADD   = -lcppunit

EXTRA_DIST = \
	CORBA_SeqUtilTests.cpp \
	SeqUtilTests.idl

# all
all: do-test

# do tests
do-test:
	./CORBA_SeqUtilTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

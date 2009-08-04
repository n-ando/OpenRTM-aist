# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for CORBA_SeqUtil unit test
# @date   $Date: 2007/01/21 06:51:16 $
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
	-I$(includedir) \
	-I$(top_builddir)/src/lib/rtm/idl/ \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(top_builddir)/src/lib/rtmd/ \
	-I$(top_builddir)/src/lib/


AM_LDFLAGS=               \
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

nodist_CORBA_SeqUtilTests_SOURCES =      \
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
	./CORBA_SeqUtilTests --xml corba_sequtiltests.xml --xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for StringUtil unit test
# @date   $Date: 2007-01-12 14:45:50 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.2 2007-01-12 14:45:50 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.1  2006/11/27 08:29:56  n-ando
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

noinst_PROGRAMS = StringUtilTests

nodist_StringUtilTests_SOURCES =       \
	../TestRunner.cpp                  \
	$(top_builddir)/rtm/StringUtil.cpp \
	StringUtilTests.cpp

StringUtilTests_LDFLAGS = -L$(libdir)
StringUtilTests_LDADD   = -lcppunit

EXTRA_DIST = \
	StringUtilTests.cpp

# all
all: do-test

# do tests
do-test:
	./StringUtilTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

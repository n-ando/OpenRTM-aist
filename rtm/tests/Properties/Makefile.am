# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for Properties unit test
# @date   $Date: 2007-01-21 06:52:57 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
# Revision 1.2  2007/01/12 14:44:49  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/11/27 08:29:54  n-ando
# TestSuites are devided into each directory.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =             \
	 -I.              \
	-I$(top_builddir) \
	-I$(includedir)


AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir)


noinst_PROGRAMS = PropertiesTests

nodist_PropertiesTests_SOURCES =           \
	../TestRunner.cpp                  \
	$(top_builddir)/rtm/Properties.cpp \
	$(top_builddir)/rtm/StringUtil.cpp \
	PropertiesTests.cpp

PropertiesTests_LDFLAGS = -L$(libdir)
PropertiesTests_LDADD   = -lcppunit

EXTRA_DIST =                   \
	PropertiesTests.cpp    \
	defaults.conf          \
	storedRead.conf        \
	splitKeyValueTest.data \
	store-test.data


# all
all: do-test

# do tests
do-test:
	./PropertiesTests

# clean-up
clean-local:
	rm -f                               \
	new.conf stored.conf                \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

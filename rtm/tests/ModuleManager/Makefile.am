# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for ModuleManager unit test
# @date   $Date: 2007-01-21 06:52:17 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =             \
	 -I.              \
	-I$(top_builddir) \
	-I$(includedir)


AM_LDFLAGS =              \
	 -L.              \
	-L$(top_builddir)


noinst_PROGRAMS = ModuleManagerTests

nodist_ModuleManagerTests_SOURCES =           \
	../TestRunner.cpp                     \
	$(top_builddir)/rtm/ModuleManager.cpp \
	$(top_builddir)/rtm/Properties.cpp    \
	$(top_builddir)/rtm/StringUtil.cpp    \
	ModuleManagerTests.cpp

ModuleManagerTests_LDFLAGS = -L$(libdir)
ModuleManagerTests_LDADD   = -lcppunit

EXTRA_DIST =               \
	ModuleManagerTests.cpp

# all
all: do-test

# do tests
do-test:
	./ModuleManagerTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

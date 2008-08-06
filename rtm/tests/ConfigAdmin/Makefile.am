# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for Properties unit test
# @date   $Date: 2008/05/12 01:48:34 $
#
# $Id: Makefile.am,v 1.1 2008/05/12 01:48:34 arafune Exp $
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.1  2008/05/12 01:48:34  arafune
# The first commitment.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS = \
	 -I. \
	-I$(top_builddir) \
	-I$(includedir)


AM_LDFLAGS = \
	-L. \
	-L$(top_builddir)


noinst_PROGRAMS = ConfigAdminTests

nodist_ConfigAdminTests_SOURCES = \
	../TestRunner.cpp \
	$(top_builddir)/rtm/Properties.cpp \
	$(top_builddir)/rtm/StringUtil.cpp \
	$(top_builddir)/rtm/ConfigAdmin.cpp \
	ConfigAdminTests.cpp

ConfigAdminTests_LDFLAGS = -L$(libdir)
ConfigAdminTests_LDADD   = -lcppunit

EXTRA_DIST = \
	ConfigAdminTests.cpp


# all
all: do-test

# do tests
do-test:
	./ConfigAdminTests --xml configadmintests.xml --xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
	new.conf stored.conf                \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

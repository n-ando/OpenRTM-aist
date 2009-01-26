# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for StringUtil unit test
# @date   $Date: 2007/01/21 06:53:55 $
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
	-I$(includedir)


AM_LDFLAGS=               \
	-L.               \
	-L$(top_builddir)

noinst_PROGRAMS = StringUtilTests

nodist_StringUtilTests_SOURCES =           \
	../TestRunner.cpp                  \
	$(top_builddir)/rtm/StringUtil.cpp \
	StringUtilTests.cpp

StringUtilTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
StringUtilTests_LDADD   = -lcppunit

EXTRA_DIST = \
	StringUtilTests.cpp

# all
all: do-test

# do tests
do-test:
	./StringUtilTests --xml stringutiltests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

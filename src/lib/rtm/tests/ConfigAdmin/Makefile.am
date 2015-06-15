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
	-coverage \
	 -I. \
	-I$(top_builddir) \
	-I$(includedir)   \
	-I$(top_builddir)/src/lib/coil/include/ \
	-I$(top_builddir)/src/lib/


AM_LDFLAGS = \
	-L. \
	-L$(top_builddir)


noinst_PROGRAMS = ConfigAdminTests

nodist_ConfigAdminTests_SOURCES = \
	../TestRunner.cpp \
	$(top_builddir)/src/lib/coil/common/Properties.cpp \
	$(top_builddir)/src/lib/coil/common/stringutil.cpp \
	$(top_builddir)/src/lib/rtm/ConfigurationListener.cpp \
	$(top_builddir)/src/lib/rtm/ConfigAdmin.cpp \
	ConfigAdminTests.cpp

ConfigAdminTests_LDFLAGS = -L$(libdir)
ConfigAdminTests_LDADD   = -lcppunit -lgcov

EXTRA_DIST = \
	ConfigAdminTests.cpp


# all
all: do-test do-coverage

do-coverage: 
	rm -rf ./Coverage
	./ConfigAdminTests 
	gcov ConfigAdminTests.gcda 
	mkdir -p ./Coverage 
	lcov -c -d . -o ./Coverage/ConfigAdminTests.info 
	../rtm_tests_changeInfo.py ./Coverage/ConfigAdminTests.info 
	genhtml -o ./Coverage ./Coverage/ConfigAdminTests.info 

# do tests
do-test:
	./ConfigAdminTests --xml configadmintests.xml --xsl default.xsl

# clean-up
clean-local:
	rm -rf ./Coverage
	rm -f *.gcda *.gcno *.gcov
	rm -f ConfigAdminTests
	rm -f                               \
        *.log *.xml                         \
	new.conf stored.conf                \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl



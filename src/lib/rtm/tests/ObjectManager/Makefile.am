# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for ObjectManager unit test
# @date   $Date: 2007/01/21 06:52:34 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS = \
	-coverage \
	 -I. \
	-I$(top_builddir) \
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(top_builddir)/src/lib/rtm \
	-I$(includedir)


AM_LDFLAGS =              \
	 -L.              \
	-L$(top_builddir)


noinst_PROGRAMS = ObjectManagerTests

nodist_ObjectManagerTests_SOURCES =     \
	../TestRunner.cpp               \
	ObjectManagerTests.cpp

ObjectManagerTests_LDFLAGS = -L$(libdir)
ObjectManagerTests_LDADD   = -lcppunit -lgcov

EXTRA_DIST =               \
	ObjectManagerTests.cpp

# all
all: do-test do-coverage

do-coverage: 
	./ObjectManagerTests 
	/usr/bin/gcov ObjectManagerTests.gcda 
	/bin/mkdir ./Coverage 
	/usr/bin/lcov -c -d . -o ./Coverage/ObjectManagerTests.info 
	/usr/bin/python ../rtm_tests_changeInfo.py ./Coverage/ObjectManagerTests.info 
	/usr/bin/genhtml -o ./Coverage ./Coverage/ObjectManagerTests.info 

# do tests
do-test:
	./ObjectManagerTests --xml objectmanagertests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -rf ./Coverage
	rm -f *.gcda *.gcno *.gcov
	rm -f ObjectManagerTests
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl


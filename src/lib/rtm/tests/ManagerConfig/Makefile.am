# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for ManagerConfig unit test
# @date   $Date: 2007/01/21 06:52:12 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =\
	-coverage \
	-I. \
	-I$(top_builddir) \
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(top_builddir)/src/lib/rtm \
	-I$(includedir)

AM_LDFLAGS = \
	-L. \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib

noinst_PROGRAMS = ManagerConfigTests

nodist_ManagerConfigTests_SOURCES =\
	../TestRunner.cpp\
	$(top_builddir)/src/lib/rtm/ManagerConfig.cpp \
	ManagerConfigTests.cpp

ManagerConfigTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
ManagerConfigTests_LDADD   = -lcppunit -lcoil -lgcov

EXTRA_DIST =               \
	ManagerConfigTests.cpp \
	rtc.conf

# all
all: do-test do-coverage

do-coverage: 
	./ManagerConfigTests 
	/usr/bin/gcov ManagerConfigTests.gcda 
	/bin/mkdir ./Coverage 
	/usr/bin/lcov -c -d . -o ./Coverage/ManagerConfigTests.info 
	/usr/bin/python ../rtm_tests_changeInfo.py ./Coverage/ManagerConfigTests.info 
	/usr/bin/genhtml -o ./Coverage ./Coverage/ManagerConfigTests.info 

# do tests
do-test:
	./ManagerConfigTests --xml managerconfigtests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -rf ./Coverage
	rm -f *.gcda *.gcno *.gcov
	rm -f ManagerConfigTests
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl


# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PeriodicECSharedComposite unit test
# @date   $Date: 2010/02/10 13:07:15 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am 1724 2010-01-21 01:32:15Z hakuta $
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
	-I$(top_builddir)/src/lib/rtm \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(includedir)

AM_LDFLAGS = \
	-L. \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/rtm/.libs \
	-L$(top_builddir)/src/lib/coil/lib


noinst_PROGRAMS = PeriodicECSharedCompositeTests

nodist_PeriodicECSharedCompositeTests_SOURCES = \
	../TestRunner.cpp \
	PeriodicECSharedCompositeTests.cpp

PeriodicECSharedCompositeTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
PeriodicECSharedCompositeTests_LDADD   = -lcppunit -lRTC -lcoil -luuid -lgcov

EXTRA_DIST = \
	PeriodicECSharedCompositeTests.cpp

# all
all: do-test do-coverage

do-coverage: 
	rm -rf ./Coverage
	./PeriodicECSharedCompositeTests 
	gcov PeriodicECSharedCompositeTests.gcda 
	mkdir -p ./Coverage 
	lcov -c -d . -o ./Coverage/PeriodicECSharedCompositeTests.info 
	../rtm_tests_changeInfo.py ./Coverage/PeriodicECSharedCompositeTests.info 
	genhtml -o ./Coverage ./Coverage/PeriodicECSharedCompositeTests.info 

# do tests
do-test:
	./PeriodicECSharedCompositeTests --xml periodicecsharedcompositetests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -rf ./Coverage
	rm -f *.gcda *.gcno *.gcov
	rm -f PeriodicECSharedCompositeTests
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl



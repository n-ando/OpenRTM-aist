# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for NumberingPolicy unit test
# @date   $Date: 2008/05/02 13:44:01 $
#
# $Id: Makefile.am,v 1.1 2008/05/02 13:44:01 arafune Exp $
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.1  2008/05/02 13:44:01  arafune
# The first commitment.
#
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
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(top_builddir)/src/lib/rtm \
	-I$(includedir)

AM_LDFLAGS = \
	-L. \
	-L$(top_builddir)

noinst_PROGRAMS = NumberingPolicyTests

nodist_NumberingPolicyTests_SOURCES = \
	../TestRunner.cpp \
	$(top_srcdir)/src/lib/rtm/NumberingPolicy.cpp \
	NumberingPolicyTests.cpp

NumberingPolicyTests_LDFLAGS = -L$(libdir)
NumberingPolicyTests_LDADD   = -lcppunit -lgcov

EXTRA_DIST = \
	NumberingPolicyTests.cpp

# all
all: do-test do-coverage

do-coverage: 
	rm -rf ./Coverage
	./NumberingPolicyTests 
	gcov NumberingPolicyTests.gcda 
	mkdir -p ./Coverage 
	lcov -c -d . -o ./Coverage/NumberingPolicyTests.info 
	../rtm_tests_changeInfo.py ./Coverage/NumberingPolicyTests.info 
	genhtml -o ./Coverage ./Coverage/NumberingPolicyTests.info 

# do tests
do-test:
	./NumberingPolicyTests --xml numberingpolicytests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -rf ./Coverage
	rm -f *.gcda *.gcno *.gcov
	rm -f NumberingPolicyTests
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl



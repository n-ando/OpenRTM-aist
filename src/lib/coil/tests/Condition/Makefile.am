# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for Condition unit test
# @date   $Date$
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log$
#


AUTOMAKE_OPTIONS = 1.9

AM_CPPFLAGS= -I.                  \
	-I$(includedir)           \
	-I$(top_builddir)         \
	-I$(top_srcdir)/include

AM_LDFLAGS= -L.                   \
	-L$(top_builddir)


noinst_PROGRAMS = ConditionTests

ConditionTests_SOURCES = ../TestRunner.cpp \
                         $(top_srcdir)/posix/coil/Task.cpp \
                         $(top_srcdir)/posix/coil/Condition.cpp \
                         ConditionTests.cpp
ConditionTests_LDFLAGS = -L$(libdir)
ConditionTests_LDADD   = -lcppunit

TEST_SRC = $(ConditionTests_SOURCES)
TEST_H   = 

# all
all: do-test

# do tests
do-test:
	./ConditionTests

# clean-up
clean-local:
	rm -f *.o *.Po *.gch *.la
	rm -f *~ *core
	rm -f *.xml
	rm -f Makefile.old
	rm -f *.vcproj
	rm -rf Release Debug

#------------------------------------------------------------
# vcproj file build rules
#------------------------------------------------------------
win32_builddir = .

vcproj: Condition_vc8.vcproj Condition_vc9.vcproj

Condition_vc8.vcproj:
	$(top_builddir)/build/vcprojtool.py vcproj \
		--projectname ConditionTest \
		--type EXE \
		--vcversion "8.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/Condition_vc8.vcproj \
		--yaml ../coil_test.vcproj.yaml \
		--source $(TEST_SRC)
#		--header $(TEST_H)
	qkc -sm $(win32_builddir)/Condition_vc8.vcproj

Condition_vc9.vcproj:
	$(top_builddir)/build/vcprojtool.py vcproj \
		--projectname ConditionTest \
		--type EXE \
		--vcversion "9.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/Condition_vc9.vcproj \
		--yaml ../coil_test.vcproj.yaml \
		--source $(TEST_SRC)
#		--header $(TEST_H)
	qkc -sm $(win32_builddir)/Condition_vc9.vcproj



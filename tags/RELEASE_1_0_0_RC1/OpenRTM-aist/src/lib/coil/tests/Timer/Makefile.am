# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for Timer unit test
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


noinst_PROGRAMS = TimerTests

TimerTests_SOURCES = ../TestRunner.cpp \
                     $(top_srcdir)/common/TimeValue.cpp \
                     $(top_srcdir)/posix/coil/Task.cpp \
                     $(top_srcdir)/posix/coil/Timer.cpp \
                     TimerTests.cpp
TimerTests_LDFLAGS = -L$(libdir)
TimerTests_LDADD   = -lcppunit

TEST_SRC = $(TimerTests_SOURCES)
TEST_H   = 

# all
all: do-test

# do tests
do-test:
	./TimerTests

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

vcproj: Timer_vc8.vcproj Timer_vc9.vcproj

Timer_vc8.vcproj:
	$(top_builddir)/build/vcprojtool.py vcproj \
		--projectname TimerTest \
		--type EXE \
		--vcversion "8.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/Timer_vc8.vcproj \
		--yaml ../coil_test.vcproj.yaml \
		--source $(TEST_SRC)
#		--header $(TEST_H)
	qkc -sm $(win32_builddir)/Timer_vc8.vcproj

Timer_vc9.vcproj:
	$(top_builddir)/build/vcprojtool.py vcproj \
		--projectname TimerTest \
		--type EXE \
		--vcversion "9.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/Timer_vc9.vcproj \
		--yaml ../coil_test.vcproj.yaml \
		--source $(TEST_SRC)
#		--header $(TEST_H)
	qkc -sm $(win32_builddir)/Timer_vc9.vcproj



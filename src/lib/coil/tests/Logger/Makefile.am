# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for Logger unit test
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

AM_CPPFLAGS= -I../../include      \
	-I$(includedir)           \
	-I$(top_builddir)

AM_LDFLAGS= -L.                   \
	-L$(top_builddir)


noinst_PROGRAMS = LoggerTests

LoggerTests_SOURCES = ../TestRunner.cpp LoggerTests.cpp
LoggerTests_LDFLAGS = -L../../lib -L$(libdir)
LoggerTests_LDADD   = -lcppunit -lcoil

TEST_SRC = $(LoggerTests_SOURCES)
TEST_H   = 

# all
all: do-test

# do tests
do-test:
	./LoggerTests
	diff3 *.log

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

vcproj: Logger_vc8.vcproj Logger_vc9.vcproj

Logger_vc8.vcproj:
	$(top_builddir)/build/vcprojtool.py vcproj \
		--projectname LoggerTest \
		--type EXE \
		--vcversion "8.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/Logger_vc8.vcproj \
		--yaml ../coil_test.vcproj.yaml \
		--source $(TEST_SRC)
#		--header $(TEST_H)
	qkc -sm $(win32_builddir)/Logger_vc8.vcproj

Logger_vc9.vcproj:
	$(top_builddir)/build/vcprojtool.py vcproj \
		--projectname LoggerTest \
		--type EXE \
		--vcversion "9.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/Logger_vc9.vcproj \
		--yaml ../coil_test.vcproj.yaml \
		--source $(TEST_SRC)
#		--header $(TEST_H)
	qkc -sm $(win32_builddir)/Logger_vc9.vcproj



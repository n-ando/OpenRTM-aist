# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for DynamicLib unit test
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
	-I$(top_builddir)

AM_LDFLAGS= -L.                   \
	-L$(top_builddir)


noinst_PROGRAMS = DynamicLibTests

DynamicLibTests_SOURCES = ../TestRunner.cpp DynamicLibTests.cpp
DynamicLibTests_LDFLAGS = -L$(libdir)
DynamicLibTests_LDADD   = -lcppunit

TEST_SRC = $(DynamicLibTests_SOURCES)
TEST_H   = 

# all
all: do-test

# do tests
do-test:
	./DynamicLibTests

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

vcproj: DynamicLib_vc8.vcproj DynamicLib_vc9.vcproj

DynamicLib_vc8.vcproj:
	$(top_builddir)/build/vcprojtool.py vcproj \
		--projectname DynamicLibTest \
		--type EXE \
		--vcversion "8.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/DynamicLib_vc8.vcproj \
		--yaml ../coil_test.vcproj.yaml \
		--source $(TEST_SRC)
#		--header $(TEST_H)
	qkc -sm $(win32_builddir)/DynamicLib_vc8.vcproj

DynamicLib_vc9.vcproj:
	$(top_builddir)/build/vcprojtool.py vcproj \
		--projectname DynamicLibTest \
		--type EXE \
		--vcversion "9.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/DynamicLib_vc9.vcproj \
		--yaml ../coil_test.vcproj.yaml \
		--source $(TEST_SRC)
#		--header $(TEST_H)
	qkc -sm $(win32_builddir)/DynamicLib_vc9.vcproj



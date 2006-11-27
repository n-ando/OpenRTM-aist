# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for ManagerConfig unit test
# @date   $Date: 2006-11-27 08:30:00 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.1 2006-11-27 08:30:00 n-ando Exp $
#
#------------------------------------------------------------

#
# $Log: not supported by cvs2svn $
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS= -I.                  \
	-I$(includedir)           \
	-I$(top_builddir)

AM_LDFLAGS= -L.                   \
	-L$(top_builddir)


#SUFFIXES = .idl Skel.cpp Stub.cpp Stub.o Skel.o
#.idlSkel.cpp:
#	$(top_srcdir)/build/makewrapper.py $< rtm/tests
#	$(IDLC) $(IDLFLAGS) $<

# if this test uses other lib libHogeSkel.a or libHogeSkel.so
#
#noinst_LTLIBRARIES = libHogeSkel.la

#IDL_SOURCES = hoge.idl
#libHogeSkel_la_SOURCES =            \
#	$(IDL_SOURCES:.idl=Skel.cpp) \
#	$(IDL_SOURCES:.idl=Stub.cpp) \
#	$(IDL_SOURCES:.idl=Skel.h)   \
#	$(IDL_SOURCES:.idl=Stub.h)
#libHogeSkel_la_LIBADD = $(LIBS)

noinst_PROGRAMS = ManagerConfigTests

ManagerConfigTests_SOURCES =               \
	../TestRunner.cpp                  \
	ManagerConfigTests.cpp             \
	$(top_builddir)/rtm/StringUtil.cpp \
	$(top_builddir)/rtm/Properties.cpp \
	$(top_builddir)/rtm/ManagerConfig.cpp
ManagerConfigTests_LDFLAGS = -L$(libdir)
ManagerConfigTests_LDADD   = -lcppunit

# all
all: do-test

# do tests
do-test:
	./ManagerConfigTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl
       

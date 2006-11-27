# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for DataInPort unit test
# @date   $Date: 2006-11-27 08:30:16 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id: Makefile.am,v 1.1 2006-11-27 08:30:16 n-ando Exp $
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

noinst_PROGRAMS = DataInPortTests

DataInPortTests_SOURCES =                        \
	../TestRunner.cpp                        \
	$(top_builddir)/rtm/idl/DataPortSkel.cpp \
	$(top_builddir)/rtm/PortBase.cpp         \
	$(top_builddir)/rtm/DataInPort.cpp       \
	DataInPortTests.cpp
DataInPortTests_LDFLAGS = -L$(libdir)
DataInPortTests_LDADD   = -lcppunit

# all
all: do-test

# do tests
do-test:
	./DataInPortTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl
       

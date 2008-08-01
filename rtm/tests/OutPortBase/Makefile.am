# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for OutPortBase unit test
# @date   $Date: 2007/01/12 14:44:30 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.3  2007/01/12 14:44:30  n-ando
# Some fixes for distribution control.
#
# Revision 1.2  2006/12/18 06:54:13  n-ando
# clean-local target OutPortBaseTests was added.
#
# Revision 1.1  2006/12/02 18:55:38  n-ando
# *** empty log message ***
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =         \
	 -I.              \
	-I$(top_builddir) \
	-I$(includedir)

AM_LDFLAGS =          \
	 -L.              \
	-L$(top_builddir)


noinst_PROGRAMS = OutPortBaseTests

nodist_OutPortBaseTests_SOURCES =       \
	../TestRunner.cpp                   \
	$(top_builddir)/rtm/OutPortBase.cpp \
	OutPortBaseTests.cpp

OutPortBaseTests_LDFLAGS = -L$(libdir)
OutPortBaseTests_LDADD   = -lcppunit

EXTRA_DIST =       \
	OutPortBaseTests.cpp

# all
all: do-test

# do tests
do-test:
	./OutPortBaseTests --xml outportbasetests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f OutPortBaseTests              \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

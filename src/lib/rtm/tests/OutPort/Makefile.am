# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for OutPort unit test
# @date   $Date: 2007/01/21 06:52:40 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.5  2007/01/21 06:52:40  n-ando
# The include search path option order in AM_CPPFLAGS was changed.
#
# Revision 1.4  2007/01/12 14:44:24  n-ando
# Some fixes for distribution control.
#
# Revision 1.3  2006/12/18 06:54:30  n-ando
# clean-local target OutPortTests was added.
#
# Revision 1.2  2006/12/02 18:52:44  n-ando
# *** empty log message ***
#
# Revision 1.1  2006/11/29 04:26:12  n-ando
# Makefile.am for OutPortTests.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =             \
	 -I.              \
	-I$(top_builddir) \
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm_corba/idl \
	-I$(top_builddir)/src/lib/rtm_corba \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(top_builddir)/src/lib/rtm \
	-I$(includedir)


AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir)


noinst_PROGRAMS = OutPortTests

nodist_OutPortTests_SOURCES =               \
	../TestRunner.cpp                   \
	$(top_builddir)/src/lib/rtm/OutPortBase.cpp \
	OutPortTests.cpp

OutPortTests_LDFLAGS = -L$(libdir)
OutPortTests_LDADD   = -lcppunit -lcoil

EXTRA_DIST =         \
	OutPortTests.cpp

# all
all: do-test

# do tests
do-test:
	./OutPortTests --xml outporttests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f OutPortTests                  \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

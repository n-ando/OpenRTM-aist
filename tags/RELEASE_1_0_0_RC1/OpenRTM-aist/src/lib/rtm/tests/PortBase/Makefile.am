# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PortBase unit test
# @date   $Date: 2007/01/21 06:52:52 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.3  2007/01/21 06:52:52  n-ando
# The include search path option order in AM_CPPFLAGS was changed.
#
# Revision 1.2  2007/01/12 14:51:52  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2006/11/27 08:35:06  n-ando
# TestSuites are devided into each directory.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =                     \
	-I.                       \
	-I$(top_builddir)         \
	-I$(top_builddir)/src/lib/ \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(top_builddir)/src/lib/rtm \
	-I$(includedir)



AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir) \
        -L$(top_builddir)/src/lib/coil/lib/ 


IDL_SOURCES =                                \
	$(top_srcdir)/src/lib/rtm/idl/RTC.idl        \
	$(top_srcdir)/src/lib/rtm/idl/SDOPackage.idl 



noinst_PROGRAMS = PortBaseTests

nodist_PortBaseTests_SOURCES =           \
	../TestRunner.cpp                \
	$(IDL_SOURCES:.idl=Skel.cpp)     \
	$(top_builddir)/src/lib/rtm/PortBase.cpp \
	PortBaseTests.cpp


PortBaseTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
PortBaseTests_LDADD   = -lcppunit -lcoil -luuid

EXTRA_DIST =          \
	PortBaseTests.cpp

# all
all: do-test

# do tests
do-test:
	./PortBaseTests --xml portbasetests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

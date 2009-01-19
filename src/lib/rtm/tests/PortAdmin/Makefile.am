# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for PortAdmin unit test
# @date   $Date: 2007/01/21 06:52:47 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =                     \
	-I.                       \
	-I$(top_builddir)         \
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(top_builddir)/src/lib/rtm \
	-I$(includedir)

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib


IDL_SOURCES =                                \
	$(top_srcdir)/src/lib/rtm/idl/RTC.idl        \
	$(top_srcdir)/src/lib/rtm/idl/SDOPackage.idl 

noinst_PROGRAMS = PortAdminTests

nodist_PortAdminTests_SOURCES =           \
	../TestRunner.cpp                 \
	$(IDL_SOURCES:.idl=Skel.cpp)      \
	$(top_builddir)/src/lib/rtm/PortBase.cpp  \
	$(top_builddir)/src/lib/rtm/PortAdmin.cpp \
	PortAdminTests.cpp

PortAdminTests_LDFLAGS = -L$(libdir) -L$(AM_LDFLAGS)
PortAdminTests_LDADD   = -lcppunit -lcoil -luuid

EXTRA_DIST =           \
	PortAdminTests.cpp

# all
all: do-test

# do tests
do-test:
	./PortAdminTests --xml portadmintests.xml \
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

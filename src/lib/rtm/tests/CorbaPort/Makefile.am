# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for CorbaPort unit test
# @date   $Date: 2007/01/21 06:51:28 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.3  2007/01/21 06:51:28  n-ando
# The include search path option order in AM_CPPFLAGS was changed.
#
# Revision 1.2  2007/01/12 14:43:07  n-ando
# Some fixes for distribution control.
#
# Revision 1.1  2007/01/04 00:50:44  n-ando
# *** empty log message ***
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
	-I$(top_builddir)/src/lib/rtm \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(includedir)

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib

SUFFIXES = .idl Skel.cpp Stub.cpp Skel.o Stub.o
.idlSkel.cpp:
	$(top_srcdir)/build/makewrapper.py $< rtm/tests/CorbaPort
	$(IDLC) $(IDLFLAGS) $<

IDL_SOURCES = MyService.idl

noinst_PROGRAMS = CorbaPortTests

nodist_CorbaPortTests_SOURCES =                  \
	../TestRunner.cpp                        \
	$(IDL_SOURCES:.idl=Skel.cpp)             \
	$(top_srcdir)/src/lib/rtm/idl/SDOPackageSkel.cpp \
	$(top_srcdir)/src/lib/rtm/idl/RTCSkel.cpp        \
	$(top_srcdir)/src/lib/coil/common/stringutil.cpp         \
	$(top_srcdir)/src/lib/coil/common/Properties.cpp         \
	$(top_srcdir)/src/lib/rtm/NVUtil.cpp             \
	$(top_srcdir)/src/lib/rtm/PortBase.cpp           \
	$(top_srcdir)/src/lib/rtm/CorbaPort.cpp          \
	CorbaPortTests.cpp

CorbaPortTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
CorbaPortTests_LDADD   = -lcppunit -lcoil -luuid

EXTRA_DIST =           \
	$(IDL_SOURCES)     \
	CorbaPortTests.cpp

# all
all: do-test

# do tests
do-test:
	./CorbaPortTests --xml corbaporttests.xml --xsl defaults.xsl

# clean-up
clean-local:
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

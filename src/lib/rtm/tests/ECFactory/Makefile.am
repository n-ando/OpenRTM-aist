# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for ECFactory unit test
# @date   $Date: 2008/04/15 08:39:40 $
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.1  2008/04/15 08:39:40  arafune
# The first commitment.
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS = \
	-I. \
	-I$(top_builddir) \
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm \
	-I$(top_builddir)/src/lib/rtm_corba/idl \
	-I$(top_builddir)/src/lib/rtm_corba \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(includedir)

AM_LDFLAGS = \
	-L. \
	-L$(top_builddir)


IDL_SOURCES = \
	$(top_srcdir)/src/lib/rtm_corba/idl/SDOPackage.idl \
	$(top_srcdir)/src/lib/rtm_corba/idl/RTC.idl \
	$(top_srcdir)/src/lib/rtm_corba/idl/OpenRTM.idl

noinst_PROGRAMS = ECFactoryTests

nodist_ECFactoryTests_SOURCES = \
	../TestRunner.cpp \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	$(top_srcdir)/src/lib/rtm/NVUtil.cpp \
	$(top_srcdir)/src/lib/coil/common/stringutil.cpp \
	$(top_srcdir)/src/lib/coil/common/Properties.cpp \
	$(top_srcdir)/src/lib/rtm/CorbaNaming.cpp \
	$(top_srcdir)/src/lib/rtm/NamingManager.cpp \
	$(top_srcdir)/src/lib/rtm/PortBase.cpp \
	$(top_srcdir)/src/lib/rtm/PortAdmin.cpp \
	$(top_srcdir)/src/lib/rtm/ConfigAdmin.cpp \
	$(top_srcdir)/src/lib/rtm/SdoConfiguration.cpp \
	$(top_srcdir)/src/lib/rtm/ModuleManager.cpp \
	$(top_srcdir)/src/lib/rtm/ManagerConfig.cpp \
	$(top_srcdir)/src/lib/rtm/RTCUtil.cpp \
	$(top_srcdir)/src/lib/coil/common/Timer.cpp \
	$(top_srcdir)/src/lib/rtm/CorbaObjectManager.cpp \
	$(top_srcdir)/src/lib/rtm/NumberingPolicy.cpp \
	$(top_srcdir)/src/lib/rtm/Manager.cpp \
	$(top_srcdir)/src/lib/rtm/Factory.cpp \
	$(top_srcdir)/src/lib/rtm/ECFactory.cpp \
	$(top_srcdir)/src/lib/rtm/PeriodicExecutionContext.cpp \
	$(top_srcdir)/src/lib/rtm/OpenHRPExecutionContext.cpp \
	$(top_srcdir)/src/lib/rtm/ExtTrigExecutionContext.cpp \
	$(top_srcdir)/src/lib/rtm/RTObject.cpp \
	ECFactoryTests.cpp

ECFactoryTests_LDFLAGS = -L$(libdir)
ECFactoryTests_LDADD   = -lcppunit -lcoil -luuid

EXTRA_DIST = \
	ECFactoryTests.cpp

# all
all: do-test

# do tests
do-test:
	./ECFactoryTests --xml ecfactorytests.xml --xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

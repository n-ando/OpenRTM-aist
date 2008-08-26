# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for RTObject unit test
# @date   $Date: 2008/04/24 08:50:14 $
#
# $Id: Makefile.am,v 1.1 2008/04/24 08:50:14 arafune Exp $
#
#------------------------------------------------------------

#
# $Log: Makefile.am,v $
# Revision 1.1  2008/04/24 08:50:14  arafune
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
	-I$(top_builddir)/rtm \
	-I$(top_builddir)/rtm/idl \
	-I$(includedir)

AM_LDFLAGS = \
	-L. \
	-L$(top_builddir)

IDL_SOURCES = \
	$(top_srcdir)/rtm/idl/SDOPackage.idl \
	$(top_srcdir)/rtm/idl/RTC.idl \
	$(top_srcdir)/rtm/idl/OpenRTM.idl

noinst_PROGRAMS = RTObjectTests

nodist_RTObjectTests_SOURCES = \
	../TestRunner.cpp \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	$(top_srcdir)/rtm/NVUtil.cpp \
	$(top_srcdir)/rtm/StringUtil.cpp \
	$(top_srcdir)/rtm/Properties.cpp \
	$(top_srcdir)/rtm/CorbaNaming.cpp \
	$(top_srcdir)/rtm/NamingManager.cpp \
	$(top_srcdir)/rtm/PortBase.cpp \
	$(top_srcdir)/rtm/PortAdmin.cpp \
	$(top_srcdir)/rtm/ConfigAdmin.cpp \
	$(top_srcdir)/rtm/SdoConfiguration.cpp \
	$(top_srcdir)/rtm/ModuleManager.cpp \
	$(top_srcdir)/rtm/ManagerConfig.cpp \
	$(top_srcdir)/rtm/RTCUtil.cpp \
	$(top_srcdir)/rtm/Timer.cpp \
	$(top_srcdir)/rtm/CorbaObjectManager.cpp \
	$(top_srcdir)/rtm/NumberingPolicy.cpp \
	$(top_srcdir)/rtm/Manager.cpp \
	$(top_srcdir)/rtm/Factory.cpp \
	$(top_srcdir)/rtm/ECFactory.cpp \
	$(top_srcdir)/rtm/ExtTrigExecutionContext.cpp \
	$(top_srcdir)/rtm/PeriodicExecutionContext.cpp \
	$(top_srcdir)/rtm/OpenHRPExecutionContext.cpp \
	$(top_srcdir)/rtm/RTObject.cpp \
	RTObjectTests.cpp

RTObjectTests_LDFLAGS = -L$(libdir)
RTObjectTests_LDADD   = -lcppunit

EXTRA_DIST = \
	RTObjectTests.cpp

# all
all: do-test

# do tests
do-test:
	./RTObjectTests --xml rtobjecttests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

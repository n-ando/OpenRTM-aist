## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for unit test
##
## $Id: Makefile.am,v 1.7 2006-10-31 13:12:49 kurihara Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.6  2006/10/26 08:56:22  n-ando
## StateMachineTests was added.
##
## Revision 1.5  2006/10/26 08:43:49  kurihara
##
## FactoryTests, PortProfileHelperTests, SdoServiceTests, are added.
##
## Revision 1.4  2006/10/24 03:07:31  kurihara
##
## ObjectManagerTests is added
##
## Revision 1.3  2006/10/23 06:29:22  kurihara
##
## add ManagerConfigTests and StringUtilTests.
##
## Revision 1.2  2006/09/20 08:50:31  n-ando
## ModuleManagerTests is added.
##
## Revision 1.1  2006/09/11 18:40:38  n-ando
## The first commit.
##
##
##------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@
TESTS = RtcNamingTests

INCLUDES = -I$(top_srcdir) -I$(includedir) -I../../ -I../../rtm/idl

IDL_SOURCES = \
	HelloWorld.idl



noinst_PROGRAMS = \
	RtcNamingTests \
	PropertiesTests \
	StringUtilTests \
	ModuleManagerTests \
	ManagerConfigTests \
	ObjectManagerTests \
	FactoryTests \
	PortProfileHelperTests \
	SdoServiceTests \
	StateMachineTests \
	SdoOrganizationTests \
	SdoConfigurationTests \
	CORBA_SeqUtilTests

RtcNamingTests_SOURCES = RtcNamingTests.cpp
RtcNamingTests_LDFLAGS = -L$(libdir)
RtcNamingTests_LDADD   = ../RtcNaming.o ./HelloWorld.o -lcppunit

PropertiesTests_SOURCES = PropertiesTests.cpp
PropertiesTests_LDFLAGS = -L$(libdir)
PropertiesTests_LDADD   = ../StringUtil.o ../Properties.o -lcppunit

StringUtilTests_SOURCES = StringUtilTests.cpp
StringUtilTests_LDFLAGS = -L$(libdir)
StringUtilTests_LDADD   = ../StringUtil.o -lcppunit

ModuleManagerTests_SOURCES = ModuleManagerTests.cpp
ModuleManagerTests_LDFLAGS = -L$(libdir)
ModuleManagerTests_LDADD   = ../StringUtil.o ../Properties.o ../ModuleManager.o  -lcppunit -lACE

ManagerConfigTests_SOURCES = ManagerConfigTests.cpp
ManagerConfigTests_LDFLAGS = -L$(libdir)
ManagerConfigTests_LDADD   = ../StringUtil.o ../Properties.o ../ManagerConfig.o -lcppunit

ObjectManagerTests_SOURCES = ObjectManagerTests.cpp
ObjectManagerTests_LDFLAGS = -L$(libdir)
ObjectManagerTests_LDADD   = -lcppunit

FactoryTests_SOURCES = FactoryTests.cpp
FactoryTests_LDFLAGS = -L$(libdir)
FactoryTests_LDADD   = ../../rtm/idl/RTMBaseSkel.o ../../rtm/idl/RTCPortBaseSkel.o ../../rtm/idl/RTCInPortSkel.o ../../rtm/idl/RTComponentSkel.o ../../rtm/idl/RTCBaseSkel.o ../RtcBase.o ../Properties.o ../Manager.o ../Factory.o -lcppunit


PortProfileHelperTests_SOURCES = PortProfileHelperTests.cpp
PortProfileHelperTests_LDFLAGS = -L$(libdir)
PortProfileHelperTests_LDADD   = ../../rtm/idl/SDOPackageSkel.o ../../rtm/idl/RTCSkel.o ../PortProfileHelper.o -lcppunit


SdoServiceTests_SOURCES = SdoServiceTests.cpp
SdoServiceTests_LDFLAGS = -L$(libdir)
SdoServiceTests_LDADD   = ../../rtm/idl/SDOPackageStub.o ../../rtm/idl/SDOPackageSkel.o ../../rtm/idl/RTCSkel.o -lcppunit

StateMachineTests_SOURCES = StateMachineTests.cpp
StateMachineTests_LDFLAGS = -L$(libdir)
StateMachineTests_LDADD   = -lcppunit

SdoOrganizationTests_SOURCES = SdoOrganizationTests.cpp
SdoOrganizationTests_LDFLAGS = -L$(libdir)
SdoOrganizationTests_LDADD   = ../../rtm/idl/SDOPackageStub.o ../SdoOrganization.o -lcppunit -lomniDynamic4


SdoConfigurationTests_SOURCES = SdoConfigurationTests.cpp
SdoConfigurationTests_LDFLAGS = -L$(libdir)
SdoConfigurationTests_LDADD   = ../../rtm/idl/SDOPackageStub.o ../SdoConfiguration.o -lcppunit -lomniDynamic4


CORBA_SeqUtilTests_SOURCES = CORBA_SeqUtilTests.cpp
CORBA_SeqUtilTests_LDFLAGS = -L$(libdir)
CORBA_SeqUtilTests_LDADD   = SeqUtilTestsSkel.o -lcppunit

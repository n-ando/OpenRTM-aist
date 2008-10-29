## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for unit test
##
## $Id$
##
## $Log: Makefile.am,v $
## Revision 1.17  2008/05/09 12:03:32  arafune
## Unit tests for Manager were added.
##
## Revision 1.16  2008/05/02 13:43:10  arafune
## Unit tests for NumberingPolicy were added.
##
## Revision 1.15  2008/05/02 11:30:20  arafune
## Unit tests for RTCUtil were added.
##
## Revision 1.14  2008/04/30 07:56:03  arafune
## Unit tests for NamingManager were added.
##
## Revision 1.13  2008/04/30 03:38:10  arafune
## Unit tests for CorbaNaming were added.
##
## Revision 1.12  2008/04/25 07:29:16  arafune
## Unit tests for CorbaObjectManager were added.
##
## Revision 1.11  2008/04/24 08:51:25  arafune
## Unit tests for RTObject were added.
##
## Revision 1.10  2008/04/18 06:34:28  arafune
## Unit tests for ConfigAdmin were added.
##
## Revision 1.9  2008/04/15 08:40:33  arafune
## Unit tests for ECFactory were added.
##
## Revision 1.15.4.1  2007/09/19 02:33:40  n-ando
## Unit tests for SyncLIFO and SyncFIFO were added.
##
## Revision 1.15  2007/01/21 13:06:23  n-ando
## The include search path option order in AM_CPPFLAGS was changed.
##
## Revision 1.14  2007/01/12 14:40:56  n-ando
## Some build subdir entry were added.
##
## Revision 1.13  2006/12/18 06:57:24  n-ando
## clean-local target alltests.xml and etc. were added.
##
## Revision 1.12  2006/11/27 08:10:26  n-ando
## TestSuites are devided into each directory.
##
## Revision 1.11  2006/11/22 11:48:33  kurihara
## CorbaConsumerTests is added.
##
## Revision 1.10  2006/11/14 07:22:28  kurihara
## NVUtilTests is added.
##
## Revision 1.9  2006/11/13 09:13:53  kurihara
## PortAdminTests and RingBufferTests were added.
##
## Revision 1.8  2006/11/08 01:18:23  kurihara
## PortBaseTests is added.
##
## Revision 1.7  2006/10/31 13:12:49  kurihara
## SdoConfigurationTests and CORBA_SeqUtilTests were added.
##
## Revision 1.6  2006/10/26 08:56:22  n-ando
## StateMachineTests was added.
##
## Revision 1.5  2006/10/26 08:43:49  kurihara
## FactoryTests, PortProfileHelperTests, SdoServiceTests, are added.
##
## Revision 1.4  2006/10/24 03:07:31  kurihara
## ObjectManagerTests is added
##
## Revision 1.3  2006/10/23 06:29:22  kurihara
## add ManagerConfigTests and StringUtilTests.
##
## Revision 1.2  2006/09/20 08:50:31  n-ando
## ModuleManagerTests is added.
##
## Revision 1.1  2006/09/11 18:40:38  n-ando
## The first commit.
##------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

SUBDIRS = \
	CORBA_SeqUtil     \
	ConfigAdmin \
	CorbaConsumer     \
	CorbaNaming \
	CorbaObjectManager \
	CorbaPort         \
	DataInOutPort     \
	DataInPort        \
	DataOutPort       \
	ECFactory \
	ExtTrigExecutionContext \
	Factory           \
	InPort            \
	InPortCorbaConsumer \
	InPortCorbaProvider \
	InPortProvider \
	InPortTcpSockConsumer \
	InPortTcpSockProvider \
	Manager  \
	ManagerConfig     \
	ModuleManager     \
	NVUtil            \
	NamingManager \
	NullBuffer        \
	NumberingPolicy \
	ObjectManager     \
	OutPort           \
	OutPortBase       \
	OutPortCorbaConsumer \
	OutPortCorbaProvider \
	OutPortProvider   \
	PeriodicExecutionContext \
	PortAdmin         \
	PortBase          \
	PublisherFactory  \
	PublisherFlush    \
	PublisherNew      \
	PublisherPeriodic \
	RTCUtil \
	RTObject \
	RingBuffer        \
	SdoConfiguration  \
	SdoOrganization  \
	SdoService  \
	StateMachine      \
	StringUtil        \
	TimeValue         \
	Timer

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS= -I.          \
	-I$(top_builddir) \
	-I$(includedir)   \
	-I$(top_builddir)/rtm/idl

AM_LDFLAGS=                       \
	-L$(top_builddir)         \
	-L$(top_builddir)/rtm     \
	-L$(top_builddir)/rtm/idl

COMMON_OBJS=SdoConfiguration/SDOPackageSkel.o   \
	PortBase/RTCSkel.o \
	PeriodicExecutionContext/OpenRTMSkel.o

RTC_OBJS=                                   \
	ConfigAdmin/ConfigAdmin.o \
	CorbaNaming/CorbaNaming.o \
	CorbaNaming/OpenHRPExecutionContext.o \
	CorbaObjectManager/CorbaObjectManager.o \
	CorbaPort/CorbaPort.o \
	DataInPort/DataInPort.o \
	DataOutPort/DataOutPort.o \
	ECFactory/ECFactory.o \
	ExtTrigExecutionContext/ExtTrigExecutionContext.o \
	Factory/Factory.o \
	InPortProvider/InPortProvider.o \
	Manager/Manager.o \
	ManagerConfig/ManagerConfig.o \
	ModuleManager/ModuleManager.o \
	NVUtil/NVUtil.o \
	NamingManager/NamingManager.o \
	NumberingPolicy/NumberingPolicy.o \
	OutPortBase/OutPortBase.o \
	OutPortProvider/OutPortProvider.o \
	PeriodicExecutionContext/PeriodicExecutionContext.o \
	PortAdmin/PortAdmin.o \
	PortBase/PortBase.o \
	Properties/Properties.o \
	PublisherFactory/PublisherFactory.o \
	PublisherFlush/PublisherFlush.o \
	PublisherNew/PublisherNew.o \
	PublisherPeriodic/PublisherPeriodic.o \
	RTCUtil/RTCUtil.o \
	RTObject/RTObject.o \
	SdoConfiguration/SdoConfiguration.o \
	SdoOrganization/SdoOrganization.o \
	StringUtil/StringUtil.o \
	Timer/Timer.o


CORBACONSUMER_OBJS=               \
	CorbaConsumer/HelloSkel.o \
	CorbaPort/MyServiceSkel.o \
	CORBA_SeqUtil/SeqUtilTestsSkel.o \
	DataInOutPort/DataPortSkel.o \
	DataInPort/BasicDataTypeSkel.o


TEST_OBJS = $(COMMON_OBJS)      \
	$(RTC_OBJS)             \
	$(CORBACONSUMER_OBJS)  \
	CORBA_SeqUtil/CORBA_SeqUtilTests.o \
	ConfigAdmin/ConfigAdminTests.o \
	CorbaConsumer/CorbaConsumerTests.o \
	CorbaNaming/CorbaNamingTests.o \
	CorbaObjectManager/CorbaObjectManagerTests.o \
	CorbaPort/CorbaPortTests.o \
	DataInOutPort/DataInOutPortTests.o \
	DataInPort/DataInPortTests.o \
	DataOutPort/DataOutPortTests.o \
	ECFactory/ECFactoryTests.o \
	ExtTrigExecutionContext/ExtTrigExecutionContextTests.o \
	Factory/FactoryTests.o \
	InPort/InPortTests.o \
	InPortCorbaConsumer/InPortCorbaConsumerTests.o \
	InPortCorbaProvider/InPortCorbaProviderTests.o \
	InPortProvider/InPortProviderTests.o \
	InPortTcpSockConsumer/InPortTcpSockConsumerTests.o \
	InPortTcpSockProvider/InPortTcpSockProviderTests.o \
	Manager/ManagerTests.o \
	ManagerConfig/ManagerConfigTests.o \
	ModuleManager/ModuleManagerTests.o \
	NVUtil/NVUtilTests.o \
	NamingManager/NamingManagerTests.o \
	NullBuffer/NullBufferTests.o \
	NumberingPolicy/NumberingPolicyTests.o \
	ObjectManager/ObjectManagerTests.o \
	OutPort/OutPortTests.o \
	OutPortBase/OutPortBaseTests.o \
	OutPortCorbaConsumer/OutPortCorbaConsumerTests.o \
	OutPortCorbaProvider/OutPortCorbaProviderTests.o \
	OutPortProvider/OutPortProviderTests.o \
	PeriodicExecutionContext/PeriodicExecutionContextTests.o \
	PortAdmin/PortAdminTests.o \
	PortBase/PortBaseTests.o \
	Properties/PropertiesTests.o \
	PublisherFactory/PublisherFactoryTests.o \
	PublisherFlush/PublisherFlushTests.o \
	PublisherNew/PublisherNewTests.o \
	PublisherPeriodic/PublisherPeriodicTests.o \
	RTCUtil/RTCUtilTests.o \
	RTObject/RTObjectTests.o \
	RingBuffer/RingBufferTests.o \
	SdoConfiguration/SdoConfigurationTests.o \
	SdoOrganization/SdoOrganizationTests.o \
	SdoService/SdoServiceTests.o \
	StateMachine/StateMachineTests.o \
	StringUtil/StringUtilTests.o \
	TimeValue/TimeValueTests.o \
	Timer/TimerTests.o


#	$(SDOSERVICE_OBJS)

noinst_PROGRAMS = AllTests

AllTests_SOURCES = TestRunner.cpp
AllTests_LDFLAGS = -L$(libdir)
AllTests_LDADD   = -lcppunit $(TEST_OBJS)


# all
all: do-test

# do tests
do-test:
#	./AllTests --xml alltests.xml --xsl default.xsl

# Cleanup
clean-local:
	rm -f alltests.xml new.conf stored.conf \
	*.o *.Po *.gch *.la \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core \
	Makefile.old \
	*.cc *.hh *.i *.a *.c *.inl

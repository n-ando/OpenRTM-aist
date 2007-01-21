## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for unit test
##
## $Id: Makefile.am,v 1.15 2007-01-21 13:06:23 n-ando Exp $
##
## $Log: not supported by cvs2svn $
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
	CorbaConsumer     \
	CorbaPort         \
	DataInOutPort     \
	DataInPort        \
	DataOutPort       \
	Factory           \
	InPort            \
	ManagerConfig     \
	ModuleManager     \
	NVUtil            \
	NullBuffer        \
	ObjectManager     \
	OutPort           \
	OutPortBase       \
	PeriodicExecutionContext \
	PortAdmin         \
	PortBase          \
	Properties        \
	PublisherFactory  \
	PublisherFlush    \
	PublisherNew      \
	PublisherPeriodic \
	RingBuffer        \
	SdoConfiguration  \
	SdoOrganization   \
	SdoService        \
	StateMachine      \
	StringUtil        \
	.


#	Factory
#	SdoService
#	PortBase
#	PortAdmin
#	RingBuffer
#	InPort

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
	PortBase/RTCSkel.o

RTC_OBJS=                                   \
	SdoOrganization/SdoOrganization.o   \
	SdoConfiguration/SdoConfiguration.o \
	CORBA_SeqUtil/CORBA_SeqUtilTests.o  \
	NVUtil/NVUtil.o                     \
	NVUtil/Properties.o                 \
	NVUtil/StringUtil.o

PROPERTIES_OBJS=Properties/PropertiesTests.o
STRINGUTIL_OBJS=StringUtil/StringUtilTests.o
SDOSERVICE_OBJS=SdoService/SdoServiceTests.o
STATEMACHINE_OBJS=StateMachine/StateMachineTests.o
SDOORGANIZATION_OBJS=SdoOrganization/SdoOrganizationTests.o
SDOCONFIGURATION_OBJS=SdoConfiguration/SdoConfigurationTests.o
CORBA_SEQUTIL_OBJS=CORBA_SeqUtil/SeqUtilTestsSkel.o
PORTBASE_OBJS=PortBase/PortBaseTests.o
PORTADMIN_OBJS=                   \
	PortAdminTests.o          \
	SDOPackageSkel.o          \
	RTCSkel.o

RINGBUFFER_OBJS=RingBuffer/RingBufferTests.o

NVUTIL_OBJS=NVUtil/NVUtilTests.o

CORBACONSUMER_OBJS=               \
	CorbaConsumer/HelloSkel.o \
	CorbaConsumer/CorbaConsumerTests.o


TEST_OBJS = $(COMMON_OBJS)      \
	$(RTC_OBJS)             \
	$(PROPERTIES_OBJS)      \
	$(STRINGUTIL_OBJS)      \
	$(STATEMACHINE_OBJS)    \
	$(SDOORGANIZATION_OBJS) \
	$(SDOCONFIGURATION_OBJS)\
	$(CORBA_SEQUTIL_OBJS)   \
	$(NVUTIL_OBJS)          \
	$(CORBACONSUMER_OBJS)

#	$(SDOSERVICE_OBJS)

noinst_PROGRAMS = AllTests

AllTests_SOURCES = TestRunner.cpp
AllTests_LDFLAGS = -L$(libdir)
AllTests_LDADD   = -lcppunit $(TEST_OBJS)


# all
all: do-test

# do tests
do-test:
	./AllTests --xml alltests.xml --xsl default.xsl

# Cleanup
clean-local:
	rm -f alltests.xml new.conf stored.conf \
	*.o *.Po *.gch *.la \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core \
	Makefile.old \
	*.cc *.hh *.i *.a *.c *.inl

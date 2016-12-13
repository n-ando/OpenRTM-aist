## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for unit test
##
## $Id$
##------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

SUBDIRS = \
	SyncFIFO          \
	SyncLIFO          \
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

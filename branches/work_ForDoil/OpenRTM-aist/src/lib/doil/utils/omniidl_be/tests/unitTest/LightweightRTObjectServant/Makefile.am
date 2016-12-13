# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for LightweightRTObjectServant unit test
# @date   $Date$
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

#
# $Log$
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

#open_rtm_dir = $(top_builddir)/../../../../..
open_rtm_dir = ../../../../../..
#target_srcdir = $(top_builddir)/..
target_srcdir = ../..

AM_CPPFLAGS = -I.
AM_CPPFLAGS += -I$(includedir)
AM_CPPFLAGS += -I$(target_srcdir)
AM_CPPFLAGS += -I$(open_rtm_dir)
AM_CPPFLAGS += -I$(open_rtm_dir)/rtc/corba/idl
AM_CPPFLAGS += -I../
AM_CPPFLAGS += -I../../
AM_CPPFLAGS += -I../../../../../../coil/posix
AM_CPPFLAGS += -I../../../../../../
AM_CPPFLAGS += -I/usr/include/omniORB4/
AM_CPPFLAGS += -I/usr/include/omniORB4/internal/
AM_CPPFLAGS += -I../
AM_CPPFLAGS += -I../stubs

AM_LDFLAGS = -L.
AM_LDFLAGS += -L$(open_rtm_dir)/coil/lib

IDL_SOURCES = $(open_rtm_dir)/rtc/corba/idl/SDOPackage.idl
IDL_SOURCES += $(open_rtm_dir)/rtc/corba/idl/RTC.idl
IDL_SOURCES += $(open_rtm_dir)/rtc/corba/idl/OpenRTM.idl

noinst_PROGRAMS = LightweightRTObjectServantTests

LightweightRTObjectServantTests_SOURCES = ../TestRunner.cpp
LightweightRTObjectServantTests_SOURCES += LightweightRTObjectServantTests.cpp
LightweightRTObjectServantTests_SOURCES += $(IDL_SOURCES:.idl=Stub.cpp)
LightweightRTObjectServantTests_SOURCES += $(open_rtm_dir)/doil/ORBManager.cpp
LightweightRTObjectServantTests_SOURCES += $(open_rtm_dir)/doil/corba/CORBAManager.cpp
LightweightRTObjectServantTests_SOURCES += ../stubs/LightweightRTObjectImpl.cpp 
LightweightRTObjectServantTests_SOURCES += ../stubs/ExecutionContextImpl.cpp 
LightweightRTObjectServantTests_SOURCES += ../stubs/Logger.cpp 

LightweightRTObjectServantTests_LDFLAGS = -L$(libdir)
#LightweightRTObjectServantTests_LDFLAGS += -L../stubs

LightweightRTObjectServantTests_LDADD   = -lomniORB4
LightweightRTObjectServantTests_LDADD  += -lomnithread
LightweightRTObjectServantTests_LDADD  += -lomniDynamic4
LightweightRTObjectServantTests_LDADD  += -lcoil
LightweightRTObjectServantTests_LDADD  += -lcppunit
#LightweightRTObjectServantTests_LDADD  += -lstubs
LightweightRTObjectServantTests_LDADD  += $(target_srcdir)/LightweightRTObjectServant.o
LightweightRTObjectServantTests_LDADD  += $(target_srcdir)/ExecutionContextServant.o
LightweightRTObjectServantTests_LDADD  += $(target_srcdir)/RTCTypeConversion.o
LightweightRTObjectServantTests_LDADD  += $(target_srcdir)/SDOPackageTypeConversion.o
LightweightRTObjectServantTests_LDADD  += $(target_srcdir)/ComponentActionServant.o

# all
all: do-test

# do tests
do-test:
	./LightweightRTObjectServantTests

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

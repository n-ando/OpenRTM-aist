# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for FsmParticipantProxy unit test
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


AM_CPPFLAGS= -I.                                    \
	-I$(includedir)                             \
	-I$(top_builddir)                           \
	-I.                                         \
	-I../                                       \
        -I$(top_builddir)/../../../../              \
        -I../../../../           \
        -I../../../../../           \
        -I../../../../../rtm           \
        -I../../../../../coil/include  \
        -I../../../../../rtc/corba/idl \
        -I../../../../../rtc/corba     \
        -I/usr/include/                             \
        -I/usr/include/omniORB4/

AM_LDFLAGS= -L.                   \
	-L$(top_builddir)         \
        -L$(top_builddir)/../../../../coil/lib


IDL_SOURCES = \
        ../../../../../rtc/corba/idl/SDOPackage.idl \
        ../../../../../rtc/corba/idl/RTC.idl        \
        ../../../../../rtc/corba/idl/OpenRTM.idl 
#        $(top_builddir)/../../../../rtc/corba/idl/SDOPackage.idl \
#        $(top_builddir)/../../../../rtc/corba/idl/RTC.idl        \
#        $(top_builddir)/../../../../rtc/corba/idl/OpenRTM.idl 

noinst_PROGRAMS = FsmParticipantProxyTests

FsmParticipantProxyTests_SOURCES = \
        ../TestRunner.cpp                                       \
	$(IDL_SOURCES:.idl=Skel.cpp)                            \
        ../../../../../doil/corba/CORBAManager.cpp \
        ../../../../../doil/ORBManager.cpp         \
        ../../../../../rtm/NVUtil.cpp              \
        ../RTCTypeConversion.cpp                   \
        ../SDOPackageTypeConversion.cpp            \
        ../LightweightRTObjectProxy.cpp \
        ../FsmParticipantActionProxy.cpp \
        ../ComponentActionProxy.cpp \
        ../FsmParticipantProxy.cpp \
        FsmParticipantProxyTests.cpp

#        $(top_builddir)/../../../../doil/corba/CORBAManager.cpp \
#        $(top_builddir)/../../../../doil/ORBManager.cpp         \
#        $(top_builddir)/../../../../rtm/NVUtil.cpp              \
#        $(top_builddir)/RTCTypeConversion.cpp                   \
#        $(top_builddir)/SDOPackageTypeConversion.cpp            \
#        $(top_builddir)/FsmParticipantProxy.cpp \
#

FsmParticipantProxyTests_LDFLAGS = -L$(libdir)
FsmParticipantProxyTests_LDADD   = \
         -lcppunit                                 \
         -lomniORB4                                \
         -lomnithread                              \
         -lomniDynamic4                            \
         -lcoil 

TEST_SRC = $(FsmParticipantProxyTests_SOURCES)
TEST_H   = 

# all
all: do-test

# do tests
do-test:
	./FsmParticipantProxyTests

# clean-up
clean-local:
	rm -f *.o *.Po *.gch *.la
	rm -f *~ *core
	rm -f *.xml
	rm -f Makefile.old
	rm -f *.vcproj
	rm -rf Release Debug

#------------------------------------------------------------
# vcproj file build rules
#------------------------------------------------------------
win32_builddir = .

vcproj: FsmParticipantProxy_vc8.vcproj FsmParticipantProxy_vc9.vcproj  FsmParticipantProxy_vc10.vcproj

FsmParticipantProxy_vc8.vcproj:
	$(top_builddir)/build/vcprojtool.py vcproj \
		--projectname FsmParticipantProxyTest \
		--type EXE \
		--vcversion "8.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/FsmParticipantProxy_vc8.vcproj \
		--yaml ../coil_test.vcproj.yaml \
		--source $(TEST_SRC)
#		--header $(TEST_H)
	qkc -sm $(win32_builddir)/FsmParticipantProxy_vc8.vcproj

FsmParticipantProxy_vc9.vcproj:
	$(top_builddir)/build/vcprojtool.py vcproj \
		--projectname FsmParticipantProxyTest \
		--type EXE \
		--vcversion "9.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/FsmParticipantProxy_vc9.vcproj \
		--yaml ../coil_test.vcproj.yaml \
		--source $(TEST_SRC)
#		--header $(TEST_H)
	qkc -sm $(win32_builddir)/FsmParticipantProxy_vc9.vcproj

FsmParticipantProxy_vc10.vcproj:
	$(top_builddir)/build/vcprojtool.py vcproj \
		--projectname FsmParticipantProxyTest \
		--type EXE \
		--vcversion "10.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/FsmParticipantProxy_vc10.vcproj \
		--yaml ../coil_test.vcproj.yaml \
		--source $(TEST_SRC)
	qkc -sm $(win32_builddir)/FsmParticipantProxy_vc10.vcproj



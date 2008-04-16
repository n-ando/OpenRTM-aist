## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for libRTCSkel
##
## $Id$
##
## $Log: not supported by cvs2svn $
## Revision 1.9.2.3  2008/02/26 14:18:58  n-ando
## Visual Studio project file generation
##
## Revision 1.9.2.2  2008/01/14 07:58:10  n-ando
## A trivial fix for TAO.
##
## Revision 1.9.2.1  2008/01/13 07:32:05  n-ando
## The improperly specified libRTCSkel source list was fixed.
##
## Revision 1.9  2007/04/13 18:24:09  n-ando
## OpenRTM specific idl definition (OpenRTM.idl) is added.
##
## Revision 1.8  2007/01/21 13:10:26  n-ando
## To avoid omniORB's stub bug on gcc4, stub creation process was changed.
##
## Revision 1.7  2007/01/12 14:40:01  n-ando
## Some trivial fixes.
##
## Revision 1.6  2007/01/09 15:39:10  n-ando
## Makefile now also builds libRTCStub.la.
##
## Revision 1.5  2006/09/11 19:08:18  n-ando
## OMG's SDO and RTC IDL targets are now included.
##
## Revision 1.4  2006/04/04 06:13:11  n-ando
## - New idl (RTCPackage, SDOPackage) was added for OMG's RTC based
##   OpenRTM-aist, which verifies consistency of AIST's RTC PIM and PSM.
##
## Revision 1.3  2005/09/07 05:11:45  n-ando
## RTCService.idl was added for RTComponent's service feature.
##
## Revision 1.2  2005/05/27 07:40:46  n-ando
## - InPort/OutPort interface was changed.
##   InPort/OutPort share SubscriptionProfile structure.
##
## Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
## Public release.
##
##------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@
AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/rtm -L$(top_builddir)/rtm/idl

# Suffix definition of sources and headers of skeletons and stubs 
SUFFIXES = .idl Skel.cpp Stub.cpp Stub.o Skel.o

# RTM idl sources
IDL_SOURCES =             \
	SDOPackage.idl    \
	RTC.idl           \
	OpenRTM.idl       \
	BasicDataType.idl \
	DataPort.idl

SKEL_H   = $(IDL_SOURCES:.idl=Skel.h)
SKEL_CPP = $(IDL_SOURCES:.idl=Skel.cpp)
STUB_H   = $(IDL_SOURCES:.idl=Stub.h)
STUB_CPP = $(IDL_SOURCES:.idl=Stub.cpp)
ALL_SRC =           \
	$(SKEL_H)   \
	$(SKEL_CPP) \
	$(STUB_H)   \
	$(STUB_CPP) \
	$(ORB_SRC)

if ORB_IS_TAO
ORB_SRC = $(TAO_SRC)
endif

if ORB_IS_OMNIORB
ORB_SRC = $(OMNIORB_SRC)
endif

if ORB_IS_MICO
ORB_SRC = $(MICO_SRC)
endif

if ORB_IS_ORBIX
ORB_SRC = $(ORBIX_SRC)
endif

if ORB_IS_ORBACUS
ORB_SRC = $(ORBACUS_SRC)
endif

if ORB_IS_ORBIT2
ORB_SRC = $(ORBIT2_SRC)
OIDLC = $(IDLC) -DORBIT2_IDL
else
OIDLC = echo
endif


TAO_SRC = \
	$(IDL_SOURCES:.idl=S.h) \
	$(IDL_SOURCES:.idl=S.cpp) \
	$(IDL_SOURCES:.idl=S.inl) \
	$(IDL_SOURCES:.idl=S_T.cpp) \
	$(IDL_SOURCES:.idl=S_T.h) \
	$(IDL_SOURCES:.idl=S_T.inl) \
	$(IDL_SOURCES:.idl=C.h) \
	$(IDL_SOURCES:.idl=C.cpp) \
	$(IDL_SOURCES:.idl=C.inl)

OMNIORB_SRC = \
	$(IDL_SOURCES:.idl=.hh) \
	$(IDL_SOURCES:.idl=SK.cc) \
	$(IDL_SOURCES:.idl=DynSK.cc)

MICO_SRC = \
	$(IDL_SOURCES:.idl=.h) \
	$(IDL_SOURCES:.idl=.cc) \
	$(IDL_SOURCES:.idl=_skel.cc)

ORBIX_SRC = \
	$(IDL_SOURCES:.idl=.hh) \
	$(IDL_SOURCES:.idl=S.cc) \
	$(IDL_SOURCES:.idl=C.cc)

ORBACUS_SRC = \
	$(IDL_SOURCES:.idl=.h) \
	$(IDL_SOURCES:.idl=.cpp) \
	$(IDL_SOURCES:.idl=_skel.h) \
	$(IDL_SOURCES:.idl=_skel.cpp)

ORBIT2_SRC = \
	$(IDL_SOURCES:.idl=.h) \
	$(IDL_SOURCES:.idl=-common.c) \
	$(IDL_SOURCES:.idl=-cpp-common.cc) \
	$(IDL_SOURCES:.idl=-cpp-common.h) \
	$(IDL_SOURCES:.idl=-cpp-skels.cc) \
	$(IDL_SOURCES:.idl=-cpp-skels.h) \
	$(IDL_SOURCES:.idl=-cpp-stubs.cc) \
	$(IDL_SOURCES:.idl=-cpp-stubs.h) \
	$(IDL_SOURCES:.idl=-cpp.cc) \
	$(IDL_SOURCES:.idl=-cpp.h)


# Install directory of headers and idl files
rtmheaderdir = $(prefix)/include/rtm
idldir =       $(rtmheaderdir)/idl
rtmskeldir =   $(rtmheaderdir)/idl

idl_DATA = $(IDL_SOURCES)

nodist_rtmskel_HEADERS = $(ALL_SRC)


#------------------------------------------------------------
# Intermediate library : libRTCSkel.a
noinst_LTLIBRARIES = libRTCSkel.la libRTCStub.la

nodist_libRTCSkel_la_SOURCES = $(SKEL_CPP)

libRTCSkel_la_LIBADD = $(LIBS)

nodist_libRTCStub_la_SOURCES = $(STUB_CPP)

libRTCStub_la_LIBADD = $(LIBS)

.idlSkel.cpp:
	$(OIDLC) $<
	$(IDLC) $(IDLFLAGS) $<
	$(top_srcdir)/build/makewrapper.py $<
.idlStub.cpp:
	$(OIDLC) $<
	$(IDLC) $(IDLFLAGS) $<
	$(top_srcdir)/build/makewrapper.py $<
#------------------------------------------------------------

# Extra sources included distribution
EXTRA_DIST = $(IDL_SOURCES) 



#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(ALL_SRC) > skelstub.lst
	echo $(IDL_SOURCES) > idls.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/

vcproj: vc8proj vc9proj

vc8proj: libRTCSkel.vcproj.yaml
	$(top_builddir)/build/vcprojtool.py vcproj \
		--type LIB \
		--vcversion "8.00" \
		--version $(RTM_VERSION) \
		--out $(win32_builddir)/rtm/idl/libRTCSkel_vc8.vcproj \
		--yaml libRTCSkel.vcproj.yaml \
		--source $(SKEL_CPP) $(STUB_CPP) \
		--header $(SKEL_H)   $(STUB_H)
	qkc -sm $(win32_builddir)/rtm/idl/libRTCSkel_vc8.vcproj

vc9proj: libRTCSkel.vcproj.yaml
	$(top_builddir)/build/vcprojtool.py vcproj \
		--type LIB \
		--vcversion "9.00" \
		--version $(RTM_VERSION) \
		--out $(win32_builddir)/rtm/idl/libRTCSkel_vc9.vcproj \
		--yaml libRTCSkel.vcproj.yaml \
		--source $(SKEL_CPP) $(STUB_CPP) \
		--header $(SKEL_H)   $(STUB_H)
	qkc -sm $(win32_builddir)/rtm/idl/libRTCSkel_vc9.vcproj

#------------------------------------------------------------
# for wxs file
#------------------------------------------------------------
wxs:
	$(top_srcdir)/build/makewxs.py flist \
		-c IDLs \
		-o $(win32_builddir)installer/idls.yaml \
		-p ..\\rtm\\idl \
		$(IDL_SORUCES) $(ALL_SRC)

dist-hook: lst vcproj wxs

# Cleanup
clean-local:
	rm -f $(ALL_SRC) *~ *.core *.lst Makefile.old

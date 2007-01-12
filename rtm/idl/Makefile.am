## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for libRTCSkel
##
## $Id: Makefile.am,v 1.7 2007-01-12 14:40:01 n-ando Exp $
##
## $Log: not supported by cvs2svn $
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
IDL_SOURCES =         \
	SDOPackage.idl    \
	RTC.idl           \
	BasicDataType.idl \
	DataPort.idl

if ORB_IS_TAO
SKEL_SOURCES = $(TAO_SOURCES)
endif

if ORB_IS_OMNIORB
SKEL_SOURCES = $(OMNIORB_SOURCES)
endif

if ORB_IS_MICO
SKEL_SOURCES = $(MICO_SOURCES)
endif

if ORB_IS_ORBIX
SKEL_SOURCES = $(ORBIX_SOURCES)
endif

if ORB_IS_ORBACUS
SKEL_SOURCES = $(ORBACUS_SOURCES)
endif

if ORB_IS_ORBIT2
SKEL_SOURCES = $(ORBIT2_SOURCES)
OIDLC = $(IDLC) -DORBIT2_IDL
else
OIDLC = echo
endif


TAO_SOURCES = \
	$(IDL_SOURCES:.idl=S.h) \
	$(IDL_SOURCES:.idl=S.cpp) \
	$(IDL_SOURCES:.idl=S.inl) \
	$(IDL_SOURCES:.idl=S_T.cpp) \
	$(IDL_SOURCES:.idl=S_T.h) \
	$(IDL_SOURCES:.idl=S_T.inl) \
	$(IDL_SOURCES:.idl=C.h) \
	$(IDL_SOURCES:.idl=C.cpp) \
	$(IDL_SOURCES:.idl=C.inl) \
	$(IDL_SOURCES:.idl=C_T.cpp) \
	$(IDL_SOURCES:.idl=C_T.h) \
	$(IDL_SOURCES:.idl=C_T.inl)

OMNIORB_SOURCES = \
	$(IDL_SOURCES:.idl=.hh) \
	$(IDL_SOURCES:.idl=SK.cc) \
	$(IDL_SOURCES:.idl=DynSK.cc)

MICO_SOURCES = \
	$(IDL_SOURCES:.idl=.h) \
	$(IDL_SOURCES:.idl=.cc) \
	$(IDL_SOURCES:.idl=_skel.cc)

ORBIX_SOURCES = \
	$(IDL_SOURCES:.idl=.hh) \
	$(IDL_SOURCES:.idl=S.cc) \
	$(IDL_SOURCES:.idl=C.cc)

ORBACUS_SOURCES = \
	$(IDL_SOURCES:.idl=.h) \
	$(IDL_SOURCES:.idl=.cpp) \
	$(IDL_SOURCES:.idl=_skel.h) \
	$(IDL_SOURCES:.idl=_skel.cpp)

ORBIT2_SOURCES = \
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

nodist_rtmskel_HEADERS =         \
	$(IDL_SOURCES:.idl=Skel.h)   \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	$(IDL_SOURCES:.idl=Stub.h)   \
	$(IDL_SOURCES:.idl=Stub.cpp) \
	$(SKEL_SOURCES)


#------------------------------------------------------------
# Intermediate library : libRTCSkel.a
noinst_LTLIBRARIES = libRTCSkel.la libRTCStub.la

nodist_libRTCSkel_la_SOURCES = $(IDL_SOURCES:.idl=Stub.cpp)

libRTCSkel_la_LIBADD = $(LIBS)

nodist_libRTCStub_la_SOURCES = $(IDL_SOURCES:.idl=Stub.cpp)

libRTCStub_la_LIBADD = $(LIBS)

#BUILT_SOURCES = $(IDL_SOURCES:.idl=Skel.cpp) $(IDL_SOURCES:.idl=Stub.cpp)

.idlSkel.cpp:
	$(top_srcdir)/build/makewrapper.py $<
	$(OIDLC) $<
	$(IDLC) $(IDLFLAGS) $<
.idlStub.cpp:
	$(top_srcdir)/build/makewrapper.py $<
	$(OIDLC) $<
	$(IDLC) $(IDLFLAGS) $<
#------------------------------------------------------------

# Extra sources included distribution
EXTRA_DIST =       \
	$(IDL_SOURCES) 


# Cleanup
clean-local:
	rm -f \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *.core \
	Makefile.old \
	*.cc *.hh *.i *.a *.c *.inl \
	*C.cpp *C.h *S.h *S.cpp *_T.h *_T.cpp \
	*-cpp-common.h *-cpp-skels.h *-cpp-stubs.h *-cpp.h \
	$(IDL_SOURCES:.idl=.h)

## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for libRTCSkel
##
## $Id: Makefile.am,v 1.2 2005-05-27 07:40:46 n-ando Exp $
##
## $Log: not supported by cvs2svn $
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
IDL_SOURCES =       	\
	RTMBase.idl     	\
	RTCDataType.idl 	\
	RTCSubscription.idl   \
	RTCPortBase.idl   	\
	RTCInPort.idl   	\
	RTCOutPort.idl  	\
	RTComponent.idl 	\
	RTCProfile.idl  	\
	RTCBase.idl     	\
	RTCManager.idl

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

TAO_SOURCES = \
	$(IDL_SOURCES:.idl=S.h) \
	$(IDL_SOURCES:.idl=S.cpp) \
	$(IDL_SOURCES:.idl=C.h) \
	$(IDL_SOURCES:.idl=S.cpp)

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

#SKEL_SOURCES = $(TAO_SOURCES) $(OMNIORB_SOURCES) $(MICO_SOURCES) $(ORBIX_SOURCES) $(ORBACUS_SOURCES)



# Install directory of headers and idl files
rtmheaderdir = $(prefix)/include/rtm
idldir =       $(rtmheaderdir)/idl
rtmskeldir =   $(rtmheaderdir)/idl

idl_HEADERS = $(IDL_SOURCES)

nodist_rtmskel_HEADERS =         \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	$(IDL_SOURCES:.idl=Stub.cpp) \
	$(IDL_SOURCES:.idl=Skel.h)   \
	$(IDL_SOURCES:.idl=Stub.h)   \
	$(SKEL_SOURCES)


#------------------------------------------------------------
# Intermediate library : libRTCSkel.a
noinst_LTLIBRARIES = libRTCSkel.la

nodist_libRTCSkel_la_SOURCES = $(IDL_SOURCES:.idl=Skel.cpp)

libRTCSkel_la_LIBADD = $(LIBS)


.idlSkel.cpp:
	$(top_srcdir)/build/makewrapper.py $<
	$(IDLC) $(IDLFLAGS) $<
#------------------------------------------------------------

# Extra sources included distribution
EXTRA_DIST =       \
	$(IDL_SOURCES) 


# Cleanup
clean-local:
	rm -f \
	*Skel.cpp \
	*Skel.h \
	*Stub.cpp \
	*Stub.h \
	*~ \
	*core \
	Makefile.old \
	*.cc \
	*.cpp \
	*.h \
	*.hh \
	*.i \
	*.a

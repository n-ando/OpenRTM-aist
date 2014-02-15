# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for unit test stubs
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

open_rtm_dir = $(top_builddir)/../../../../..
target_srcdir = $(top_builddir)/..

AM_CPPFLAGS = -I.
AM_CPPFLAGS += -I$(includedir)
AM_CPPFLAGS += -I$(target_srcdir)
AM_CPPFLAGS += -I$(open_rtm_dir)
AM_CPPFLAGS += -I$(open_rtm_dir)/rtc/corba/idl
AM_CPPFLAGS += -I../../../../../../
AM_CPPFLAGS += -I../../

AM_LDFLAGS = -L.
AM_LDFLAGS += -L$(open_rtm_dir)/coil/lib


lib_LIBRARIES = libstubs.a
libstubs_a_SOURCES = ConfigurationImpl.cpp
libstubs_a_SOURCES += Logger.cpp
libstubs_a_SOURCES += ComponentActionImpl.cpp
libstubs_a_SOURCES += DataFlowComponentActionImpl.cpp
libstubs_a_SOURCES += LightweightRTObjectImpl.cpp
libstubs_a_SOURCES += DataFlowComponentImpl.cpp
libstubs_a_SOURCES += ExecutionContextServiceImpl.cpp
libstubs_a_SOURCES += FsmObjectImpl.cpp
libstubs_a_SOURCES += FsmParticipantActionImpl.cpp
libstubs_a_SOURCES += FsmServiceImpl.cpp
libstubs_a_SOURCES += ModeImpl.cpp
libstubs_a_SOURCES += ModeCapableImpl.cpp
libstubs_a_SOURCES += MultiModeComponentActionImpl.cpp
libstubs_a_SOURCES += OrganizationImpl.cpp
libstubs_a_SOURCES += SDOSystemElementImpl.cpp
libstubs_a_SOURCES += SDOImpl.cpp
libstubs_a_SOURCES += RTObjectImpl.cpp
libstubs_a_SOURCES += PortServiceImpl.cpp
stubsdir = .

noinst_LIBRARIES = libstubs.a


# all
all: $(StubsLib)

# Stubs lib
$(StubLib):
	$(AR) $(ARFLAGS) $(StubsLib) $(stubs_SOURCES:.cpp=.o)

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl


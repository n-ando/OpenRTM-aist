## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for MyServiceProvider/MyServiceConsumer components
##
## $Id: Makefile.am,v 1.5.2.1 2007-07-22 14:26:37 n-ando Exp $
##
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/rtm -L$(top_builddir)/rtm/idl

SUFFIXES = .o .so .idl Skel.cpp Stub.cpp Stub.o Skel.o

WRAPPER  = $(top_builddir)/utils/rtm-skelwrapper/rtm-skelwrapper
WRAPPER_FLAGS = --include-dir="" --skel-suffix=Skel --stub-suffix=Stub

.idlSkel.cpp:
	$(IDLC) $(IDLFLAGS) MyService.idl
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=MyService.idl

.idlStub.cpp:
	$(IDLC) $(IDLFLAGS) MyService.idl
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=MyService.idl

IDL_SOURCES = MyService.idl

SKEL_OBJ = MyServiceSkel.o
STUB_OBJ = MyServiceStub.o
IMPL_OBJ = MyServiceSVC_impl.o

noinst_PROGRAMS = MyServiceConsumerComp MyServiceProviderComp

nodist_MyServiceProviderComp_SOURCES = \
	$(IDL_SOURCES:.idl=Skel.cpp)   \
	MyServiceSVC_impl.cpp          \
	MyServiceProvider.cpp          \
	MyServiceProviderComp.cpp
MyServiceProviderComp_LDFLAGS = -L$(top_builddir)/rtm
MyServiceProviderComp_LDADD = -lRTC

nodist_MyServiceConsumerComp_SOURCES = \
	$(IDL_SOURCES:.idl=Stub.cpp)   \
	MyServiceConsumer.cpp          \
	MyServiceConsumerComp.cpp
MyServiceConsumerComp_LDFLAGS = -L$(top_builddir)/rtm
MyServiceConsumerComp_LDADD = -lRTC

EXTRA_DIST =                       \
	$(IDL_SOURCES)             \
	Makefile.MyServiceProvider \
	Makefile.MyServiceConsumer \
	README.MyServiceProvider   \
	README.MyServiceConsumer   \
	MyServiceSVC_impl.cpp      \
	MyServiceSVC_impl.h        \
	MyServiceProvider.h        \
	MyServiceProvider.cpp      \
	MyServiceProviderComp.cpp  \
	MyServiceConsumer.h        \
	MyServiceConsumer.cpp      \
	MyServiceConsumerComp.cpp  \
	gen.sh                     \
	rtc.conf

clean_objs:
	rm -f $(OBJS) SimpleService.so SimpleServiceComp

clean_skelstub:
	rm -f *Skel.h *Skel.cpp
	rm -f *Stub.h *Stub.cpp

clean-local: clean_objs clean_skelstub
	rm -f *.bak *.rpo *.sym lib*.*_pure_* Makefile.old *core *~ *loT

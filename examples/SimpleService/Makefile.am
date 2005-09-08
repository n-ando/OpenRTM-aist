## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for ConsoleIn/ConsoleOut components
##
## $Id: Makefile.am,v 1.1 2005-09-08 13:03:31 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.1.1.1  2005/05/12 09:06:20  n-ando
## Public release.
##
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@ -I$(top_srcdir)/rtm/idl
LIBS = @LIBS@

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/rtm -L$(top_builddir)/rtm/idl

SUFFIXES = .so

SHFLAGS  = -shared
WRAPPER  = $(top_builddir)/utils/rtm-skelwrapper/rtm-skelwrapper
WRAPPER_FLAGS = --include-dir="" --skel-suffix=Skel --stub-suffix=Stub

SKEL_OBJ = MyServiceSkel.o
STUB_OBJ = MyServiceStub.o
IMPL_OBJ = MyServiceSVC_impl.o
OBJS     = SimpleService.o $(SKEL_OBJ) $(IMPL_OBJ)

noinst_PROGRAMS = SimpleServiceComp
SimpleServiceComp_SOURCES = SimpleServiceComp.cpp 
SimpleServiceComp_LDADD = $(top_builddir)/rtm/libRTC.la $(OBJS)
SimpleServiceComp_LDFLAGS = -L$(top_builddir)/rtm/.libs


.o.so:
	rm -f $@
	$(CXX) $(SHFLAGS) -o $@ $(OBJS) $(AM_LDFLAGS)

clean_objs:
	rm -f $(OBJS) SimpleService.so SimpleServiceComp

clean_skelstub:
	rm -f *Skel.h *Skel.cpp
	rm -f *Stub.h *Stub.cpp

clean-local: clean_objs clean_skelstub
	rm -f *.bak *.rpo *.sym lib*.*_pure_* Makefile.old *core *~ *loT


MyServiceSkel.cpp : MyService.idl
	$(IDLC) $(IDLFLAGS) MyService.idl
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=MyService.idl
MyServiceSkel.h : MyService.idl
	$(IDLC) $(IDLFLAGS) MyService.idl
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=MyService.idl
MyServiceStub.cpp : MyService.idl
	$(IDLC) $(IDLFLAGS) MyService.idl
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=MyService.idl
MyServiceStub.h : MyService.idl
	$(IDLC) $(IDLFLAGS) MyService.idl
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=MyService.idl
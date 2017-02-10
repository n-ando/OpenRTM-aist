## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for ART-Linux execution context
##
## $Id: Makefile.am 1429 2009-07-06 08:28:25Z hakuta $
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

SUBDIRS = . example

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@ -I../$(top_srcdir)/src/lib/rtm/idl
LIBS = @LIBS@

AM_CPPFLAGS=-I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/coil/include -I$(top_srcdir)/src/lib/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/src/lib/rtm -L$(top_builddir)/src/lib/rtm/idl

#------------------------------------------------------------
# Some rules for IDL compile
#------------------------------------------------------------
SUFFIXES = .o .so .idl Skel.cpp Stub.cpp Stub.o Skel.o

WRAPPER  = $(top_builddir)/utils/rtm-skelwrapper/rtm-skelwrapper
WRAPPER_FLAGS = --include-dir="" --skel-suffix=Skel --stub-suffix=Stub

idl-stamp: $(IDL_SOURCES)
	@touch idl-stamp
	mkdir -p idl
	(cd $(top_builddir)/utils/rtm-config; $(MAKE))
	@for f in $(IDL_SOURCES) ; do \
		cp $$f idl/ ; \
		(cd idl ; $(IDLC) $(IDLFLAGS) $$f ; cd ..) ; \
		PYTHONPATH="$(top_srcdir)/build:$(PYTHONPATH)" \
		PATH="$(top_srcdir)/utils/rtm-config:$(PATH)"  \
		$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=$$f --include-dir=idl/ ; \
	done ;

$(ALL_SRC): idl-stamp
	@if test -f $@ ; then \
		touch $@ ; \
	else \
		rm -f idl-stamp ; \
		$(MAKE) $(AM_MAKEFLAGS) idl-stamp ; \
	fi ;

#------------------------------------------------------------
# Source list
#------------------------------------------------------------
IDL_SOURCES = LogicalTimeTriggeredEC.idl

OBSERVER_DIST_SRC   = LogicalTimeTriggeredEC.cpp
OBSERVER_NODIST_SRC = $(IDL_SOURCES:.idl=Stub.cpp) $(IDL_SOURCES:.idl=Skel.cpp)
OBSERVER_NDWIN_SRC  = $(IDL_SOURCES:.idl=Stub.cpp) $(IDL_SOURCES:.idl=Skel.cpp)
OBSERVER_SRC        = $(OBSERVER_DIST_SRC) $(OBSERVER_NODIST_SRC)
OBSERVER_WIN_SRC    = $(OBSERVER_DIST_SRC) $(OBSERVER_NDWIN_SRC)

OBSERVER_DIST_H     = $(OBSERVER_DIST_SRC:.cpp=.h)
OBSERVER_NODIST_H   = $(OBSERVER_NODIST_SRC:.cpp=.h)
OBSERVER_NDWIN_H    = $(OBSERVER_NDWIN_SRC:.cpp=.h)
OBSERVER_H          = $(OBSERVER_DIST_H) $(OBSERVER_NODIST_H)
OBSERVER_WIN_H      = $(OBSERVER_DIST_H) $(OBSERVER_NDWIN_H)

#------------------------------------------------------------
# Object list
#------------------------------------------------------------
OBSERVER_OBJ=$(OBSERVER_DIST_SRC:.cpp=.o)

#------------------------------------------------------------
# Targets
#------------------------------------------------------------
# Targets directories
socompdir = $(rtm_ecdir)

# Loadable Module
noinst_LTLIBRARIES = libLogicalTimeTriggeredECSkel.la libLogicalTimeTriggeredECStub.la 
nodist_libLogicalTimeTriggeredECSkel_la_SOURCES = $(IDL_SOURCES:.idl=Skel.cpp)
nodist_libLogicalTimeTriggeredECStub_la_SOURCES = $(IDL_SOURCES:.idl=Stub.cpp)

socomp_LTLIBRARIES = LogicalTimeTriggeredEC.la

dist_LogicalTimeTriggeredEC_la_SOURCES = \
	$(OBSERVER_DIST_SRC) $(OBSERVER_DIST_H)
LogicalTimeTriggeredEC_la_LDFLAGS = -module
LogicalTimeTriggeredEC_la_DEPENDENCIES = libLogicalTimeTriggeredECSkel.la
LogicalTimeTriggeredEC_la_LIBADD  =                 \
	libLogicalTimeTriggeredECStub.la            \
	$(top_builddir)/src/lib/rtm/libRTC.la       \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

#------------------------------------------------------------
# Extra distributed files
#------------------------------------------------------------
EXTRA_DIST = $(IDL_SOURCES)

ALL_SRC = $(OBSERVER_SRC)

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(ALL_SRC) > src.lst
	echo $(EXTRA_DIST) > other.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/ext/ec/logical_time
PROJNAME=LogicalTimeTriggeredEC

vcproj: vc9proj vcxproj

vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "$(PROJNAME)"                     \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/$(PROJNAME)Dll_vc9.vcproj  \
		--yaml $(top_builddir)/examples/rtcdll.vcproj.yaml \
		--source $(OBSERVER_WIN_SRC)                        \
		--header $(OBSERVER_WIN_H)

vcxproj:
	for ver in $(VC_VERSION); do \
		$(top_builddir)/build/vcxprojtool.py vcxproj              \
			--type DLL                                        \
			--vcversion "$${ver}.00"                               \
			--projectname "$(PROJNAME)"                       \
			--version $(RTM_VERSION)                          \
			--out $(win32_builddir)/$(PROJNAME)Dll_vc$${ver}.vcxproj \
			--yaml $(top_builddir)/examples/rtcdll.vcproj.yaml  \
			--source $(OBSERVER_WIN_SRC)                          \
			--header $(OBSERVER_WIN_H) ; \
	done

dist-hook: lst vcproj


clean_objs:
	rm -f $(OBJS)

clean_skelstub:
	rm -f *Skel.h *Skel.cpp
	rm -f *Stub.h *Stub.cpp
	rm -rf idl
	rm -f *.hh *SK.cc
	rm -f *S.cpp *S.h *_T.cpp *_T.h *.inl

clean-local: clean_objs clean_skelstub
	rm -f *.bak *.rpo *.sym lib*.*_pure_*
	rm -f *.lst *core *~ *loT *.log
	rm -f Makefile.old
	rm -f idl-stamp

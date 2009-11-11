## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for AutoTestOut components
##
## $Id: Makefile.am 1135 2009-01-19 16:11:02Z n-ando $
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS=-I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/coil/include -I$(top_srcdir)/src/lib/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/src/lib/rtm -L$(top_builddir)/src/lib/rtm/idl

#------------------------------------------------------------
# Some rules for IDL compile
#------------------------------------------------------------
SUFFIXES = .o .so .idl Stub.cpp Stub.o

WRAPPER  = $(top_builddir)/utils/rtm-skelwrapper/rtm-skelwrapper
WRAPPER_FLAGS = --include-dir="" --stub-suffix=Stub

.idlStub.cpp:
	$(IDLC) $(IDLFLAGS) $<
	PYTHONPATH=$(PYTHONPATH):$(top_srcdir)/build \
	PATH=$(top_srcdir)/utils/rtm-config:$(PATH)  \
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=$<

#------------------------------------------------------------
# Source list
#------------------------------------------------------------
IDL_SOURCES = AutoTestService.idl

CONSUMER_DIST_SRC   = AutoTestOut.cpp
CONSUMER_NODIST_SRC = $(IDL_SOURCES:.idl=Stub.cpp)
CONSUMER_SRC        = $(CONSUMER_DIST_SRC) $(CONSUMER_NODIST_SRC)

CONSUMER_DIST_H     = $(CONSUMER_DIST_SRC:.cpp=.h)
CONSUMER_NODIST_H   = $(CONSUMER_NODIST_SRC:.cpp=.h)
CONSUMER_H          = $(CONSUMER_DIST_H) $(CONSUMER_NODIST_H)
CONSUMER_COMP_SRC   = $(CONSUMER_SRC) AutoTestOutComp.cpp

#------------------------------------------------------------
# Object list
#------------------------------------------------------------
CONSUMER_OBJ=$(CONSUMER_DIST_SRC:.cpp=.o)

#------------------------------------------------------------
# Targets
#------------------------------------------------------------
# Targets directories
exampledir = $(pkgdatadir)/examples
socompdir  = $(exampledir)/rtcs
sourcedir  = $(exampledir)/src/AutoTestOut

# Loadable RTCs
noinst_LTLIBRARIES = libAutoTestServiceStub.la 
nodist_libAutoTestServiceStub_la_SOURCES = $(CONSUMER_NODIST_SRC)

socomp_LTLIBRARIES = AutoTestOut.la

dist_AutoTestOut_la_SOURCES = $(CONSUMER_DIST_SRC) $(CONSUMER_DIST_H)
AutoTestOut_la_LDFLAGS = -module
AutoTestOut_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.libs
AutoTestOut_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la -lAutoTestServiceStub

# Standalone RTCs
example_PROGRAMS = AutoTestOutComp
AutoTestOutComp_SOURCES = AutoTestOutComp.cpp
AutoTestOutComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
AutoTestOutComp_LDADD   = .libs/AutoTestOut.a \
	$(top_builddir)/src/lib/rtm/libRTC.la


# Example sources
source_DATA = $(ALL_SRC) $(EXTRA_DIST)

#------------------------------------------------------------
# Extra distributed files
#------------------------------------------------------------
EXTRA_DIST =                       \
	$(IDL_SOURCES)             \
	Makefile.AutoTestOut \
	README.AutoTestOut   \
	rtc.conf

ALL_SRC =                    \
	$(IDL_SOURCES)       \
        $(CONSUMER_COMP_SRC)

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(ALL_SRC) > src.lst
	echo $(EXTRA_DIST) > other.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/examples/AutoTestOut

vcproj: vc8proj vc9proj

vc8proj: 
	$(top_builddir)/build/vcprojtool.py vcproj                   \
		--type EXE                                           \
		--vcversion "8.00"                                   \
		--projectname "AutoTestOutComp"                \
		--version $(RTM_VERSION)                             \
		--out $(win32_builddir)/AutoTestOut_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                            \
		--source $(CONSUMER_COMP_SRC)                        \
		--header $(CONSUMER_H)
	qkc -sm $(win32_builddir)/AutoTestOut_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj                      \
		--type DLL                                              \
		--vcversion "8.00"                                      \
		--projectname "AutoTestOut"                       \
		--version $(RTM_VERSION)                                \
		--out $(win32_builddir)/AutoTestOutDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                            \
		--source $(CONSUMER_COMP_SRC)                           \
		--header $(CONSUMER_H)
	qkc -sm $(win32_builddir)/AutoTestOutDll_vc8.vcproj

vc9proj: 
	$(top_builddir)/build/vcprojtool.py vcproj                   \
		--type EXE                                           \
		--vcversion "9.00"                                   \
		--projectname "AutoTestOutComp"                \
		--version $(RTM_VERSION)                             \
		--out $(win32_builddir)/AutoTestOut_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                            \
		--source $(CONSUMER_COMP_SRC)                        \
		--header $(CONSUMER_H)
	qkc -sm $(win32_builddir)/AutoTestOut_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj                      \
		--type DLL                                              \
		--vcversion "9.00"                                      \
		--projectname "AutoTestOut"                       \
		--version $(RTM_VERSION)                                \
		--out $(win32_builddir)/AutoTestOutDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                            \
		--source $(CONSUMER_COMP_SRC)                           \
		--header $(CONSUMER_H)
	qkc -sm $(win32_builddir)/AutoTestOutDll_vc9.vcproj

dist-hook: lst vcproj


clean_objs:
	rm -f $(OBJS)

clean_skelstub:
	rm -f *Skel.h *Skel.cpp
	rm -f *Stub.h *Stub.cpp
	rm -f *.hh *SK.cc
	rm -f *C.cpp *C.h *S.cpp *S.h *_T.cpp *_T.h *.inl

clean-local: clean_objs clean_skelstub
	rm -f \
	*.bak *.rpo *.sym lib*.*_pure_* *.lst \
	Makefile.old *core *~ *loT

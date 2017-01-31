## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for ExtendedFsmService implementation
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@ -I../$(top_srcdir)/src/lib/rtm/idl
LIBS = @LIBS@

AM_CPPFLAGS=-I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/coil/include -I$(top_srcdir)/src/lib/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/src/lib/rtm -L$(top_builddir)/src/lib/rtm/idl

#------------------------------------------------------------
# Source list
#------------------------------------------------------------
EXT_FSM_SVC_DIST_SRC   = ExtendedFsmServiceProvider.cpp
EXT_FSM_SVC_SRC        = $(EXT_FSM_SVC_DIST_SRC)
EXT_FSM_SVC_WIN_SRC    = $(EXT_FSM_SVC_DIST_SRC)

EXT_FSM_SVC_DIST_H     = $(EXT_FSM_SVC_DIST_SRC:.cpp=.h)
EXT_FSM_SVC_H          = $(EXT_FSM_SVC_DIST_H)
EXT_FSM_SVC_WIN_H      = $(EXT_FSM_SVC_DIST_H)

#------------------------------------------------------------
# Object list
#------------------------------------------------------------
EXT_FSM_SVC_OBJ=$(EXT_FSM_SVC_DIST_SRC:.cpp=.o)

#------------------------------------------------------------
# Targets
#------------------------------------------------------------
# Targets directories
socompdir = $(rtm_sdodir)

# Loadable Module

socomp_LTLIBRARIES = ExtendedFsmServiceProvider.la

dist_ExtendedFsmServiceProvider_la_SOURCES = \
	$(EXT_FSM_SVC_DIST_SRC) $(EXT_FSM_SVC_DIST_H)
ExtendedFsmServiceProvider_la_LDFLAGS = -module
ExtendedFsmServiceProvider_la_LIBADD  =                \
	$(top_builddir)/src/lib/rtm/libRTC.la         \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

#------------------------------------------------------------
# Extra distributed files
#------------------------------------------------------------
ALL_SRC = $(EXT_FSM_SVC_SRC)

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(ALL_SRC) > src.lst
	echo $(EXTRA_DIST) > other.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/ext/sdo/extended_fsm
PROJNAME=ExtendedFsmServiceProvider

vcproj: vc8proj vc9proj vc10proj vc11proj vc12proj vc14proj

vc8proj: 
	$(top_builddir)/build/vcprojtool.py vcproj             \
		--type DLL                                         \
		--vcversion "8.00"                                 \
		--projectname "$(PROJNAME)"                        \
		--version $(RTM_VERSION)                           \
		--out $(win32_builddir)/$(PROJNAME)Dll_vc8.vcproj  \
		--yaml $(top_builddir)/examples/rtcdll.vcproj.yaml \
		--source $(EXT_FSM_SVC_WIN_SRC)                    \
		--header $(EXT_FSM_SVC_WIN_H)
	qkc -O- -sm $(win32_builddir)/$(PROJNAME)Dll_vc8.vcproj

vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj             \
		--type DLL                                         \
		--vcversion "9.00"                                 \
		--projectname "$(PROJNAME)"                        \
		--version $(RTM_VERSION)                           \
		--out $(win32_builddir)/$(PROJNAME)Dll_vc9.vcproj  \
		--yaml $(top_builddir)/examples/rtcdll.vcproj.yaml \
		--source $(EXT_FSM_SVC_WIN_SRC)                    \
		--header $(EXT_FSM_SVC_WIN_H)
	qkc -O- -sm $(win32_builddir)/$(PROJNAME)Dll_vc9.vcproj

vc10proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj            \
		--type DLL                                          \
		--vcversion "10.00"                                 \
		--projectname "$(PROJNAME)"                         \
		--version $(RTM_VERSION)                            \
		--out $(win32_builddir)/$(PROJNAME)Dll_vc10.vcxproj \
		--yaml $(top_builddir)/examples/rtcdll.vcproj.yaml  \
		--source $(EXT_FSM_SVC_WIN_SRC)                     \
		--header $(EXT_FSM_SVC_WIN_H)
	qkc -O- -sm $(win32_builddir)/$(PROJNAME)Dll_vc10.vcxproj

vc11proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj            \
		--type DLL                                          \
		--vcversion "11.00"                                 \
		--projectname "$(PROJNAME)"                         \
		--version $(RTM_VERSION)                            \
		--out $(win32_builddir)/$(PROJNAME)Dll_vc11.vcxproj \
		--yaml $(top_builddir)/examples/rtcdll.vcproj.yaml  \
		--source $(EXT_FSM_SVC_WIN_SRC)                     \
		--header $(EXT_FSM_SVC_WIN_H)
	qkc -O- -sm $(win32_builddir)/$(PROJNAME)Dll_vc11.vcxproj

vc12proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj            \
		--type DLL                                          \
		--vcversion "12.00"                                 \
		--projectname "$(PROJNAME)"                         \
		--version $(RTM_VERSION)                            \
		--out $(win32_builddir)/$(PROJNAME)Dll_vc12.vcxproj \
		--yaml $(top_builddir)/examples/rtcdll.vcproj.yaml  \
		--source $(EXT_FSM_SVC_WIN_SRC)                     \
		--header $(EXT_FSM_SVC_WIN_H)
	qkc -O- -sm $(win32_builddir)/$(PROJNAME)Dll_vc12.vcxproj

vc14proj:
	$(top_builddir)/build/vcxprojtool.py vcxproj            \
		--type DLL                                          \
		--vcversion "14.00"                                 \
		--projectname "$(PROJNAME)"                         \
		--version $(RTM_VERSION)                            \
		--out $(win32_builddir)/$(PROJNAME)Dll_vc14.vcxproj \
		--yaml $(top_builddir)/examples/rtcdll.vcproj.yaml  \
		--source $(EXT_FSM_SVC_WIN_SRC)                     \
		--header $(EXT_FSM_SVC_WIN_H)
	qkc -O- -sm $(win32_builddir)/$(PROJNAME)Dll_vc14.vcxproj
	
dist-hook: lst vcproj


clean_objs:
	rm -f $(OBJS)

clean_skelstub:
	rm -f *Skel.h *Skel.cpp
	rm -f *Stub.h *Stub.cpp
	rm -rf idl
	rm -f *.hh *SK.cc
	rm -f *C.cpp *C.h *S.cpp *S.h *_T.cpp *_T.h *.inl

clean-local: clean_objs clean_skelstub
	rm -f *.bak *.rpo *.sym lib*.*_pure_*
	rm -f *.lst *core *~ *loT *.log
	rm -f Makefile.old
	rm -rf idl-stamp

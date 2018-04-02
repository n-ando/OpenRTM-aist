## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for RT preempt linux kternel execution context
##
## $Id$
##---------------------------------------------------------------------------

AM_CPPFLAGS=-I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/coil/include -I$(top_srcdir)/src/lib/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/src/lib/rtm -L$(top_builddir)/src/lib/rtm/idl

#------------------------------------------------------------
# Targets
#------------------------------------------------------------
# Targets directories
moduledir = $(rtm_ecdir)

module_LTLIBRARIES = FileNameservice.la

FileNameservice_la_SOURCES = FileNameservice.cpp FileNameservice.h
FileNameservice_la_LDFLAGS = -module -shared -lboost_system -lboost_filesystem
FileNameservice_la_FLAGS   =  -L$(top_builddir)/src/lib/rtm/.lib
FileNameservice_la_LIBADD  = \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la 


FILENAMESERVICE_DIST_SRC = FileNameservice.cpp
FILENAMESERVICE_SRC = $(FILENAMESERVICE_DIST_SRC)

FILENAMESERVICE_DIST_H = $(FILENAMESERVICE_DIST_SRC:.cpp=.h)
FILENAMESERVICE_H = $(FILENAMESERVICE_DIST_H)


#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/ext/local_service/nameservice_file
PROJNAME=FileNameservice

vcproj: vc9proj vcxproj

vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "$(PROJNAME)"                     \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/$(PROJNAME)Dll_vc9.vcproj  \
		--yaml $(top_builddir)/examples/rtcdll.vcproj.yaml \
		--source $(FILENAMESERVICE_SRC)                        \
		--header $(FILENAMESERVICE_H)

vcxproj:
	for ver in $(VC_VERSION); do \
		$(top_builddir)/build/vcxprojtool.py vcxproj              \
			--type DLL                                        \
			--vcversion "$${ver}.00"                               \
			--projectname "$(PROJNAME)"                       \
			--version $(RTM_VERSION)                          \
			--out $(win32_builddir)/$(PROJNAME)Dll_vc$${ver}.vcxproj \
			--yaml $(top_builddir)/examples/rtcdll.vcproj.yaml  \
			--source $(FILENAMESERVICE_SRC)                          \
			--header $(FILENAMESERVICE_H) ; \
	done

#dist-hook: vcproj

clean-local:
	rm -rf *~ *.o *.so

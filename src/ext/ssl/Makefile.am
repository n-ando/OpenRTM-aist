## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for external libraries
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS= \
	-I$(top_srcdir)/src/lib \
	-I$(top_srcdir)/src/lib/coil/include \
	-I$(top_srcdir)/src/lib/rtm/idl

AM_LDFLAGS= \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/rtm \
	-L$(top_builddir)/src/lib/rtm/idl


SSL_SRC        = SSLTransport.cpp
SSL_WIN_SRC    = SSLTransport.cpp

SSL_H          = 
SSL_WIN_H      = 

#------------------------------------------------------------
# Targets
#------------------------------------------------------------
# Targets directories
socompdir = $(rtm_ssldir)

socomp_LTLIBRARIES = SSLTransport.la



SSLTransport_la_SOURCES  = $(SSL_SRC)
SSLTransport_la_LDFLAGS  = -module -shared
SSLTransport_la_LIBADD   = \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

clean-local:
	rm -rf *~ *.o *.so



#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(ALL_SRC) > src.lst
	echo $(EXTRA_DIST) > other.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/ext/ssl
PROJNAME=SSLTransport

vcproj: vc9proj vcxproj

vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
	        --vcversion "9.00"                              \
	        --projectname "$(PROJNAME)"                     \
	        --version $(RTM_VERSION)                        \
	        --out $(win32_builddir)/$(PROJNAME)Dll_vc9.vcproj  \
	        --yaml $(top_builddir)/examples/rtcdll.vcproj.yaml \
	        --source $(SSL_WIN_SRC) ;                       \
	qkc -O- -sm $(win32_builddir)/$(PROJNAME)Dll_vc9.vcproj

vcxproj:
	for ver in $(VC_VERSION); do \
                $(top_builddir)/build/vcxprojtool.py vcxproj              \
	                --type DLL                                        \
                        --vcversion "$${ver}.00"                               \
                        --projectname "$(PROJNAME)"                       \
                        --version $(RTM_VERSION)                          \
                        --out $(win32_builddir)/$(PROJNAME)Dll_vc$${ver}.vcxproj \
                        --yaml $(top_builddir)/examples/rtcdll.vcproj.yaml  \
                        --source $(SSL_WIN_SRC) ;                         \
		qkc -O- -sm $(win32_builddir)/$(PROJNAME)Dll_vc$${ver}.vcxproj ; \
        done

dist-hook: lst vcproj


clean_objs:
	rm -f $(OBJS)


clean-local: clean_objs
	rm -f *.bak *.rpo *.sym lib*.*_pure_*
	rm -f *.lst *core *~ *loT *.log
	rm -f Makefile.old 

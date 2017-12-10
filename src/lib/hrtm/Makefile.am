## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for libHRTM
##
## $Id: Makefile.am 2720 2016-05-20 10:35:25Z n-ando $
##------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

SUBDIRS = idls

AM_CPPFLAGS = \
	-I$(top_srcdir)/src/lib              \
	-I$(top_srcdir)/src/lib/coil/include \
	-I$(top_srcdir)/src/lib/rtm          \
	-I$(top_srcdir)/src/lib/rtm/idl      \
	-I$(top_srcdir)/src/lib/hrtm
AM_LDFLAGS = \
	-L$(top_builddir)                    \
	-L$(top_builddir)/src/lib/rtm        \
	-L$(top_builddir)/src/lib/rtm/idl    \
	-L$(top_builddir)/src/lib/coil/lib

# libHRTM.so, libHRTM.a library build entry
lib_LTLIBRARIES = libHRTM.la

# sources of libHRTM.la
HRTM_SRC = \
	component_manager.cpp             \
	data_flow_component.cpp           \
	logger.cpp                        \
	properties.cpp                    \
	statechart.cpp

libHRTM_la_SOURCES = $(HRTM_SRC)

libHRTM_la_LIBADD = \
	$(top_builddir)/src/lib/coil/lib/libcoil.la   \
	$(top_builddir)/src/lib/rtm/idl/libRTCSkel.la \
	$(top_builddir)/src/lib/rtm/libRTC.la

libHRTM_la_LDFLAGS =                  \
	-no-undefined                     \
	-L$(top_builddir)/src/lib/rtm/idl \
	-L$(top_builddir)/src/lib/rtm     \
	-release $(PACKAGE_VERSION)


hrtmheaderdir = $(rtm_includedir)/hrtm

hrtmheader_HEADERS = \
	$(libHRTM_la_SOURCES:.cpp=.h)    \
	defs.h                           \
	in_port.h                        \
	out_port.h                       \
	utils.h                          \
	version.h


#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(HRTM_SRC) > src.lst
	echo $(hrtmheader_HEADERS) > header.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir = $(top_builddir)/win32/OpenRTM-aist/

vcproj: vc8proj vc9proj vc10proj vc11proj vc12proj vc14proj

vc8proj: libHRTM.vcproj.yaml
	$(top_builddir)/build/vcprojtool.py vcproj \
		--type DLL \
		--vcversion "8.00" \
		--version $(RTM_VERSION) \
		--out $(win32_builddir)/hrtm/libHRTM_vc8.vcproj \
		--yaml libHRTM.vcproj.yaml \
		--source $(HRTM_SRC) \
		--header $(hrtmheader_HEADERS)
	qkc -O- -sm $(win32_builddir)/hrtm/libHRTM_vc8.vcproj

vc9proj: libHRTM.vcproj.yaml
	$(top_builddir)/build/vcprojtool.py vcproj \
		--type DLL \
		--vcversion "9.00" \
		--version $(RTM_VERSION) \
		--out $(win32_builddir)/hrtm/libHRTM_vc9.vcproj \
		--yaml libHRTM.vcproj.yaml \
		--source $(HRTM_SRC) \
		--header $(hrtmheader_HEADERS)
	qkc -O- -sm $(win32_builddir)/hrtm/libHRTM_vc9.vcproj

vc10proj: libHRTM.vcproj.yaml
	$(top_builddir)/build/vcxprojtool.py vcxproj \
		--type DLL \
		--vcversion "10.00" \
		--version $(RTM_VERSION) \
		--out $(win32_builddir)/hrtm/libHRTM_vc10.vcxproj \
		--yaml libHRTM.vcproj.yaml \
		--source $(HRTM_SRC) \
		--header $(hrtmheader_HEADERS)
	qkc -O- -sm $(win32_builddir)/hrtm/libHRTM_vc10.vcxproj

vc11proj: libHRTM.vcproj.yaml
	$(top_builddir)/build/vcxprojtool.py vcxproj \
		--type DLL \
		--vcversion "11.00" \
		--version $(RTM_VERSION) \
		--out $(win32_builddir)/hrtm/libHRTM_vc11.vcxproj \
		--yaml libHRTM.vcproj.yaml \
		--source $(HRTM_SRC) \
		--header $(hrtmheader_HEADERS)
	qkc -O- -sm $(win32_builddir)/hrtm/libHRTM_vc11.vcxproj

vc12proj: libHRTM.vcproj.yaml
	$(top_builddir)/build/vcxprojtool.py vcxproj \
		--type DLL \
		--vcversion "12.00" \
		--version $(RTM_VERSION) \
		--out $(win32_builddir)/hrtm/libHRTM_vc12.vcxproj \
		--yaml libHRTM.vcproj.yaml \
		--source $(HRTM_SRC) \
		--header $(hrtmheader_HEADERS)
	qkc -O- -sm $(win32_builddir)/hrtm/libHRTM_vc12.vcxproj

vc14proj: libHRTM.vcproj.yaml
	$(top_builddir)/build/vcxprojtool.py vcxproj \
		--type DLL \
		--vcversion "14.00" \
		--version $(RTM_VERSION) \
		--out $(win32_builddir)/hrtm/libHRTM_vc14.vcxproj \
		--yaml libHRTM.vcproj.yaml \
		--source $(HRTM_SRC) \
		--header $(hrtmheader_HEADERS)
	qkc -O- -sm $(win32_builddir)/hrtm/libHRTM_vc14.vcxproj

#------------------------------------------------------------
# for wxs file
#------------------------------------------------------------
wxs:
	$(top_srcdir)/build/makewxs.py flist \
		-c Headers \
		-o $(win32_builddir)installer/headers.yaml \
		-p ..\\hrtm \
		*.h version.txt



dist-hook: lst vcproj wxs

clean-local:
	rm -f *~ Makefile.old *core
	rm -f *.lst
	rm -f *.gch *.bak *.rpo *.sym lib*.*_pure_*


EXTRA_DIST = \
	$(hrtmheader_HEADERS) \
	libHRTM.vcproj.yaml


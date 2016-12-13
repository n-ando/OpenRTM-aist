## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for libHRTM
##
## $Id: Makefile.am 2720 2016-05-20 10:35:25Z n-ando $
##------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

hrtmheaderdir = $(rtm_includedir)/hrtm/idls

hrtmheader_HEADERS =    \
	BasicDataType.h     \
	ExtendedDataTypes.h \
	HRTM.h

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(hrtmheader_HEADERS) > header.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir = $(top_builddir)/win32/OpenRTM-aist/

#------------------------------------------------------------
# for wxs file
#------------------------------------------------------------
wxs:
	$(top_srcdir)/build/makewxs.py flist \
		-c Headers \
		-o $(win32_builddir)installer/headers.yaml \
		-p ..\\hrtm\\idls \
		*.h


dist-hook: lst

clean-local:
	rm -f *~ Makefile.old *core
	rm -f *.lst
	rm -f *.gch *.bak *.rpo *.sym lib*.*_pure_*


EXTRA_DIST = \
	$(hrtmheader_HEADERS)


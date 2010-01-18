## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/installer
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf *.yaml *.wxs *~ autowix.cmd
	rm -rf *.wixobj *.wixpdb *.mst *.msi 

wxs:
	sed -e 's/__VERSION__/$(VERSION)/g' OpenRTM-aist.wxs.yaml.in > OpenRTM-aist.wxs.yaml.1
	sed -e 's/__SHORT_VERSION__/$(RTM_MAJOR_VERSION)\.$(RTM_MINOR_VERSION)/g' OpenRTM-aist.wxs.yaml.1 > OpenRTM-aist.wxs.yaml
	rm -f OpenRTM-aist.wxs.yaml.1
	sed -e 's/__VERSION__/$(VERSION)/g' autowix.cmd.in > autowix.cmd
	$(top_srcdir)/build/makewxs.py wxs \
		-o OpenRTM-aist.wxs \
		-i OpenRTM-aist.wxs.in \
		*.yaml

dist-hook: wxs

EXTRA_DIST =                     \
	WiLangId.vbs             \
	WiSubStg.vbs             \
	OpenRTM-aist.wxs.in      \
	OpenRTM-aist.wxs.yaml.in \
	omniORB_inc.wxs.in       \
	omniwxs.py               \
	autowix.cmd.in           \
	License.rtf              \
	langs.txt                \
	crean.cmd

DIST_SUBDIRS = Bitmaps

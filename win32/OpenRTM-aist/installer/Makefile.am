## Makefile.am for win32/OpenRTM-aist/installer
##
## $Id: Makefile.am,v 1.1.2.1 2008-02-09 20:03:52 n-ando Exp $
##
##---------------------------------------------------------------------------
clean-local:
	rm -rf *.yaml *.wxs *.wixobj *.msi *~ autowix.cmd

wxs:
	sed -e 's/__VERSION__/$(VERSION)/g' OpenRTM-aist.wxs.yaml.in > OpenRTM-aist.wxs.yaml
	sed -e 's/__VERSION__/$(VERSION)/g' autowix.cmd.in > autowix.cmd
	$(top_srcdir)/build/makewxs.py wxs \
		-o OpenRTM-aist.wxs \
		-i OpenRTM-aist.wxs.in \
		*.yaml

dist-hook: wxs

EXTRA_DIST = \
	OpenRTM-aist.wxs.in \
	OpenRTM-aist.wxs.yaml.in \
	wixui_ja-jp.wxl \
	License.rtf

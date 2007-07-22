## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist
##
## $Id: Makefile.am,v 1.1.2.2 2007-07-22 10:59:38 n-ando Exp $
##
## $Log: not supported by cvs2svn $
##---------------------------------------------------------------------------
SUBDIRS = OpenRTM-aist .


clean-clocal:
	rm -rf ../$(PACKAGE_TARNAME)-$(VERSION)-win32.zip *~
dist-hook:
	find ./OpenRTM-aist/ \! -path '*CVS*' > zip_list
	zip -r ../$(PACKAGE_TARNAME)-$(VERSION)-win32.zip `cat zip_list`
	rm -f zip_list

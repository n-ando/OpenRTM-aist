## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist
##
## $Id$
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.2  2007/07/22 10:59:38  n-ando
## *** empty log message ***
##
##---------------------------------------------------------------------------
SUBDIRS = OpenRTM-aist .


clean-clocal:
	rm -rf ../$(PACKAGE_TARNAME)-$(VERSION)-win32.zip *~


dist-hook:
	rm -rf ../$(PACKAGE_TARNAME)-$(VERSION)-win32.zip
	find ./OpenRTM-aist/ \! -path '*.svn*' \! -path '*CVS*' \
		\! -path '*#*' \! -path '*~' > zip_list
	cat zip_list | zip -@ ../$(PACKAGE_TARNAME)-$(VERSION)-win32.zip
	rm -f zip_list

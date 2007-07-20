SUBDIRS = OpenRTM-aist .

dist-hook:
	rm -f ../$(PACKAGE_TARNAME)-$(VERSION)-win32.zip *~
	zip -r ../$(PACKAGE_TARNAME)-$(VERSION)-win32.zip OpenRTM-aist/

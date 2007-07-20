## Makefile.am for win32/OpenRTM-aist/bin
##
## $Id: Makefile.am,v 1.1.2.1 2007-07-20 16:26:26 n-ando Exp $
##
## $Log: not supported by cvs2svn $
##
##---------------------------------------------------------------------------
clean-local:
	rm -f *~ *.dll *.lib
	rm -rf *~ *.py

dist-hook: clean-local
	cp $(top_srcdir)/build/*.py .
	cp $(top_srcdir)/utils/rtm-skelwrapper/*.py .
	cp $(top_srcdir)/utils/rtm-skelwrapper/rtm-skelwrapper rtm-skelwrapper.py


## Makefile.am win32/OpenRTM-aist/docs
##
## $Id: Makefile.am,v 1.1.2.1 2007-07-20 16:26:34 n-ando Exp $
##
## $Log: not supported by cvs2svn $
##
##---------------------------------------------------------------------------

ClassReference:
	cp -r $(top_srcdir)/docs/ClassReference .


ClassReference-en:
	cp -r $(top_srcdir)/docs/ClassReference-en .


IDLReference:
	cp -r $(top_srcdir)/docs/IDLReference .


IDLReference-en:
	cp -r $(top_srcdir)/docs/IDLReference-en .


clean-local:
	rm -rf *~ ClassReference ClassReference-en IDLReference IDLReference-en


dist-hook: clean-local ClassReference ClassReference-en IDLReference IDLReference-en

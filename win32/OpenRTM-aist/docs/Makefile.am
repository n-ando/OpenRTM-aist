## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am win32/OpenRTM-aist/docs
##
## $Id$
##---------------------------------------------------------------------------

ClassReference:
	cp -p -r $(top_srcdir)/docs/ClassReference .

ClassReference-en:
	cp -p -r $(top_srcdir)/docs/ClassReference-en .

IDLReference:
	cp -p -r $(top_srcdir)/docs/IDLReference .

IDLReference-en:
	cp -p -r $(top_srcdir)/docs/IDLReference-en .

clean-local:
	rm -rf *~ ClassReference ClassReference-en IDLReference IDLReference-en

dist-hook: clean-local ClassReference ClassReference-en IDLReference IDLReference-en

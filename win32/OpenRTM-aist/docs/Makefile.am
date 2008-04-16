## Makefile.am win32/OpenRTM-aist/docs
##
## $Id$
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.1  2007/07/20 16:26:34  n-ando
## Makefile for Win32 source tree management.
##
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

wxs:
	$(top_srcdir)/build/makewxs.py flist \
		-c Classref_jp \
		-o ../installer/classref_jp.yaml \
		-p ..\\docs\\ClassReference\\html \
		./ClassReference/html/*
	$(top_srcdir)/build/makewxs.py flist \
		-c Classref_en \
		-o ../installer/classref_en.yaml \
		-p ..\\docs\\ClassReference-en\\html \
		./ClassReference-en/html/*
	$(top_srcdir)/build/makewxs.py flist \
		-c IDLref_jp \
		-o ../installer/idlref_jp.yaml \
		-p ..\\docs\\IDLReference\\html \
		./IDLReference/html/*
	$(top_srcdir)/build/makewxs.py flist \
		-c IDLref_en \
		-o ../installer/idlref_en.yaml \
		-p ..\\docs\\IDLReference-en\\html \
		./IDLReference-en/html/*

clean-local:
	rm -rf *~ ClassReference ClassReference-en IDLReference IDLReference-en

dist-hook: clean-local ClassReference ClassReference-en IDLReference IDLReference-en wxs

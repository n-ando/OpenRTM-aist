## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for swig
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

ClassReference:
	make -f Makefile.docs ClassReference

ClassReference-en:
	make -f Makefile.docs ClassReference-en

IDLReference:
	make -f Makefile.docs IDLReference

IDLReference-en:
	make -f Makefile.docs IDLReference-en

#DevelopersGuide.ps:
#	make -f Makefile.docs DevelopersGuide.ps

#DevelopersGuide.pdf:
#	make -f Makefile.docs DevelopersGuide.pdf

docsdir = $(pkgdatadir)

EXTRA_DIST = \
	ClassReference \
	ClassReference-en \
	IDLReference \
	IDLReference-en
#	DevelopersGuide.ps \
#	DevelopersGuide.pdf

#install-manual:
#	$(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/docs/
#	if test -f DevelopersGuide.ps; then \
#	  $(INSTALL_DATA) DevelopersGuide.ps $(DESTDIR)$(pkgdatadir)/docs/; \
#	fi
#	if test -f DevelopersGuide.pdf; then \
#	  $(INSTALL_DATA) DevelopersGuide.pdf $(DESTDIR)$(pkgdatadir)/docs/; \
#	fi

install-class-reference:
	if test -d ClassReference; then \
	  $(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/docs/ClassReference/html; \
	  for x in ClassReference/html/*; do \
	    if test -f $$x; then \
	      $(INSTALL_DATA) $$x $(DESTDIR)$(pkgdatadir)/docs/ClassReference/html/;\
	    fi \
	  done \
	fi

install-class-reference-en:
	if test -d ClassReference-en; then \
	  $(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/docs/ClassReference-en/html; \
	  for x in ClassReference-en/html/*; do \
	    if test -f $$x; then \
	      $(INSTALL_DATA) $$x $(DESTDIR)$(pkgdatadir)/docs/ClassReference-en/html/;\
	    fi \
	  done \
	fi

install-idl-reference:
	if test -d IDLReference; then \
	  $(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/docs/IDLReference/html; \
	  for x in IDLReference/html/*; do \
	    if test -f $$x; then \
	      $(INSTALL_DATA) $$x $(DESTDIR)$(pkgdatadir)/docs/IDLReference/html/;\
	    fi \
	  done \
	fi

install-idl-reference-en:
	if test -d IDLReference-en; then \
	  $(mkinstalldirs) $(DESTDIR)$(pkgdatadir)/docs/IDLReference-en/html; \
	  for x in IDLReference-en/html/*; do \
	    if test -f $$x; then \
	      $(INSTALL_DATA) $$x $(DESTDIR)$(pkgdatadir)/docs/IDLReference-en/html/;\
	    fi \
	  done \
	fi

#install-data-local: install-class-reference install-class-reference-en install-idl-reference install-idl-reference-en

install-data-local: generate-refs install-refs

generate-refs: ClassReference ClassReference-en IDLReference IDLReference-en

install-refs: install-class-reference install-class-reference-en install-idl-reference install-idl-reference-en

clean-local:
	rm -f Makefile.old *~

maintainer-clean:
	rm -rf \
	Makefile \
	ClassReference \
	ClassReference-en \
	IDLReference \
	IDLReference-en \
	docs/DevelopersGuide/ClassReference \
	docs/DevelopersGuide/IDLReference

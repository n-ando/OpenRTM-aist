## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtc-link
##
## $Id: Makefile.am,v 1.4 2005-09-08 12:52:03 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.3  2005/05/27 10:08:19  n-ando
## - InPort/OutPort interface was changed.
##   rtc-link assembly function is enabled now.
##
## Revision 1.2  2005/05/23 07:13:43  n-ando
## - Now, DESTDIR is supported for rtc-link python modules.
##
## Revision 1.1.1.1  2005/05/12 09:06:19  n-ando
## Public release.
##
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

# IDL and omniidl path and options
IDLDIR = ../../rtm/idl/
IDLC = omniidl
IDLPYFLAGS = -bpython -nf

VPATH = $(IDLDIR)

# Suffix and suffix rule
SUFFIXES = .idl _idl.py 
.idl_idl.py:
	$(IDLC) $(IDLPYFLAGS) $(IDLDIR)$<


# rtc-link script to be installed bin directory
bin_SCRIPTS = rtc-link

rtc-link:

# Something to install to libdir
pymoduledir = $(pkglibdir)/rtc-link
pymodule_SCRIPTS = \
	$(PY_STUBS) \
	$(RTCLINK_SOURCES)

# RTCLink python sources
RTCLINK_SOURCES = \
	RtcLink.py \
	RtcLink.pyw \
	RtmAbout.py \
	RtmNSHelper.py \
	RtmProfileList.py \
	RtmCompData.py \
	RtmLineUtil.py \
	RtmSystemDraw.py \
	RtmFrame.py \
	RtmParser.py \
	RtmTreeCtrl.py \
	rtimages.py \
	RtmDialog.py \
	RtmDtdValidator.py \
	rtc-link

# rule for installing RTM RTM__POA directories
install-stubs:
	if test -d RTM; then \
	  $(mkinstalldirs) $(DESTDIR)$(pymoduledir)/RTM; \
	  for x in RTM/*; do \
	    if test -f $$x; then \
	      $(INSTALL_DATA) $$x $(DESTDIR)$(pymoduledir)/RTM/ ;\
	    fi \
	  done \
	fi
	if test -d RTM__POA; then \
	  $(mkinstalldirs) $(DESTDIR)$(pymoduledir)/RTM__POA; \
	  for x in RTM__POA/*; do \
	    if test -f $$x; then \
	      $(INSTALL_DATA) $$x $(DESTDIR)$(pymoduledir)/RTM__POA/ ;\
	    fi \
	  done \
	fi


install-data-local: install-stubs


IDL_SOURCES =       \
	RTMBase.idl     \
	RTCDataType.idl \
	RTCSubscription.idl	\
	RTCPortBase.idl	\
	RTCInPort.idl   \
	RTCOutPort.idl  \
	RTCService.idl  \
	RTComponent.idl \
	RTCProfile.idl  \
	RTCBase.idl     \
	RTCManager.idl

#
# RTM idl stubs for python
PY_STUBS = $(IDL_SOURCES:.idl=_idl.py)

#RTMBase_idl.py: RTMBase.idl

py_stub: $(PY_STUBS)

dist-hook: py_stub

EXTRA_DIST = \
	$(RTCLINK_SOURCES) \
	$(PY_STUBS) \
	RTM \
	RTM__POA


clean-local:
	rm -rf *~ *core *.pyc *_idl.py RTM RTM__POA

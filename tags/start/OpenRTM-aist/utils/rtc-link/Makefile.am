## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for rtc-link
##
## $Id: Makefile.am,v 1.1.1.1 2005-05-12 09:06:19 n-ando Exp $
##
## $Log: not supported by cvs2svn $
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
	  $(mkinstalldirs) $(pymoduledir)/RTM; \
	  for x in RTM/*; do \
	    if test -f $$x; then \
	      $(INSTALL_DATA) $$x $(pymoduledir)/RTM/ ;\
	    fi \
	  done \
	fi
	if test -d RTM__POA; then \
	  $(mkinstalldirs) $(pymoduledir)/RTM__POA; \
	  for x in RTM__POA/*; do \
	    if test -f $$x; then \
	      $(INSTALL_DATA) $$x $(pymoduledir)/RTM__POA/ ;\
	    fi \
	  done \
	fi


install-data-local: install-stubs


#IDL_SOURCES =       \
#	$(IDLDIR)RTMBase.idl     \
#	$(IDLDIR)RTCDataType.idl \
#	$(IDLDIR)RTCInPort.idl   \
#	$(IDLDIR)RTCOutPort.idl  \
#	$(IDLDIR)RTComponent.idl \
#	$(IDLDIR)RTCProfile.idl  \
#	$(IDLDIR)RTCBase.idl     \
#	$(IDLDIR)RTCManager.idl
IDL_SOURCES =       \
	RTMBase.idl     \
	RTCDataType.idl \
	RTCInPort.idl   \
	RTCOutPort.idl  \
	RTComponent.idl \
	RTCProfile.idl  \
	RTCBase.idl     \
	RTCManager.idl
#
# RTM idl stubs for python
PY_STUBS = $(IDL_SOURCES:.idl=_idl.py)

#	RTMBase_idl.py     \
#	RTCDataType_idl.py \
#	RTCInPort_idl.py   \
#	RTCOutPort_idl.py  \
#	RTComponent_idl.py \
#	RTCProfile_idl.py  \
#	RTCBase_idl.py     \
#	RTCManager_idl.py

RTMBase_idl.py: RTMBase.idl

py_stub: $(PY_STUBS)

dist-hook: py_stub

EXTRA_DIST = \
	$(RTCLINK_SOURCES) \
	$(PY_STUBS) \
	RTM \
	RTM__POA


clean-local:
	rm -rf *~ *core *.pyc *_idl.py RTM RTM__POA

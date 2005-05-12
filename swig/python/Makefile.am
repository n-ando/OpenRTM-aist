## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for swig
##
## $Id: Makefile.am,v 1.1.1.1 2005-05-12 09:06:19 n-ando Exp $
##
## $Log: not supported by cvs2svn $
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/rtm -L$(top_builddir)/rtm/idl

CXXFLAGS=@CXXFLAGS@
CPPFLAGS=@CPPFLAGS@

WRAPPER_CXXFLAGS = -c $(AM_CPPFLAGS) -I$(top_srcdir) -I$(top_srcdir)/rtm/idl -I. $(PYTHON_FLAGS) $(CXXFLAGS) $(CPPFLAGS) -I. 
WRAPPER_LD_FLAGS = $(AM_LDFLAGS) -L$(top_builddir)/rtm/.libs -L/usr/local/lib -lRTC -lACE $(LDFLAGS) 
SUFFIXES =  _wrap.cpp _wrap.o _wrap.so .i .o .so 

SWIG=swig
SWIG_FLAGS=-python -Wall -shadow -proxy -c++ -I../.. -I..

SWIGISOURCES = \
	_defs.i \
	typemaps_py.i \
	RTM.i \
	RtcBase.i \
	RtcManager.i \
	RtcInPort.i \
	RtcOutPort.i \
	RtcModuleProfile.i \
	RTComponent.i \
	RTCInPort.i \
	RTCOutPort.i \
	RTCManager.i

SWIG_WRAP = RTM_wrap.cpp

PYMODULES = RTM_wrap.so


all: $(PYMODULES)

_wrap.cpp_wrap.o:
	$(CXX) $(WRAPPER_CXXFLAGS) -o $@ $<


_wrap.o_wrap.so:
	$(CXX) -shared $(WRAPPER_LD_FLAGS) -o $@ $<
	mv $@ _`echo $@ | sed -e 's/_wrap//g'`


RTM_wrap.cpp: RTM.i $(I_SOURCES)
	$(SWIG) $(SWIG_FLAGS) -o $@ RTM.i
	mv $@ RTM_wrap0.cpp
	sed -e 's/RTCBase \*/RTCBase_ptr /g' RTM_wrap0.cpp | \
	sed -e 's/RTComponent \*/RTComponent_ptr /g' | \
	sed -e 's/InPort \*/InPort_ptr /g' | \
	sed -e 's/OutPort \*/OutPort_ptr /g' | \
	sed -e 's/RTCManager \*/RTCManager_ptr /g'  > $@
	rm -f RTM_wrap0.cpp

RTM_wrap.h: RTM_wrap.cpp

EXTRA_DIST = \
	$(SWIGISOURCES) \
	$(PYMODULES:_wrap.so=.py) \
	$(PYMODULES:.so=.cpp) \
	RTM_wrap.h \
	RtcDataConv.h \
	pyhelper.h

py_wrap: $(SWIG_WRAP)

dist-hook: py_wrap

clean-wrap:
	rm -f *_wrap.cpp *_wrap.h

clean-local:
	rm -f *.so *_wrap.o Makefile.old *~

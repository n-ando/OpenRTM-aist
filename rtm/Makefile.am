## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for libRTC
##
## $Id: Makefile.am,v 1.3 2006-09-11 18:44:23 n-ando Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.2  2005/09/07 04:58:22  n-ando
## RTComponent's service management feature was added.
##
## Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
## Public release.
##
##------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

ARTLIB = @ARTLIB@
SUBDIRS = idl . tests

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/rtm -L$(top_builddir)/rtm/idl

lib_LTLIBRARIES = libRTC.la

# sources of libShared.la
RTC_SRC = \
	Properties.cpp \
	RtcNaming.cpp \
	RtcNameComponent.cpp \
	RtcConfig.cpp \
	RtcSubscriber.cpp \
	RtcInPortBase.cpp \
	RtcOutPortBase.cpp \
	RtcServiceBase.cpp \
	RtcModuleProfile.cpp \
	RtcBase.cpp \
	RtcFactory.cpp \
	RtcManager.cpp \
	RtcLifeCycle.cpp \
	RtcComponentAction.cpp \
	RTObject.cpp \
	RtcPort.o \
	SdoOrganization.cpp \
	SdoConfiguration.cpp \
	SdoSystemElement.cpp

#	RtcConfiguration.cpp \
#	RtcProfile.cpp \
#	RtcTimeStatistics.cpp
#	RtcCompositeBase.cpp 

libRTC_la_SOURCES = \
	Properties.cpp \
	RtcNaming.cpp \
	RtcNameComponent.cpp \
	RtcConfig.cpp \
	RtcSubscriber.cpp \
	RtcInPortBase.cpp \
	RtcOutPortBase.cpp \
	RtcServiceBase.cpp \
	RtcModuleProfile.cpp \
	RtcBase.cpp \
	RtcFactory.cpp \
	RtcManager.cpp

#	RtcConfiguration.cpp \
#	RtcProfile.cpp \
#	RtcTimeStatistics.cpp
#	RtcCompositeBase.cpp 

libRTC_la_LIBADD = $(top_builddir)/rtm/idl/libRTCSkel.la $(ARTLIB)
libRTC_la_LDFLAGS = -static -L$(top_builddir)/rtm/idl


rtmheaderdir = $(prefix)/include/rtm

rtmheader_HEADERS = \
	$(libRTC_la_SOURCES:.cpp=.h) \
	RTC.h \
	RtcRingBuffer.h \
	RtcInPort.h \
	RtcOutPort.h \
	RtcServiceBase.h \
	RtcFactoryPy.h \
	RtcSystemLogger.h \
	config_rtc.h

EXTRA_DIST = $(rtmheader_HEADERS)

clean-local:
	rm -f *.bak *.rpo *.sym lib*.*_pure_* Makefile.old *core *~

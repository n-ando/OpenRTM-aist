## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for unit test
##
## $Id: Makefile.am,v 1.1 2006-09-11 18:40:38 n-ando Exp $
##
## $Log: not supported by cvs2svn $
##
##------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@
TESTS = RtcNamingTests

INCLUDES = -I$(top_srcdir) -I$(includedir)

IDL_SOURCES = \
	HelloWorld.idl



noinst_PROGRAMS = \
	RtcNamingTests \
	PropertiesTests

RtcNamingTests_SOURCES = RtcNamingTests.cpp
RtcNamingTests_LDFLAGS = -L$(libdir)
RtcNamingTests_LDADD   = ../RtcNaming.o ./HelloWorld.o -lcppunit

PropertiesTests_SOURCES = PropertiesTests.cpp
PropertiesTests_LDFLAGS = -L$(libdir)
PropertiesTests_LDADD   = ../Properties.o -lcppunit


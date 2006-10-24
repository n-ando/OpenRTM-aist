## -*- Makefile -*-
##------------------------------------------------------------
## Makefile.am for unit test
##
## $Id: Makefile.am,v 1.4 2006-10-24 03:07:31 kurihara Exp $
##
## $Log: not supported by cvs2svn $
## Revision 1.3  2006/10/23 06:29:22  kurihara
##
## add ManagerConfigTests and StringUtilTests.
##
## Revision 1.2  2006/09/20 08:50:31  n-ando
## ModuleManagerTests is added.
##
## Revision 1.1  2006/09/11 18:40:38  n-ando
## The first commit.
##
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
	PropertiesTests \
	StringUtilTests \
	ModuleManagerTests \
	ManagerConfigTests \
	ObjectManagerTests

RtcNamingTests_SOURCES = RtcNamingTests.cpp
RtcNamingTests_LDFLAGS = -L$(libdir)
RtcNamingTests_LDADD   = ../RtcNaming.o ./HelloWorld.o -lcppunit

PropertiesTests_SOURCES = PropertiesTests.cpp
PropertiesTests_LDFLAGS = -L$(libdir)
PropertiesTests_LDADD   = ../Properties.o -lcppunit

StringUtilTests_SOURCES = StringUtilTests.cpp
StringUtilTests_LDFLAGS = -L$(libdir)
StringUtilTests_LDADD   = -lcppunit

ModuleManagerTests_SOURCES = ModuleManagerTests.cpp
ModuleManagerTests_LDFLAGS = -L$(libdir)
ModuleManagerTests_LDADD   = ../Properties.o ../ModuleManager.o  -lcppunit -lACE

ManagerConfigTests_SOURCES = ManagerConfigTests.cpp
ManagerConfigTests_LDFLAGS = -L$(libdir)
ManagerConfigTests_LDADD   = ../Properties.o ../ManagerConfig.o -lcppunit

ObjectManagerTests_SOURCES = ObjectManagerTests.cpp
ObjectManagerTests_LDFLAGS = -L$(libdir)
ObjectManagerTests_LDADD   = -lcppunit

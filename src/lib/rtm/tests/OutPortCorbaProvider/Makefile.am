#
# $Log: Makefile.am,v $
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =                    \
	 -I.                      \
	-I$(top_builddir)         \
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm_corba/idl \
	-I$(top_builddir)/src/lib/rtm_corba \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(top_builddir)/src/lib/rtm \
	-I$(includedir)

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib

IDL_SOURCES = \
	$(top_srcdir)/src/lib/rtm_corba/idl/BasicDataType.idl \
	$(top_srcdir)/src/lib/rtm_corba/idl/DataPort.idl

noinst_PROGRAMS = OutPortCorbaProviderTests

nodist_OutPortCorbaProviderTests_SOURCES =             \
	../TestRunner.cpp                \
	$(IDL_SOURCES:.idl=Skel.cpp)                \
	$(top_srcdir)/src/lib/coil/common/stringutil.cpp \
	$(top_srcdir)/src/lib/coil/common/Properties.cpp \
	$(top_srcdir)/src/lib/rtm/NVUtil.cpp     \
	$(top_srcdir)/src/lib/rtm/OutPortProvider.cpp \
	OutPortCorbaProviderTests.cpp

OutPortCorbaProviderTests_LDFLAGS = -L$(libdir)
OutPortCorbaProviderTests_LDADD   = -lcppunit -lcoil

EXTRA_DIST =        \
	OutPortCorbaProviderTests.cpp

# all
all: do-test

# do tests
do-test:
	./OutPortCorbaProviderTests --xml outportcorbaprovidertests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

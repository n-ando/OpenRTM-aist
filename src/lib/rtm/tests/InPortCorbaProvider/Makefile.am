#
# $Log: Makefile.am,v $
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS = \
	-I. \
	-I$(top_builddir) \
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(includedir)

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib

IDL_SOURCES = \
	$(top_srcdir)/src/lib/rtm/idl/BasicDataType.idl \
	$(top_srcdir)/src/lib/rtm/idl/DataPort.idl

noinst_PROGRAMS = InPortCorbaProviderTests

nodist_InPortCorbaProviderTests_SOURCES = \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	../TestRunner.cpp \
	$(top_srcdir)/src/lib/rtm/Properties.cpp \
	$(top_srcdir)/src/lib/rtm/NVUtil.cpp \
	$(top_srcdir)/src/lib/rtm/InPortProvider.cpp \
	InPortCorbaProviderTests.cpp

InPortCorbaProviderTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
InPortCorbaProviderTests_LDADD   = -lcppunit -lcoil

EXTRA_DIST =        \
	InPortCorbaProviderTests.cpp

# all
all: do-test

# do tests
do-test:
	./InPortCorbaProviderTests --xml inportcorbaprovidertests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

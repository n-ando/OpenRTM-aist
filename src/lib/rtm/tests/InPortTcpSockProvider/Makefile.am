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
	-I$(top_builddir)/rtm/idl \
	-I$(includedir)

AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir)

IDL_SOURCES = \
	$(top_srcdir)/rtm/idl/BasicDataType.idl \
	$(top_srcdir)/rtm/idl/DataPort.idl

noinst_PROGRAMS = InPortTcpSockProviderTests

nodist_InPortTcpSockProviderTests_SOURCES = \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	../TestRunner.cpp \
	$(top_srcdir)/rtm/StringUtil.cpp \
	$(top_srcdir)/rtm/Properties.cpp \
	$(top_srcdir)/rtm/NVUtil.cpp \
	$(top_srcdir)/rtm/InPortProvider.cpp \
	InPortTcpSockProviderTests.cpp

InPortTcpSockProviderTests_LDFLAGS = -L$(libdir)
InPortTcpSockProviderTests_LDADD   = -lcppunit

EXTRA_DIST =        \
	InPortTcpSockProviderTests.cpp

# all
all: do-test

# do tests
do-test:
	./InPortTcpSockProviderTests --xml inporttcpsockprovidertests.xml \
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

# -*- Makefile -*-
#
# $Log: Makefile.am,v $
#
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

AM_LDFLAGS=               \
	-L.               \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib

IDL_SOURCES = \
	$(top_srcdir)/src/lib/rtm/idl/DataPort.idl \
	$(top_srcdir)/src/lib/rtm/idl/SDOPackage.idl

SUFFIXES = .idl Skel.cpp Stub.cpp Stub.o Skel.o
.idlSkel.cpp:
	$(top_srcdir)/build/makewrapper.py $< rtm/tests/InPortTcpSockConsumer/
	$(IDLC) $(IDLFLAGS) $<

noinst_PROGRAMS = InPortTcpSockConsumerTests

nodist_InPortTcpSockConsumerTests_SOURCES = \
	../TestRunner.cpp \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	$(top_srcdir)/src/lib/rtm/Properties.cpp \
	$(top_srcdir)/src/lib/rtm/NVUtil.cpp \
	InPortTcpSockConsumerTests.cpp

InPortTcpSockConsumerTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
InPortTcpSockConsumerTests_LDADD   = -lcppunit -lcoil -lACE

EXTRA_DIST =               \
	InPortTcpSockConsumerTests.cpp \
	$(IDL_SOURCES)

# all
all: do-test

# do tests
do-test:
	./InPortTcpSockConsumerTests --xml inporttcpsockconsumertests.xml \
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

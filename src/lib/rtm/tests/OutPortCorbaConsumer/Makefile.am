# -*- Makefile -*-
#
# $Log: Makefile.am,v $
#
#


AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS=               \
	-I.                \
	-I$(top_builddir)  \
	-I$(top_builddir)/src/lib \
	-I$(top_builddir)/src/lib/rtm_corba/idl \
	-I$(top_builddir)/src/lib/rtm_corba \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(top_builddir)/src/lib/rtm \
	-I$(includedir)

AM_LDFLAGS=           \
	-L.               \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib

IDL_SOURCES = \
	$(top_srcdir)/src/lib/rtm_corba/idl/BasicDataType.idl \
	$(top_srcdir)/src/lib/rtm_corba/idl/DataPort.idl

SUFFIXES = .idl Skel.cpp Stub.cpp Stub.o Skel.o
.idlSkel.cpp:
	$(top_srcdir)/build/makewrapper.py $< rtm/tests/OutPortCorbaConsumer/
	$(IDLC) $(IDLFLAGS) $<

noinst_PROGRAMS = OutPortCorbaConsumerTests

nodist_OutPortCorbaConsumerTests_SOURCES = \
	../TestRunner.cpp \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	$(top_srcdir)/src/lib/coil/common/stringutil.cpp \
	$(top_srcdir)/src/lib/coil/common/Properties.cpp \
	$(top_srcdir)/src/lib/rtm/NVUtil.cpp \
	OutPortCorbaConsumerTests.cpp

OutPortCorbaConsumerTests_LDFLAGS = -L$(libdir)
OutPortCorbaConsumerTests_LDADD   = -lcppunit -lcoil

EXTRA_DIST =               \
	OutPortCorbaConsumerTests.cpp \
	$(IDL_SOURCES)

# all
all: do-test

# do tests
do-test:
	./OutPortCorbaConsumerTests --xml outportcorbaconsumertests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

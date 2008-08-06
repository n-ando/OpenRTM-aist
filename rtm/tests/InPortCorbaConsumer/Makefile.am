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
	-I$(top_builddir)/rtm/idl  \
	-I$(includedir)

AM_LDFLAGS=           \
	-L.               \
	-L$(top_builddir)

IDL_SOURCES = \
	$(top_srcdir)/rtm/idl/DataPort.idl

SUFFIXES = .idl Skel.cpp Stub.cpp Stub.o Skel.o
.idlSkel.cpp:
	$(top_srcdir)/build/makewrapper.py $< rtm/tests/InPortCorbaConsumer/
	$(IDLC) $(IDLFLAGS) $<

noinst_PROGRAMS = InPortCorbaConsumerTests

nodist_InPortCorbaConsumerTests_SOURCES = \
	../TestRunner.cpp \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	$(top_srcdir)/rtm/StringUtil.cpp \
	$(top_srcdir)/rtm/Properties.cpp \
	$(top_srcdir)/rtm/NVUtil.cpp \
	InPortCorbaConsumerTests.cpp

InPortCorbaConsumerTests_LDFLAGS = -L$(libdir)
InPortCorbaConsumerTests_LDADD   = -lcppunit

EXTRA_DIST =               \
	InPortCorbaConsumerTests.cpp \
	$(IDL_SOURCES)

# all
all: do-test

# do tests
do-test:
	./InPortCorbaConsumerTests --xml inportcorbaconsumertests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

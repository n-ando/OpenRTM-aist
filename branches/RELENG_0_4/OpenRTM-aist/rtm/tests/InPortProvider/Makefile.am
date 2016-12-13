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


IDL_SOURCES =                                \
	$(top_srcdir)/rtm/idl/RTC.idl        \
	$(top_srcdir)/rtm/idl/SDOPackage.idl 

noinst_PROGRAMS = InPortProviderTests

nodist_InPortProviderTests_SOURCES =             \
	../TestRunner.cpp                \
	$(IDL_SOURCES:.idl=Skel.cpp)     \
	$(top_srcdir)/rtm/StringUtil.cpp \
	$(top_srcdir)/rtm/Properties.cpp \
	$(top_srcdir)/rtm/NVUtil.cpp     \
	$(top_srcdir)/rtm/InPortProvider.cpp \
	InPortProviderTests.cpp

InPortProviderTests_LDFLAGS = -L$(libdir)
InPortProviderTests_LDADD   = -lcppunit

EXTRA_DIST =        \
	InPortProviderTests.cpp

# all
all: do-test

# do tests
do-test:
	./InPortProviderTests --xml inportprovidertests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

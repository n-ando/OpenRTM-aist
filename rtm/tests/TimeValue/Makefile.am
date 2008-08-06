AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS =             \
	-I.               \
	-I$(top_builddir) \
	-I$(top_builddir)/rtm/idl \
	-I$(includedir)


AM_LDFLAGS =              \
	-L.               \
	-L$(top_builddir)

noinst_PROGRAMS = TimeValueTests

nodist_TimeValueTests_SOURCES = \
	../TestRunner.cpp \
	TimeValueTests.cpp

TimeValueTests_LDFLAGS = -L$(libdir)
TimeValueTests_LDADD   = -lcppunit

EXTRA_DIST =            \
	TimeValueTests.cpp

# all
all: do-test

# do tests
do-test:
	./TimeValueTests --xml timevaluetests.xml \
	--xsl default.xsl

# clean-up
clean-local:
	rm -f                               \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl

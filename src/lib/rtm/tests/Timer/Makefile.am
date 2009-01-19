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

noinst_PROGRAMS = TimerTests

nodist_TimerTests_SOURCES = \
	../TestRunner.cpp \
	$(top_builddir)/rtm/Timer.cpp \
	TimerTests.cpp

TimerTests_LDFLAGS = -L$(libdir)
TimerTests_LDADD   = -lcppunit

EXTRA_DIST =            \
	TimerTests.cpp

# all
all: do-test

# do tests
do-test:
	./TimerTests --xml timertests.xml \
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

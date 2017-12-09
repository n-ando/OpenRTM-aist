# -*- Makefile -*-
#------------------------------------------------------------
# @file   Makefile.am
# @brief  Makefile.am for InPort unit test
# @date   $Date: 2007/01/21 06:52:04 $
# @author Noriaki Ando <n-ando@aist.go.jp>
#
# $Id$
#
#------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS = \
	-coverage \
	 -I. \
	-I$(top_builddir) \
	-I$(top_builddir)/src/lib/ \
	-I$(top_builddir)/src/lib/rtm \
	-I$(top_builddir)/src/lib/rtm/idl \
	-I$(top_builddir)/src/lib/coil/include \
	-I$(includedir)

AM_LDFLAGS =              \
	 -L.              \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/coil/lib

IDL_SOURCES = \
	$(top_srcdir)/src/lib/rtm/idl/SDOPackage.idl \
	$(top_srcdir)/src/lib/rtm/idl/RTC.idl \
	$(top_srcdir)/src/lib/rtm/idl/OpenRTM.idl \
	$(top_srcdir)/src/lib/rtm/idl/Manager.idl \
	$(top_srcdir)/src/lib/rtm/idl/BasicDataType.idl \
	$(top_srcdir)/src/lib/rtm/idl/DataPort.idl

noinst_PROGRAMS = InPortTests

nodist_InPortTests_SOURCES =     \
	../TestRunner.cpp        \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	$(top_srcdir)/src/lib/rtm/ManagerActionListener.cpp \
	$(top_srcdir)/src/lib/rtm/PortConnectListener.cpp \
	$(top_srcdir)/src/lib/rtm/NVUtil.cpp \
	$(top_srcdir)/src/lib/rtm/PortBase.cpp \
	$(top_srcdir)/src/lib/rtm/CdrRingBuffer.cpp            \
	$(top_srcdir)/src/lib/rtm/InPortBase.cpp                 \
	$(top_srcdir)/src/lib/rtm/InPortConnector.cpp            \
	$(top_srcdir)/src/lib/rtm/InPortPullConnector.cpp        \
	$(top_srcdir)/src/lib/rtm/ConnectorListener.cpp      \
	InPortTests.cpp



InPortTests_LDFLAGS = -L$(libdir) $(AM_LDFLAGS)
InPortTests_LDADD   = -lcppunit -lcoil -lgcov

EXTRA_DIST =        \
	InPortTests.cpp

# all
all: do-test do-coverage

do-coverage: 
	rm -rf ./Coverage
	./InPortTests 
	gcov InPortTests.gcda 
	mkdir -p ./Coverage 
	lcov -c -d . -o ./Coverage/InPortTests.info 
	../rtm_tests_changeInfo.py ./Coverage/InPortTests.info 
	genhtml -o ./Coverage ./Coverage/InPortTests.info 

# do tests
do-test:
	./InPortTests --xml inporttests.xml --xsl default.xsl

# clean-up
clean-local:
	rm -rf ./Coverage
	rm -f *.gcda *.gcno *.gcov
	rm -f InPortTests
	rm -f                               \
        *.log *.xml                         \
	*.o *.Po *.gch *.la                 \
	*Skel.cpp *Skel.h *Stub.cpp *Stub.h \
	*~ *core                            \
	Makefile.old                        \
	*.cc *.hh *.i *.a *.c *.inl



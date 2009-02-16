## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for coil (Component Object Infrastructure Layer)
##
## $Id$
##---------------------------------------------------------------------------

AM_CPPFLAGS=-I../

# posix API dependent sources
COIL_PLATFORM_SRC =    \
	Condition.cpp  \
	DynamicLib.cpp \
	Mutex.cpp      \
	Signal.cpp     \
	Task.cpp       \
	Time.cpp       \
	UUID.cpp

# posix API dependent headers
COIL_PLATFORM_H   =    \
	atomic.h       \
	OS.h           \
	$(COIL_PLATFORM_SRC:.cpp=.h)

# coil common source
COIL_COMMON_SRC =      \
	stringutil.cpp \
	Properties.cpp \
	TimeValue.cpp  \
	Timer.cpp

# coil common headers
COIL_COMMON_H =        \
	Guard.h        \
	NonCopyable.h  \
	Listener.h     \
	$(COIL_COMMON_SRC:.cpp=.h)

# coil all sources and headers
COIL_SRC = $(COIL_COMMON_SRC) $(COIL_PLATFORM_SRC)
COIL_H   = $(COIL_COMMON_H) $(COIL_PLATFORM_H)
COIL_ALL = $(COIL_SRC) $(COIL_H)

$(COIL_COMMON_SRC):
	cp $(top_srcdir)/common/*.cpp .
	cp $(top_srcdir)/common/*.h .
	qkc -ms *.cpp *.h

$(COIL_COMMON_H):
	cp $(top_srcdir)/common/*.h .
	qkc -ms *.cpp *.h


coilheaderdir = $(prefix)/include/coil

coilheader_HEADERS = $(COIL_H)

lib_LTLIBRARIES = libcoil.la

libcoil_la_SOURCES =          \
	$(COIL_ALL)

clean-local:
	rm -f config_coil.h
	rm -f *~
	rm -f *.o *.lo *.loT
	rm -f $(COIL_COMMON_SRC) $(COIL_COMMON_H)
	rm -f *.vcproj
	rm -f *.user *.def
	rm -rf Release Debug
	chmod 644 *.cpp *.h

EXTRA_DIST =                \
	$(COIL_ALL)         \
	libcoil_vc8.vcproj  \
	libcoil_vc9.vcproj  \
	libcoil.vcproj.yaml

#------------------------------------------------------------
# vcproj file build rules
#------------------------------------------------------------
win32_builddir = .

vcproj: libcoil_vc8.vcproj libcoil_vc9.vcproj

libcoil_vc8.vcproj: libcoil.vcproj.yaml $(COIL_ALL)
	$(top_builddir)/build/vcprojtool.py vcproj \
		--type DLL \
		--vcversion "8.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/libcoil_vc8.vcproj \
		--yaml libcoil.vcproj.yaml \
		--source $(COIL_SRC) \
		--header $(COIL_H)
	qkc -sm $(win32_builddir)/libcoil_vc8.vcproj

libcoil_vc9.vcproj: libcoil.vcproj.yaml $(COIL_ALL)
	$(top_builddir)/build/vcprojtool.py vcproj \
		--type DLL \
		--vcversion "9.00" \
		--version $(COIL_VERSION) \
		--out $(win32_builddir)/libcoil_vc9.vcproj \
		--yaml libcoil.vcproj.yaml \
		--source $(COIL_SRC) \
		--header $(COIL_H)
	qkc -sm $(win32_builddir)/libcoil_vc9.vcproj

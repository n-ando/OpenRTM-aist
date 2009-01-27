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
	config_coil.h  \
	atomic.h       \
	File.h         \
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

config_coil.h:
	cp $(top_srcdir)/config_coil.h .

$(COIL_COMMON_SRC):
	cp $(top_srcdir)/config_coil.h .
	cp $(top_srcdir)/common/*.cpp .
	cp $(top_srcdir)/common/*.h .

$(COIL_COMMON_H):
	cp $(top_srcdir)/common/*.h .


coilheaderdir = $(prefix)/include/coil

coilheader_HEADERS = $(COIL_H)

lib_LTLIBRARIES = libcoil.la

libcoil_la_SOURCES =          \
	config_coil.h         \
	$(COIL_ALL)

clean-local:
	rm -f config_coil.h
	rm -f *~
	rm -f *.o *.lo *.loT
	rm -f $(COIL_COMMON_SRC) $(COIL_COMMON_H)
	chmod 644 *.cpp *.h

## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for coil (Component Object Infrastructure Layer)
##
## $Id$
##---------------------------------------------------------------------------

AM_CPPFLAGS=-I../ -I../../include

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
	File.h         \
	OS.h           \
	$(COIL_PLATFORM_SRC:.cpp=.h)

# coil common source
COIL_COMMON_SRC =       \
	PeriodicTask.cpp\
	Properties.cpp  \
	TimeValue.cpp   \
	TimeMeasure.cpp \
	Timer.cpp       \
	stringutil.cpp

# coil common headers
COIL_COMMON_H   =       \
	Async.h         \
	Listener.h      \
	TimeMeasure.h   \
	memory.h        \
	NonCopyable.h   \
	TimeValue.h     \
	stringutil.h    \
	Guard.h         \
	PeriodicTask.h  \
	Properties.h    \
	Timer.h         \
	Logger.h        \
	Singleton.h     \
	Factory.h

# coil all sources and headers
COIL_SRC = $(COIL_COMMON_SRC) $(COIL_PLATFORM_SRC)
COIL_H   = $(COIL_COMMON_H) $(COIL_PLATFORM_H)
COIL_ALL = $(COIL_SRC) $(COIL_H)

$(COIL_COMMON_SRC):
	cp $(top_srcdir)/common/*.cpp .
	cp $(top_srcdir)/common/*.h .

$(COIL_COMMON_H):
	cp $(top_srcdir)/common/*.h .


coilheaderdir = $(prefix)/include/coil

coilheader_HEADERS = $(COIL_H) $(top_srcdir)/include/coil/config_coil.h

#lib_LTLIBRARIES = libcoil.la
noinst_LTLIBRARIES = libcoil.la

libcoil_la_SOURCES =          \
	$(COIL_ALL)

clean-local:
	rm -f *~
	rm -f *.o *.lo *.loT
	rm -f $(COIL_COMMON_SRC) $(COIL_COMMON_H)
	chmod 644 *.cpp *.h

## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for external libraries
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

AM_CPPFLAGS= \
	-I$(top_srcdir)/src/ext/logger/fluentbit_stream/fluent-bit/include \
	-I$(top_srcdir)/src/ext/logger/fluentbit_stream/fluent-bit/lib/monkey/include \
	-I$(top_srcdir)/src/ext/logger/fluentbit_stream/fluent-bit/lib/mbedtls-2.5.1/include \
	-I$(top_srcdir)/src/ext/logger/fluentbit_stream/fluent-bit/lib/msgpack-2.1.3/include \
	-I$(top_srcdir)/src/ext/logger/fluentbit_stream/fluent-bit/lib/flb_libco \
	-I$(top_srcdir)/src/ext/logger/fluentbit_stream/fluent-bit/lib/jemalloc/include \
	-I$(top_srcdir)/src/ext/logger/fluentbit_stream/fluent-bit/lib/jsmn \
	-I$(top_srcdir)/src/ext/logger/fluentbit_stream/fluent-bit/lib/onigmo \
	-I$(top_srcdir)/src/ext/logger/fluentbit_stream/fluent-bit/lib/sha1 \
	-I$(top_srcdir)/src/ext/logger/fluentbit_stream/fluent-bit/lib/sqlite-amalgamation-3200000 \
	-I$(top_srcdir)/src/lib \
	-I$(top_srcdir)/src/lib/coil/include \
	-I$(top_srcdir)/src/lib/rtm/idl

AM_LDFLAGS= \
	-L$(top_builddir)/src/ext/logger/fluentbit_stream/fluent-bit/build/lib \
	-L$(top_builddir) \
	-L$(top_builddir)/src/lib/rtm \
	-L$(top_builddir)/src/lib/rtm/idl

FluentBit.cpp FluentBit.h: fluent-bit.h libfluent-bit.so
fluent-bit.h: fluent-bit-clone
libfluent-bit.so: fluent-bit-clone fluent-bit-build

fluent-bit-clone:
	@if test -d fluent-bit ;  then    \
		echo "fluent-bit pulling";    \
		(cd fluent-bit ; git pull);   \
	else                              \
		rm -rf fluent-bit;            \
		echo "fluent-bit cloneing";   \
		git clone --depth 1 -b v0.12.5 https://github.com/fluent/fluent-bit.git; \
	fi; 

fluent-bit-build: fluent-bit-clone
	mkdir -p fluent-bit/build
	( cd fluent-bit/build ; cmake .. -DCMAKE_INSTALL_PREFIX=/usr ; make )

fluent-bit-install: fluent-bit-build
	( cd fluent-bit/build; make install )

install-data-local: fluent-bit-install

#------------------------------------------------------------
# Targets
#------------------------------------------------------------
# Targets directories
moduledir = $(rtm_loggerdir)

module_LTLIBRARIES = FluentBit.la

FluentBit_la_SOURCES  = FluentBit.cpp FluentBit.h
FluentBit_la_LDFLAGS  = -module -shared -lfluent-bit \
	-L$(top_builddir)/src/ext/logger/fluentbit_stream/fluent-bit/build/lib
FluentBit_la_LIBADD   = \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

EXTRA_DIST = fluentbit.conf

clean-local:
	rm -rf *~ *.o *.so
	rm -rf fluent-bit

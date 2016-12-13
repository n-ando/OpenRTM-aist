## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for MyServiceProvider/MyServiceConsumer components
##
## $Id$
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.4

IDLC = @IDLC@
IDLFLAGS = @IDL_FLAGS@
LIBS = @LIBS@

AM_CPPFLAGS=-I$(top_srcdir) -I$(top_srcdir)/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/rtm -L$(top_builddir)/rtm/idl

SUFFIXES = .o .so .idl Skel.cpp Stub.cpp Stub.o Skel.o

WRAPPER  = $(top_builddir)/utils/rtm-skelwrapper/rtm-skelwrapper
WRAPPER_FLAGS = --include-dir="" --skel-suffix=Skel --stub-suffix=Stub

.idlSkel.cpp:
	$(IDLC) $(IDLFLAGS) MyService.idl
	PYTHONPATH=$(top_srcdir)/build:$(PYTHONPATH) \
	PATH=$(top_srcdir)/utils/rtm-config:$(PATH)  \
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=MyService.idl

.idlStub.cpp:
	$(IDLC) $(IDLFLAGS) MyService.idl
	PYTHONPATH=$(PYTHONPATH):$(top_srcdir)/build \
	PATH=$(top_srcdir)/utils/rtm-config:$(PATH)  \
	$(WRAPPER) $(WRAPPER_FLAGS) --idl-file=MyService.idl

IDL_SOURCES = MyService.idl

SKEL_OBJ = MyServiceSkel.o
STUB_OBJ = MyServiceStub.o
IMPL_OBJ = MyServiceSVC_impl.o

PROVIDER_SRC = \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	$(IDL_SOURCES:.idl=Stub.cpp) \
	MyServiceSVC_impl.cpp        \
	MyServiceProvider.cpp

PROVIDER_COMP_SRC = $(PROVIDER_SRC) MyServiceProviderComp.cpp

PROVIDER_H = \
	$(IDL_SOURCES:.idl=Skel.h) \
	$(IDL_SOURCES:.idl=Stub.h) \
	MyServiceSVC_impl.h        \
	MyServiceProvider.h

CONSUMER_SRC = \
	$(IDL_SOURCES:.idl=Skel.cpp) \
	$(IDL_SOURCES:.idl=Stub.cpp) \
	MyServiceConsumer.cpp

CONSUMER_COMP_SRC = $(CONSUMER_SRC) MyServiceConsumerComp.cpp

CONSUMER_H = \
	$(IDL_SOURCES:.idl=Skel.h) \
	$(IDL_SOURCES:.idl=Stub.h) \
	MyServiceConsumer.h


noinst_PROGRAMS = MyServiceConsumerComp MyServiceProviderComp

nodist_MyServiceProviderComp_SOURCES = $(PROVIDER_COMP_SRC)
MyServiceProviderComp_LDFLAGS = -L$(top_builddir)/rtm
MyServiceProviderComp_LDADD = -lRTC

nodist_MyServiceConsumerComp_SOURCES = $(CONSUMER_COMP_SRC)
MyServiceConsumerComp_LDFLAGS = -L$(top_builddir)/rtm
MyServiceConsumerComp_LDADD = -lRTC

EXTRA_DIST =                       \
	$(IDL_SOURCES)             \
	Makefile.MyServiceProvider \
	Makefile.MyServiceConsumer \
	README.MyServiceProvider   \
	README.MyServiceConsumer   \
	MyServiceSVC_impl.cpp      \
	MyServiceSVC_impl.h        \
	MyServiceProvider.h        \
	MyServiceProvider.cpp      \
	MyServiceProviderComp.cpp  \
	MyServiceConsumer.h        \
	MyServiceConsumer.cpp      \
	MyServiceConsumerComp.cpp  \
	gen.sh                     \
	rtc.conf

ALL_SRC = \
	$(PROVIDER_COMP_SRC) \
	$(CONSUMER_COMP_SRC)

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(ALL_SRC) > src.lst
	echo $(EXTRA_DIST) > other.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/examples/SimpleService

vcproj: vc8proj vc9proj

vc8proj: 
	$(top_builddir)/build/vcprojtool.py vcproj                   \
		--type EXE                                           \
		--vcversion "8.00"                                   \
		--projectname "MyServiceProviderComp"                \
		--version $(RTM_VERSION)                             \
		--out $(win32_builddir)/MyServiceProvider_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                            \
		--source $(PROVIDER_COMP_SRC)                        \
		--header $(PROVIDER_H)
	qkc -sm $(win32_builddir)/MyServiceProvider_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj                      \
		--type DLL                                              \
		--vcversion "8.00"                                      \
		--projectname "MyServiceProvider"                       \
		--version $(RTM_VERSION)                                \
		--out $(win32_builddir)/MyServiceProviderDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                            \
		--source $(PROVIDER_SRC)                                \
		--header $(PROVIDER_H)
	qkc -sm $(win32_builddir)/MyServiceProviderDll_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj                   \
		--type EXE                                           \
		--vcversion "8.00"                                   \
		--projectname "MyServiceConsumerComp"                \
		--version $(RTM_VERSION)                             \
		--out $(win32_builddir)/MyServiceConsumer_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                            \
		--source $(CONSUMER_COMP_SRC)                        \
		--header $(CONSUMER_H)
	qkc -sm $(win32_builddir)/MyServiceConsumer_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj                      \
		--type DLL                                              \
		--vcversion "8.00"                                      \
		--projectname "MyServiceConsumer"                       \
		--version $(RTM_VERSION)                                \
		--out $(win32_builddir)/MyServiceConsumerDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                            \
		--source $(CONSUMER_COMP_SRC)                           \
		--header $(CONSUMER_H)
	qkc -sm $(win32_builddir)/MyServiceConsumerDll_vc8.vcproj

vc9proj: 
	$(top_builddir)/build/vcprojtool.py vcproj                   \
		--type EXE                                           \
		--vcversion "9.00"                                   \
		--projectname "MyServiceProviderComp"                \
		--version $(RTM_VERSION)                             \
		--out $(win32_builddir)/MyServiceProvider_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                            \
		--source $(PROVIDER_COMP_SRC)                        \
		--header $(PROVIDER_H)
	qkc -sm $(win32_builddir)/MyServiceProvider_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj                      \
		--type DLL                                              \
		--vcversion "9.00"                                      \
		--projectname "MyServiceProvider"                       \
		--version $(RTM_VERSION)                                \
		--out $(win32_builddir)/MyServiceProviderDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                            \
		--source $(PROVIDER_SRC)                                \
		--header $(PROVIDER_H)
	qkc -sm $(win32_builddir)/MyServiceProviderDll_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj                   \
		--type EXE                                           \
		--vcversion "9.00"                                   \
		--projectname "MyServiceConsumerComp"                \
		--version $(RTM_VERSION)                             \
		--out $(win32_builddir)/MyServiceConsumer_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                            \
		--source $(CONSUMER_COMP_SRC)                        \
		--header $(CONSUMER_H)
	qkc -sm $(win32_builddir)/MyServiceConsumer_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj                      \
		--type DLL                                              \
		--vcversion "9.00"                                      \
		--projectname "MyServiceConsumer"                       \
		--version $(RTM_VERSION)                                \
		--out $(win32_builddir)/MyServiceConsumerDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                            \
		--source $(CONSUMER_COMP_SRC)                           \
		--header $(CONSUMER_H)
	qkc -sm $(win32_builddir)/MyServiceConsumerDll_vc9.vcproj

dist-hook: lst vcproj


clean_objs:
	rm -f $(OBJS) SimpleService.so SimpleServiceComp

clean_skelstub:
	rm -f *Skel.h *Skel.cpp
	rm -f *Stub.h *Stub.cpp
	rm -f *.hh *SK.cc

clean-local: clean_objs clean_skelstub
	rm -f \
	*.bak *.rpo *.sym lib*.*_pure_* *.lst \
	Makefile.old *core *~ *loT

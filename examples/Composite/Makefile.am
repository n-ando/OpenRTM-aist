## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for Motro components
##
## $Id: Makefile.am 849 2008-09-25 11:20:51Z n-ando $
##---------------------------------------------------------------------------

AUTOMAKE_OPTIONS = 1.9

AM_CPPFLAGS=-I$(top_srcdir)/src/lib -I$(top_srcdir)/src/lib/coil/include -I$(top_srcdir)/src/lib/rtm/idl
AM_LDFLAGS=-L$(top_builddir) -L$(top_builddir)/src/lib/rtm -L$(top_builddir)/src/lib/rtm/idl

#------------------------------------------------------------
# Targets
#------------------------------------------------------------
# Targets directories
exampledir = $(rtm_exampledir)
socompdir  = $(exampledir)/rtc
sourcedir  = $(exampledir)/src/Composite

# Loadable RTCs
socomp_LTLIBRARIES = Controller.la Motor.la Sensor.la

Controller_la_SOURCES = Controller.cpp Controller.h
Controller_la_LDFLAGS = -module
Controller_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Controller_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

Motor_la_SOURCES = Motor.cpp Motor.h
Motor_la_LDFLAGS = -module
Motor_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Motor_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

Sensor_la_SOURCES = Sensor.cpp Sensor.h
Sensor_la_LDFLAGS = -module
Sensor_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Sensor_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

# Standalone RTCs
example_PROGRAMS = ControllerComp MotorComp SensorComp Composite
example_DATA = rtc.conf composite.conf rtc.composite.linux.conf

ControllerComp_SOURCES = ControllerComp.cpp 
ControllerComp_DEPENDENCIES = Controller.la
ControllerComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
ControllerComp_LDADD   =  Controller.o \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

MotorComp_SOURCES = MotorComp.cpp 
MotorComp_DEPENDENCIES = Motor.la
MotorComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
MotorComp_LDADD   = Motor.o \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

SensorComp_SOURCES = SensorComp.cpp 
SensorComp_DEPENDENCIES = Sensor.la
SensorComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
SensorComp_LDADD   =  Sensor.o \
	$(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

Composite_SOURCES = Composite.cpp
Composite_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
Composite_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la \
	$(top_builddir)/src/lib/coil/lib/libcoil.la

# Example sources
source_DATA = $(ALL_SRC) $(EXTRA_DIST)

#------------------------------------------------------------
# Extra distributed files
#------------------------------------------------------------
EXTRA_DIST =                \
	gen_motor.sh        \
	gen_sensor.sh       \
	gen_controller.sh   \
	Makefile.Controller \
	Makefile.Motor      \
	Makefile.Sensor     \
	README.Controller   \
	README.Motor        \
	README.Sensor       \
	rtc.conf            \
	composite.conf      \
	rtc.composite.linux.conf

ALL_SRC =                  \
	ControllerComp.cpp \
	Controller.cpp     \
	Controller.h       \
	MotorComp.cpp      \
	Motor.cpp          \
	Motor.h            \
	SensorComp.cpp     \
	Sensor.cpp         \
	Sensor.h           \
	Composite.cpp

#------------------------------------------------------------
# File list for deb/ports packages
#------------------------------------------------------------
lst:
	echo $(ALL_SRC) > src.lst
	echo $(EXTRA_DIST) > other.lst

#------------------------------------------------------------
# Visual Studio Project
#------------------------------------------------------------
win32_builddir=$(top_builddir)/win32/OpenRTM-aist/examples/Composite

vcproj: vc9proj vcxproj

vc9proj:
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "9.00"                           \
		--projectname "ControllerComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Controller_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Controller.cpp ControllerComp.cpp     \
		--header Controller.h
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "Controller"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/ControllerDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Controller.cpp                          \
		--header Controller.h

	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "9.00"                           \
		--projectname "MotorComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Motor_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Motor.cpp MotorComp.cpp     \
		--header Motor.h
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "Motor"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/MotorDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Motor.cpp                          \
		--header Motor.h

	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "9.00"                           \
		--projectname "SensorComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Sensor_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Sensor.cpp SensorComp.cpp     \
		--header Sensor.h
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "Sensor"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/SensorDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Sensor.cpp                          \
		--header Sensor.h
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "9.00"                           \
		--projectname "Composite"                    \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Composite_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Composite.cpp

vcxproj:
	for ver in $(VC_VERSION); do \
		$(top_builddir)/build/vcxprojtool.py vcxproj           \
			--type EXE                                   \
			--vcversion "$${ver}.00"                           \
			--projectname "ControllerComp"                \
			--version $(RTM_VERSION)                     \
			--out $(win32_builddir)/Controller_vc$${ver}.vcxproj \
			--yaml ../rtc.vcproj.yaml                    \
			--source Controller.cpp ControllerComp.cpp     \
			--header Controller.h ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj              \
			--type DLL                                      \
			--vcversion "$${ver}.00"                              \
			--projectname "Controller"                       \
			--version $(RTM_VERSION)                        \
			--out $(win32_builddir)/ControllerDll_vc$${ver}.vcxproj \
			--yaml ../rtcdll.vcproj.yaml                    \
			--source Controller.cpp                          \
			--header Controller.h ; \
		\
		$(top_builddir)/build/vcxprojtool.py vcxproj           \
			--type EXE                                   \
			--vcversion "$${ver}.00"                           \
			--projectname "MotorComp"                \
			--version $(RTM_VERSION)                     \
			--out $(win32_builddir)/Motor_vc$${ver}.vcxproj \
			--yaml ../rtc.vcproj.yaml                    \
			--source Motor.cpp MotorComp.cpp     \
			--header Motor.h ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj              \
			--type DLL                                      \
			--vcversion "$${ver}.00"                              \
			--projectname "Motor"                       \
			--version $(RTM_VERSION)                        \
			--out $(win32_builddir)/MotorDll_vc$${ver}.vcxproj \
			--yaml ../rtcdll.vcproj.yaml                    \
			--source Motor.cpp                          \
			--header Motor.h ; \
		\
		$(top_builddir)/build/vcxprojtool.py vcxproj           \
			--type EXE                                   \
			--vcversion "$${ver}.00"                           \
			--projectname "SensorComp"                \
			--version $(RTM_VERSION)                     \
			--out $(win32_builddir)/Sensor_vc$${ver}.vcxproj \
			--yaml ../rtc.vcproj.yaml                    \
			--source Sensor.cpp SensorComp.cpp     \
			--header Sensor.h ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj              \
			--type DLL                                      \
			--vcversion "$${ver}.00"                              \
			--projectname "Sensor"                       \
			--version $(RTM_VERSION)                        \
			--out $(win32_builddir)/SensorDll_vc$${ver}.vcxproj \
			--yaml ../rtcdll.vcproj.yaml                    \
			--source Sensor.cpp                          \
			--header Sensor.h ; \
		$(top_builddir)/build/vcxprojtool.py vcxproj           \
			--type EXE                                   \
			--vcversion "$${ver}.00"                           \
			--projectname "Composite"                    \
			--version $(RTM_VERSION)                     \
			--out $(win32_builddir)/Composite_vc$${ver}.vcxproj \
			--yaml ../rtc.vcproj.yaml                    \
			--source Composite.cpp ; \
	done

dist-hook: lst vcproj

clean-local:
	rm -f \
	*.bak *.rpo *.sym lib*.*_pure_* *.lst \
	Makefile.old *core *~ *.so *.log

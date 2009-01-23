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
exampledir = $(pkgdatadir)/examples
socompdir  = $(exampledir)/rtcs
sourcedir  = $(exampledir)/src/Composite

# Loadable RTCs
socomp_LTLIBRARIES = Controller.la Motor.la Sensor.la

Controller_la_SOURCES = Controller.cpp Controller.h
Controller_la_LDFLAGS = -module
Controller_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Controller_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la

Motor_la_SOURCES = Motor.cpp Motor.h
Motor_la_LDFLAGS = -module
Motor_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Motor_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la

Sensor_la_SOURCES = Sensor.cpp Sensor.h
Sensor_la_LDFLAGS = -module
Sensor_la_FLAGS   = -L$(top_builddir)/src/lib/rtm/.lib
Sensor_la_LIBADD  = $(top_builddir)/src/lib/rtm/libRTC.la

# Standalone RTCs
example_PROGRAMS = ControllerComp MotorComp SensorComp Composite
example_DATA = rtc.conf composite.conf

ControllerComp_SOURCES = ControllerComp.cpp 
ControllerComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
ControllerComp_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la Controller.o

MotorComp_SOURCES = MotorComp.cpp 
MotorComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
MotorComp_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la Motor.o

SensorComp_SOURCES = SensorComp.cpp 
SensorComp_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
SensorComp_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la Sensor.o

Composite_SOURCES = Composite.cpp
Composite_LDFLAGS = -L$(top_builddir)/src/lib/rtm/.libs
Composite_LDADD   = $(top_builddir)/src/lib/rtm/libRTC.la

# Example sources
source_DATA = $(ALL_SRC) $(EXTRA_DIST)

#------------------------------------------------------------
# Extra distributed files
#------------------------------------------------------------
EXTRA_DIST =                \
	gen_motor.sh              \
	gen_sensor.sh              \
	gen_controller.sh              \
	Makefile.Controller  \
	Makefile.Motor  \
	Makefile.Sensor  \
	README.Controller    \
	README.Motor    \
	README.Sensor    \
	rtc.conf            \
	composite.conf

ALL_SRC =                  \
	ControllerComp.cpp  \
	Controller.cpp      \
	Controller.h        \
	MotorComp.cpp  \
	Motor.cpp      \
	Motor.h        \
	SensorComp.cpp  \
	Sensor.cpp      \
	Sensor.h        \
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

vcproj: vc8proj vc9proj

vc8proj: 
	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "8.00"                           \
		--projectname "ControllerComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Controller_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Controller.cpp ControllerComp.cpp     \
		--header Controller.h
	qkc -sm $(win32_builddir)/Controller_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "8.00"                              \
		--projectname "Controller"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/ControllerDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Controller.cpp                          \
		--header Controller.h
	qkc -sm $(win32_builddir)/ControllerDll_vc8.vcproj

	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "8.00"                           \
		--projectname "MotorComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Motor_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Motor.cpp MotorComp.cpp     \
		--header Motor.h
	qkc -sm $(win32_builddir)/Motor_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "8.00"                              \
		--projectname "Motor"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/MotorDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Motor.cpp                          \
		--header Motor.h
	qkc -sm $(win32_builddir)/MotorDll_vc8.vcproj

	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "8.00"                           \
		--projectname "SensorComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Sensor_vc8.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Sensor.cpp SensorComp.cpp     \
		--header Sensor.h
	qkc -sm $(win32_builddir)/Sensor_vc8.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "8.00"                              \
		--projectname "Sensor"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/SensorDll_vc8.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Sensor.cpp                          \
		--header Sensor.h
	qkc -sm $(win32_builddir)/SensorDll_vc8.vcproj

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
	qkc -sm $(win32_builddir)/Controller_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "Controller"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/ControllerDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Controller.cpp                          \
		--header Controller.h
	qkc -sm $(win32_builddir)/ControllerDll_vc9.vcproj

	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "9.00"                           \
		--projectname "MotorComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Motor_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Motor.cpp MotorComp.cpp     \
		--header Motor.h
	qkc -sm $(win32_builddir)/Motor_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "Motor"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/MotorDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Motor.cpp                          \
		--header Motor.h
	qkc -sm $(win32_builddir)/MotorDll_vc9.vcproj

	$(top_builddir)/build/vcprojtool.py vcproj           \
		--type EXE                                   \
		--vcversion "9.00"                           \
		--projectname "SensorComp"                \
		--version $(RTM_VERSION)                     \
		--out $(win32_builddir)/Sensor_vc9.vcproj \
		--yaml ../rtc.vcproj.yaml                    \
		--source Sensor.cpp SensorComp.cpp     \
		--header Sensor.h
	qkc -sm $(win32_builddir)/Sensor_vc9.vcproj
	$(top_builddir)/build/vcprojtool.py vcproj              \
		--type DLL                                      \
		--vcversion "9.00"                              \
		--projectname "Sensor"                       \
		--version $(RTM_VERSION)                        \
		--out $(win32_builddir)/SensorDll_vc9.vcproj \
		--yaml ../rtcdll.vcproj.yaml                    \
		--source Sensor.cpp                          \
		--header Sensor.h
	qkc -sm $(win32_builddir)/SensorDll_vc9.vcproj

dist-hook: lst vcproj

clean-local:
	rm -f \
	*.bak *.rpo *.sym lib*.*_pure_* *.lst \
	Makefile.old *core *~ *.so *.log

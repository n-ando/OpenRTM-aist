## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/USBCamera
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf USBCameraAcquire USBCameraAcquireComp
	rm -rf USBCameraMonitor USBCameraMonitorComp
	rm -rf *.vcproj *.user *.ncb *.suo *.sln *.lst
	rm -rf rtm_config.vsprops


vcproj: vc8proj vc9proj

vc8proj: USBCameraAcquireComp_vc8.vcproj USBCameraAcquire_vc8.vcproj \
	USBCameraMonitorComp_vc8.vcproj USBCameraMonitor_vc8.vcproj

vc9proj: USBCameraAcquireComp_vc9.vcproj USBCameraAcquire_vc9.vcproj\
	USBCameraMonitorComp_vc9.vcproj USBCameraMonitor_vc9.vcproj

USBCameraAcquireComp_vc8.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                        \
		--type RTCEXE                                           \
		--vcversion "8.00"                                      \
		--projectname "USBCameraAcquireComp"                    \
		--version $(RTM_VERSION)                                \
		--out USBCameraAcquireComp_vc8.vcproj                   \
		--source USBCameraAcquire.cpp USBCameraAcquireComp.cpp  \
		--header USBCameraAcquire.h
	qkc -sm USBCameraAcquireComp_vc8.vcproj
USBCameraAcquire_vc8.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                 \
		--type RTCDLL                                    \
		--vcversion "8.00"                               \
		--projectname "USBCameraAcquire"                 \
		--version $(RTM_VERSION)                         \
		--out USBCameraAcquire_vc8.vcproj                \
		--source USBCameraAcquire.cpp                    \
		--header USBCameraAcquire.h
	qkc -sm USBCameraAcquire_vc8.vcproj
USBCameraMonitorComp_vc8.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                        \
		--type RTCEXE                                           \
		--vcversion "8.00"                                      \
		--projectname "USBCameraMonitorComp"                    \
		--version $(RTM_VERSION)                                \
		--out USBCameraMonitorComp_vc8.vcproj                   \
		--source USBCameraMonitor.cpp USBCameraMonitorComp.cpp  \
		--header USBCameraMonitor.h
	qkc -sm USBCameraMonitorComp_vc8.vcproj
USBCameraMonitor_vc8.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                 \
		--type RTCDLL                                    \
		--vcversion "8.00"                               \
		--projectname "USBCameraMonitor"                 \
		--version $(RTM_VERSION)                         \
		--out USBCameraMonitor_vc8.vcproj                \
		--source USBCameraMonitor.cpp                    \
		--header USBCameraMonitor.h
	qkc -sm USBCameraMonitor_vc8.vcproj

USBCameraAcquireComp_vc9.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                        \
		--type RTCEXE                                           \
		--vcversion "9.00"                                      \
		--projectname "USBCameraAcquireComp"                    \
		--version $(RTM_VERSION)                                \
		--out USBCameraAcquireComp_vc9.vcproj                   \
		--source USBCameraAcquire.cpp USBCameraAcquireComp.cpp  \
		--header USBCameraAcquire.h
	qkc -sm USBCameraAcquireComp_vc9.vcproj
USBCameraAcquire_vc9.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                 \
		--type RTCDLL                                    \
		--vcversion "9.00"                               \
		--projectname "USBCameraAcquire"                 \
		--version $(RTM_VERSION)                         \
		--out USBCameraAcquire_vc9.vcproj                \
		--source USBCameraAcquire.cpp                    \
		--header USBCameraAcquire.h
	qkc -sm USBCameraAcquire_vc9.vcproj
USBCameraMonitorComp_vc9.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                       \
		--type RTCEXE                                          \
		--vcversion "9.00"                                     \
		--projectname "USBCameraMonitorComp"                   \
		--version $(RTM_VERSION)                               \
		--out USBCameraMonitorComp_vc9.vcproj                  \
		--source USBCameraMonitor.cpp USBCameraMonitorComp.cpp \
		--header USBCameraMonitor.h
	qkc -sm USBCameraMonitorComp_vc9.vcproj
USBCameraMonitor_vc9.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                 \
		--type RTCDLL                                    \
		--vcversion "9.00"                               \
		--projectname "USBCameraMonitor"                 \
		--version $(RTM_VERSION)                         \
		--out USBCameraMonitor_vc9.vcproj                \
		--source USBCameraMonitor.cpp                    \
		--header USBCameraMonitor.h
	qkc -sm USBCameraMonitor_vc9.vcproj

sln: USBCamera_vc8.sln USBCamera_vc9.sln

USBCamera_vc8.sln: vc8proj
	$(top_srcdir)/build/slntool.py  \
		--vcversion VC8         \
		--out USBCamera_vc8.sln \
		`find ./ -name '*_vc8.vcproj'`
	qkc -ms USBCamera_vc8.sln

USBCamera_vc9.sln: vc9proj
	$(top_srcdir)/build/slntool.py  \
		--vcversion VC9         \
		--out USBCamera_vc9.sln \
		`find ./ -name '*_vc9.vcproj'`
	qkc -ms USBCamera_vc9.sln

rtm_config.vsprops:
	cp ../../rtm_config.vsprops .

dist-hook: vcproj sln lst

EXTRA_DIST =                             \
	rtm_config.vsprops               \
	user_config.vsprops              \
	USBCameraAcquire.cpp             \
	USBCameraAcquire.h               \
	USBCameraAcquireComp.cpp         \
	USBCameraMonitor.cpp             \
	USBCameraMonitor.h               \
	USBCameraMonitorComp.cpp         \
	USBCameraAcquire_vc8.vcproj      \
	USBCameraAcquireComp_vc8.vcproj  \
	USBCameraAcquire_vc9.vcproj      \
	USBCameraAcquireComp_vc9.vcproj  \
	USBCameraMonitor_vc8.vcproj      \
	USBCameraMonitorComp_vc8.vcproj  \
	USBCameraMonitor_vc9.vcproj      \
	USBCameraMonitorComp_vc9.vcproj  \
	USBCamera_vc8.sln                \
	USBCamera_vc9.sln                \
	rtc.conf

lst:
	echo $(EXTRA_DIST) > src.lst


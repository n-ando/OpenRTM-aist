## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/USBCamera
##
## $Id$
##---------------------------------------------------------------------------
clean-local:
	rm -rf USBCameraAcquire USBCameraAcquireComp
	rm -rf USBCameraMonitor USBCameraMonitorComp
	rm -rf *.vcproj *.user *.ncb *.suo *.sln *.lst *.vcxproj


vcproj: vc9proj vc10proj

vc9proj: USBCameraAcquireComp_vc9.vcproj USBCameraAcquire_vc9.vcproj\
	USBCameraMonitorComp_vc9.vcproj USBCameraMonitor_vc9.vcproj

vc10proj: USBCameraAcquireComp_vc10.vcxproj USBCameraAcquire_vc10.vcxproj\
	USBCameraMonitorComp_vc10.vcxproj USBCameraMonitor_vc10.vcxproj

USBCameraAcquireComp_vc9.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                        \
		--type RTCEXE                                           \
		--vcversion "9.00"                                      \
		--projectname "USBCameraAcquireComp"                    \
		--version $(RTM_VERSION)                                \
		--out USBCameraAcquireComp_vc9.vcproj                   \
		--source USBCameraAcquire.cpp USBCameraAcquireComp.cpp  \
		--header USBCameraAcquire.h
USBCameraAcquire_vc9.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                 \
		--type RTCDLL                                    \
		--vcversion "9.00"                               \
		--projectname "USBCameraAcquire"                 \
		--version $(RTM_VERSION)                         \
		--out USBCameraAcquire_vc9.vcproj                \
		--source USBCameraAcquire.cpp                    \
		--header USBCameraAcquire.h
USBCameraMonitorComp_vc9.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                       \
		--type RTCEXE                                          \
		--vcversion "9.00"                                     \
		--projectname "USBCameraMonitorComp"                   \
		--version $(RTM_VERSION)                               \
		--out USBCameraMonitorComp_vc9.vcproj                  \
		--source USBCameraMonitor.cpp USBCameraMonitorComp.cpp \
		--header USBCameraMonitor.h
USBCameraMonitor_vc9.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                 \
		--type RTCDLL                                    \
		--vcversion "9.00"                               \
		--projectname "USBCameraMonitor"                 \
		--version $(RTM_VERSION)                         \
		--out USBCameraMonitor_vc9.vcproj                \
		--source USBCameraMonitor.cpp                    \
		--header USBCameraMonitor.h

USBCameraAcquireComp_vc10.vcxproj:
	$(top_srcdir)/build/vcxprojtool.py vcxproj                        \
		--type RTCEXE                                           \
		--vcversion "10.00"                                      \
		--projectname "USBCameraAcquireComp"                    \
		--version $(RTM_VERSION)                                \
		--out USBCameraAcquireComp_vc10.vcxproj                   \
		--source USBCameraAcquire.cpp USBCameraAcquireComp.cpp  \
		--header USBCameraAcquire.h
USBCameraAcquire_vc10.vcxproj:
	$(top_srcdir)/build/vcxprojtool.py vcxproj                 \
		--type RTCDLL                                    \
		--vcversion "10.00"                               \
		--projectname "USBCameraAcquire"                 \
		--version $(RTM_VERSION)                         \
		--out USBCameraAcquire_vc10.vcxproj                \
		--source USBCameraAcquire.cpp                    \
		--header USBCameraAcquire.h
USBCameraMonitorComp_vc10.vcxproj:
	$(top_srcdir)/build/vcxprojtool.py vcxproj                       \
		--type RTCEXE                                          \
		--vcversion "10.00"                                     \
		--projectname "USBCameraMonitorComp"                   \
		--version $(RTM_VERSION)                               \
		--out USBCameraMonitorComp_vc10.vcxproj                  \
		--source USBCameraMonitor.cpp USBCameraMonitorComp.cpp \
		--header USBCameraMonitor.h
USBCameraMonitor_vc10.vcxproj:
	$(top_srcdir)/build/vcxprojtool.py vcxproj                 \
		--type RTCDLL                                    \
		--vcversion "10.00"                               \
		--projectname "USBCameraMonitor"                 \
		--version $(RTM_VERSION)                         \
		--out USBCameraMonitor_vc10.vcxproj                \
		--source USBCameraMonitor.cpp                    \
		--header USBCameraMonitor.h

sln: USBCamera_vc9.sln USBCamera_vc10.sln

USBCamera_vc9.sln: vc9proj
	$(top_srcdir)/build/slntool.py  \
		--vcversion VC9         \
		--out USBCamera_vc9.sln \
		`find ./ -name '*_vc9.vcproj'`

USBCamera_vc10.sln: vc10proj
	$(top_srcdir)/build/slntool.py  \
		--vcversion VC10         \
		--out USBCamera_vc10.sln \
		`find ./ -name '*_vc10.vcxproj'`

dist-hook: vcproj sln lst

EXTRA_DIST =                             \
	user_config.vsprops              \
	USBCameraAcquire.cpp             \
	USBCameraAcquire.h               \
	USBCameraAcquireComp.cpp         \
	USBCameraMonitor.cpp             \
	USBCameraMonitor.h               \
	USBCameraMonitorComp.cpp         \
	USBCameraAcquire_vc9.vcproj      \
	USBCameraAcquireComp_vc9.vcproj  \
	USBCameraAcquire_vc10.vcxproj      \
	USBCameraAcquireComp_vc10.vcxproj  \
	USBCameraMonitor_vc9.vcproj      \
	USBCameraMonitorComp_vc9.vcproj  \
	USBCameraMonitor_vc10.vcxproj      \
	USBCameraMonitorComp_vc10.vcxproj  \
	USBCamera_vc9.sln                \
	USBCamera_vc10.sln                \
	rtc.conf

lst:
	echo $(EXTRA_DIST) > src.lst


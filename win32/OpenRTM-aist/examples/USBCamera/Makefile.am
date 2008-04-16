## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/USBCamera
##
## $Id$
##
## $Log: not supported by cvs2svn $
## Revision 1.1.2.1  2007/07/22 13:48:06  n-ando
## *** empty log message ***
##
##---------------------------------------------------------------------------
clean-local:
	rm -rf USBCameraAcquire USBCameraAcquireComp
	rm -rf USBCameraMonitor USBCameraMonitorComp
	rm -rf *.vcproj *.user *.ncb *.suo


vcproj: vc8proj vc9proj

vc8proj: USBCameraAcquireComp_vc8.vcproj USBCameraAcquire_vc8.vcproj \
	USBCameraMonitorComp_vc8.vcproj USBCameraMonitor_vc8.vcproj

vc9proj: USBCameraAcquireComp_vc9.vcproj USBCameraAcquire_vc9.vcproj\
	USBCameraMonitorComp_vc9.vcproj USBCameraMonitor_vc9.vcproj

USBCameraAcquireComp_vc8.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                        \
		--type EXE                                              \
		--vcversion "8.00"                                      \
		--projectname "USBCameraAcquireComp"                    \
		--version $(RTM_VERSION)                                \
		--out USBCameraAcquireComp_vc8.vcproj                   \
		--yaml $(top_srcdir)/examples/rtc.vcproj.yaml           \
		--source USBCameraAcquire.cpp USBCameraAcquireComp.cpp  \
		--header USBCameraAcquire.h
	qkc -sm USBCameraAcquireComp_vc8.vcproj
USBCameraAcquire_vc8.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                 \
		--type DLL                                       \
		--vcversion "8.00"                               \
		--projectname "USBCameraAcquire"                 \
		--version $(RTM_VERSION)                         \
		--out USBCameraAcquire_vc8.vcproj                \
		--yaml $(top_srcdir)/examples/rtcdll.vcproj.yaml \
		--source USBCameraAcquire.cpp                    \
		--header USBCameraAcquire.h
	qkc -sm USBCameraAcquire_vc8.vcproj
USBCameraMonitorComp_vc8.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                        \
		--type EXE                                              \
		--vcversion "8.00"                                      \
		--projectname "USBCameraMonitorComp"                    \
		--version $(RTM_VERSION)                                \
		--out USBCameraMonitorComp_vc8.vcproj                   \
		--yaml $(top_srcdir)/examples/rtc.vcproj.yaml           \
		--source USBCameraMonitor.cpp USBCameraMonitorComp.cpp  \
		--header USBCameraMonitor.h
	qkc -sm USBCameraMonitorComp_vc8.vcproj
USBCameraMonitor_vc8.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                 \
		--type DLL                                       \
		--vcversion "8.00"                               \
		--projectname "USBCameraMonitor"                 \
		--version $(RTM_VERSION)                         \
		--out USBCameraMonitor_vc8.vcproj                \
		--yaml $(top_srcdir)/examples/rtcdll.vcproj.yaml \
		--source USBCameraMonitor.cpp                    \
		--header USBCameraMonitor.h
	qkc -sm USBCameraMonitor_vc8.vcproj

USBCameraAcquireComp_vc9.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                        \
		--type EXE                                              \
		--vcversion "9.00"                                      \
		--projectname "USBCameraAcquireComp"                    \
		--version $(RTM_VERSION)                                \
		--out USBCameraAcquireComp_vc9.vcproj                   \
		--yaml $(top_srcdir)/examples/rtc.vcproj.yaml           \
		--source USBCameraAcquire.cpp USBCameraAcquireComp.cpp  \
		--header USBCameraAcquire.h
	qkc -sm USBCameraAcquireComp_vc9.vcproj
USBCameraAcquire_vc9.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                 \
		--type DLL                                       \
		--vcversion "9.00"                               \
		--projectname "USBCameraAcquire"                 \
		--version $(RTM_VERSION)                         \
		--out USBCameraAcquire_vc9.vcproj                \
		--yaml $(top_srcdir)/examples/rtcdll.vcproj.yaml \
		--source USBCameraAcquire.cpp                    \
		--header USBCameraAcquire.h
	qkc -sm USBCameraAcquire_vc9.vcproj
USBCameraMonitorComp_vc9.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                       \
		--type EXE                                             \
		--vcversion "9.00"                                     \
		--projectname "USBCameraMonitorComp"                   \
		--version $(RTM_VERSION)                               \
		--out USBCameraMonitorComp_vc9.vcproj                  \
		--yaml $(top_srcdir)/examples/rtc.vcproj.yaml          \
		--source USBCameraMonitor.cpp USBCameraMonitorComp.cpp \
		--header USBCameraMonitor.h
	qkc -sm USBCameraMonitorComp_vc9.vcproj
USBCameraMonitor_vc9.vcproj:
	$(top_srcdir)/build/vcprojtool.py vcproj                 \
		--type DLL                                       \
		--vcversion "9.00"                               \
		--projectname "USBCameraMonitor"                 \
		--version $(RTM_VERSION)                         \
		--out USBCameraMonitor_vc9.vcproj                \
		--yaml $(top_srcdir)/examples/rtcdll.vcproj.yaml \
		--source USBCameraMonitor.cpp                    \
		--header USBCameraMonitor.h
	qkc -sm USBCameraMonitor_vc9.vcproj

sln: USBCamera_vc8.sln USBCamera_vc9.sln

USBCamera_vc8.sln: vc8proj
	$(top_srcdir)/build/slntool.py \
		--out USBCamera_vc8.sln \
		`find ./ -name '*_vc8.vcproj'`
	qkc -ms USBCamera_vc8.sln

USBCamera_vc9.sln: vc9proj
	$(top_srcdir)/build/slntool.py \
		--out USBCamera_vc9.sln \
		`find ./ -name '*_vc9.vcproj'`
	qkc -ms USBCamera_vc9.sln


dist-hook: vcproj sln lst

EXTRA_DIST =                             \
	OpenRTM-aist.vsprops             \
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


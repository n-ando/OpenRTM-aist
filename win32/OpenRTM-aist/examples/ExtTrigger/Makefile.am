## -*- Makefile -*-
##---------------------------------------------------------------------------
## Makefile.am for win32/OpenRTM-aist/examples/ExtTrigger
##
## $Id: Makefile.am 2556 2014-04-09 17:05:15Z n-ando $
##---------------------------------------------------------------------------
clean-local:
	rm -rf Debug Release
	rm -rf *~ *.cpp *.h *.idl rtc.conf
	rm -rf *.vcproj *.vcxproj *.user *.ncb *.suo
	rm -rf ExtConnectorComp ExtConsoleIn ExtConsoleInComp ExtConsoleOut ExtConsoleOutComp

src:
	cp -p $(top_srcdir)/examples/ExtTrigger/*.cpp .
	cp -p $(top_srcdir)/examples/ExtTrigger/*.h .
	cp -p $(top_srcdir)/examples/ExtTrigger/rtc.conf .

dist-hook: src

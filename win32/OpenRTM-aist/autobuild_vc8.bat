@rem
@rem @brief Visual Studio automatic build script
@rem @date $Date: 2008-03-06 06:55:42 $
@rem @author Norkai Ando <n-ando@aist.go.jp>
@rem
@rem Copyright (C) 2008
@rem     Noriaki Ando
@rem     Task-intelligence Research Group,
@rem     Intelligent Systems Research Institute,
@rem     National Institute of
@rem         Advanced Industrial Science and Technology (AIST), Japan
@rem     All rights reserved.
@rem
@rem $Id: autobuild_vc8.bat,v 1.1.2.1 2008-03-06 06:55:42 n-ando Exp $
@rem

@rem $Log: not supported by cvs2svn $
@rem Revision 1.1.2.2  2008/02/09 20:01:28  n-ando
@rem For wix's wxs file generation.
@rem
@rem Revision 1.1.2.1  2008/01/25 10:53:30  n-ando
@rem Automatic build script for Visual Studio
@rem

@set RTM_ROOT=%~dp0
@set PATH=C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727;"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE";%PATH%

@rem ============================================================
@rem build OpenRTM-aist
@rem ============================================================

devenv.com OpenRTM-aist_vc8.sln /rebuild Release /projectconfig Release > build_release.log
devenv.com OpenRTM-aist_vc8.sln /rebuild Debug /projectconfig Debug > build_debug.log

@rem ============================================================
@rem build USBCamera examples
@rem ============================================================
devenv.com examples\USBCamera\USBCameraAcquire_vc8.vcproj /rebuild Release /projectconfig Release >> build.log
devenv.com examples\USBCamera\USBCameraMonitor_vc8.vcproj /rebuild Release /projectconfig Release >> build.log
devenv.com examples\USBCamera\USBCameraAcquire_vc8.vcproj /rebuild Debug /projectconfig Debug >> build.log
devenv.com examples\USBCamera\USBCameraMonitor_vc8.vcproj /rebuild Debug /projectconfig Debug >> build.log


cd installer
call autowix.cmd

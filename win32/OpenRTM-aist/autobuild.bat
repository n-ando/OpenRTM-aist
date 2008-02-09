@rem
@rem @brief Visual Studio automatic build script
@rem @date $Date: 2008-02-09 20:01:28 $
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
@rem $Id: autobuild.bat,v 1.1.2.2 2008-02-09 20:01:28 n-ando Exp $
@rem

@rem $Log: not supported by cvs2svn $
@rem Revision 1.1.2.1  2008/01/25 10:53:30  n-ando
@rem Automatic build script for Visual Studio
@rem

@set RTM_ROOT=%~dp0
@set PATH=C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727;"C:\Program Files\Microsoft Visual Studio 8\Common7\IDE";%PATH%

@rem ============================================================
@rem build OpenRTM-aist
@rem ============================================================

devenv.com OpenRTM-aist.sln /rebuild Release /projectconfig Release > build.log
devenv.com OpenRTM-aist.sln /rebuild Debug /projectconfig Debug >> build.log

@rem ============================================================
@rem build USBCamera examples
@rem ============================================================
devenv.com examples\USBCamera\USBCameraAcquire.vcproj /rebuild Release /projectconfig Release >> build.log
devenv.com examples\USBCamera\USBCameraMonitor.vcproj /rebuild Release /projectconfig Release >> build.log
devenv.com examples\USBCamera\USBCameraAcquire.vcproj /rebuild Debug /projectconfig Debug >> build.log
devenv.com examples\USBCamera\USBCameraMonitor.vcproj /rebuild Debug /projectconfig Debug >> build.log


cd installer
call autowix.cmd

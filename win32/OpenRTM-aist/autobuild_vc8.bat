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
@rem $Id$
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
devenv.com examples\USBCamera\USBCamera_vc8.sln /rebuild Release /projectconfig Release > USBCamera_build_release.log
devenv.com examples\USBCamera\USBCamera_vc8.sln /rebuild Debug /projectconfig Debug > USBCamera_build_debug.log

cd installer
call autowix.cmd
cd ..

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
@rem $Id: autobuild_vc8.bat 726 2008-05-14 03:05:42Z n-ando $
@rem

@set RTM_ROOT=%~dp0
@set PATH=C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727;"C:\Program Files\Microsoft Visual Studio 9.0\VC\vcpackages";%PATH%

@rem ============================================================
@rem rename and copy property sheet
@rem ============================================================
rename rtm_config.vsprops rtm_config_omni407.vsprops
rename rtm_config_omni412.vsprops rtm_config.vsprops
rename examples\USBCamera\rtm_config.vsprops rtm_config_omni407.vsprops
copy   rtm_config.vsprops examples\USBCamera\rtm_config.vsprops

@rem ============================================================
@rem build OpenRTM-aist
@rem ============================================================

vcbuild OpenRTM-aist_vc9.sln

@rem ============================================================
@rem build USBCamera examples
@rem ============================================================
vcbuild examples\USBCamera\USBCamera_vc8.sln

cd installer
call autowix.cmd
cd ..

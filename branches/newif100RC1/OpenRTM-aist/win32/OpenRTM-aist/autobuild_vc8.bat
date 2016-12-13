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
@set PATH="C:\Program Files\Microsoft Visual Studio 8\VC\vcpackages";%PATH%

@rem ============================================================
@rem copy property sheet
@rem ============================================================
copy   etc\rtm_config_omni407.vsprops rtm_config.vsprops
copy   etc\rtm_config_omni407.vsprops examples\USBCamera\rtm_config.vsprops
copy   coil_config.vsprops examples\USBCamera\coil_config.vsprops

@rem ============================================================
@rem build OpenRTM-aist
@rem ============================================================

vcbuild /rebuild OpenRTM-aist_vc8.sln

@rem ============================================================
@rem build USBCamera examples
@rem ============================================================
vcbuild /rebuild examples\USBCamera\USBCamera_vc8.sln

cd installer
call autowix.cmd
cd ..

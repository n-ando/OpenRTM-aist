@rem
@rem @brief Visual Studio automatic build script
@rem @date $Date: 2008-03-06 06:55:42 $
@rem @author Norkai Ando <n-ando@aist.go.jp>
@rem
@rem Copyright (C) 2008-2010
@rem     Noriaki Ando
@rem     Task-intelligence Research Group,
@rem     Intelligent Systems Research Institute,
@rem     National Institute of
@rem         Advanced Industrial Science and Technology (AIST), Japan
@rem     All rights reserved.
@rem
@rem $Id$
@rem

@rem ------------------------------------------------------------
@rem Notice:
@rem   omniORB should be under the following OMNI_ROOT directory.
@rem   RTSE should be under the following OMNI_ROOT directory.
@rem ------------------------------------------------------------
@set RTM_ROOT=%~dp0
@set PATH="C:\Program Files\Microsoft Visual Studio 8\VC\vcpackages";%PATH%
@set OMNI_ROOT=C:\distribution\omniORB-4.1.4_vc8
@set RTSE_ROOT=C:\distribution\OpenRTP\RTSystemEditor
@set VC_VERSION=Visual C++ 2005

@rem ============================================================
@rem copy property sheet
@rem ============================================================
copy   etc\rtm_config_omni414.vsprops rtm_config.vsprops
copy   etc\rtm_config_omni414.vsprops examples\USBCamera\rtm_config.vsprops
copy   coil_config.vsprops examples\USBCamera\coil_config.vsprops

@rem ============================================================
@rem build OpenRTM-aist
@rem ============================================================

vcbuild /M2 /rebuild OpenRTM-aist_vc8.sln

@rem ============================================================
@rem build USBCamera examples
@rem ============================================================
vcbuild /M2 /rebuild examples\USBCamera\USBCamera_vc8.sln

cd installer
call autowix.cmd
cd ..

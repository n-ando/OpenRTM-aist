@echo off
@rem ============================================================
@rem OpenRTM-aist for Windows build batch
@rem
@rem @author Noriaki Ando <n-ando@aist.go.jp>
@rem                Copyright (C) 2014 n-ando All Rights Reserved
@rem
@rem In order to compile OpenRTM-aist on Windows, this batch file can be
@rem used with the following prerequisite tools and environments.
@rem
@rem 0. 64bit Windows 7 or later
@rem   If you want to compile both 32 bit and 64 bit binaries on one OS,
@rem   64 bit OS is required.  Because the omniidl which is built as
@rem   target architecture executable in midstream is required to
@rem   compile omniORB itself. OS have to execute both (32 bit /64 bit)
@rem   executable.
@rem
@rem 1. Cygwin
@rem   cygwin-lite distributed from omniORB is not recommended.
@rem   The following command should be installed on Cygwin
@rem   wget, make, zip, svn
@rem
@rem 2. Visual C++
@rem   Currently VC2008, 2010, 2012, 2013 are supported.
@rem   Different versions in the same machine are not recommended.
@rem
@rem Environment vairables required
@rem
@rem OMNI_ROOT: omniORB binary installation dir
@rem ARCH: x86 or x86_64
@rem VC_VERSION: 9(=VC2008), 10(=VC2010), 11(=VC2012), 12(=VC2013),....
@rem PYTHON_DIR: /cygdrive/c/Python27
@rem
@rem ============================================================

set RTM_ROOT=%~dp0
set COIL_ROOT=%RTM_ROOT%\coil
set OMNI_ROOT=%RTM_ROOT%\omniORB
if not DEFINED ARCH       set ARCH=x86_64
if not DEFINED VC_VERSION set VC_VERSION=10
if not DEFINED PYTHON_DIR set PYTHON_DIR=c:\python27

@rem ------------------------------------------------------------
@rem Printing env variables
echo Environment variables:
echo OMNI_ROOT  : %OMNI_ROOT%
echo ARCH       : %ARCH%
echo VC_VERSION : %VC_VERSION%
echo PYTHON_DIR : %PYTHON_DIR%

set PATH_ORG=%PATH%
set PATH=%PATH%;C:\cygwin\bin;C:\cygwin64\bin
set PATH=%OMNI_ROOT%\bin\x86_win32;%PATH%

if %ARCH% == x86       set DLL_ARCH=
if %ARCH% == x86_64    set DLL_ARCH=_x64

set COIL_DLLVER=111_vc%VC_VERSION%%DLL_ARCH%
set COIL_VERSION=1.1.1
set COIL_SHORTVER=1.1

set RTM_DLLVER=111_vc%VC_VERSION%%DLL_ARCH%
set RTM_VERSION=1.1.1
set RTM_SHORTVER=1.1

set OMNI_DLLVER=417
set OMNI_VERSION=4.1.7
set OMNI_SHORTVER=4.1
set OMNITHREAD_DLLVER=34
set OMNITHREAD_VERSION=3.4

@rem ------------------------------------------------------------
@rem Copying Config.cmake
@rem ------------------------------------------------------------
%PYTHON_DIR%\python build\cmakeconfgen.py rtm_config.vsprops
move OpenRTMConfig.cmake cmake


@rem ============================================================
@rem  switching to x86 or x86_64
@rem ============================================================
echo ARCH %ARCH%
if %ARCH% == x86       goto x86
if %ARCH% == x86_64    goto x86_64
goto END

@rem ============================================================
@rem  Compiling 32bit binaries
@rem ============================================================
:x86
echo Compiling 32bit binaries
echo Setting up Visual C++ environment.
if %VC_VERSION% == 9  (
   call "C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86
   goto VCBUILDx86
   )
if %VC_VERSION% == 10 (
   call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat%" x86
   set VCTOOLSET=4.0
   set PLATFORMTOOL=
   goto MSBUILDx86
   )
if %VC_VERSION% == 11 (
   call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat" x86
   set VCTOOLSET=4.0
   set PLATFORMTOOL=/p:PlatformToolset=v110
   goto MSBUILDx86
   )
if %VC_VERSION% == 12 (
   call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86
   set VCTOOLSET=12.0
   set PLATFORMTOOL=/p:PlatformToolset=v120
   goto MSBUILDx86
   )

@rem ------------------------------------------------------------
@rem Build (VC2008 x86)
@rem ------------------------------------------------------------
:VCBUILDx86
echo Visual Studio Dir: %VSINSTALLDIR%
echo LIB: %LIB%
vcbuild /M2 /rebuild OpenRTM-aist_vc%VC_VERSION%.sln
goto END

@rem ------------------------------------------------------------
@rem Build (VC2010- x86)
@rem ------------------------------------------------------------
:MSBUILDx86
echo Visual Studio Dir: %VSINSTALLDIR%
echo LIB: %LIB%
set OPT=/M:4 /toolsversion:%VCTOOLSET% %PLATFORMTOOL% /p:platform=Win32
set SLN=OpenRTM-aist_vc%VC_VERSION%.sln
set LOG=/fileLogger /flp:logfile=debug.log /v:diag 

msbuild /t:clean /p:configuration=debug     %OPT% %SLN%
msbuild /t:rebuild /p:configuration=debug   %OPT% %LOG% %SLN%

msbuild /t:clean /p:configuration=release   %OPT% %SLN%
msbuild /t:rebuild /p:configuration=release %OPT% %LOG% %SLN%

goto END

@rem ============================================================
@rem  Compiling 64bit binaries
@rem ============================================================
:x86_64
echo Compiling 64bit binaries
@rem Setting up Visual C++ environment
if /i %VC_VERSION% == 9  (
   echo 64bit compilation on Visual C++ 2008 is not supported. Aborting.
   goto END
   )
if /i %VC_VERSION% == 10 (
   call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" amd64
   set VCTOOLSET=4.0
   set PLATFORMTOOL=
   goto MSBUILDx64
   )
if /i %VC_VERSION% == 11 (
   call "C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat" amd64
   set VCTOOLSET=4.0
   set PLATFORMTOOL=/p:PlatformToolset=v110
   goto MSBUILDx64
   )
if /i %VC_VERSION% == 12 (
   call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" amd64
   set VCTOOLSET=12.0
   set PLATFORMTOOL=/p:PlatformToolset=v120
   goto MSBUILDx64
   )
echo Visual Studio Dir: %VSINSTALLDIR%
echo LIB: %LIB%

@rem ------------------------------------------------------------
@rem Build (VC2008 x64)
@rem ------------------------------------------------------------
:VCBUILDx64
echo Visual Studio Dir: %VSINSTALLDIR%
echo LIB: %LIB%
vcbuild /M2 /rebuild OpenRTM-aist_vc%VC_VERSION%.sln
goto END

@rem ------------------------------------------------------------
@rem Build (VC2010- x64)
@rem ------------------------------------------------------------
:MSBUILDx64
echo Visual Studio Dir: %VSINSTALLDIR%
echo LIB: %LIB%
set OPT=/M:4 /toolsversion:%VCTOOLSET% %PLATFORMTOOL% /p:platform=x64
set SLN=OpenRTM-aist_vc%VC_VERSION%.sln
set LOG=/fileLogger /flp:logfile=debug.log /v:diag 

msbuild /t:clean /p:configuration=debug     %OPT% %SLN%
msbuild /t:rebuild /p:configuration=debug   %OPT% %LOG% %SLN%

msbuild /t:clean /p:configuration=release   %OPT% %SLN%
msbuild /t:rebuild /p:configuration=release %OPT% %LOG% %SLN%

goto END

:END
set PATH=%PATH_ORG%

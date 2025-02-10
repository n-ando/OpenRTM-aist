// -*- C++ -*-
/*!
 * @file rtcd.cpp
 * @brief RT component server daemon
 * @date $Date: 2005-05-12 09:06:19 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: rtcd.cpp 775 2008-07-28 16:14:45Z n-ando $
 *
 */

#include <iostream>
#include <rtm/Manager.h>

#if defined(RTM_OS_VXWORKS) && !defined(__RTP__)
int rtcd_main (char* arg1, char* arg2, char* arg3,
               char* arg4, char* arg5, char* arg6,
               char* arg7, char* arg8, char* arg9)
{
  int   argc     = 0;
  char* argv[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  argv[argc++] = "rtcd";
  if (arg1 != 0 && *arg1 != 0) argv[argc++] = arg1; else goto End_Args;
  if (arg2 != 0 && *arg2 != 0) argv[argc++] = arg2; else goto End_Args;
  if (arg3 != 0 && *arg3 != 0) argv[argc++] = arg3; else goto End_Args;
  if (arg4 != 0 && *arg4 != 0) argv[argc++] = arg4; else goto End_Args;
  if (arg5 != 0 && *arg5 != 0) argv[argc++] = arg5; else goto End_Args;
  if (arg6 != 0 && *arg6 != 0) argv[argc++] = arg6; else goto End_Args;
  if (arg7 != 0 && *arg7 != 0) argv[argc++] = arg7; else goto End_Args;
  if (arg8 != 0 && *arg8 != 0) argv[argc++] = arg8; else goto End_Args;
  if (arg9 != 0 && *arg9 != 0) argv[argc++] = arg9; else goto End_Args;

End_Args:
#else
int main (int argc, char** argv)
{
#endif

  RTC::Manager* manager;
  manager = RTC::Manager::init(argc, argv);

  manager->activateManager();
  manager->runManager();

  return 0;
}



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

#if defined(RTM_OS_VXWORKS) && not defined(__RTP__)
int rtcd_main (int argc, char** argv)
#else
int main (int argc, char** argv)
#endif
{
  RTC::Manager* manager;
  manager = RTC::Manager::init(argc, argv);

  manager->activateManager();

  manager->runManager();

  return 0;
}



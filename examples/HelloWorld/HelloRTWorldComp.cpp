// -*- C++ -*-
/*!
 * @file HelloRTWorldComp.h
 * @brief Hello RT world component
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * $Id$
 */



#include <rtm/RtcManager.h>
#include <string>
#include "HelloRTWorld.h"



#if defined(RTM_OS_VXWORKS) && not defined(__RTP__)
int hellortworld_main()
{
  RTC::Manager* manager = &RTC::Manager::instance();
  RTC::RtcBase* comp;
  HelloRTWorldInit(manager);
  std::string name;
  comp = manager->createComponent("HelloRTWorld", "example", name);
  if(comp)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
#else

void MyModuleInit(RtcManager* manager)
{
  HelloRTWorldInit(manager);

  std::string name;
  RtcBase* comp;
  comp = manager->createComponent("HelloRTWorld", "example", name);
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  comp->rtc_start();

}


int main (int argc, char** argv)
{
  RTM::RtcManager manager(argc, argv);
  // Initialize manager
  manager.initManager();
  // Activate manager and register to naming service
  manager.activateManager();
  // Initialize my module on this maneger
  manager.initModuleProc(MyModuleInit);
  // Main loop
  manager.runManager();
  return 0;
}

#endif


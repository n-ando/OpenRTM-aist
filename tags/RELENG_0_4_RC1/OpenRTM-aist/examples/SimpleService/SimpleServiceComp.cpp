// -*- C++ -*-
/*!
 * @file SimpleServiceComp.cpp
 * @brief Standalone component
 * @date $Date: 2005-09-08 13:04:42 $
 *
 * $Id: SimpleServiceComp.cpp,v 1.1 2005-09-08 13:04:42 n-ando Exp $
 */

#include <rtm/RtcManager.h>
#include <iostream>
#include <string>
#include "SimpleService.h"


void MyModuleInit(RtcManager* manager)
{
  SimpleServiceInit(manager);

  char* name;
  RTCBase_ptr comp;
  comp = manager->create_component("SimpleService", "Generic", name);
  manager->runManagerNoBlocking();
  std::cout << "RTComponent: " << name << " was created." << std::endl;

  MyService_ptr svc;
  svc = MyService::_narrow(comp->get_service("MySVC"));

  float gain;
  while (1)
	{
	  std::cout << "gain: ";
	  std::cin >> gain;
	  svc->setGain(gain);
	  std::cout << "Current gain = " << svc->getGain() << std::endl;
	}
  
  return;
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

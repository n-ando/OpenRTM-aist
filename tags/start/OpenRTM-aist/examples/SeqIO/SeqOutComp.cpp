// -*- C++ -*-
/*!
 * @file SeqOutComp.h
 * @brief SeqOut component
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * $Id: SeqOutComp.cpp,v 1.1.1.1 2005-05-12 09:06:20 n-ando Exp $
 */



#include <rtm/RtcManager.h>
#include <iostream>
#include <string>
#include "SeqOut.h"


void MyModuleInit(RtcManager* manager)
{
  SeqOutInit(manager);

  std::string name;
  RtcBase* comp;
  comp = manager->createComponent("SeqOut", "Generic", name);

  std::cout << "RTComponent: " << name << " was created." << std::endl;

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


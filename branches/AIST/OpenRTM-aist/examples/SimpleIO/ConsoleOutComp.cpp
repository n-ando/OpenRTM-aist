// -*- C++ -*-
/*!
 * @file ConsoleOutComp.cpp
 * @brief Stand alone component
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * Copyright (c) 2004 Noriaki Ando <n-ando@aist.go.jp>
 *          National Institute of Industrial Science (AIST),
 *          Japan. All rights reserved.
 *
 * $Id: ConsoleOutComp.cpp,v 1.1.1.1 2005-05-12 09:06:20 n-ando Exp $
 */

#include <iostream>
#include <string>
#include <RtcManager.h>
#include "ConsoleOut.h"

using namespace std;


void MyModuleInit(RtcManager* manager)
{
  ConsoleOutInit(manager);

  std::string name;
  RtcBase* comp;
  cout << "Creating a component: \"ConsoleOut\"....";
  comp = manager->createComponent("ConsoleOut", "example", name);
  /*
    if (CORBA::is_nil(comp))
	{
	cout << "failed." << endl;
	exit(1);
	}
  */
  cout << "succeed." << endl;
  cout << "Instance name is " << name << endl;

  RTCProfile_var prof;
  prof = comp->profile();
  cout << "=======================================================" << endl;
  cout << " Component Profile" << endl;
  cout << "-------------------------------------------------------" << endl;
  cout << "InstanceID:     " << prof->instance_id << endl;
  cout << "Implementation: " << prof->implementation_id << endl;
  cout << "Description:    " << prof->description << endl;
  cout << "Version:        " << prof->version << endl;
  cout << "Maker:          " << prof->maker << endl;
  cout << "Category:       " << prof->category << endl;
  cout << "CompType:       " << prof->component_type << endl;
  cout << "Category:       " << prof->activity_type << endl;
  cout << "MaxInst.:       " << prof->max_instance << endl;
  cout << "Lang:           " << prof->language << endl;
  cout << "LangType:       " << prof->language_type << endl;
  PortProfileList inpp = prof->inport_profile_list;
  PortProfileList outpp = prof->outport_profile_list;
  cout << "InPort:         " << inpp.length() << endl;
  cout << "OutPort:        " << outpp.length() << endl;
  cout << "=======================================================" << endl;
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


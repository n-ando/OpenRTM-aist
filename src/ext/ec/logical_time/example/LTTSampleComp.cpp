// -*- C++ -*-
/*!
 * @file LTTSampleComp.cpp
 * @brief Standalone component
 * @date $Date: 2008-01-14 07:45:55 $
 *
 * $Id: LTTSampleComp.cpp 778 2008-07-29 04:59:25Z n-ando $
 */

#include <rtm/Manager.h>
#include <iostream>
#include <string>
#include "LTTSample.h"
#include <rtm/NVUtil.h>
#include <LogicalTimeTriggeredECStub.h>


void MyModuleInit(RTC::Manager* manager)
{
  LTTSampleInit(manager);
  RTC::RtcBase* comp;

  // Create a component
  std::cout << "Creating a component: \"LTTSample\"....";
  comp = manager->createComponent("LTTSample");
  std::cout << "succeed." << std::endl;
  RTC::ExecutionContextList_var eclist = comp->get_owned_contexts();
  if ( eclist->length() > 0) {
      eclist[0]->start();
      RTC::RTObject_var rtobj = comp->getObjRef();
      eclist[0]->activate_component(rtobj.in());
  }
  else {
      std::cerr << "No owned EC." << std::endl;
  }
  RTC::ComponentProfile_var prof;
  prof = comp->get_component_profile();
  std::cout << "=================================================" << std::endl;
  std::cout << " Component Profile" << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;
  std::cout << "InstanceID:     " << prof->instance_name << std::endl;
  std::cout << "Implementation: " << prof->type_name << std::endl;
  std::cout << "Description:    " << prof->description << std::endl;
  std::cout << "Version:        " << prof->version << std::endl;
  std::cout << "Maker:          " << prof->vendor << std::endl;
  std::cout << "Category:       " << prof->category << std::endl;
  std::cout << "  Other properties   " << std::endl;
  NVUtil::dump(prof->properties);
  std::cout << "=================================================" << std::endl;

  PortServiceList_var portlist;
  portlist = comp->get_ports();

  for (CORBA::ULong i(0), n(portlist->length()); i < n; ++i)
    {
      PortService_var port;
      port = PortService::_duplicate(portlist[i]);
      RTC::PortProfile_var portprof = port->get_port_profile();
      std::cout << "================================================="
                << std::endl;
      std::cout << "Port" << i << " (name): ";
      std::cout << portprof->name << std::endl;
      std::cout << "-------------------------------------------------"
                << std::endl;
      RTC::PortInterfaceProfileList iflist;
      iflist = portprof->interfaces;
      for (CORBA::ULong i(0), n(iflist.length()); i < n; ++i)
        {
          std::cout << "I/F name: ";
          std::cout << iflist[i].instance_name << std::endl;
          std::cout << "I/F type: ";
          std::cout << iflist[i].type_name << std::endl;
          const char* pol;
          pol = iflist[i].polarity == 0 ? "PROVIDED" : "REQUIRED";
          std::cout << "Polarity: " << pol << std::endl;
        }
      std::cout << "- properties -" << std::endl;
      NVUtil::dump(portprof->properties);
      std::cout << "-------------------------------------------------"
                << std::endl;
    }
  return;
}


int main (int argc, char** argv)
{
  std::cout << "Usage:" << std::endl;
  std::cout << argv[0] << " [--standalone]" << std::endl;
  std::cout << std::endl;
  std::cout << "    --standalone: send tick to the EC internally" << std::endl;

  bool standalone(false);
  for (int i(0); i < argc; ++i)
    {
      if (std::string("--standalone") == argv[i])
        {
          standalone = true;
        }
    }
  RTC::Manager* manager;
  if (standalone)
    {
      manager = RTC::Manager::init(0, 0);
    }
  else
    {
      manager = RTC::Manager::init(argc, argv);
    }

  // Set module initialization proceduer
  // This procedure will be invoked in activateManager() function.
  manager->setModuleInitProc(MyModuleInit);

  // Activate manager and register to naming service
  manager->activateManager();

  // run the manager in blocking mode
  // runManager(false) is the default.
  manager->runManager(standalone);

  // If you want to run the manager in non-blocking mode, do like this
  // manager->runManager(true);

  RTC::RTObject_impl* rtobj = manager->getComponent("LTTSample0");
  if (rtobj == NULL)
    {
      std::cerr << "rtobj is NULL" << std::endl;
      abort();
    }
  RTC::ExecutionContextList_var eclist = rtobj->get_owned_contexts();
  std::cout << "EC list: " << eclist->length() <<std::endl;

  if (CORBA::is_nil(eclist[0]))
    {
      std::cerr << "EC is nil" << std::endl;
      abort();
    }

  OpenRTM::LogicalTimeTriggeredEC_var ttlec;
  ttlec = OpenRTM::LogicalTimeTriggeredEC::_narrow(eclist[0]);
  if (CORBA::is_nil(ttlec))
    {
      std::cerr << "TTL EC is nil" << std::endl;
      abort();
    }
  for (size_t i(0); i < 100; ++i)
    {
      std::cout << "sending a tick (time: " << i;
      std::cout << " [s], " << i * 1000 << " [usec])" << std::endl;
      ttlec->tick(i, i * 1000);
      CORBA::ULong sec, usec;
      ttlec->get_time(sec, usec);
      std::cout << "getting time   (time: " << sec;
      std::cout << " [s], " << usec << " [usec])" << std::endl;
      std::cout << std::endl;
      std::this_thread::sleep_for(std::chrono::millisecconds(500));
    }
  manager->shutdown();
  return 0;
}

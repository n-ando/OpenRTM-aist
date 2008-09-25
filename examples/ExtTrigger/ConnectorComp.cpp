// -*- C++ -*-
/*!
 * @file ConnectorComp.cpp
 * @brief connector application
 * @date $Date: 2008-01-13 07:24:05 $
 *
 * Copyright (c) 2003-2007 Noriaki Ando <n-ando@aist.go.jp>
 *          Task-intelligence Research Group,
 *          Intelligent System Research Institute,
 *          National Institute of Industrial Science (AIST), Japan
 *          All rights reserved.
 *
 * $Id$
 */

#include <iostream>
#include <vector>
#include <string>
#include <rtm_corba/idl/OpenRTMSkel.h>
#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/NVUtil.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/CorbaConsumer.h>
#include <assert.h>


using namespace RTC;

void usage()
{
  std::cout << std::endl;
  std::cout << "usage: ConnectorComp [options]" << std::endl;
  std::cout << std::endl;
  std::cout << "  --flush         ";
  std::cout << ": Set subscription type Flush" << std::endl;
  std::cout << "  --new           ";
  std::cout << ": Set subscription type New" << std::endl;
  std::cout << "  --periodic [Hz] ";
  std::cout << ": Set subscription type Periodic" << std::endl;	
  std::cout << std::endl;
}

int main (int argc, char** argv)
{
  int _argc(0);
  char** _argv(0);

  std::string subs_type;
  std::string period;
  for (int i = 1; i < argc; ++i)
    {
      std::string arg(argv[i]);
      if (arg == "--flush")         subs_type = "Flush";
      else if (arg == "--new")      subs_type = "New";
      else if (arg == "--periodic")
	{
	  subs_type = "Periodic";
	  if (++i < argc) period = argv[i];
	  else            period = "1.0";
	}
      else if (arg == "--help")
	{
	  usage();
	  exit(1);
	}
      else
	{
	  subs_type = "Flush";
	}
    }
  
  std::cout << "Subscription Type: " << subs_type << std::endl;
  if (period != "")
    std::cout << "Period: " << period << " [Hz]" << std::endl;


  CORBA::ORB_var orb = CORBA::ORB_init(_argc, _argv);
  CorbaNaming naming(orb, "localhost:9876");

  CorbaConsumer<RTObject> conin, conout;
  CorbaConsumer<OpenRTM::ExtTrigExecutionContextService> ec0, ec1;

  PortServiceList_var pin;
  PortServiceList_var pout;

  // find ConsoleIn0 component
  conin.setObject(naming.resolve("ConsoleIn0.rtc"));

  // get ports
  pin = conin->get_ports();
  pin[(CORBA::ULong)0]->disconnect_all();
  assert(pin->length() > 0);
  // activate ConsoleIn0
  ExecutionContextList_var eclisti;
  eclisti = conin->get_owned_contexts();
  eclisti[(CORBA::ULong)0]->activate_component(RTObject::_duplicate(conin._ptr()));
  ec0.setObject(eclisti[(CORBA::ULong)0]);

  // find ConsoleOut0 component
  conout.setObject(naming.resolve("ConsoleOut0.rtc"));
  // get ports
  pout = conout->get_ports();
  pout[(CORBA::ULong)0]->disconnect_all();
  assert(pout->length() > 0);
  // activate ConsoleOut0
  ExecutionContextList_var eclisto;
  eclisto = conout->get_owned_contexts();
  eclisto[(CORBA::ULong)0]->activate_component(RTObject::_duplicate(conout._ptr()));
  ec1.setObject(eclisto[(CORBA::ULong)0]);

  // connect ports
  ConnectorProfile prof;
  prof.connector_id = "";
  prof.name = CORBA::string_dup("connector0");
  prof.ports.length(2);
  prof.ports[0] = pin[(CORBA::ULong)0];
  prof.ports[1] = pout[(CORBA::ULong)0];
  CORBA_SeqUtil::push_back(prof.properties,
			   NVUtil::newNV("dataport.interface_type",
					 "CORBA_Any"));
  CORBA_SeqUtil::push_back(prof.properties,
			   NVUtil::newNV("dataport.dataflow_type",
					 "Push"));
  CORBA_SeqUtil::push_back(prof.properties,
			   NVUtil::newNV("dataport.subscription_type",
					 subs_type.c_str()));
  if (period != "")
  CORBA_SeqUtil::push_back(prof.properties,
			   NVUtil::newNV("dataport.push_interval",
					 period.c_str()));
  ReturnCode_t ret;
  ret = pin[(CORBA::ULong)0]->connect(prof);
  assert(ret == RTC::RTC_OK);

  std::cout << "Connector ID: " << prof.connector_id << std::endl;
  NVUtil::dump(prof.properties);

  std::string cmd;
  while (1)
    {
      try
	{
	  std::cout << std::endl;
	  std::cout << std::endl;
	  std::cout << "0: tick ConsoleIn component" << std::endl;
	  std::cout << "1: tick ConsoleOut component" << std::endl;
	  std::cout << "2: tick both components" << std::endl;
	  std::cout << "cmd? >";
	  std::cin >> cmd;
	  if (cmd == "0")
	    {
	      ec0->tick();
	    }
	  else if (cmd == "1")
	    {
	      ec1->tick();
	    }
	  else if (cmd == "2")
	    {
	      ec0->tick();
	      ec1->tick();
	    }
	}
      catch (...)
	{
	}
    }
  orb->destroy();
  exit(1);
}


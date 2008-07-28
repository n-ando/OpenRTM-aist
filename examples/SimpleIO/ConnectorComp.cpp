// -*- C++ -*-
/*!
 * @file ConnectorComp.cpp
 * @brief connector application
 * @date $Date: 2008-01-13 07:24:08 $
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
  PortList_var pin;
  PortList_var pout;

  // find ConsoleIn0 component
  conin.setObject(naming.resolve("ConsoleIn0.rtc"));

  // get ports
  pin = conin->get_ports();
  pin[(CORBA::ULong)0]->disconnect_all();
  assert(pin->length() > 0);
  // activate ConsoleIn0
  ExecutionContextServiceList_var eclisti;
  eclisti = conin->get_execution_context_services();
  eclisti[(CORBA::ULong)0]->activate_component(RTObject::_duplicate(conin._ptr()));

  // find ConsoleOut0 component
  conout.setObject(naming.resolve("ConsoleOut0.rtc"));
  // get ports
  pout = conout->get_ports();
  pout[(CORBA::ULong)0]->disconnect_all();
  assert(pout->length() > 0);
  // activate ConsoleOut0
  ExecutionContextServiceList_var eclisto;
  eclisto = conout->get_execution_context_services();
  eclisto[(CORBA::ULong)0]->activate_component(RTObject::_duplicate(conout._ptr()));

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

  orb->destroy();
  exit(1);
}


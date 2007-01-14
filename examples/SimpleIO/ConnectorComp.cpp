// -*- C++ -*-
/*!
 * @file ConnectorComp.cpp
 * @brief connector application
 * @date $Date: 2007-01-14 22:51:36 $
 *
 * Copyright (c) 2003 Noriaki Ando <n-ando@aist.go.jp>
 *          Task-intelligence Research Group,
 *          Intelligent System Research Institute,
 *          National Institute of Industrial Science (AIST), Japan
 *          All rights reserved.
 *
 * $Id: ConnectorComp.cpp,v 1.3 2007-01-14 22:51:36 n-ando Exp $
 */

#include <iostream>
#include <vector>
#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/NVUtil.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/CorbaConsumer.h>
#include <assert.h>


using namespace RTC;

int main (int argc, char** argv)
{
  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
  CorbaNaming naming(orb, "localhost:9876");
  std::cout << "hoge" << std::endl;
  CorbaConsumer<RTObject> conin, conout;
  PortList* pin;
  PortList* pout;

  // find ConsoleIn0 component
  conin.setObject(naming.resolve("ConsoleIn0.rtc"));
  // get ports
  pin = conin->get_ports();
  assert(pin->length() > 0);
  // activate ConsoleIn0
  ExecutionContextServiceList* eclisti;
  eclisti = conin->get_execution_context_services();
  (*eclisti)[0]->activate_component(RTObject::_duplicate(conin._ptr()));


  // find ConsoleOut0 component
  conout.setObject(naming.resolve("ConsoleOut0.rtc"));
  // get ports
  pout = conout->get_ports();
  assert(pout->length() > 0);
  // activate ConsoleOut0
  ExecutionContextServiceList* eclisto;
  eclisto = conout->get_execution_context_services();
  (*eclisto)[0]->activate_component(RTObject::_duplicate(conout._ptr()));

  // connect ports
  ConnectorProfile prof;
  prof.connector_id = "";
  prof.name = CORBA::string_dup("connector0");
  prof.ports.length(2);
  prof.ports[0] = (*pin)[0];
  prof.ports[1] = (*pout)[0];
  CORBA_SeqUtil::push_back(prof.properties,
			   NVUtil::newNV("dataport.interface_type",
					 "CORBA_Any"));
  CORBA_SeqUtil::push_back(prof.properties,
			   NVUtil::newNV("dataport.dataflow_type",
					 "Push"));
  CORBA_SeqUtil::push_back(prof.properties,
			   NVUtil::newNV("dataport.subscription_type",
					 "Flush"));
  ReturnCode_t ret;
  ret = (*pin)[0]->connect(prof);
  assert(ret == RTC::OK);

  std::cout << "Connector ID: " << prof.connector_id << std::endl;
  NVUtil::dump(prof.properties);

  orb->destroy();
  return 0;
}


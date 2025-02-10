// -*- C++ -*-
/*!
 * @file  ConsoleIn.cpp
 * @brief Console input component
 * $Date: 2007-04-13 14:59:11 $
 *
 * $Id$
 */

#include "ConsoleIn.h"
#include <iostream>

// Module specification
// <rtc-template block="module_spec">
static const char* const consolein_spec[] =
  {
    "implementation_id", "ConsoleIn",
    "type_name",         "ConsoleIn",
    "description",       "Console input component",
    "version",           "1.0",
    "vendor",            "Noriaki Ando, AIST",
    "category",          "example",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "10",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

ConsoleIn::ConsoleIn(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    // <rtc-template block="initializer">
    m_outOut("out", m_out)
    // </rtc-template>
{
}

ConsoleIn::~ConsoleIn() = default;


RTC::ReturnCode_t ConsoleIn::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("out", m_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  return RTC::RTC_OK;
}

RTC::ReturnCode_t ConsoleIn::onExecute(RTC::UniqueId  /*ec_id*/)
{
  std::cout << "Please input number: ";
  std::cin >> m_out.data;

  if(std::cin.fail())
  {
      std::cin.clear();
      std::cin.ignore(1024, '\n');
      return RTC::RTC_ERROR;
  }
  
  std::cout << "Sending to subscriber: " << m_out.data << std::endl;
  m_outOut.write();

  return RTC::RTC_OK;
}


extern "C"
{
 
  void ConsoleInInit(RTC::Manager* manager)
  {
    coil::Properties profile(consolein_spec);
    manager->registerFactory(profile,
                             RTC::Create<ConsoleIn>,
                             RTC::Delete<ConsoleIn>);
  }
  
}



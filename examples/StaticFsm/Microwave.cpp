// -*- C++ -*-
/*!
 * @file  Microwave.cpp
 * @brief Microwave oven FSM sample component
 * $Date$
 *
 * $Id$
 */

#include "Microwave.h"

// Module specification
// <rtc-template block="module_spec">
static const char* consoleout_spec[] =
  {
    "implementation_id", "Microwave",
    "type_name",         "Microwave",
    "description",       "Console output component",
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

Microwave::Microwave(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    // <rtc-template block="initializer">
    m_fsm(this),
    m_eventIn("event", m_fsm)
    // </rtc-template>
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

}

Microwave::~Microwave()
{
}


RTC::ReturnCode_t Microwave::onInitialize()
{
  addInPort("event", m_eventIn);

  m_eventIn.bindEvent("open",   &MicrowaveFsm::Top::open);
  m_eventIn.bindEvent("close",  &MicrowaveFsm::Top::close);
  m_eventIn.bindEvent("minute", &MicrowaveFsm::Top::minute);
  m_eventIn.bindEvent("start",  &MicrowaveFsm::Top::start);
  m_eventIn.bindEvent("stop",   &MicrowaveFsm::Top::stop);
  m_eventIn.bindEvent("tick",   &MicrowaveFsm::Top::tick);

 return RTC::RTC_OK;
}

RTC::ReturnCode_t Microwave::onExecute(RTC::UniqueId ec_id)
{
  coil::usleep(1000000);

  return RTC::RTC_OK;
}

extern "C"
{
  void MicrowaveInit(RTC::Manager* manager)
  {
    coil::Properties profile(consoleout_spec);
    manager->registerFactory(profile,
                             RTC::Create<Microwave>,
                             RTC::Delete<Microwave>);
  }
};



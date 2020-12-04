// -*- C++ -*-
/*!
 * @file  Display.cpp
 * @brief Display oven FSM sample component
 * $Date$
 *
 * $Id$
 */

#include "Display.h"

// Module specification
// <rtc-template block="module_spec">
static const char* const display_spec[] =
  {
    "implementation_id", "Display",
    "type_name",         "Display",
    "description",       "Display component for Microwave example",
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

Display::Display(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    // <rtc-template block="initializer">
    m_inIn("in", m_in)
    
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

Display::~Display() = default;


RTC::ReturnCode_t Display::onInitialize()
{
  addInPort("in", m_inIn);
 
  m_inIn.addConnectorDataListener(ConnectorDataListenerType::ON_BUFFER_WRITE,
                                    new DataListener("ON_BUFFER_WRITE"));
  m_inIn.addConnectorDataListener(ConnectorDataListenerType::ON_BUFFER_FULL, 
                                    new DataListener("ON_BUFFER_FULL"));
  m_inIn.addConnectorDataListener(ConnectorDataListenerType::ON_BUFFER_WRITE_TIMEOUT, 
                                    new DataListener("ON_BUFFER_WRITE_TIMEOUT"));
  m_inIn.addConnectorDataListener(ConnectorDataListenerType::ON_BUFFER_OVERWRITE, 
                                    new DataListener("ON_BUFFER_OVERWRITE"));
  m_inIn.addConnectorDataListener(ConnectorDataListenerType::ON_BUFFER_READ, 
                                    new DataListener("ON_BUFFER_READ"));
  m_inIn.addConnectorDataListener(ConnectorDataListenerType::ON_SEND, 
                                    new DataListener("ON_SEND"));
  m_inIn.addConnectorDataListener(ConnectorDataListenerType::ON_RECEIVED,
                                    new DataListener("ON_RECEIVED"));
  m_inIn.addConnectorDataListener(ConnectorDataListenerType::ON_RECEIVER_FULL, 
                                    new DataListener("ON_RECEIVER_FULL"));
  m_inIn.addConnectorDataListener(ConnectorDataListenerType::ON_RECEIVER_TIMEOUT, 
                                    new DataListener("ON_RECEIVER_TIMEOUT"));

  m_inIn.addConnectorListener(ConnectorListenerType::ON_BUFFER_EMPTY,
                                    new ConnListener("ON_BUFFER_EMPTY"));
  m_inIn.addConnectorListener(ConnectorListenerType::ON_BUFFER_READ_TIMEOUT,
                                    new ConnListener("ON_BUFFER_READ_TIMEOUT"));
  m_inIn.addConnectorListener(ConnectorListenerType::ON_SENDER_EMPTY,
                                    new ConnListener("ON_SENDER_EMPTY"));
  m_inIn.addConnectorListener(ConnectorListenerType::ON_SENDER_TIMEOUT,
                                    new ConnListener("ON_SENDER_TIMEOUT"));
  m_inIn.addConnectorListener(ConnectorListenerType::ON_SENDER_ERROR,
                                    new ConnListener("ON_SENDER_ERROR"));
  m_inIn.addConnectorListener(ConnectorListenerType::ON_CONNECT,
                                    new ConnListener("ON_CONNECT"));
  m_inIn.addConnectorListener(ConnectorListenerType::ON_DISCONNECT,
                                    new ConnListener("ON_DISCONNECT"));


 return RTC::RTC_OK;
}

RTC::ReturnCode_t Display::onExecute(RTC::UniqueId  /*ec_id*/)
{
  if (m_inIn.isNew())
    {
      m_inIn.read();
      std::cout << "Received: " << m_in.data << std::endl;
      std::cout << "TimeStamp: " << m_in.tm.sec << "[s] ";
      std::cout << m_in.tm.nsec << "[ns]" << std::endl;
    }
  std::this_thread::sleep_for(std::chrono::milliseconds(1));

  return RTC::RTC_OK;
}

extern "C"
{
  void DisplayInit(RTC::Manager* manager)
  {
    coil::Properties profile(display_spec);
    manager->registerFactory(profile,
                             RTC::Create<Display>,
                             RTC::Delete<Display>);
  }
}



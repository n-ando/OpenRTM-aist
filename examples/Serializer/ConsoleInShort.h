// -*- C++ -*-
/*!
 * @file  ConsoleInShort.h
 * @brief Console input component
 * @date  $Date: 2019-06-25 04:55:01 $
 *
 * $Id$
 */

#ifndef CONSOLEINSHORT_H
#define CONSOLEINSHORT_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/ConnectorListener.h>

#include <iostream>
// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;


class DataListener
  : public ConnectorDataListenerT<RTC::TimedShort>
{
  USE_CONNLISTENER_STATUS;
public:
  DataListener(const char* name) : m_name(name) {}
  ~DataListener() override
  {
    std::cout << "dtor of " << m_name << std::endl;
  }

  ReturnCode operator()(ConnectorInfo& info,
                                TimedShort& data) override
  {
    std::cout << "------------------------------"   << std::endl;
    std::cout << "Data Listener: " << m_name       << std::endl;
    std::cout << "Profile::name: " << info.name    << std::endl;
    std::cout << "Profile::id:   " << info.id      << std::endl;
//    std::cout << "Profile::properties: "            << std::endl;
//    std::cout << info.properties;
//    std::cout                                       << std::endl;
    std::cout << "Data:          " << data.data    << std::endl;
    std::cout << "------------------------------"   << std::endl;
    return NO_CHANGE;
  }
  std::string m_name;
};


class ConnListener
  : public ConnectorListener
{
  USE_CONNLISTENER_STATUS;
public:
  ConnListener(const char* name) : m_name(name) {}
  ~ConnListener() override
  {
    std::cout << "dtor of " << m_name << std::endl;
  }

  ReturnCode operator()(ConnectorInfo& info) override
  {
    std::cout << "------------------------------"   << std::endl;
    std::cout << "Connector Listener: " << m_name       << std::endl;
    std::cout << "Profile::name:      " << info.name    << std::endl;
    std::cout << "Profile::id:        " << info.id      << std::endl;
    std::cout << "Profile::properties: "            << std::endl;
    std::cout << info.properties;
    std::cout                                       << std::endl;
    std::cout << "------------------------------"   << std::endl;
    return NO_CHANGE;
  }
  std::string m_name;
};


class ConsoleInShort
  : public RTC::DataFlowComponentBase
{
 public:
  ConsoleInShort(RTC::Manager* manager);
  ~ConsoleInShort() override;

  RTC::ReturnCode_t onInitialize() override;
  RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id) override;

 protected:
  TimedShort m_out;
  OutPort<TimedShort> m_outOut;

 private:

};


extern "C"
{
  DLL_EXPORT void ConsoleInShortInit(RTC::Manager* manager);
}

#endif // CONSOLEINSHORT_H


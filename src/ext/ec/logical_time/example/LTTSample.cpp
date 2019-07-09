// -*- C++ -*-
/*!
 * @file  LTTSample.cpp
 * @brief Console input component
 * $Date: 2007-04-13 14:59:11 $
 *
 * $Id: LTTSample.cpp 1661 2010-01-15 09:12:51Z kurihara $
 */

#include "LTTSample.h"
#include <iostream>
#include <iomanip>
// Module specification
// <rtc-template block="module_spec">
static const char* const consolein_spec[] =
  {
    "implementation_id", "LTTSample",
    "type_name",         "LTTSample",
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

LTTSample::LTTSample(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    m_clock(coil::ClockManager::instance().getClock("logical"))
    // <rtc-template block="initializer">
    // </rtc-template>
{
}

LTTSample::~LTTSample()
{
}


RTC::ReturnCode_t LTTSample::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  return RTC::RTC_OK;
}

RTC::ReturnCode_t LTTSample::onExecute(RTC::UniqueId ec_id)
{
  std::cout.setf(std::ios_base::fixed,std::ios_base::floatfield);
  std::cout << std::setprecision(6);
  std::cout << "Current time (in onExecute()): " << std::setw(10) << m_clock.gettime() << std::endl;
  return RTC::RTC_OK;
}


extern "C"
{
 
  void LTTSampleInit(RTC::Manager* manager)
  {
    coil::Properties profile(consolein_spec);
    manager->registerFactory(profile,
                             RTC::Create<LTTSample>,
                             RTC::Delete<LTTSample>);
  }
  
};



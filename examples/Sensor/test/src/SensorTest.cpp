// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  SensorTest.cpp
 * @brief Sensor component (test code)
 *
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 */
// </rtc-template>

#include "SensorTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* const sensor_spec[] =
  {
    "implementation_id", "SensorTest",
    "type_name",         "SensorTest",
    "description",       "Sensor component",
    "version",           "2.0.0",
    "vendor",            "AIST",
    "category",          "example",
    "activity_type",     "SPORADIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "10",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SensorTest::SensorTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inOut("in", m_in),
    m_outIn("out", m_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SensorTest::~SensorTest()
{
}



RTC::ReturnCode_t SensorTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("out", m_outIn);
  
  // Set OutPort buffer
  addOutPort("in", m_inOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SensorTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t SensorTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SensorTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SensorTest::onActivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SensorTest::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t SensorTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t SensorTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SensorTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SensorTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SensorTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SensorTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool SensorTest::runTest()
{
    return true;
}


extern "C"
{
 
  void SensorTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(sensor_spec);
    manager->registerFactory(profile,
                             RTC::Create<SensorTest>,
                             RTC::Delete<SensorTest>);
  }
  
}

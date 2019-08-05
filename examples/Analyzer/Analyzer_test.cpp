// -*- C++ -*-
/*!
 * @file  Analyzer_test.cpp
 * @brief Clock Analyzer test
 * @date $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * $Id$
 */

#include "Analyzer_test.h"

// Module specification
// <rtc-template block="module_spec">
static const char* const analyzer_test_spec[] =
  {
    "implementation_id", "Analyzer_test",
    "type_name",         "Analyzer_test",
    "description",       "Clock Analyzer test",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Test",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.sleep_time", "0.1",

    // Widget
    "conf.__widget__.sleep_time", "text",
    // Constraints

    "conf.__type__.sleep_time", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Analyzer_test::Analyzer_test(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in),
    m_outOut("out", m_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Analyzer_test::~Analyzer_test() = default;



RTC::ReturnCode_t Analyzer_test::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  
  // Set OutPort buffer
  addOutPort("out", m_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("sleep_time", m_sleep_time, "0.1");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Analyzer_test::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer_test::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer_test::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer_test::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer_test::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Analyzer_test::onExecute(RTC::UniqueId  /*ec_id*/)
{
	if (m_inIn.isNew())
	{
		auto start = std::chrono::system_clock::now();
		m_inIn.read();
		m_out = m_in;
		std::this_thread::sleep_until(start + m_sleep_time);
		
		m_outOut.write();
	}
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Analyzer_test::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer_test::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer_test::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer_test::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer_test::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void Analyzer_testInit(RTC::Manager* manager)
  {
    coil::Properties profile(analyzer_test_spec);
    manager->registerFactory(profile,
                             RTC::Create<Analyzer_test>,
                             RTC::Delete<Analyzer_test>);
  }
  
}


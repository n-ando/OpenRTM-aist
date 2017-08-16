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
static const char* analyzer_test_spec[] =
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
Analyzer_test::~Analyzer_test()
{
}



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


RTC::ReturnCode_t Analyzer_test::onExecute(RTC::UniqueId ec_id)
{
	if (m_inIn.isNew())
	{
		coil::TimeValue start(coil::gettimeofday());
		//coil::TimeValue start1(coil::gettimeofday());
		m_inIn.read();
		//std::cout << "Analyzer_test: " << &m_in << std::endl;
		//coil::TimeValue start2(coil::gettimeofday());
		m_out = m_in;
		//coil::TimeValue start3(coil::gettimeofday());
		//coil::sleep(coil::TimeValue(m_sleep_time));
		//coil::TimeValue end(coil::gettimeofday());
		//std::cout << double(end-start1) << "\t" << double(end-start2) << "\t" << double(end-start3) << std::endl;
		coil::TimeValue end(coil::gettimeofday());
		double diff = (double)(end - start);
		//std::cout << "Analyzer_test: " << m_sleep_time - diff << std::endl;
		if(diff < m_sleep_time)
		{
			coil::sleep(coil::TimeValue(m_sleep_time - diff));
		}
		//std::cout << "Analyzer_test: " << m_sleep_time - (double)(end - start) << std::endl;
		
		//std::cout << double(start3-start2) << std::endl;
		m_outOut.write();
		//std::cout << "Analyzer_test" << std::endl;
		//std::cout << "Analyzer_test: " << m_out.tm.sec << "\t" << m_out.tm.nsec << std::endl;
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
  
};



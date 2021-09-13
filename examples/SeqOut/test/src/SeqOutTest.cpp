// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  SeqOutTest.cpp
 * @brief Sequence OutPort component (test code)
 *
 */
// </rtc-template>

#include "SeqOutTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* const seqout_spec[] =
  {
    "implementation_id", "SeqOutTest",
    "type_name",         "SeqOutTest",
    "description",       "Sequence OutPort component",
    "version",           "2.0.0",
    "vendor",            "AIST",
    "category",          "example",
    "activity_type",     "PERIODIC",
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
SeqOutTest::SeqOutTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_OctetIn("Octet", m_Octet),
    m_ShortIn("Short", m_Short),
    m_LongIn("Long", m_Long),
    m_FloatIn("Float", m_Float),
    m_DoubleIn("Double", m_Double),
    m_OctetSeqIn("OctetSeq", m_OctetSeq),
    m_ShortSeqIn("ShortSeq", m_ShortSeq),
    m_LongSeqIn("LongSeq", m_LongSeq),
    m_FloatSeqIn("FloatSeq", m_FloatSeq),
    m_DoubleSeqIn("DoubleSeq", m_DoubleSeq)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SeqOutTest::~SeqOutTest()
{
}



RTC::ReturnCode_t SeqOutTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("Octet", m_OctetIn);
  addInPort("Short", m_ShortIn);
  addInPort("Long", m_LongIn);
  addInPort("Float", m_FloatIn);
  addInPort("Double", m_DoubleIn);
  addInPort("OctetSeq", m_OctetSeqIn);
  addInPort("ShortSeq", m_ShortSeqIn);
  addInPort("LongSeq", m_LongSeqIn);
  addInPort("FloatSeq", m_FloatSeqIn);
  addInPort("DoubleSeq", m_DoubleSeqIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SeqOutTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t SeqOutTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqOutTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqOutTest::onActivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqOutTest::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t SeqOutTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t SeqOutTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqOutTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqOutTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqOutTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqOutTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool SeqOutTest::runTest()
{
    return true;
}


extern "C"
{
 
  void SeqOutTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(seqout_spec);
    manager->registerFactory(profile,
                             RTC::Create<SeqOutTest>,
                             RTC::Delete<SeqOutTest>);
  }
  
}

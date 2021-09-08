// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  SeqInTest.cpp
 * @brief Sequence InPort component (test code)
 *
 */
// </rtc-template>

#include "SeqInTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* const seqin_spec[] =
  {
    "implementation_id", "SeqInTest",
    "type_name",         "SeqInTest",
    "description",       "Sequence InPort component",
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
SeqInTest::SeqInTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_OctetOut("Octet", m_Octet),
    m_ShortOut("Short", m_Short),
    m_LongOut("Long", m_Long),
    m_FloatOut("Float", m_Float),
    m_DoubleOut("Double", m_Double),
    m_OctetSeqOut("OctetSeq", m_OctetSeq),
    m_ShortSeqOut("ShortSeq", m_ShortSeq),
    m_LongSeqOut("LongSeq", m_LongSeq),
    m_FloatSeqOut("FloatSeq", m_FloatSeq),
    m_DoubleSeqOut("DoubleSeq", m_DoubleSeq)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SeqInTest::~SeqInTest()
{
}



RTC::ReturnCode_t SeqInTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("Octet", m_OctetOut);
  addOutPort("Short", m_ShortOut);
  addOutPort("Long", m_LongOut);
  addOutPort("Float", m_FloatOut);
  addOutPort("Double", m_DoubleOut);
  addOutPort("OctetSeq", m_OctetSeqOut);
  addOutPort("ShortSeq", m_ShortSeqOut);
  addOutPort("LongSeq", m_LongSeqOut);
  addOutPort("FloatSeq", m_FloatSeqOut);
  addOutPort("DoubleSeq", m_DoubleSeqOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SeqInTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t SeqInTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqInTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqInTest::onActivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqInTest::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


RTC::ReturnCode_t SeqInTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t SeqInTest::onAborting(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqInTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqInTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqInTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t SeqInTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool SeqInTest::runTest()
{
    return true;
}


extern "C"
{
 
  void SeqInTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(seqin_spec);
    manager->registerFactory(profile,
                             RTC::Create<SeqInTest>,
                             RTC::Delete<SeqInTest>);
  }
  
}

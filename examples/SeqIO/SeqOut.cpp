// -*- C++ -*-
/*!
 * @file  SeqOut.cpp
 * @brief Sequence OutPort component
 * $Date: 2007-04-13 15:02:49 $
 *
 * $Id$
 */

#include "SeqOut.h"
#include <stdlib.h>

// Module specification
// <rtc-template block="module_spec">
static const char* seqout_spec[] =
  {
    "implementation_id", "SeqOut",
    "type_name",         "SequenceOutComponent",
    "description",       "Sequence OutPort component",
    "version",           "1.0",
    "vendor",            "Noriaki Ando, AIST",
    "category",          "example",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "10",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.data_type", "random",
    "conf.mode0.data_type", "serial",
    ""
  };
// </rtc-template>

SeqOut::SeqOut(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    // <rtc-template block="initializer">
    m_ShortOut("Short", m_Short),
    m_LongOut("Long", m_Long),
    m_FloatOut("Float", m_Float),
    m_DoubleOut("Double", m_Double),
    m_ShortSeqOut("ShortSeq", m_ShortSeq),
    m_LongSeqOut("LongSeq", m_LongSeq),
    m_FloatSeqOut("FloatSeq", m_FloatSeq),
    m_DoubleSeqOut("DoubleSeq", m_DoubleSeq)
    
    // </rtc-template>
{
}

SeqOut::~SeqOut()
{
}



RTC::ReturnCode_t SeqOut::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  registerOutPort("Short", m_ShortOut);
  registerOutPort("Long", m_LongOut);
  registerOutPort("Float", m_FloatOut);
  registerOutPort("Double", m_DoubleOut);
  registerOutPort("ShortSeq", m_ShortSeqOut);
  registerOutPort("LongSeq", m_LongSeqOut);
  registerOutPort("FloatSeq", m_FloatSeqOut);
  registerOutPort("DoubleSeq", m_DoubleSeqOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  m_DoubleSeq.data.length(10);
  m_FloatSeq.data.length(10);
  m_LongSeq.data.length(10);
  m_ShortSeq.data.length(10);

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("data_type", m_data_type, "random");
  
  // </rtc-template>

  return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t SeqOut::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeqOut::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeqOut::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeqOut::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeqOut::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t SeqOut::onExecute(RTC::UniqueId ec_id)
{
  static short  cnt1, cntseq1;
  static long   cnt2, cntseq2;
  static float  cnt3, cntseq3;
  static double cnt4, cntseq4;

  // Configuration check
  if (m_data_type == "serial")
    {
      ++cnt1;
      if( cnt1 > 30000 )
        {
          cnt1 = 1;
        }
      m_Short.data = cnt1;

      ++cnt2;
      if( cnt2 > 30000 )
        {
          cnt2 = 1;
        }
      m_Long.data = cnt2;

      ++cnt3;
      if( cnt3 > 30000 )
        {
          cnt3 = 1.0;
        }
      m_Float.data = cnt3 + 0.12;

      ++cnt4;
      if( cnt4 > 30000 )
        {
          cnt4 = 1.0;
        }
      m_Double.data = cnt4 + 0.345;
    }
  else				//default
    {
      m_Short.data = rand();
      m_Long.data = rand();
      m_Float.data = rand();
      m_Double.data = rand();
    }

  std::cout << "-: ";
  std::cout << m_Double.data << " ";
  std::cout << m_Float.data << " ";
  std::cout << m_Long.data << " ";
  std::cout << m_Short.data << "                                   " << std::endl << std::endl;

  for (CORBA::ULong i = 0; i < 10; ++i)
    {
      // Configuration check
      if (m_data_type == "serial")
        {
          ++cntseq1;
          if( cntseq1 > 30000 )
            {
              cntseq1 = 1;
            }
          m_ShortSeq.data[i] = cntseq1;

          ++cntseq2;
          if( cntseq2 > 30000 )
            {
              cntseq2 = 1;
            }
          m_LongSeq.data[i] = cntseq2;

          ++cntseq3;
          if( cntseq3 > 30000 )
            {
              cntseq3 = 1.0;
            }
          m_FloatSeq.data[i] = cntseq3 + 0.12;

          ++cntseq4;
          if( cntseq4 > 30000 )
            {
              cntseq4 = 1.0;
            }
          m_DoubleSeq.data[i] = cntseq4 + 0.345;
        }
      else				//default
        {
          m_DoubleSeq.data[i] = static_cast<double>(rand());
          m_FloatSeq.data[i] = static_cast<float>(rand());
          m_LongSeq.data[i] = static_cast<long>(rand());
          m_ShortSeq.data[i] = static_cast<short>(rand());
        }

      std::cout << i << ": ";
      std::cout << m_DoubleSeq.data[i] << " ";
      std::cout << m_FloatSeq.data[i] << " ";
      std::cout << m_LongSeq.data[i] << " ";
      std::cout << m_ShortSeq.data[i] << "                                " << std::endl;
    }
  // Configuration check
  if (m_data_type == "serial")
    {
      std::cout << std::endl << "write data type : serial" << std::endl;
    }
  else				//default
    {
      std::cout << std::endl << "write data type : random" << std::endl;
    }
  std::cout << "[A\r[A\r[A\r[A\r[A\r[A\r[A\r[A\r[A\r[A\r[A\r[A\r[A\r[A\r";

  m_ShortOut.write();
  m_LongOut.write();
  m_FloatOut.write();
  m_DoubleOut.write();

  m_ShortSeqOut.write();
  m_LongSeqOut.write();
  m_FloatSeqOut.write();
  m_DoubleSeqOut.write();

  coil::usleep(200000);

  return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t SeqOut::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeqOut::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeqOut::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeqOut::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SeqOut::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void SeqOutInit(RTC::Manager* manager)
  {
    coil::Properties profile(seqout_spec);
    manager->registerFactory(profile,
                             RTC::Create<SeqOut>,
                             RTC::Delete<SeqOut>);
  }
  
};



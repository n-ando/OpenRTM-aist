// -*- C++ -*-
/*!
 * @file SeqIn.h
 * @brief SeqIn component
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * $Id: SeqIn.h,v 1.1.1.1 2005-05-12 09:06:20 n-ando Exp $
 */

#ifndef __SEQIN_h__
#define __SEQIN_h__


#include <rtm/RtcBase.h>
#include <rtm/RtcManager.h>
#include <rtm/RtcInPort.h>
#include <rtm/RtcOutPort.h>

using namespace RTM;

static RtcModuleProfSpec seqin_spec[] =
  {
  
  {RTC_MODULE_NAME, "SeqIn"},
  {RTC_MODULE_DESC, "SeqIn component"},
  {RTC_MODULE_VERSION, "0.1"},
  {RTC_MODULE_AUTHOR, "DrSample"},
  {RTC_MODULE_CATEGORY, "Generic"},
  {RTC_MODULE_COMP_TYPE, "COMMUTATIVE"},
  {RTC_MODULE_ACT_TYPE, "SPORADIC"},
  {RTC_MODULE_MAX_INST, "10"},
  {RTC_MODULE_LANG, "C++"},
  {RTC_MODULE_LANG_TYPE, "COMPILE"},
  {RTC_MODULE_SPEC_END, NULL}
  };


	
class SeqIn
  : public RTM::RtcBase
{
 public:
  SeqIn(RtcManager* manager);

  virtual RtmRes rtc_ready_do();
  virtual RtmRes rtc_active_do();

  TimedDouble m_Double;
  InPortAny<TimedDouble> m_DoubleIn;
  TimedFloat m_Float;
  InPortAny<TimedFloat> m_FloatIn;
  TimedLong m_Long;
  InPortAny<TimedLong> m_LongIn;
  TimedShort m_Short;
  InPortAny<TimedShort> m_ShortIn;

  TimedDoubleSeq m_DoubleSeq;
  InPortAny<TimedDoubleSeq> m_DoubleSeqIn;
  TimedFloatSeq m_FloatSeq;
  InPortAny<TimedFloatSeq> m_FloatSeqIn;
  TimedLongSeq m_LongSeq;
  InPortAny<TimedLongSeq> m_LongSeqIn;
  TimedShortSeq m_ShortSeq;
  InPortAny<TimedShortSeq> m_ShortSeqIn;

};


extern "C" {
  RtcBase* SeqInNew(RtcManager* manager);
  void SeqInDelete(RtcBase* p);
  void SeqInInit(RtcManager* manager);
};
#endif // __SEQIN_h__


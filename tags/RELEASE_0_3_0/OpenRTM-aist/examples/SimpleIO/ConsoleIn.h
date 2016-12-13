// -*- C++ -*-
/*!
 * @file ConsoleIn.h
 * @brief Sample Component: Console In
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * Copyright (c) 2004 Noriaki Ando <n-ando@aist.go.jp>
 *          National Institute of Industrial Science (AIST), Japan. All rights reserved.
 *
 * $Id: ConsoleIn.h,v 1.1.1.1 2005-05-12 09:06:20 n-ando Exp $
 */

#ifndef __ConsoleIn_h__
#define __ConsoleIn_h__


#include <RtcBase.h>
#include <RtcManager.h>
#include <RtcOutPort.h>
#include <iostream>


using namespace RTM;
using namespace std;

static RtcModuleProfSpec consolein_spec[] =
  {
	{RTC_MODULE_NAME,      "ConsoleIn"},
	{RTC_MODULE_DESC,      "Console input component"},
	{RTC_MODULE_VERSION,   "1.0"},
	{RTC_MODULE_AUTHOR,    "Noriaki Ando"},
	{RTC_MODULE_COMPANY,   "AIST, Japan"},
	{RTC_MODULE_CATEGORY,  "example"},
	{RTC_MODULE_COMP_TYPE, "COMMUTATIVE"},
	{RTC_MODULE_ACT_TYPE,  "SPORADIC"},
	{RTC_MODULE_MAX_INST,  "10"},
	{RTC_MODULE_LANG,      "C++"},
	{RTC_MODULE_LANG_TYPE, "COMPILE"},
	{RTC_MODULE_SPEC_END, NULL}
  };


class ConsoleIn
  : public RTM::RtcBase
{
 public:
  ConsoleIn(RtcManager* manager);

  virtual RtmRes rtc_active_do();
  
  TimedLong out;
  OutPortAny<TimedLong> m_Out;
};

extern "C" {
  RtcBase* ConsoleInNew(RtcManager* manager);
  void ConsoleInDelete(RtcBase* p);
  void ConsoleInInit(RtcManager* manager);
};
#endif // __ConsoleIn_h__

// -*- C++ -*-
/*!
 * @file ConsoleOut.h
 * @brief Sample Component: Console In
 * @date $Date: 2005-05-12 09:06:20 $
 *
 * Copyright (c) 2004 Noriaki Ando <n-ando@aist.go.jp>
 *          National Institute of Industrial Science (AIST), Japan. All rights reserved.
 *
 * $Id: ConsoleOut.h,v 1.1.1.1 2005-05-12 09:06:20 n-ando Exp $
 */

#ifndef __ConsoleOut_h__
#define __ConsoleOut_h__


#include <RtcBase.h>
#include <RtcManager.h>
#include <RtcInPort.h>
#include <iostream>


using namespace RTM;
using namespace std;

static RtcModuleProfSpec consolein_spec[] =
  {
	{RTC_MODULE_NAME,      "ConsoleOut"},
	{RTC_MODULE_DESC,      "Console output component"},
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


class ConsoleOut
  : public RTM::RtcBase
{
 public:
  ConsoleOut(RtcManager* manager);

  virtual RtmRes rtc_active_do();
  
  TimedLong in;
  InPortAny<TimedLong> m_In;

};

extern "C" {
  RtcBase* ConsoleOutNew(RtcManager* manager);
  void ConsoleOutDelete(RtcBase* p);
  void ConsoleOutInit(RtcManager* manager);
};
#endif // __ConsoleOut_h__

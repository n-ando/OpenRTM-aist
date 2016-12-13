// -*- C++ -*-
/*!
 * @file  SimpleService.h
 * @brief Simple service example component
 * @date  $Date: 2005-09-08 13:04:31 $
 *
 * $Id: SimpleService.h,v 1.1 2005-09-08 13:04:31 n-ando Exp $
 */

#ifndef SIMPLESERVICE_H
#define SIMPLESERVICE_H

#include <rtm/RtcBase.h>
#include <rtm/RtcManager.h>
#include <rtm/RtcInPort.h>
#include <rtm/RtcOutPort.h>

// Service implementation headers
// <rtc-template block="service_impl_h">
#include "MyServiceSVC_impl.h"
// </rtc-template>

using namespace RTM;

// Module specification
// <rtc-template block="module_spec">
static RtcModuleProfSpec simpleservice_spec[] =
  {
    {RTC_MODULE_NAME,      "SimpleService"},
    {RTC_MODULE_DESC,      "Simple service example component"},
    {RTC_MODULE_VERSION,   "0.1"},
    {RTC_MODULE_AUTHOR,    "DrSample"},
    {RTC_MODULE_CATEGORY,  "Generic"},
    {RTC_MODULE_COMP_TYPE, "COMMUTATIVE"},
    {RTC_MODULE_ACT_TYPE,  "SPORADIC"},
    {RTC_MODULE_MAX_INST,  "10"},
    {RTC_MODULE_LANG,      "C++"},
    {RTC_MODULE_LANG_TYPE, "COMPILE"},
    {RTC_MODULE_SPEC_END,  NULL}
  };
// </rtc-template>

class SimpleService
  : public RTM::RtcBase
{
 public:
  SimpleService(RtcManager* manager);

  // Initializing state
  //  virtual RtmRes rtc_init_entry();

  // Ready state
  //  virtual RtmRes rtc_ready_entry();
  //  virtual RtmRes rtc_ready_do();
  //  virtual RtmRes rtc_ready_exit();
  // HogeHoge
  // DaraDara
  // Starting state
  //  virtual RtmRes rtc_starting_entry();

  // Active state
  //  virtual RtmRes rtc_active_entry();
  virtual RtmRes rtc_active_do();
  //  virtual RtmRes rtc_active_exit();

  // Stopping state
  //  virtual RtmRes rtc_stopping_entry();

  // Aborting state
  //  virtual RtmRes rtc_aborting_entry();

  // Error state
  //  virtual RtmRes rtc_error_entry();
  //  virtual RtmRes rtc_error_do();
  //  virtual RtmRes rtc_error_exit();

  // Fatal Error state
  //  virtual RtmRes rtc_fatal_entry();
  //  virtual RtmRes rtc_fatal_do();
  //  virtual RtmRes rtc_fatal_exit();

  // Exiting state
  //  virtual RtmRes rtc_exiting_entry();


 protected:
  // InPort declaration
  // <rtc-template block="inport_declar">
  TimedFloatSeq m_Ref;
  InPortAny<TimedFloatSeq> m_RefIn;
  
  // </rtc-template>


  // OutPort declaration
  // <rtc-template block="outport_declar">
  TimedFloatSeq m_GaindRef;
  OutPortAny<TimedFloatSeq> m_GaindRefOut;
  TimedFloat m_Gain;
  OutPortAny<TimedFloat> m_GainOut;
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declar">
  MyServiceSVC_impl m_MySVC;
  RtcServiceProfile m_MyServiceProfile;
  // DaraDara 
  // </rtc-template>


 private:
  int dummy;

};


extern "C"
{
  RtcBase* SimpleServiceNew(RtcManager* manager);
  void SimpleServiceDelete(RtcBase* p);
  void SimpleServiceInit(RtcManager* manager);
};

#endif // SIMPLESERVICE_H

// -*- C++ -*-
/*!
 * @file  Phantom.h
 * @brief PHANToM component
 * @date  $Date$
 *
 * $Id$
 */

#ifndef PHANTOM_H
#define PHANTOM_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <HD/hd.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>

#define B_OFF  0
#define B_ON   1
#define B_PUSH 2
#define B_FREE 4
#define POS_ELEMENT 3
#define RPY_ELEMENT 3
#define FORCE_ELEMENT 3

using namespace RTC;

/*!
 * @class Phantom
 * @brief PHANToM component
 *
 */
class Phantom
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Phantom(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~Phantom();

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);


 protected:
  // Configuration variable declaration
  /*!
   * 
   * - Name:  force_gain
   * - DefaultValue: 1.0,1.0,1.0
   */
  std::vector<double> m_force_gain;
  /*!
   * 
   * - Name:  cnt_mode
   * - DefaultValue: joystick
   */
  std::string m_cnt_mode;
  /*!
   * 
   * - Name:  coordinate
   * - DefaultValue: 0,1,2,3,4,5
   */
  std::vector<int> m_coordinate;
  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  TimedFloatSeq m_ref;
  /*!
   * The data for force feedback.
   */
  InPort<TimedFloatSeq> m_refIn;
  
  // DataOutPort declaration
  TimedFloatSeq m_cur;
  /*!
   * current force.
   */
  OutPort<TimedFloatSeq> m_curOut;
  
 private:
  std::string m_last_mode;
  HHD m_hHD;
  HDSchedulerHandle m_CallbackHandle;

};


extern "C"
{
  DLL_EXPORT void PhantomInit(RTC::Manager* manager);
};

#endif // PHANTOM_H

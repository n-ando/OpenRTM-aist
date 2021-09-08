// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  SeqOut.h
 * @brief Sequence OutPort component
 *
 */
// </rtc-template>

#ifndef SEQOUT_H
#define SEQOUT_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "BasicDataTypeStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

using namespace RTC;

// Connector Listener Dump Flag : default OFF
extern bool g_Listener_dump_enabled;

class DataListener
  : public ConnectorDataListenerT<RTC::TimedLong>
{
  USE_CONNLISTENER_STATUS;
public:
  DataListener(const char* name) : m_name(name) {}
  ~DataListener() override
  {
    // Connector Listener Dump check
    if(g_Listener_dump_enabled)
      {
        std::cout << "dtor of " << m_name << std::endl;
      }
  }

  ReturnCode operator()(ConnectorInfo& info,
                                TimedLong& data) override
  {
    // Connector Listener Dump check
    if(g_Listener_dump_enabled)
      {
        std::cout << "------------------------------"   << std::endl;
        std::cout << "Data Listener: " << m_name       << std::endl;
        std::cout << "Profile::name: " << info.name    << std::endl;
        std::cout << "Profile::id:   " << info.id      << std::endl;
        std::cout << "Data:          " << data.data    << std::endl;
        std::cout << "------------------------------"   << std::endl;
      }
    return NO_CHANGE;
  }
  std::string m_name;
};


class ConnListener
  : public ConnectorListener
{
  USE_CONNLISTENER_STATUS;
public:
  ConnListener(const char* name) : m_name(name) {}
  ~ConnListener() override
  {
    // Connector Listener Dump check
    if(g_Listener_dump_enabled)
      {
        std::cout << "dtor of " << m_name << std::endl;
      }
  }

  ReturnCode operator()(ConnectorInfo& info) override
  {
    // Connector Listener Dump check
    if(g_Listener_dump_enabled)
      {
        std::cout << "------------------------------"   << std::endl;
        std::cout << "Connector Listener: " << m_name       << std::endl;
        std::cout << "Profile::name:      " << info.name    << std::endl;
        std::cout << "Profile::id:        " << info.id      << std::endl;
        std::cout << "Profile::properties: "            << std::endl;
        std::cout << info.properties;
        std::cout                                       << std::endl;
        std::cout << "------------------------------"   << std::endl;
      }
    return NO_CHANGE;
  }
  std::string m_name;
};

// <rtc-template block="component_description">
/*!
 * @class SeqOut
 * @brief Sequence OutPort component
 *
 */
// </rtc-template>
class SeqOut
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  SeqOut(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~SeqOut() override;

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  // <rtc-template block="activity">
  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onInitialize() override;

  /***
   *
   * The finalize action (on ALIVE->END transition)
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onFinalize() override;

  /***
   *
   * The startup action when ExecutionContext startup
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id) override;

  /***
   *
   * The shutdown action when ExecutionContext stop
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id) override;

  /***
   *
   * The activated action (Active state entry action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id) override;

  /***
   *
   * The deactivated action (Active state exit action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id) override;

  /***
   *
   * The execution action that is invoked periodically
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id) override;

  /***
   *
   * The aborting action when main logic error occurred.
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id) override;

  /***
   *
   * The error action in ERROR state
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onError(RTC::UniqueId ec_id) override;

  /***
   *
   * The reset action that is invoked resetting
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onReset(RTC::UniqueId ec_id) override;
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id) override;

  /***
   *
   * The action that is invoked when execution context's rate is changed
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id) override;
  // </rtc-template>


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedOctet m_Octet;
  /*!
   */
  RTC::OutPort<RTC::TimedOctet> m_OctetOut;
  RTC::TimedShort m_Short;
  /*!
   */
  RTC::OutPort<RTC::TimedShort> m_ShortOut;
  RTC::TimedLong m_Long;
  /*!
   */
  RTC::OutPort<RTC::TimedLong> m_LongOut;
  RTC::TimedFloat m_Float;
  /*!
   */
  RTC::OutPort<RTC::TimedFloat> m_FloatOut;
  RTC::TimedDouble m_Double;
  /*!
   */
  RTC::OutPort<RTC::TimedDouble> m_DoubleOut;
  RTC::TimedOctetSeq m_OctetSeq;
  /*!
   */
  RTC::OutPort<RTC::TimedOctetSeq> m_OctetSeqOut;
  RTC::TimedShortSeq m_ShortSeq;
  /*!
   */
  RTC::OutPort<RTC::TimedShortSeq> m_ShortSeqOut;
  RTC::TimedLongSeq m_LongSeq;
  /*!
   */
  RTC::OutPort<RTC::TimedLongSeq> m_LongSeqOut;
  RTC::TimedFloatSeq m_FloatSeq;
  /*!
   */
  RTC::OutPort<RTC::TimedFloatSeq> m_FloatSeqOut;
  RTC::TimedDoubleSeq m_DoubleSeq;
  /*!
   */
  RTC::OutPort<RTC::TimedDoubleSeq> m_DoubleSeqOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>
  std::string m_data_type;

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void SeqOutInit(RTC::Manager* manager);
};

#endif // SEQOUT_H

// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  SeqIn.h
 * @brief Sequence InPort component
 *
 */
// </rtc-template>

#ifndef SEQIN_H
#define SEQIN_H

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
 * @class SeqIn
 * @brief Sequence InPort component
 *
 */
// </rtc-template>
class SeqIn
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  SeqIn(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~SeqIn() override;

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
  RTC::TimedOctet m_Octet;
  /*!
   */
  RTC::InPort<RTC::TimedOctet> m_OctetIn;
  RTC::TimedShort m_Short;
  /*!
   */
  RTC::InPort<RTC::TimedShort> m_ShortIn;
  RTC::TimedLong m_Long;
  /*!
   */
  RTC::InPort<RTC::TimedLong> m_LongIn;
  RTC::TimedFloat m_Float;
  /*!
   */
  RTC::InPort<RTC::TimedFloat> m_FloatIn;
  RTC::TimedDouble m_Double;
  /*!
   */
  RTC::InPort<RTC::TimedDouble> m_DoubleIn;
  RTC::TimedOctetSeq m_OctetSeq;
  /*!
   */
  RTC::InPort<RTC::TimedOctetSeq> m_OctetSeqIn;
  RTC::TimedShortSeq m_ShortSeq;
  /*!
   */
  RTC::InPort<RTC::TimedShortSeq> m_ShortSeqIn;
  RTC::TimedLongSeq m_LongSeq;
  /*!
   */
  RTC::InPort<RTC::TimedLongSeq> m_LongSeqIn;
  RTC::TimedFloatSeq m_FloatSeq;
  /*!
   */
  RTC::InPort<RTC::TimedFloatSeq> m_FloatSeqIn;
  RTC::TimedDoubleSeq m_DoubleSeq;
  /*!
   */
  RTC::InPort<RTC::TimedDoubleSeq> m_DoubleSeqIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  
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


 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void SeqInInit(RTC::Manager* manager);
};

#endif // SEQIN_H

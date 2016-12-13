// -*- C++ -*-
/*!
 * @file RTObjectImpl.h
 * @brief RTObjectImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef RTOBJECT_IMPL_H
#define RTOBJECT_IMPL_H


#include <doil/ImplBase.h>
#include <IRTObject.h>
#include <ExecutionContextImpl.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class RTObjectImpl
   * @brief RTObject試験用インプリメントクラス
   * @else
   * @class RTObjectImpl
   * @brief RTObject implementation class for RTObjectServant' unittest.
   * @endif
   */

  class RTObjectImpl
   : public virtual doil::ImplBase,
     public virtual ::RTC::Local::IRTObject,
     public virtual ::RTC::Local::ILightweightRTObject,
     public virtual ::SDOPackage::Local::ISDO,
     public virtual ::RTC::Local::IComponentAction,
     public virtual ::SDOPackage::Local::ISDOSystemElement

  {
  public:
    RTObjectImpl();
    RTObjectImpl(Logger& aLogger);

    virtual ~RTObjectImpl();

    virtual ::RTC::Local::ComponentProfile get_component_profile()
      throw ();

    virtual ::RTC::Local::PortServiceList get_ports()
      throw ();


    //ILightweightRTObject
    virtual ::RTC::Local::ReturnCode_t initialize()
      throw ();

    virtual ::RTC::Local::ReturnCode_t finalize()
      throw ();

    virtual bool is_alive(const ::RTC::Local::IExecutionContext* exec_context)
      throw ();

    virtual ::RTC::Local::ReturnCode_t exit()
      throw ();

    virtual ::RTC::Local::ExecutionContextHandle_t attach_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ();

    virtual ::RTC::Local::ReturnCode_t detach_context(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::IExecutionContext* get_context(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ExecutionContextList get_owned_contexts()
      throw ();

    virtual ::RTC::Local::ExecutionContextList get_participating_contexts()
      throw ();

    virtual ::RTC::Local::ExecutionContextHandle_t get_context_handle(const ::RTC::Local::IExecutionContext* cxt)
      throw ();

    //
    virtual ::RTC::Local::ReturnCode_t on_initialize()
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_finalize()
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_startup(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_shutdown(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_activated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_deactivated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_aborting(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_error(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_reset(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    //ISDOSystemElement
    virtual ::SDOPackage::Local::OrganizationList get_owned_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    //ISDO
    virtual ::std::string get_sdo_id()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::std::string get_sdo_type()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::DeviceProfile get_device_profile()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::ServiceProfileList get_service_profiles()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::ServiceProfile get_service_profile(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::ISDOService* get_sdo_service(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::IConfiguration* get_configuration()
      throw (::SDOPackage::Local::InterfaceNotImplemented,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::IMonitoring* get_monitoring()
      throw (::SDOPackage::Local::InterfaceNotImplemented,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::OrganizationList get_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::NVList get_status_list()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::std::string get_status(const ::std::string& nme)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    //
    const char* id() { return "RTObject"; }
    const char* name() { return m_name; }
    void incRef() { refcount++; }
    void decRef() { refcount--; }
    ::UnitTest::Servant::ExecutionContextImpl m_pec;
  private:
    static int count;
    char m_name[32];
    int refcount;
    Logger *m_logger;
  };

}; // namespace Servant
}; // namespace UnitTest

#endif  // 

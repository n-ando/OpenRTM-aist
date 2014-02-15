// -*- C++ -*-
/*!
 * @file RTObjectImpl.h
 * @brief RTObjectImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <RTObjectImpl.h>
#include <ExecutionContextImpl.h>
#include <iostream>
#include <string>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{
  /*!
   * @if jp
   * @class RTObjectImpl
   * @brief RTObjectServant試験用インプリメントクラス
   * @else
   * @class RTObjectImpl
   * @brief RTObject implementation class for RTObjectServant' unittest.
   * @endif
   */
   int RTObjectImpl::count = 0;

    RTObjectImpl::RTObjectImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    RTObjectImpl::RTObjectImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    RTObjectImpl::~RTObjectImpl()
    {
    }

    ::RTC::Local::ComponentProfile RTObjectImpl::get_component_profile()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_component_profile");
          }
        ::RTC::Local::ComponentProfile ret;
        return ret;
    }

    ::RTC::Local::PortServiceList RTObjectImpl::get_ports()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_ports");
          }
        ::RTC::Local::PortServiceList ret;
        return ret;
    }

    //LightweightRTObject
    ::RTC::Local::ReturnCode_t RTObjectImpl::initialize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("initialize");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t RTObjectImpl::finalize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("finalize");
          }
        return RTC::Local::RTC_OK;
    }

    bool RTObjectImpl::is_alive(const ::RTC::Local::IExecutionContext* exec_context)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("is_alive");
          }
        return true;
    }

    ::RTC::Local::ReturnCode_t RTObjectImpl::exit()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("exit");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ExecutionContextHandle_t RTObjectImpl::attach_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("attach_context");
          }
        ::RTC::Local::ExecutionContextHandle_t ret;
        return ret;
    }

    ::RTC::Local::ReturnCode_t RTObjectImpl::detach_context(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("detach_context");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::IExecutionContext* RTObjectImpl::get_context(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_context");
          }
       std::cout<<"010"<<std::endl;
       ::RTC::Local::IExecutionContext *ret = new ::UnitTest::Servant::ExecutionContextImpl();
       std::cout<<"020"<<std::endl;
        //return ret;
        return (::RTC::Local::IExecutionContext *)&m_pec;
    }

    ::RTC::Local::ExecutionContextList RTObjectImpl::get_owned_contexts()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_owned_contexts");
          }
        ::RTC::Local::ExecutionContextList ret;
        return ret;
    }

    ::RTC::Local::ExecutionContextList RTObjectImpl::get_participating_contexts()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_participating_contexts");
          }
        ::RTC::Local::ExecutionContextList ret;
        return ret;
    }

    ::RTC::Local::ExecutionContextHandle_t RTObjectImpl::get_context_handle(const ::RTC::Local::IExecutionContext* cxt)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_context_handle");
          }
        ::RTC::Local::ExecutionContextHandle_t ret;
        return ret;
    }

    //
    ::RTC::Local::ReturnCode_t RTObjectImpl::on_initialize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_initialize");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t RTObjectImpl::on_finalize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_finalize");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t RTObjectImpl::on_startup(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_startup");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t RTObjectImpl::on_shutdown(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_shutdown");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t RTObjectImpl::on_activated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_activated");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t RTObjectImpl::on_deactivated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_deactivated");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t RTObjectImpl::on_error(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_error");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t RTObjectImpl::on_aborting(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            //std::cout<<"size:"<<m_logger->size()<<std::endl;
            m_logger->push("on_aborting");
            //std::cout<<"size:"<<m_logger->size()<<std::endl;
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t RTObjectImpl::on_reset(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_reset");
          }
        return RTC::Local::RTC_OK;
    }

    //SDOSystemElement
    ::SDOPackage::Local::OrganizationList RTObjectImpl::get_owned_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_owned_organizations");
          }
        ::SDOPackage::Local::OrganizationList ret;
        return ret;
    }
    //SDO
    ::std::string RTObjectImpl::get_sdo_id()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_sdo_id");
          }
        return "bar";
    }

    ::std::string RTObjectImpl::get_sdo_type()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_sdo_type");
          }
        return "bar";
    }

    ::SDOPackage::Local::DeviceProfile RTObjectImpl::get_device_profile()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_device_profile");
          }
        ::SDOPackage::Local::DeviceProfile prof;
        return prof;
    }

    ::SDOPackage::Local::ServiceProfileList RTObjectImpl::get_service_profiles()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_service_profiles");
          }
        ::SDOPackage::Local::ServiceProfileList profs;
        return profs;
    }

    ::SDOPackage::Local::ServiceProfile RTObjectImpl::get_service_profile(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_service_profile");
          }
        ::SDOPackage::Local::ServiceProfile prof;
        return prof;
    }

    ::SDOPackage::Local::ISDOService* RTObjectImpl::get_sdo_service(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_sdo_service");
          }
        ::SDOPackage::Local::ISDOService* ret;
        return ret;
    }

    ::SDOPackage::Local::IConfiguration* RTObjectImpl::get_configuration()
      throw (::SDOPackage::Local::InterfaceNotImplemented,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_configuration");
          }
        ::SDOPackage::Local::IConfiguration* ret;
        return ret;
    }

    ::SDOPackage::Local::IMonitoring* RTObjectImpl::get_monitoring()
      throw (::SDOPackage::Local::InterfaceNotImplemented,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_monitoring");
          }
        ::SDOPackage::Local::IMonitoring* ret;
        return ret;
    }

    ::SDOPackage::Local::OrganizationList RTObjectImpl::get_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_organizations");
          }
        ::SDOPackage::Local::OrganizationList ret;
        return ret;
    }

    ::SDOPackage::Local::NVList RTObjectImpl::get_status_list()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_status_list");
          }
        ::SDOPackage::Local::NVList ret;
        return ret;
    }


    ::std::string RTObjectImpl::get_status(const ::std::string& nme)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError)
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_status");
          }
        return "bar";
    }
    
}; // namespace Local 
}; // namespace SDOPackage 

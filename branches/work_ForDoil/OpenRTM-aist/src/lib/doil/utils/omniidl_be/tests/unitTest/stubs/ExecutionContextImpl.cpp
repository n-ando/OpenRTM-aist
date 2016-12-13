// -*- C++ -*-
/*!
 * @file ExecutionContextImpl.h
 * @brief ExecutionContextImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <ExecutionContextImpl.h>
#include <iostream>
#include <sstream>
#include <string>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{
  /*!
   * @if jp
   * @class ExecutionContextImpl
   * @brief ExecutionContextServant試験用インプリメントクラス
   * @else
   * @class ExecutionContextImpl
   * @brief ExecutionContext implementation class for LightweightRTObjecServant' unittest.
   * @endif
   */
   int ExecutionContextImpl::count = 0;

    ExecutionContextImpl::ExecutionContextImpl()
    {
      sprintf(m_name, "%s", id());
      ++count;
      m_logger = new Logger();
    } 
    ExecutionContextImpl::ExecutionContextImpl(Logger& aLogger)
    {
      sprintf(m_name, "%s", id());
      ++count;
      m_logger = &aLogger;
    } 

    ExecutionContextImpl::~ExecutionContextImpl()
    {
    }


    bool ExecutionContextImpl::is_running()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("is_running");
          }
        return true;
    }


    ::RTC::Local::ReturnCode_t ExecutionContextImpl::start()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("start");
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::stop()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("stop");
          }
        return ::RTC::Local::RTC_OK;
    }

    double ExecutionContextImpl::get_rate()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_rate");
          }
        return 100.0;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::set_rate(double rate)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("set_rate");
            std::ostringstream oss;
            oss << rate;
            std::string str(oss.str());
            m_logger->push(str);
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::add_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("add_component");
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::remove_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("remove_component");
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::activate_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("activate_component");
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::deactivate_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("deactivate_component");
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::reset_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("reset_component");
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::LifeCycleState ExecutionContextImpl::get_component_state(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_component_state");
          }
        return ::RTC::Local::CREATED_STATE;
    }

    ::RTC::Local::ExecutionKind ExecutionContextImpl::get_kind()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_kind");
          }
        return ::RTC::Local::PERIODIC;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::on_initialize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_initialize");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::on_finalize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_finalize");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::on_startup(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_startup");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::on_shutdown(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_shutdown");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::on_activated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_activated");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::on_deactivated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_deactivated");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::on_error(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_error");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::on_aborting(::RTC::Local::ExecutionContextHandle_t exec_handle)
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

    ::RTC::Local::ReturnCode_t ExecutionContextImpl::on_reset(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_reset");
          }
        return RTC::Local::RTC_OK;
    }






}; // namespace Local 
}; // namespace SDOPackage 

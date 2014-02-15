// -*- C++ -*-
/*!
 * @file ExecutionContextServiceImpl.h
 * @brief ExecutionContextServiceImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <ExecutionContextServiceImpl.h>
#include <RTObjectImpl.h>
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
   * @class ExecutionContextServiceImpl
   * @brief ExecutionContextServiceServant試験用インプリメントクラス
   * @else
   * @class ExecutionContextServiceImpl
   * @brief ExecutionContextService implementation class for LightweightRTObjecServant' unittest.
   * @endif
   */
   int ExecutionContextServiceImpl::count = 0;

    ExecutionContextServiceImpl::ExecutionContextServiceImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    ExecutionContextServiceImpl::ExecutionContextServiceImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    ExecutionContextServiceImpl::~ExecutionContextServiceImpl()
    {
    }


    ::RTC::Local::ExecutionContextProfile ExecutionContextServiceImpl::get_profile()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_profile");
          }
        ::RTC::Local::ExecutionContextProfile ret;
        m_ret.kind = ::RTC::Local::PERIODIC;
        m_ret.rate = 100.0;
        m_ret.owner = new UnitTest::Servant::RTObjectImpl();
        return m_ret;
    }

    bool ExecutionContextServiceImpl::is_running()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("is_running");
          }
        return true;
    }


    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::start()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("start");
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::stop()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("stop");
          }
        return ::RTC::Local::RTC_OK;
    }

    double ExecutionContextServiceImpl::get_rate()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_rate");
          }
        return 100.0;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::set_rate(double rate)
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

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::add_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("add_component");
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::remove_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("remove_component");
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::activate_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("activate_component");
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::deactivate_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("deactivate_component");
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::reset_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("reset_component");
          }
        return ::RTC::Local::RTC_OK;
    }

    ::RTC::Local::LifeCycleState ExecutionContextServiceImpl::get_component_state(const ::RTC::Local::ILightweightRTObject* comp)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_component_state");
          }
        return ::RTC::Local::CREATED_STATE;
    }

    ::RTC::Local::ExecutionKind ExecutionContextServiceImpl::get_kind()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_kind");
          }
        return ::RTC::Local::PERIODIC;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::on_initialize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_initialize");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::on_finalize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_finalize");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::on_startup(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_startup");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::on_shutdown(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_shutdown");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::on_activated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_activated");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::on_deactivated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_deactivated");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::on_error(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_error");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::on_aborting(::RTC::Local::ExecutionContextHandle_t exec_handle)
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

    ::RTC::Local::ReturnCode_t ExecutionContextServiceImpl::on_reset(::RTC::Local::ExecutionContextHandle_t exec_handle)
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

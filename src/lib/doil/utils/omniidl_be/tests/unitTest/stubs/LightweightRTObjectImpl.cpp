// -*- C++ -*-
/*!
 * @file LightweightRTObjectImpl.h
 * @brief LightweightRTObjectImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <LightweightRTObjectImpl.h>
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
   * @class LightweightRTObjectImpl
   * @brief LightweightRTObjectServant試験用インプリメントクラス
   * @else
   * @class LightweightRTObjectImpl
   * @brief LightweightRTObject implementation class for LightweightRTObjecServant' unittest.
   * @endif
   */
   int LightweightRTObjectImpl::count = 0;

    LightweightRTObjectImpl::LightweightRTObjectImpl()
    {
      ++count;
      m_logger = new Logger();
      m_pec = new ::UnitTest::Servant::ExecutionContextImpl();
    } 
    LightweightRTObjectImpl::LightweightRTObjectImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
      m_pec = new ::UnitTest::Servant::ExecutionContextImpl();
    } 

    LightweightRTObjectImpl::~LightweightRTObjectImpl()
    {
    }

    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::initialize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("initialize");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::finalize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("finalize");
          }
        return RTC::Local::RTC_OK;
    }

    bool LightweightRTObjectImpl::is_alive(const ::RTC::Local::IExecutionContext* exec_context)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("is_alive");
          }
        return true;
    }

    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::exit()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("exit");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ExecutionContextHandle_t LightweightRTObjectImpl::attach_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("attach_context");
          }
        ::RTC::Local::ExecutionContextHandle_t ret;
        return ret;
    }

    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::detach_context(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("detach_context");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::IExecutionContext* LightweightRTObjectImpl::get_context(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_context");
          }
       ::RTC::Local::IExecutionContext *ret = new ::UnitTest::Servant::ExecutionContextImpl();
       std::cout<<"020:"<< m_pec <<std::endl;
        //return ret;
        return m_pec;
    }

    ::RTC::Local::ExecutionContextList LightweightRTObjectImpl::get_owned_contexts()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_owned_contexts");
          }
        ::RTC::Local::ExecutionContextList ret;
        return ret;
    }

    ::RTC::Local::ExecutionContextList LightweightRTObjectImpl::get_participating_contexts()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_participating_contexts");
          }
        ::RTC::Local::ExecutionContextList ret;
        return ret;
    }

    ::RTC::Local::ExecutionContextHandle_t LightweightRTObjectImpl::get_context_handle(const ::RTC::Local::IExecutionContext* cxt)
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
    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::on_initialize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_initialize");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::on_finalize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_finalize");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::on_startup(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_startup");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::on_shutdown(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_shutdown");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::on_activated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_activated");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::on_deactivated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_deactivated");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::on_error(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_error");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::on_aborting(::RTC::Local::ExecutionContextHandle_t exec_handle)
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

    ::RTC::Local::ReturnCode_t LightweightRTObjectImpl::on_reset(::RTC::Local::ExecutionContextHandle_t exec_handle)
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

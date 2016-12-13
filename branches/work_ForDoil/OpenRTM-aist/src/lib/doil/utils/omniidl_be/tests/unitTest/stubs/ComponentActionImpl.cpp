// -*- C++ -*-
/*!
 * @file ComponentActionImpl.h
 * @brief ComponentActionImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <ComponentActionImpl.h>
#include <iostream>
#include <string>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{
  /*!
   * @if jp
   * @class ComponentActionImpl
   * @brief ComponentActionServant試験用インプリメントクラス
   * @else
   * @class ComponentActionImpl
   * @brief ComponentAction implementation class for ComponentActionServant' unittest.
   * @endif
   */
   int ComponentActionImpl::count = 0;

    ComponentActionImpl::ComponentActionImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    ComponentActionImpl::ComponentActionImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    ComponentActionImpl::~ComponentActionImpl()
    {
    }

    ::RTC::Local::ReturnCode_t ComponentActionImpl::on_initialize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_initialize");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ComponentActionImpl::on_finalize()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_finalize");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ComponentActionImpl::on_startup(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_startup");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ComponentActionImpl::on_shutdown(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_shutdown");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ComponentActionImpl::on_activated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_activated");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ComponentActionImpl::on_deactivated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_deactivated");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ComponentActionImpl::on_error(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_error");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t ComponentActionImpl::on_aborting(::RTC::Local::ExecutionContextHandle_t exec_handle)
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

    ::RTC::Local::ReturnCode_t ComponentActionImpl::on_reset(::RTC::Local::ExecutionContextHandle_t exec_handle)
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

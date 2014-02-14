// -*- C++ -*-
/*!
 * @file DataFlowComponentActionImpl.h
 * @brief DataFlowComponentActionImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <DataFlowComponentActionImpl.h>
#include <iostream>
#include <string>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{
  /*!
   * @if jp
   * @class DataFlowComponentActionImpl
   * @brief DataFlowComponentActionServant試験用インプリメントクラス
   * @else
   * @class DataFlowComponentActionImpl
   * @brief DataFlowComponentAction implementation class for DataFlowComponentActionServant' unittest.
   * @endif
   */
   int DataFlowComponentActionImpl::count = 0;

    DataFlowComponentActionImpl::DataFlowComponentActionImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    DataFlowComponentActionImpl::DataFlowComponentActionImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    DataFlowComponentActionImpl::~DataFlowComponentActionImpl()
    {
    }

    ::RTC::Local::ReturnCode_t DataFlowComponentActionImpl::on_execute(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_execute");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t DataFlowComponentActionImpl::on_state_update(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_state_update");
          }
        return RTC::Local::RTC_OK;
    }

    ::RTC::Local::ReturnCode_t DataFlowComponentActionImpl::on_rate_changed(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_rate_changed");
          }
        return RTC::Local::RTC_OK;
    }



}; // namespace Local 
}; // namespace SDOPackage 

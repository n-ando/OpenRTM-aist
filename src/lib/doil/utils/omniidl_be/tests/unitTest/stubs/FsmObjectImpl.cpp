// -*- C++ -*-
/*!
 * @file FsmObjectImpl.h
 * @brief FsmObjectImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <FsmObjectImpl.h>
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
   * @class FsmObjectImpl
   * @brief FsmObjectServant試験用インプリメントクラス
   * @else
   * @class FsmObjectImpl
   * @brief FsmObject implementation class for FsmObjectServant' unittest.
   * @endif
   */
   int FsmObjectImpl::count = 0;

    FsmObjectImpl::FsmObjectImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    FsmObjectImpl::FsmObjectImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    FsmObjectImpl::~FsmObjectImpl()
    {
    }

    ::RTC::Local::ReturnCode_t FsmObjectImpl::send_stimulus(const ::std::string&message, ::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("send_stimulus");
          }
        return RTC::Local::RTC_OK;
    }






}; // namespace Local 
}; // namespace SDOPackage 

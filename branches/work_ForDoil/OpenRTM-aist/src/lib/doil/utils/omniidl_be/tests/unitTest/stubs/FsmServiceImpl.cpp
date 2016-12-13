// -*- C++ -*-
/*!
 * @file FsmServiceImpl.h
 * @brief FsmServiceImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <FsmServiceImpl.h>
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
   * @class FsmServiceImpl
   * @brief FsmServiceServant試験用インプリメントクラス
   * @else
   * @class FsmServiceImpl
   * @brief FsmService implementation class for FsmServiceServant' unittest.
   * @endif
   */
   int FsmServiceImpl::count = 0;

    FsmServiceImpl::FsmServiceImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    FsmServiceImpl::FsmServiceImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    FsmServiceImpl::~FsmServiceImpl()
    {
    }

    ::RTC::Local::FsmProfile FsmServiceImpl::get_fsm_profile()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_fsm_profile");
          }
        ::RTC::Local::FsmProfile ret;
        return ret;
    }

    ::RTC::Local::ReturnCode_t FsmServiceImpl::set_fsm_profile(const ::RTC::Local::FsmProfile& fsm_profile)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("set_fsm_profile");
          }
        return RTC::Local::RTC_OK;
    }







}; // namespace Local 
}; // namespace SDOPackage 

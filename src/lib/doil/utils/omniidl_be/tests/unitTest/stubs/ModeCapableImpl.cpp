// -*- C++ -*-
/*!
 * @file ModeCapableImpl.h
 * @brief ModeCapableImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <ModeCapableImpl.h>
#include <ModeImpl.h>
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
   * @class ModeCapableImpl
   * @brief ModeCapableServant試験用インプリメントクラス
   * @else
   * @class ModeCapableImpl
   * @brief ModeCapable implementation class for ModeCapableServant' unittest.
   * @endif
   */
   int ModeCapableImpl::count = 0;

    ModeCapableImpl::ModeCapableImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    ModeCapableImpl::ModeCapableImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    ModeCapableImpl::~ModeCapableImpl()
    {
    }

    ::RTC::Local::IMode* ModeCapableImpl::get_default_mode()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_fsm_profile");
          }
        //ModeImpl* lo_ret = new ModeImpl();
        //::RTC::Local::IMode * ret = new UnitTest::Servant::ModeImpl(); 
        //::UnitTest::Servant::ModeImpl * ret = new ::UnitTest::Servant::ModeImpl(); 
        //::UnitTest::Servant::ModeImpl  ret;
        return NULL;
    }

    ::RTC::Local::IMode* ModeCapableImpl::get_current_mode()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_current_mode");
          }
        //::RTC::Local::IMode *ret = NULL;
        return NULL;
    }

    ::RTC::Local::IMode* ModeCapableImpl::get_current_mode_in_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_current_mode_in_context");
          }
        //::RTC::Local::IMode *ret = NULL;
        return NULL;
    }

    ::RTC::Local::IMode* ModeCapableImpl::get_pending_mode()
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_pending_mode");
          }
        //::RTC::Local::IMode *ret = NULL;
        return NULL;
    }

    ::RTC::Local::IMode* ModeCapableImpl::get_pending_mode_in_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("get_pending_mode_in_context");
          }
        //::RTC::Local::IMode ret = *NULL;
        return NULL;
    }

    ::RTC::Local::ReturnCode_t ModeCapableImpl::set_mode(const ::RTC::Local::IMode*new_mode, bool immediate)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("set_mode");
          }
        return RTC::Local::RTC_OK;
    }






}; // namespace Local 
}; // namespace SDOPackage 

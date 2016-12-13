// -*- C++ -*-
/*!
 * @file MultiModeComponentActionImpl.h
 * @brief MultiModeComponentActionImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <MultiModeComponentActionImpl.h>
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
   * @class MultiModeComponentActionImpl
   * @brief MultiModeComponentActionServant試験用インプリメントクラス
   * @else
   * @class MultiModeComponentActionImpl
   * @brief MultiModeComponentAction implementation class for MultiModeComponentActionServant' unittest.
   * @endif
   */
   int MultiModeComponentActionImpl::count = 0;

    MultiModeComponentActionImpl::MultiModeComponentActionImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    MultiModeComponentActionImpl::MultiModeComponentActionImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    MultiModeComponentActionImpl::~MultiModeComponentActionImpl()
    {
    }

    ::RTC::Local::ReturnCode_t MultiModeComponentActionImpl::on_mode_changed(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_mode_changed");
          }
        return RTC::Local::RTC_OK;
    }






}; // namespace Local 
}; // namespace SDOPackage 

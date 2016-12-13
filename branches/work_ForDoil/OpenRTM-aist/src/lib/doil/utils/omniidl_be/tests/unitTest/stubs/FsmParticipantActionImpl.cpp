// -*- C++ -*-
/*!
 * @file FsmParticipantActionImpl.h
 * @brief FsmParticipantActionImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */


#include <stdio.h>
#include <FsmParticipantActionImpl.h>
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
   * @class FsmParticipantActionImpl
   * @brief FsmParticipantActionServant試験用インプリメントクラス
   * @else
   * @class FsmParticipantActionImpl
   * @brief FsmParticipantAction implementation class for FsmParticipantActionServant' unittest.
   * @endif
   */
   int FsmParticipantActionImpl::count = 0;

    FsmParticipantActionImpl::FsmParticipantActionImpl()
    {
      ++count;
      m_logger = new Logger();
    } 
    FsmParticipantActionImpl::FsmParticipantActionImpl(Logger& aLogger)
    {
      ++count;
      m_logger = &aLogger;
    } 

    FsmParticipantActionImpl::~FsmParticipantActionImpl()
    {
    }

    ::RTC::Local::ReturnCode_t FsmParticipantActionImpl::on_action(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ()
    {
        if (m_logger != NULL) 
          {
            m_logger->push("on_action");
          }
        return RTC::Local::RTC_OK;
    }







}; // namespace Local 
}; // namespace SDOPackage 

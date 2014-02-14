// -*- C++ -*-
/*!
 * @file FsmParticipantActionImpl.h
 * @brief FsmParticipantActionImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef FSMPARTICIPANTACTION_IMPL_H
#define FSMPARTICIPANTACTION_IMPL_H


#include <doil/ImplBase.h>
#include <IFsmParticipantAction.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class FsmParticipantActionImpl
   * @brief FsmParticipantAction試験用インプリメントクラス
   * @else
   * @class FsmParticipantActionImpl
   * @brief FsmParticipantAction implementation class for FsmParticipantActionServant' unittest.
   * @endif
   */

  class FsmParticipantActionImpl
   : public virtual doil::ImplBase,
     public virtual ::RTC::Local::IFsmParticipantAction

  {
  public:
    FsmParticipantActionImpl();
    FsmParticipantActionImpl(Logger& aLogger);

    virtual ~FsmParticipantActionImpl();
    
    virtual ::RTC::Local::ReturnCode_t on_action(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    const char* id() { return "FsmParticipantAction"; }
    const char* name() { return m_name; }
    void incRef() { refcount++; }
    void decRef() { refcount--; }
  private:
    static int count;
    char m_name[32];
    int refcount;
    Logger *m_logger;
  };

}; // namespace Servant
}; // namespace UnitTest

#endif  // 

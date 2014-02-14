// -*- C++ -*-
/*!
 * @file FsmServiceImpl.h
 * @brief FsmServiceImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef FSMPARTICIPANTACTION_IMPL_H
#define FSMPARTICIPANTACTION_IMPL_H


#include <doil/ImplBase.h>
#include <IFsmService.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class FsmServiceImpl
   * @brief FsmService試験用インプリメントクラス
   * @else
   * @class FsmServiceImpl
   * @brief FsmService implementation class for FsmServiceServant' unittest.
   * @endif
   */

  class FsmServiceImpl
   : public virtual doil::ImplBase,
     public virtual ::RTC::Local::IFsmService,
     public virtual ::SDOPackage::Local::ISDOService

  {
  public:
    FsmServiceImpl();
    FsmServiceImpl(Logger& aLogger);

    virtual ~FsmServiceImpl();
    
    virtual ::RTC::Local::FsmProfile get_fsm_profile()
      throw ();

    virtual ::RTC::Local::ReturnCode_t set_fsm_profile(const ::RTC::Local::FsmProfile& fsm_profile)
      throw ();


    const char* id() { return "FsmService"; }
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

// -*- C++ -*-
/*!
 * @file FsmObjectImpl.h
 * @brief FsmObjectImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef FSMOBJECT_IMPL_H
#define FSMOBJECT_IMPL_H


#include <doil/ImplBase.h>
#include <IFsmObject.h>
#include <IExecutionContext.h>
#include <ISDOService.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class FsmObjectImpl
   * @brief FsmObject試験用インプリメントクラス
   * @else
   * @class FsmObjectImpl
   * @brief FsmObject implementation class for FsmObjectServant' unittest.
   * @endif
   */

  class FsmObjectImpl
   : public virtual doil::ImplBase,
     public virtual ::RTC::Local::IFsmObject

  {
  public:
    FsmObjectImpl();
    FsmObjectImpl(Logger& aLogger);

    virtual ~FsmObjectImpl();
    
    virtual ::RTC::Local::ReturnCode_t send_stimulus(const ::std::string&message, ::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    const char* id() { return "FsmObject"; }
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

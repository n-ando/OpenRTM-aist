// -*- C++ -*-
/*!
 * @file ComponentActionImpl.h
 * @brief ComponentActionImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef COMPONENTACTION_IMPL_H
#define COMPONENTACTION_IMPL_H


#include <doil/ImplBase.h>
#include <IComponentAction.h>
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

  class ComponentActionImpl
   : public virtual doil::ImplBase,
     public virtual RTC::Local::IComponentAction

  {
  public:
    ComponentActionImpl();
    ComponentActionImpl(Logger& aLogger);

    virtual ~ComponentActionImpl();

    virtual ::RTC::Local::ReturnCode_t on_initialize()
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_finalize()
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_startup(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_shutdown(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_activated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_deactivated(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_aborting(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_error(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_reset(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    const char* id() { return "ComponentAction"; }
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

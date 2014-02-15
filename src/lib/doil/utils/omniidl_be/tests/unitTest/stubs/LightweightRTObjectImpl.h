// -*- C++ -*-
/*!
 * @file LightweightRTObjectImpl.h
 * @brief LightweightRTObjectImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef LIGHTWEIGHTRTOBJECT_IMPL_H
#define LIGHTWEIGHTRTOBJECT_IMPL_H


#include <doil/ImplBase.h>
#include <ILightweightRTObject.h>
#include <ExecutionContextImpl.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class LightweightRTObjectImpl
   * @brief LightweightRTObject試験用インプリメントクラス
   * @else
   * @class LightweightRTObjectImpl
   * @brief LightweightRTObject implementation class for LightweightRTObjectServant' unittest.
   * @endif
   */

  class LightweightRTObjectImpl
   : public virtual doil::ImplBase,
     public virtual RTC::Local::IComponentAction,
     public virtual RTC::Local::ILightweightRTObject

  {
  public:
    LightweightRTObjectImpl();
    LightweightRTObjectImpl(Logger& aLogger);

    virtual ~LightweightRTObjectImpl();


    virtual ::RTC::Local::ReturnCode_t initialize()
      throw ();

    virtual ::RTC::Local::ReturnCode_t finalize()
      throw ();

    virtual bool is_alive(const ::RTC::Local::IExecutionContext* exec_context)
      throw ();

    virtual ::RTC::Local::ReturnCode_t exit()
      throw ();

    virtual ::RTC::Local::ExecutionContextHandle_t attach_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ();

    virtual ::RTC::Local::ReturnCode_t detach_context(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::IExecutionContext* get_context(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ExecutionContextList get_owned_contexts()
      throw ();

    virtual ::RTC::Local::ExecutionContextList get_participating_contexts()
      throw ();

    virtual ::RTC::Local::ExecutionContextHandle_t get_context_handle(const ::RTC::Local::IExecutionContext* cxt)
      throw ();

    //
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

    //
    const char* id() { return "LightweightRTObject"; }
    const char* name() { return m_name; }
    void incRef() { refcount++; }
    void decRef() { refcount--; }
  private:
    static int count;
    char m_name[32];
    int refcount;
    Logger *m_logger;
    ::RTC::Local::IExecutionContext * m_pec;
    //::UnitTest::Servant::ExecutionContextImpl m_pec;
  };

}; // namespace Servant
}; // namespace UnitTest

#endif  // 

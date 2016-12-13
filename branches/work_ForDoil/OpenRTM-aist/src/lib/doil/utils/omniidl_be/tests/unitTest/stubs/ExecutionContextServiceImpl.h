// -*- C++ -*-
/*!
 * @file ExecutionContextServiceImpl.h
 * @brief ExecutionContextServiceImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef EXECUTIONCONTEXTSERVICE_IMPL_H
#define EXECUTIONCONTEXTSERVICE_IMPL_H


#include <doil/ImplBase.h>
#include <IExecutionContextService.h>
#include <IExecutionContext.h>
#include <ISDOService.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class ExecutionContextServiceImpl
   * @brief ExecutionContextService試験用インプリメントクラス
   * @else
   * @class ExecutionContextServiceImpl
   * @brief ExecutionContextService implementation class for ExecutionContextServiceServant' unittest.
   * @endif
   */

  class ExecutionContextServiceImpl
   : public virtual doil::ImplBase,
     public virtual ::RTC::Local::IExecutionContext,
     public virtual ::SDOPackage::Local::ISDOService,
     public virtual ::RTC::Local::IExecutionContextService

  {
  public:
    ExecutionContextServiceImpl();
    ExecutionContextServiceImpl(Logger& aLogger);

    virtual ~ExecutionContextServiceImpl();
    
    virtual ::RTC::Local::ExecutionContextProfile get_profile()
      throw ();

    //
    virtual bool is_running()
      throw ();

    virtual ::RTC::Local::ReturnCode_t start()
      throw ();

    virtual ::RTC::Local::ReturnCode_t stop()
      throw ();

    virtual double get_rate()
      throw ();

    virtual ::RTC::Local::ReturnCode_t set_rate(double rate)
      throw ();

    virtual ::RTC::Local::ReturnCode_t add_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ();

    virtual ::RTC::Local::ReturnCode_t remove_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ();

    virtual ::RTC::Local::ReturnCode_t activate_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ();

    virtual ::RTC::Local::ReturnCode_t deactivate_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ();

    virtual ::RTC::Local::ReturnCode_t reset_component(const ::RTC::Local::ILightweightRTObject* comp)
      throw ();

    virtual ::RTC::Local::LifeCycleState get_component_state(const ::RTC::Local::ILightweightRTObject* comp)
      throw ();

    virtual ::RTC::Local::ExecutionKind get_kind()
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

    const char* id() { return "ExecutionContextService"; }
    const char* name() { return m_name; }
    void incRef() { refcount++; }
    void decRef() { refcount--; }
    ::RTC::Local::ExecutionContextProfile m_ret;
  private:
    static int count;
    char m_name[32];
    int refcount;
    Logger *m_logger;
  };

}; // namespace Servant
}; // namespace UnitTest

#endif  // 

// -*- C++ -*-
/*!
 * @file DataFlowComponentActionImpl.h
 * @brief DataFlowComponentActionImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef DATAFLOWCOMPONENTACTION_IMPL_H
#define DATAFLOWCOMPONENTACTION_IMPL_H


#include <doil/ImplBase.h>
#include <IDataFlowComponentAction.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class DataFlowComponentActionImpl
   * @brief DataFlowComponentAction試験用インプリメントクラス
   * @else
   * @class DataFlowComponentActionImpl
   * @brief DataFlowComponentAction implementation class for DataFlowComponentActionServant' unittest.
   * @endif
   */

  class DataFlowComponentActionImpl
   : public virtual doil::ImplBase,
     public virtual RTC::Local::IDataFlowComponentAction

  {
  public:
    DataFlowComponentActionImpl();
    DataFlowComponentActionImpl(Logger& aLogger);

    virtual ~DataFlowComponentActionImpl();


    virtual ::RTC::Local::ReturnCode_t on_execute(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_state_update(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();

    virtual ::RTC::Local::ReturnCode_t on_rate_changed(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    const char* id() { return "DataFlowComponentAction"; }
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

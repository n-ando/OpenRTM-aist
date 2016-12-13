// -*- C++ -*-
/*!
 * @file DataFlowComponentImpl.h
 * @brief DataFlowComponentImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef DATAFLOWCOMPONENT_IMPL_H
#define DATAFLOWCOMPONENT_IMPL_H


#include <doil/ImplBase.h>
#include <IDataFlowComponent.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class DataFlowComponentImpl
   * @brief DataFlowComponent試験用インプリメントクラス
   * @else
   * @class DataFlowComponentImpl
   * @brief DataFlowComponent implementation class for DataFlowComponentServant' unittest.
   * @endif
   */

  class DataFlowComponentImpl
   : public virtual doil::ImplBase,
     public virtual RTC::Local::ILightweightRTObject,
     public virtual RTC::Local::IDataFlowComponent,
     public virtual RTC::Local::IComponentAction

  {
  public:
    DataFlowComponentImpl();
    DataFlowComponentImpl(Logger& aLogger);

    virtual ~DataFlowComponentImpl();




    const char* id() { return "DataFlowComponent"; }
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

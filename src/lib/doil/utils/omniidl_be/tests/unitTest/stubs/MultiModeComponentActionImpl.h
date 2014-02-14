// -*- C++ -*-
/*!
 * @file MultiModeComponentActionImpl.h
 * @brief MultiModeComponentActionImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef MULTIMODECOMPONENTACTION_IMPL_H
#define MULTIMODECOMPONENTACTION_IMPL_H


#include <doil/ImplBase.h>
#include <IMultiModeComponentAction.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class MultiModeComponentActionImpl
   * @brief MultiModeComponentAction試験用インプリメントクラス
   * @else
   * @class MultiModeComponentActionImpl
   * @brief MultiModeComponentAction implementation class for MultiModeComponentActionServant' unittest.
   * @endif
   */

  class MultiModeComponentActionImpl
   : public virtual doil::ImplBase,
     public virtual ::RTC::Local::IMultiModeComponentAction

  {
  public:
    MultiModeComponentActionImpl();
    MultiModeComponentActionImpl(Logger& aLogger);

    virtual ~MultiModeComponentActionImpl();
    
    virtual ::RTC::Local::ReturnCode_t on_mode_changed(::RTC::Local::ExecutionContextHandle_t exec_handle)
      throw ();


    const char* id() { return "MultiModeComponentAction"; }
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

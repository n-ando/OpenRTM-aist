// -*- C++ -*-
/*!
 * @file ModeImpl.h
 * @brief ModeImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef MODECAPABLE_IMPL_H
#define MODECAPABLE_IMPL_H


#include <doil/ImplBase.h>
#include <IMode.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class ModeImpl
   * @brief Mode試験用インプリメントクラス
   * @else
   * @class ModeImpl
   * @brief Mode implementation class for ModeServant' unittest.
   * @endif
   */

  class ModeImpl
   : public virtual doil::ImplBase,
     public virtual ::RTC::Local::IMode

  {
  public:
    ModeImpl();
    ModeImpl(Logger& aLogger);

    virtual ~ModeImpl();
    


    const char* id() { return "Mode"; }
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

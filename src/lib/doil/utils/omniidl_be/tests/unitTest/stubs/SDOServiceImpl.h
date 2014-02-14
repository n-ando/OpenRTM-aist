// -*- C++ -*-
/*!
 * @file SDOServiceImpl.h
 * @brief SDOServiceImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef EXECUTIONCONTEXT_IMPL_H
#define EXECUTIONCONTEXT_IMPL_H


#include <doil/ImplBase.h>
#include <ISDOService.h>
#include <IComponentAction.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class SDOServiceImpl
   * @brief SDOService試験用インプリメントクラス
   * @else
   * @class SDOServiceImpl
   * @brief SDOService implementation class for SDOServiceServant' unittest.
   * @endif
   */

  class SDOServiceImpl
   : public virtual doil::ImplBase,
     public virtual RTC::Local::ISDOService

  {
  public:
    SDOServiceImpl();
    SDOServiceImpl(Logger& aLogger);

    virtual ~SDOServiceImpl();


    const char* id() { return "SDOService"; }
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

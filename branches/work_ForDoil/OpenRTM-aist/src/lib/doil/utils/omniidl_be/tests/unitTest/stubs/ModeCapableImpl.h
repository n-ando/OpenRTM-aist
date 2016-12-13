// -*- C++ -*-
/*!
 * @file ModeCapableImpl.h
 * @brief ModeCapableImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef MODECAPABLE_IMPL_H
#define MODECAPABLE_IMPL_H


#include <doil/ImplBase.h>
#include <IModeCapable.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class ModeCapableImpl
   * @brief ModeCapable試験用インプリメントクラス
   * @else
   * @class ModeCapableImpl
   * @brief ModeCapable implementation class for ModeCapableServant' unittest.
   * @endif
   */

  class ModeCapableImpl
   : public virtual doil::ImplBase,
     public virtual ::RTC::Local::IModeCapable

  {
  public:
    ModeCapableImpl();
    ModeCapableImpl(Logger& aLogger);

    virtual ~ModeCapableImpl();
    
    virtual ::RTC::Local::IMode* get_default_mode()
      throw ();

    virtual ::RTC::Local::IMode* get_current_mode()
      throw ();

    virtual ::RTC::Local::IMode* get_current_mode_in_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ();

    virtual ::RTC::Local::IMode* get_pending_mode()
      throw ();

    virtual ::RTC::Local::IMode* get_pending_mode_in_context(const ::RTC::Local::IExecutionContext* exec_context)
      throw ();

    virtual ::RTC::Local::ReturnCode_t set_mode(const ::RTC::Local::IMode*new_mode, bool immediate)
      throw ();


    const char* id() { return "ModeCapable"; }
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

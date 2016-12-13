// -*- C++ -*-
/*!
 * @file PortServiceImpl.h
 * @brief PortServiceImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef PORTSERVICE_IMPL_H
#define PORTSERVICE_IMPL_H


#include <doil/ImplBase.h>
#include <IPortService.h>
#include <ExecutionContextImpl.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class PortServiceImpl
   * @brief PortService試験用インプリメントクラス
   * @else
   * @class PortServiceImpl
   * @brief PortService implementation class for PortServiceServant' unittest.
   * @endif
   */

  class PortServiceImpl
   : public virtual doil::ImplBase,
     public virtual ::RTC::Local::IPortService,
     public virtual ::SDOPackage::Local::ISDOService

  {
  public:
    PortServiceImpl();
    PortServiceImpl(Logger& aLogger);

    virtual ~PortServiceImpl();

    virtual ::RTC::Local::PortProfile get_port_profile()
      throw ();

    virtual ::RTC::Local::ConnectorProfileList get_connector_profiles()
      throw ();

    virtual ::RTC::Local::ConnectorProfile get_connector_profile(const ::std::string& connector_id)
      throw ();

    virtual ::RTC::Local::ReturnCode_t connect(::RTC::Local::ConnectorProfile& connector_profile)
      throw ();

    virtual ::RTC::Local::ReturnCode_t disconnect(const ::std::string& connector_id)
      throw ();

    virtual ::RTC::Local::ReturnCode_t disconnect_all()
      throw ();

    virtual ::RTC::Local::ReturnCode_t notify_connect(::RTC::Local::ConnectorProfile& connector_profile)
      throw ();

    virtual ::RTC::Local::ReturnCode_t notify_disconnect(const ::std::string& connector_id)
      throw ();


    //ISDOService

    //
    const char* id() { return "PortService"; }
    const char* name() { return m_name; }
    void incRef() { refcount++; }
    void decRef() { refcount--; }
    ::UnitTest::Servant::ExecutionContextImpl m_pec;
  private:
    static int count;
    char m_name[32];
    int refcount;
    Logger *m_logger;
  };

}; // namespace Servant
}; // namespace UnitTest

#endif  // 

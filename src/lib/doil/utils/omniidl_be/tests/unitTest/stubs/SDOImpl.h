// -*- C++ -*-
/*!
 * @file SDOImpl.h
 * @brief SDOImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef SDO_IMPL_H
#define SDO_IMPL_H


#include <doil/ImplBase.h>
#include <ISDO.h>
#include <ISDOSystemElement.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class SDOImpl
   * @brief SDO試験用インプリメントクラス
   * @else
   * @class SDOImpl
   * @brief SDO implementation class for SDOServant' unittest.
   * @endif
   */

  class SDOImpl
   : public virtual doil::ImplBase,
     public virtual SDOPackage::Local::ISDO,
     public virtual ::SDOPackage::Local::ISDOSystemElement

  {
  public:
    SDOImpl();
    SDOImpl(Logger& aLogger);

    virtual ~SDOImpl();

    virtual ::std::string get_sdo_id()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::std::string get_sdo_type()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::DeviceProfile get_device_profile()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::ServiceProfileList get_service_profiles()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::ServiceProfile get_service_profile(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::ISDOService* get_sdo_service(const ::std::string& id)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::IConfiguration* get_configuration()
      throw (::SDOPackage::Local::InterfaceNotImplemented,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::IMonitoring* get_monitoring()
      throw (::SDOPackage::Local::InterfaceNotImplemented,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::OrganizationList get_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::SDOPackage::Local::NVList get_status_list()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    virtual ::std::string get_status(const ::std::string& nme)
      throw (::SDOPackage::Local::InvalidParameter,
             ::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    //
    virtual ::SDOPackage::Local::OrganizationList get_owned_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);

    const char* id() { return "SDO"; }
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

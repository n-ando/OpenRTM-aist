// -*- C++ -*-
/*!
 * @file SDOSystemElementImpl.h
 * @brief SDOSystemElementImpl C++ implementation sample for doil
 * @date $Date$
 * @author 
 *
 * $Id$
 */

#ifndef SDOSYSTEMELEMENT_IMPL_H
#define SDOSYSTEMELEMENT_IMPL_H


#include <doil/ImplBase.h>
#include <ISDOSystemElement.h>
#include <Logger.h>

namespace UnitTest
{
namespace Servant
{

  /*!
   * @if jp
   * @class SDOSystemElementImpl
   * @brief SDOSystemElement試験用インプリメントクラス
   * @else
   * @class SDOSystemElementImpl
   * @brief SDOSystemElement implementation class for SDOSystemElementServant' unittest.
   * @endif
   */

  class SDOSystemElementImpl
   : public virtual doil::ImplBase,
     public virtual ::SDOPackage::Local::ISDOSystemElement

  {
  public:
    SDOSystemElementImpl();
    SDOSystemElementImpl(Logger& aLogger);

    virtual ~SDOSystemElementImpl();

    virtual ::SDOPackage::Local::OrganizationList get_owned_organizations()
      throw (::SDOPackage::Local::NotAvailable,
             ::SDOPackage::Local::InternalError);


    const char* id() { return "SDOSystemElement"; }
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

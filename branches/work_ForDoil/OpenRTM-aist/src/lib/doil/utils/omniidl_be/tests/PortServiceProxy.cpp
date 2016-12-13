// -*- C++ -*-
/*!
 * @file PortServiceProxy.cpp 
 * @brief IPortService CORBA proxy for doil
 * @date $Date$
 * @author This file was automatically generated form RTC.idl 
 *         by omniidl/doil backend
 *
 * $Id$
 */

#include <doil/corba/CORBAManager.h>
#include <IPortService.h>
#include <PortServiceProxy.h>
#include <RTCTypeConversion.h>
#include <doil/corba/BasicTypeConversion.h>

namespace RTC 
{
namespace CORBA 
{
  /*!
   * @brief ctor
   */ 
  PortServiceProxy::PortServiceProxy(::CORBA::Object_ptr obj)
   : ::doil::CORBA::CORBAProxyBase(obj),
     m_obj(::RTC::PortService::_nil()),
     m_refcount(1),
     ::SDOPackage::CORBA::SDOServiceProxy(obj)//   : m_obj(::RTC::PortService::_nil()),
//     ::SDOPackage::SDOServiceProxy(obj)
  {
    m_obj = ::RTC::PortService::_narrow(obj);
    if (::CORBA::is_nil(m_obj)) throw std::bad_alloc();
    m_obj = ::RTC::PortService::_duplicate(m_obj);
  }

  /*!
   * @brief dtor
   */ 
  PortServiceProxy::~PortServiceProxy()
  {
    ::CORBA::release(m_obj);
  }

  
  /*!
   * @brief get_port_profile 
   */ 
  ::RTC::Local::PortProfile PortServiceProxy::get_port_profile()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::PortProfile* corba_ret;
    ::RTC::Local::PortProfile local_ret;
    corba_ret = m_obj->get_port_profile();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_connector_profiles 
   */ 
  ::RTC::Local::ConnectorProfileList PortServiceProxy::get_connector_profiles()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::ConnectorProfileList* corba_ret;
    ::RTC::Local::ConnectorProfileList local_ret;
    corba_ret = m_obj->get_connector_profiles();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief get_connector_profile 
   */ 
  ::RTC::Local::ConnectorProfile PortServiceProxy::get_connector_profile(const ::std::string& connector_id)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _connector_id;
    local_to_corba(connector_id, _connector_id);

    // Execute the method. 
    ::RTC::ConnectorProfile* corba_ret;
    ::RTC::Local::ConnectorProfile local_ret;
    corba_ret = m_obj->get_connector_profile(_connector_id);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(*corba_ret, local_ret);
    delete corba_ret; 
    return local_ret;
  }

  /*!
   * @brief connect 
   */ 
  ::RTC::Local::ReturnCode_t PortServiceProxy::connect(::RTC::Local::ConnectorProfile& connector_profile)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::ConnectorProfile _connector_profile;
    local_to_corba(connector_profile, _connector_profile);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->connect(_connector_profile);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)
    corba_to_local(_connector_profile, connector_profile);

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief disconnect 
   */ 
  ::RTC::Local::ReturnCode_t PortServiceProxy::disconnect(const ::std::string& connector_id)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _connector_id;
    local_to_corba(connector_id, _connector_id);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->disconnect(_connector_id);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief disconnect_all 
   */ 
  ::RTC::Local::ReturnCode_t PortServiceProxy::disconnect_all()
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->disconnect_all();

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief notify_connect 
   */ 
  ::RTC::Local::ReturnCode_t PortServiceProxy::notify_connect(::RTC::Local::ConnectorProfile& connector_profile)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    ::RTC::ConnectorProfile _connector_profile;
    local_to_corba(connector_profile, _connector_profile);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->notify_connect(_connector_profile);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)
    corba_to_local(_connector_profile, connector_profile);

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

  /*!
   * @brief notify_disconnect 
   */ 
  ::RTC::Local::ReturnCode_t PortServiceProxy::notify_disconnect(const ::std::string& connector_id)
      throw ()
  {
    // Convert Local to CORBA.
    // (The direction of the argument is 'in' or 'inout'.)
    char* _connector_id;
    local_to_corba(connector_id, _connector_id);

    // Execute the method. 
    ::RTC::ReturnCode_t corba_ret;
    ::RTC::Local::ReturnCode_t local_ret;
    corba_ret = m_obj->notify_disconnect(_connector_id);

    // Convert CORBA to Local.
    // (The direction of the argument is 'out' or 'inout'.)

    // Generate the return value.
    corba_to_local(corba_ret, local_ret);
    return local_ret;
  }

}; // namespace CORBA
}; // namespace RTC 

extern "C"
{
  void PortServiceProxyCORBAInit(coil::Properties& prop)
  {
    doil::CORBA::CORBAManager& mgr(doil::CORBA::CORBAManager::instance());
    mgr.registerProxyFactory("PortServiceProxy",
                        doil::New< ::RTC::CORBA::PortServiceProxy >,
                        doil::Delete< ::RTC::CORBA::PortServiceProxy >);
  }
};


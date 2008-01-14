// -*- C++ -*-
/*!
 * @file SdoOrganization.cpp
 * @brief SDO Organization class
 * @date $Date: 2008-01-14 07:49:31 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoOrganization.cpp,v 1.7.2.2 2008-01-14 07:49:31 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.7.2.1  2007/12/31 03:08:07  n-ando
 * Class reference by doxygen comment was revised.
 *
 * Revision 1.7  2007/04/26 15:33:28  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.6  2006/11/27 10:00:56  n-ando
 * Some trivial fixes.
 *
 * Revision 1.5  2006/10/30 08:10:47  n-ando
 * CORBA sequence operations were replaced by CORBA_SeqUtil functions.
 *
 * Revision 1.4  2006/10/26 09:36:23  n-ando
 * set_organization_property_value() was not implemented. It was added.
 *
 * Revision 1.3  2006/10/26 09:15:39  n-ando
 * Header comments were fixed.
 *
 */

#include <rtm/SdoOrganization.h>
#include <ace/ACE.h>
#include <ace/UUID.h> 
#include <rtm/CORBA_SeqUtil.h>

namespace SDOPackage
{
  /* @if jp
   * @brief コンストラクタ
   * @else
   * @endif
   */
  Organization_impl::Organization_impl()
  {
    ACE_Utils::UUID_Generator uugen;
    uugen.init();
    ACE_Utils::UUID* uuid = uugen.generateUUID(2,0x01);
    m_pId = CORBA::string_dup((uuid->to_string())->c_str());
#ifdef WIN32
    uuid->~UUID();
#else
    delete uuid;
#endif
  }
  
  /* @if jp
   * @brief 仮想デストラクタ
   * @else
   * @brief virtual destractor
   * @endif
   */
  Organization_impl::~Organization_impl()
  {
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Organization ID を取得する
   * @else
   * @brief [CORBA interface] Get Organization Id
   * @endif
   */
  char* Organization_impl::get_organization_id()
    throw (CORBA::SystemException,
	   InvalidParameter, NotAvailable, InternalError)
  {
    return m_pId;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] OrganizationProperty の取得
   * @else
   * @brief [CORBA interface] Get OrganizationProperty
   * @endif
   */
  OrganizationProperty* Organization_impl::get_organization_property()
    throw (CORBA::SystemException,
	   NotAvailable, InternalError)
  {
    Guard guard(m_org_mutex);
    OrganizationProperty_var prop;
    prop = new OrganizationProperty(m_orgProperty);
    return prop._retn();
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] OrganizationProperty の特定の値の取得
   * @else
   * @brief [CORBA interface] Get specified value of OrganizationProperty
   * @endif
   */
  CORBA::Any*
  Organization_impl::get_organization_property_value(const char* name)
    throw (CORBA::SystemException,
	   InvalidParameter, NotAvailable, InternalError)
  {
    if (name == "")
      throw InvalidParameter("Empty name.");
    
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_orgProperty.properties, nv_name(name));
    
    if (index < 0)
      throw InvalidParameter("Not found.");
    
    try
      {
	CORBA::Any_var value;
	value = new CORBA::Any(m_orgProperty.properties[index].value);
	return value._retn();
      }
    catch (...)
      {
	throw InternalError("get_organization_property_value()");
      }
    // never reach here
    return new CORBA::Any();
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] OrganizationProperty のセット
   * @else
   * @brief [CORBA interface] Set OrganizationProperty
   * @endif
   */
  CORBA::Boolean
  Organization_impl::
  set_organization_property(const OrganizationProperty& organization_property)
    throw (CORBA::SystemException,
	   InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
	Guard guard(m_org_mutex);
	m_orgProperty = organization_property;
	return true;
      }
    catch (...)
      {
	throw InternalError("set_organization_property()");
      }
    return false;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] OrganizationProperty の値のセット
   * @else
   * @brief [CORBA interface] Set specified value of OrganizationProperty
   * @endif
   */
  CORBA::Boolean
  Organization_impl::set_organization_property_value(const char* name,
						     const CORBA::Any& value)
    throw (CORBA::SystemException,
	   InvalidParameter, NotAvailable, InternalError)
  {
    if (name == "")
      {
	throw InvalidParameter("set_organization_property_value(): Enpty name.");
      }
    
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_orgProperty.properties,nv_name(name));
    if (index < 0)
      {
	NameValue nv;
	nv.name = CORBA::string_dup(name);
	nv.value = value;
	CORBA_SeqUtil::push_back(m_orgProperty.properties, nv);
      }
    else
      {
	m_orgProperty.properties[index].value = value;
      }
    return true;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] OrganizationProperty の削除
   * @else
   * @brief [CORBA interface] Remove specified OrganizationProperty
   * @endif
   */   
  CORBA::Boolean
  Organization_impl::remove_organization_property(const char* name)
    throw (CORBA::SystemException,
	   InvalidParameter, NotAvailable, InternalError)
  {
    if (name == "")
      throw InvalidParameter("set_organization_property_value(): Enpty name.");
    
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_orgProperty.properties,nv_name(name));
    if (index < 0)
      throw InvalidParameter("set_organization_property_value(): Not found.");
    
    try
      {
	CORBA_SeqUtil::erase(m_orgProperty.properties, index);
	return true;
      }
    catch (...)
      {
	throw InternalError("remove_organization_property()");
      }
    return false;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Organization のオーナーを取得する
   * @else
   * @brief [CORBA interface] Get the owner of the SDO
   * @endif
   */
  SDOSystemElement_ptr Organization_impl::get_owner()
    throw (CORBA::SystemException,
	   NotAvailable, InternalError)
  {
    return m_varOwner._retn();
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Organization にオーナーをセットする
   * @else
   * @brief [CORBA interface] Set the orner of the Organization
   * @endif
   */
  CORBA::Boolean Organization_impl::set_owner(SDOSystemElement_ptr sdo)
    throw (CORBA::SystemException,
	   InvalidParameter, NotAvailable, InternalError)
  {
    if (CORBA::is_nil(sdo))
      throw InvalidParameter("set_owner()");
    try
      {
	m_varOwner = sdo;
	return true;
      }
    catch (...)
      {
	throw InternalError("set_owner()");
      }
    return true;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Organization のメンバーを取得する
   * @else
   * @brief [CORBA interface] Get a menber list of the Organization
   * @endif
   */
  SDOList* Organization_impl::get_members()
    throw (CORBA::SystemException,
	   NotAvailable, InternalError)
  {
    try
      {
	SDOList_var sdos;
	sdos = new SDOList(m_memberList);
	return sdos._retn();
      }
    catch (...)
      {
	throw InternalError("get_members()");
      }
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] SDO の ServiceProfile のセット
   * @else
   * @brief [CORBA interface] Set SDO's ServiceProfile
   * @endif
   */
  CORBA::Boolean Organization_impl::set_members(const SDOList& sdos)
    throw (CORBA::SystemException,
	   InvalidParameter, NotAvailable, InternalError)
  {
    if (sdos.length() == 0)
      throw InvalidParameter("set_members(): SDOList is empty.");
    try
      {
	m_memberList = sdos;
	return true;
      }
    catch (...)
      {
	throw InternalError("set_members()");
      }
    return true;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] SDO メンバーの追加
   * @else
   * @brief [CORBA interface] Add the menebr SDOs
   * @endif
   */
  CORBA::Boolean Organization_impl::add_members(const SDOList& sdo_list)
    throw (CORBA::SystemException,
	   InvalidParameter, NotAvailable, InternalError)
  {
    try
      {
	CORBA_SeqUtil::push_back_list(m_memberList, sdo_list);
	return true;
      }
    catch (...)
      {
	throw InternalError("add_members()");
      }
    return false;	
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] SDO メンバーの削除
   * @else
   * @brief [CORBA interface] Remove menber SDO from Organization
   * @endif
   */
  CORBA::Boolean Organization_impl::remove_member(const char* id)
    throw (CORBA::SystemException,
	   InvalidParameter, NotAvailable, InternalError)
  {
    if (id == "")
      throw InvalidParameter("remove_member(): Enpty name.");
    
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_memberList, sdo_id(id));
    
    if (index < 0)
      throw InvalidParameter("remove_member(): Not found.");
    
    try
      {
	CORBA_SeqUtil::erase(m_memberList, index);
	return true;
      }
    catch (...)
      {
	throw InternalError("remove_member(): Not found.");
      }
    return false;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Organization の DependencyType を取得
   * @else
   * @brief [CORBA interface] Get the DependencyType of the Organization
   * @endif
   */
  DependencyType Organization_impl::get_dependency()
    throw (CORBA::SystemException,
	   NotAvailable, InternalError)
  {
    return m_dependency;
  }
  
  /*!
   * @if jp
   * @brief [CORBA interface] Organization の DependencyType をセットする
   * @else
   * @brief [CORBA interface] Set the DependencyType of the Organization
   * @endif
   */
  CORBA::Boolean Organization_impl::set_dependency(DependencyType dependency)
    throw (CORBA::SystemException,
	   NotAvailable, InternalError)
  {
    try
      {
	m_dependency = dependency;
	return true;
      }
    catch (...)
      {
	throw InternalError("set_dependency(): Unknown.");
      }
    return false;
  }
};

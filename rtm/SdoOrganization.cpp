// -*- C++ -*-
/*!
 * @file RtcBase.h
 * @brief RT component base class
 * @date $Date: 2006-10-26 09:13:31 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoOrganization.cpp,v 1.2 2006-10-26 09:13:31 n-ando Exp $
 *
 */
#include <ace/ACE.h>
#include <ace/UUID.h> 
#include "rtm/SdoOrganization.h"

namespace SDOPackage
{
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


  Organization_impl::~Organization_impl()
  {
  }


  char* Organization_impl::get_organization_id()
    throw (InvalidParameter, NotAvailable, InternalError)
  {
	return m_pId;
  }


  OrganizationProperty* Organization_impl::get_organization_property()
    throw (NotAvailable, InternalError)
  {
	return new SDOPackage::OrganizationProperty(m_OrganizationProperty);
  }


  CORBA::Any*
  Organization_impl::get_organization_property_value(const char* name)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
	//	return new CORBA::Any(NVList_helper::find(m_OrganizationProperty.properties, name));
	return new CORBA::Any(m_OrganizationProperty.properties[0].value);
  }


  CORBA::Boolean
  Organization_impl::set_organization_property(const OrganizationProperty& organization_property)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
	m_OrganizationProperty = organization_property;
	return true;
   }

  CORBA::Boolean
  Organization_impl::remove_organization_property(const char* name)
    throw (InvalidParameter, NotAvailable, InternalError)
  {

	return true;
  }

  SDOSystemElement_ptr Organization_impl::get_owner()
    throw (NotAvailable, InternalError)
  {
	return m_varOwner._retn();
  }

  CORBA::Boolean Organization_impl::set_owner(SDOSystemElement_ptr sdo)
     throw (InvalidParameter, NotAvailable, InternalError)
  {
	m_varOwner = sdo;
	return true;
  }

  SDOList* Organization_impl::get_members()
     throw (NotAvailable, InternalError)
  {
	return new SDOPackage::SDOList(m_MemberList);
  }

  CORBA::Boolean Organization_impl::set_members(const SDOList& sdos)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
	m_MemberList = sdos;
	return true;
  }

  CORBA::Boolean Organization_impl::add_members(const SDOList& sdo_list)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
	//	m_MemberList.add(sdo_list);
	return true;
  }

  CORBA::Boolean Organization_impl::remove_member(const char* id)
    throw (InvalidParameter, NotAvailable, InternalError)
  {
	//	m_MemberList.remove(id);
	return true;
  }
	
  DependencyType Organization_impl::get_dependency()
     throw (NotAvailable, InternalError)
  {
	return m_Dependency;
  }
  
  CORBA::Boolean Organization_impl::set_dependency(DependencyType dependency)
    throw (NotAvailable, InternalError)
  {
	m_Dependency = dependency;
	return true;
  }

};

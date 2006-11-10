// -*- C++ -*-
/*!
 * @file NVUtil.h
 * @brief NameValue and NVList utility functions
 * @date $Date: 2006-11-10 04:32:38 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: NVUtil.cpp,v 1.1 2006-11-10 04:32:38 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include <map>
#include <string>
#include <CORBA_SeqUtil.h>
#include <NVUtil.h>

namespace NVUtil
{
  SDOPackage::NameValue newNVChar(const char* name, const CORBA::Char value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= CORBA::Any::from_char(value);
    return nv;
  }
    
  SDOPackage::NameValue newNVBool(const char* name, const CORBA::Boolean value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= CORBA::Any::from_boolean(value);
    return nv;
  }
    
  SDOPackage::NameValue newNVOctet(const char* name, const CORBA::Octet value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= CORBA::Any::from_octet(value);
    return nv;
  }
    
  void copy(SDOPackage::NVList& nv, RTC::Properties& prop)
  {
    CORBA::ULong len((CORBA::ULong)prop.size());
    nv.length(len);

    std::map<std::string, std::string>::iterator it, it_end;
    it     = prop.begin();
    it_end = prop.end();

    for (CORBA::ULong i = 0; i < len; ++i, ++it)
      {
	nv[i].name = CORBA::string_dup((it->first).c_str());
	nv[i].value <<= (it->second).c_str();
      }
  }

  struct nv_find
  {
    nv_find(const char* name) : m_name(name) {};
    bool operator()(const SDOPackage::NameValue& nv)
    {
      std::string name(nv.name);
      return m_name == name;
    }
    std::string m_name;
  };

  const CORBA::Any& find(SDOPackage::NVList& nv, const char* name)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(nv, NVUtil::nv_find(name));
    if (index < 0) throw;
    return nv[index].value;
  }

  bool isString(SDOPackage::NVList& nv, const char* name)
  {
    try
      {
	CORBA::Any value;
	value = find(nv, name);
	char* str_value;
	return value >>= str_value;
      }
    catch (...)
      {
	return false;
      }
  }

  std::string toString(SDOPackage::NVList& nv, const char* name)
  {
    char* str_value;
    try
      {
	find(nv, name) >>= str_value;
      }
    catch (...)
      {
	str_value = "";
      }
    return str_value;
  }
};

// -*- C++ -*-
/*!
 * @file NVUtil.h
 * @brief NameValue and NVList utility functions
 * @date $Date: 2007-04-13 18:05:14 $
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
 * $Id: NVUtil.cpp,v 1.7 2007-04-13 18:05:14 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6  2007/01/21 09:51:06  n-ando
 * A trivial bug fix.
 *
 * Revision 1.5  2007/01/12 14:33:50  n-ando
 * The dump() function was added to dump NVList entries.
 *
 * Revision 1.4  2007/01/06 17:55:29  n-ando
 * toProperties()'s argument was changed to const.
 * Some functions were added.
 * - isStringValue()
 * - appendStringValue()
 * - append()
 *
 * Revision 1.3  2006/12/02 18:44:27  n-ando
 * Argument's const declaration was fixed.
 *
 * Revision 1.2  2006/11/27 09:54:42  n-ando
 * Conversion function from NVList to Properties: toProperties() was added.
 *
 * Revision 1.1  2006/11/10 04:32:38  n-ando
 * NVUtil is SDOPackage::NVList utility.
 *
 *
 */

#include <map>
#include <string>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/StringUtil.h>
#include <rtm/NVUtil.h>

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
    
  SDOPackage::NameValue newNVAny(const char* name, const CORBA::Any& value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value = value;
    return nv;
  }
    
  void copy(SDOPackage::NVList& nv, const RTC::Properties& prop)
  {
    std::vector<std::string> keys;
    keys = prop.propertyNames();
    CORBA::ULong len((CORBA::ULong)keys.size());
    nv.length(len);

    for (CORBA::ULong i = 0; i < len; ++i)
      {
	nv[i].name = CORBA::string_dup(keys[i].c_str());
	nv[i].value <<= prop[keys[i]].c_str();
      }
  }


  struct to_prop
  {
    to_prop()
    {
    };
    void operator()(const SDOPackage::NameValue& nv)
    {
      char* value;
      if (nv.value >>= value)
	{
	  m_prop.setProperty(CORBA::string_dup(nv.name), value);
	};
    }
    RTC::Properties m_prop;
  };

  RTC::Properties toProperties(const SDOPackage::NVList& nv)
  {
    to_prop p;
    p = CORBA_SeqUtil::for_each(nv, p);
    return p.m_prop;
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

  const CORBA::Any& find(const SDOPackage::NVList& nv, const char* name)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(nv, NVUtil::nv_find(name));
    if (index < 0) throw std::string("Not found");
    return nv[index].value;
  }

  const CORBA::Long find_index(const SDOPackage::NVList& nv, const char* name)
  {
    return  CORBA_SeqUtil::find(nv, NVUtil::nv_find(name));
  }

  bool isString(const SDOPackage::NVList& nv, const char* name)
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

  bool isStringValue(const SDOPackage::NVList& nv,
		     const char* name,
		     const char* value)
  {
    if (isString(nv, name))
      {
	if (toString(nv, name) == value)
	  {
	    return true;
	  }
      }
    return false;
  }

  std::string toString(const SDOPackage::NVList& nv, const char* name)
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

  bool appendStringValue(SDOPackage::NVList& nv, const char* name,
			 const char* value)
  {
	//    if (!isString(nv, name)) return false;

    CORBA::Long index;
    index = find_index(nv, name);

	if (index > 0)
	  {
		char* tmp_char;
		nv[index].value >>= tmp_char;
		std::string tmp_str(tmp_char);
		
		std::vector<std::string> values;
		values = split(tmp_str, ",");
		if (values.end() == std::find(values.begin(), values.end(), value))
		  {
			tmp_str.append(", ");
			tmp_str.append(value);
			nv[index].value <<= tmp_str.c_str();
		  }
	  }
	else
	  {
		CORBA_SeqUtil::push_back(nv, newNV(name, value));
	  }
    return true;
  }

  void append(SDOPackage::NVList& dest, const SDOPackage::NVList& src)
  {
    for (CORBA::ULong i = 0, len = src.length(); i < len; ++i)
      {
		CORBA_SeqUtil::push_back(dest, src[i]);
      }
  }


  void dump(SDOPackage::NVList& nv)
  {
    for (CORBA::ULong i(0), n(nv.length()); i < n; ++i)
      {
	char* str_value;
	if (nv[i].value >>= str_value)
	  {
	    std::cout << nv[i].name << ": " << str_value << std::endl;
	  }
	else
	  {
	    std::cout << nv[i].name << ": not a string value" << std::endl;
	  }
      }
  }	    

};

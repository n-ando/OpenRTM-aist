// -*- C++ -*-
/*!
 * @file NVUtil.h
 * @brief NameValue and NVList utility functions
 * @date $Date: 2008-01-13 07:41:08 $
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
 * $Id: NVUtil.cpp,v 1.8.2.3 2008-01-13 07:41:08 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.8.2.2  2007/12/31 03:08:04  n-ando
 * Class reference by doxygen comment was revised.
 *
 * Revision 1.8.2.1  2007/07/20 15:56:50  n-ando
 * STL algorithm header include.
 *
 * Revision 1.8  2007/04/23 04:54:28  n-ando
 * Conversion functions between Properties and NVList were added.
 *
 * Revision 1.7  2007/04/13 18:05:14  n-ando
 * Some changes of the logic accompanying change of the Properties class.
 *
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

#include <rtm/CORBA_SeqUtil.h>
#include <rtm/StringUtil.h>
#include <rtm/NVUtil.h>
#include <string>
#include <map>
#include <algorithm>

namespace NVUtil
{
  /*!
   * @if jp
   * @brief value が CORBA::Char の NameValue を生成する
   * @else
   * 
   * @endif
   */
  SDOPackage::NameValue newNVChar(const char* name, const CORBA::Char value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= CORBA::Any::from_char(value);
    return nv;
  }
  
  /*!
   * @if jp
   * @brief value が CORBA::Boolean の NameValue を生成する
   * @else
   * 
   * @endif
   */
  SDOPackage::NameValue newNVBool(const char* name, const CORBA::Boolean value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= CORBA::Any::from_boolean(value);
    return nv;
  }
  
  /*!
   * @if jp
   * @brief value が CORBA::Octet の NameValue を生成する
   * @else
   * 
   * @endif
   */
  SDOPackage::NameValue newNVOctet(const char* name, const CORBA::Octet value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= CORBA::Any::from_octet(value);
    return nv;
  }
  
  /*!
   * @if jp
   * @brief value が CORBA::Any の NameValue を生成する
   * @else
   * 
   * @endif
   */
  SDOPackage::NameValue newNVAny(const char* name, const CORBA::Any& value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value = value;
    return nv;
  }
  
  /*!
   * @if jp
   * @brief Properties を NVList へコピーする
   * @else
   * 
   * @endif
   */
  void copyFromProperties(SDOPackage::NVList& nv, const RTC::Properties& prop)
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
  
  /*!
   * @if jp
   * @brief NVList を Properties へコピーする
   * @else
   * 
   * @endif
   */
  void copyToProperties(RTC::Properties& prop, const SDOPackage::NVList& nv)
  {
    for (CORBA::ULong i(0), len(nv.length()); i < len; ++i)
      {
	const char* value;
	if (nv[i].value >>= value)
	  {
	    const char* name(nv[i].name);
	    prop[name] = value;
	  };
      }
  }
  
  /*!
   * @if jp
   * @brief NVList を Properties に変換するためのファンクタ
   * @else
   *
   * @endif
   */
  struct to_prop
  {
    to_prop()
    {
    };
    void operator()(const SDOPackage::NameValue& nv)
    {
      const char* value;
      if (nv.value >>= value)
	{
	  m_prop.setProperty(CORBA::string_dup(nv.name), value);
	};
    }
    RTC::Properties m_prop;
  };
  
  /*!
   * @if jp
   * @brief NVList を Properties へ変換する
   * @else
   * 
   * @endif
   */
  RTC::Properties toProperties(const SDOPackage::NVList& nv)
  {
    to_prop p;
    p = CORBA_SeqUtil::for_each(nv, p);
    return p.m_prop;
  }
  
  /*!
   * @if jp
   * @brief NVList を検索するためのファンクタ
   * @else
   *
   * @endif
   */
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
  
  /*!
   * @if jp
   * @brief NVList から name で指定された value を返す
   * @else
   * 
   * @endif
   */
  const CORBA::Any& find(const SDOPackage::NVList& nv, const char* name)
  {
    CORBA::Long index;
    index = CORBA_SeqUtil::find(nv, NVUtil::nv_find(name));
    if (index < 0) throw std::string("Not found");
    return nv[index].value;
  }
  
  /*!
   * @if jp
   * @brief name で指定された要素のインデックスを返す
   * @else
   * 
   * @endif
   */
  const CORBA::Long find_index(const SDOPackage::NVList& nv, const char* name)
  {
    return  CORBA_SeqUtil::find(nv, NVUtil::nv_find(name));
  }
  
  /*!
   * @if jp
   * @brief 指定された name の value の型が string であるか検証する
   * @else
   * 
   * @endif
   */
  bool isString(const SDOPackage::NVList& nv, const char* name)
  {
    try
      {
	CORBA::Any value;
	value = find(nv, name);
	const char* str_value;
	return value >>= str_value;
      }
    catch (...)
      {
	return false;
      }
  }
  
  /*!
   * @if jp
   * @brief 指定された name の value の型が指定した文字列と一致するか検証する
   * @else
   * 
   * @endif
   */
  bool isStringValue(const SDOPackage::NVList& nv,
		     const char* name, const char* value)
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
  
  /*!
   * @if jp
   * @brief 指定された name の NVList を string として返す。
   * @else
   * 
   * @endif
   */
  std::string toString(const SDOPackage::NVList& nv, const char* name)
  {
    const char* str_value;
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
  
  /*!
   * @if jp
   * @brief 指定された文字列を NVList の要素に追加する。
   * @else
   * 
   * @endif
   */
  bool appendStringValue(SDOPackage::NVList& nv, const char* name,
			 const char* value)
  {
    //    if (!isString(nv, name)) return false;
    
    CORBA::Long index;
    index = find_index(nv, name);
    
    if (index > 0)
      {
	const char* tmp_char;
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
  
  /*!
   * @if jp
   * @brief NVList に要素を追加する。
   * @else
   * 
   * @endif
   */
  void append(SDOPackage::NVList& dest, const SDOPackage::NVList& src)
  {
    for (CORBA::ULong i = 0, len = src.length(); i < len; ++i)
      {
	CORBA_SeqUtil::push_back(dest, src[i]);
      }
  }
  
  /*!
   * @if jp
   * @brief NVList に設定されている内容を文字列として出力する。
   * @else
   * 
   * @endif
   */
  void dump(SDOPackage::NVList& nv)
  {
    for (CORBA::ULong i(0), n(nv.length()); i < n; ++i)
      {
	const char* str_value;
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

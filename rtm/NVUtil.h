// -*- C++ -*-
/*!
 * @file NVUtil.h
 * @brief NameValue and NVList utility functions
 * @date $Date: 2006-11-10 04:46:15 $
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
 * $Id: NVUtil.h,v 1.2 2006-11-10 04:46:15 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/10 04:32:46  n-ando
 * NVUtil is SDOPackage::NVList utility.
 *
 *
 */
#include <string>
#include <rtm/idl/SDOPackageSkel.h>
#include <rtm/Properties.h>

namespace NVUtil
{
  /*!
   * @if jp
   *
   * @brief NameValue を生成する
   *
   * このオペレーションはNameValueを作成する。
   * CORBA::Char, CORBA::Boolean, CORBA::Octet は作成できない。
   * これらの値は newNVChar(), newNVBool(), newNVOctet() で作成する。
   *
   * @param name NameValue の name
   * @param value NameValue の value
   * @return NameValue
   *
   * @else
   *
   * @brief Create NameVale
   *
   * This operation creates NameVale.
   * CORBA::Char, CORBA::Boolean, CORBA::Octet creation is not supported.
   * These type of NameValue should be created by using 
   * newNVChar(), newNVBool(), newNVOctet() functions.
   *
   * @param name name of NameValue
   * @param value value of NameValue
   * @return NameValue
   *
   * @endif
   */
  template <class Value>
  SDOPackage::NameValue newNV(const char* name, Value value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= value;
    return nv;
  }


  /*!
   * @if jp
   *
   * @brief value が CORBA::string の NameValue を生成する
   *
   * このオペレーションはf value が CORBA::string の NameValueを作成する。
   *
   * @param name NameValue の name
   * @param value NameValue の value
   * @return NameValue
   *
   * @else
   *
   * @brief Create CORBA::string value type NameVale
   *
   * This operation creates CORBA::string value type NameVale.
   *
   * @param name name of NameValue
   * @param value value of NameValue
   * @return NameValue
   *
   * @endif
   */
  template <>
  SDOPackage::NameValue newNV(const char* name, const char* value)
  {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= value;
    return nv;
  }
    

  /*!
   * @if jp
   *
   * @brief value が CORBA::Char の NameValue を生成する
   *
   * このオペレーションはf value が CORBA::Char の NameValueを作成する。
   *
   * @param name NameValue の name
   * @param value NameValue の value
   * @return NameValue
   *
   * @else
   *
   * @brief Create CORBA::Char value type NameVale
   *
   * This operation creates CORBA::Char value type NameVale.
   *
   * @param name name of NameValue
   * @param value value of NameValue
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVChar(const char* name, const CORBA::Char value);
    

  /*!
   * @if jp
   *
   * @brief value が CORBA::Boolean の NameValue を生成する
   *
   * このオペレーションはf value が CORBA::Boolean の NameValueを作成する。
   *
   * @param name NameValue の name
   * @param value NameValue の value
   * @return NameValue
   *
   * @else
   *
   * @brief Create CORBA::Boolean value type NameVale
   *
   * This operation creates CORBA::Boolean value type NameVale.
   *
   * @param name name of NameValue
   * @param value value of NameValue
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVBool(const char* name,
				  const CORBA::Boolean value);

    
  /*!
   * @if jp
   *
   * @brief value が CORBA::Octet の NameValue を生成する
   *
   * このオペレーションはf value が CORBA::Octet の NameValueを作成する。
   *
   * @param name NameValue の name
   * @param value NameValue の value
   * @return NameValue
   *
   * @else
   *
   * @brief Create CORBA::Octet value type NameVale
   *
   * This operation creates CORBA::Octet value type NameVale.
   *
   * @param name name of NameValue
   * @param value value of NameValue
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVOctet(const char* name, const CORBA::Octet value);


  /*!
   * @if jp
   *
   * @brief Properties を NVList へコピーする
   *
   * このオペレーションは Properties を NVList へコピーする。
   * NVList の value は全て CORBA::string 型としてコピーする。
   *
   * @param nv Properties の値を格納する NVList
   * @param prop コピー元の Properties
   *
   * @else
   *
   * @brief Copy to NVList from Proeprties
   *
   * This operation copies Properties to NVList.
   * Created NVList's values are CORBA::string.
   *
   * @param nv NVList to store Properties values
   * @param prop Properties that is copies from
   *
   * @endif
   */
  void copy(SDOPackage::NVList& nv, RTC::Properties& prop);


  /*!
   * @if jp
   *
   * @brief NVList から name で指定された value を返す
   *
   * このオペレーションは name で指定された value を Any 型で返す。
   *
   * @param nv 検索対象の NVList
   * @param name 検索する名前
   *
   * @else
   *
   * @brief Get value in NVList specified by name
   *
   * This operation returns Any type of value specified by name.
   * Created NVList's values are CORBA::string.
   *
   * @param nv NVList to be searched
   * @param prop name to seartch in NVList
   *
   * @endif
   */
  const CORBA::Any& find(SDOPackage::NVList& nv, const char* name);


  /*!
   * @if jp
   *
   * @brief 指定された name の value の型が string であるかどうか？
   *
   * このオペレーションは name で指定された value の型が CORBA::string
   * かどうかを bool 値で返す。
   *
   * @param nv 検索対象の NVList
   * @param name 検索する名前
   *
   * @else
   *
   * @brief Whether the name of NVList's value is CORBA::string
   *
   * This operation returns boolean value whether the name of NVList's value
   * is CORBA::string.
   *
   * @param nv NVList to be searched
   * @param prop name to seartch in NVList
   *
   * @endif
   */
  bool isString(SDOPackage::NVList& nv, const char* name);

  /*!
   * @if jp
   *
   * @brief 指定された name の NVList を string として返す。
   *
   * このオペレーションは name で指定された NVList の値を string で返す。
   * もし、name で指定した value の値が CORBA::string でなければ、
   * 空の文字列のstringを返す。
   *
   * @param nv 検索対象の NVList
   * @param name 検索する名前
   * @return name に対応する値のstring型の値
   *
   * @else
   *
   * @brief Get string value in NVList specified by name
   *
   * This operation returns string value in NVList specified by name.
   * If the value in NVList specified by name is not CORBA::string type
   * this operation returns empty string value.
   *
   * @param nv NVList to be searched
   * @param name name to to serach
   * @return string value named by name
   *
   * @endif
   */
  std::string toString(SDOPackage::NVList& nv, const char* name);

};

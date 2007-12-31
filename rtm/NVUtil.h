// -*- C++ -*-
/*!
 * @file NVUtil.h
 * @brief NameValue and NVList utility functions
 * @date $Date: 2007-12-31 03:08:04 $
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
 * $Id: NVUtil.h,v 1.6.2.1 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.6  2007/04/23 04:54:32  n-ando
 * Conversion functions between Properties and NVList were added.
 *
 * Revision 1.5  2007/01/12 14:33:57  n-ando
 * The dump() function was added to dump NVList entries.
 *
 * Revision 1.4  2007/01/06 17:55:35  n-ando
 * toProperties()'s argument was changed to const.
 * Some functions were added.
 * - isStringValue()
 * - appendStringValue()
 * - append()
 *
 * Revision 1.3  2006/11/27 09:54:48  n-ando
 * Conversion function from NVList to Properties: toProperties() was added.
 *
 * Revision 1.2  2006/11/10 04:46:15  n-ando
 * Kanji-code was changed to EUC.
 *
 * Revision 1.1  2006/11/10 04:32:46  n-ando
 * NVUtil is SDOPackage::NVList utility.
 *
 *
 */

#ifndef NVUtil_h
#define NVUtil_h

#include <string>
#include <iostream>
#include <rtm/idl/SDOPackageSkel.h>
#include <rtm/Properties.h>

/*!
 * @if jp
 * @namespace NVUtil
 *
 * @brief NameValue 用ユーティリティ
 *
 * @else
 *
 * @namespace NVUtil
 *
 * @endif
 */
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
   *
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
   *
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
  
  /***
   * @if jp
   *
   * @brief value が CORBA::string の NameValue を生成する
   *
   * このオペレーションはf value が CORBA::string の NameValueを作成する。
   *
   * @param name NameValue の name
   * @param value NameValue の value
   *
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
   *
   * @return NameValue
   *
   * @endif
   */
  /*
    template <>
    SDOPackage::NameValue newNV(const char* name, const char* value)
    {
    SDOPackage::NameValue nv;
    nv.name = CORBA::string_dup(name);
    nv.value <<= value;
    return nv;
    }
  */ 
  
  /*!
   * @if jp
   *
   * @brief value が CORBA::Char の NameValue を生成する
   *
   * このオペレーションはf value が CORBA::Char の NameValueを作成する。
   *
   * @param name NameValue の name
   * @param value NameValue の value
   *
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
   *
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
   *
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
   *
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
   *
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
   *
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVOctet(const char* name, const CORBA::Octet value);
  
  /*!
   * @if jp
   *
   * @brief value が CORBA::Any の NameValue を生成する
   *
   * このオペレーションはf value が CORBA::Any の NameValueを作成する。
   *
   * @param name NameValue の name
   * @param value NameValue の value
   *
   * @return NameValue
   *
   * @else
   *
   * @brief Create CORBA::Any value type NameVale
   *
   * This operation creates CORBA::any value type NameVale.
   *
   * @param name name of NameValue
   * @param value value of NameValue
   *
   * @return NameValue
   *
   * @endif
   */
  SDOPackage::NameValue newNVAny(const char* name, const CORBA::Any& value);
  
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
  void copyFromProperties(SDOPackage::NVList& nv, const RTC::Properties& prop);
  
  /*!
   * @if jp
   *
   * @brief NVList を Properties へコピーする
   *
   * このオペレーションは NVList を Properties へコピーする。
   *
   * @param prop NVList の値を格納する Properties
   * @param nv コピー元の NVList
   *
   * @else
   *
   * @brief Copy to Proeprties from NVList
   *
   * This operation copies NVList to Properties.
   *
   * @param prop Properties to store NVList values
   * @param nv NVList that is copies from
   *
   * @endif
   */
  void copyToProperties(RTC::Properties& prop, const SDOPackage::NVList& nv);
  
  /*!
   * @if jp
   *
   * @brief NVList を Properties へ変換する
   *
   * このオペレーションは NVList を Properties へ変換する。
   *
   * @param nv 変換元の NVList
   *
   * @return 変換結果Property
   *
   * @else
   *
   * @endif
   */
  RTC::Properties toProperties(const SDOPackage::NVList& nv);
  
  /*!
   * @if jp
   *
   * @brief NVList から name で指定された value を返す
   *
   * このオペレーションは name で指定された value を Any 型で返す。
   * 指定した名称の要素が存在しない場合は例外を発生させる。
   *
   * @param nv 検索対象の NVList
   * @param name 検索する名前
   *
   * @return 検索結果
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
  const CORBA::Any& find(const SDOPackage::NVList& nv, const char* name);
  
  /*!
   * @if jp
   *
   * @brief name で指定された要素のインデックスを返す
   *
   * このオペレーションは name で指定された要素が格納されている位置の
   * インデックスを返す。
   *
   * @param nv 検索対象の NVList
   * @param name 検索する名前
   *
   * @return 検索対象のインデックス
   *
   * @else
   *
   * @endif
   */
  const CORBA::Long find_index(const SDOPackage::NVList& nv, const char* name);
  
  /*!
   * @if jp
   *
   * @brief 指定された name の value の型が string であるか検証する
   *
   * このオペレーションは name で指定された value の型が CORBA::string
   * かどうかを bool 値で返す。
   *
   * @param nv 検索対象の NVList
   * @param name 検索する名前
   *
   * @return string検証結果(string:true、それ以外:false)
   *
   * @else
   *
   * @endif
   */
  bool isString(const SDOPackage::NVList& nv, const char* name);
  
  /*!
   * @if jp
   *
   * @brief 指定された name の value の型が指定した文字列と一致するか検証する
   *
   * このオペレーションは name で指定された value の型が CORBA::string
   * かどうかを判断し、  CORBA::string である場合には指定した文字列と一致するか
   * をbool 値で返す。
   *
   * @param nv 検索対象の NVList
   * @param name 検索する名前
   * @param value 比較対象文字列
   *
   * @return 検証結果(文字列と一致:true、非一致:false)
   *
   * @else
   *
   * @endif
   */
  bool isStringValue(const SDOPackage::NVList& nv, const char* name,
		     const char* value);
  
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
   *
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
   *
   * @return string value named by name
   *
   * @endif
   */
  std::string toString(const SDOPackage::NVList& nv, const char* name);
  
  /*!
   * @if jp
   *
   * @brief 指定された文字列を NVList の要素に追加する。
   *
   * このオペレーションは name で指定された要素に value で指定された文字列を
   * 追加する。
   * name で指定した要素に既に value の値が設定されている場合には何もしない。
   * name で指定した要素に value の値が設定されていない場合は、 ","区切りで
   * value の値を追加する。
   * 指定された値を設定する。
   * name で指定した要素が存在しない場合は、 NVList の最後に新たな要素を追加し、
   * 指定された値を設定する。
   *
   * @param nv 検索対象の NVList
   * @param name 追加対象要素名
   * @param value 追加する文字列
   *
   * @return 追加操作結果
   *
   * @else
   *
   * @endif
   */
  bool appendStringValue(SDOPackage::NVList& nv, const char* name,
			 const char* value);
  
  /*!
   * @if jp
   *
   * @brief NVList に要素を追加する。
   *
   * このオペレーションは dest で指定された NVList に src で指定された要素を
   * 追加する。
   *
   * @param dest 追加される NVList
   * @param src 追加する NVList
   *
   * @else
   *
   * @endif
   */
  void append(SDOPackage::NVList& dest, const SDOPackage::NVList& src);
  
  /*!
   * @if jp
   *
   * @brief NVList に設定されている内容を文字列として出力する。
   *
   * 指定された NVList に設定された内容を文字列として出力する。
   * なお、設定されている要素が文字列型以外の場合には、その旨(文字列ではない)を
   * 出力する。
   *
   * @param nv 出力対象 NVList
   *
   * @else
   *
   * @endif
   */
  void dump(SDOPackage::NVList& nv);
};
#endif // NVUtil_h

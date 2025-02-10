// -*- C++ -*-
/*!
 * @file DataTypeUtil.h
 * @brief Data type utility function
 * @date $Date: 2020-03-17 15:06:58 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2006-2020
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_DATATYPEUTIL_H
#define RTC_DATATYPEUTIL_H

namespace CORBA_Util
{
  /*!
   * @if jp
   * @brief CORBA型のデータを別変数にコピーする
   * omniORBではSequence型のデータはコピーコンストラクタでfor文により各要素をコピーする処理を行うため、
   * Octet型の配列のデータのコピーにはmemcpyを使用する関数を独自に定義することで高速化する。
   *
   * @param data1 コピー先の変数
   * @param data2 コピー元の変数
   *
   * @else
   * @brief 
   *
   * @param data1 
   * @param data2 
   *
   * @endif
   */
  template <class T>
  void copyData(T& data1, const T& data2)
  {
     data1 = data2;
  }
} // namespace CORBA_Util


#endif  // RTC_DATATYPEUTIL_H

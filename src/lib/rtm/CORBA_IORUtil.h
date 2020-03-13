// -*- C++ -*-
/*!
 * @file CORBA_IORUtil.h
 * @brief CORBA IOR manipulation utility functions
 * @date $Date: 2007-12-31 03:06:24 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2010
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef CORBA_IORUTIL_H
#define CORBA_IORUTIL_H

#include <rtm/RTC.h>
#ifdef ORB_IS_ORBEXPRESS
#include <IOP.h>
#endif

#include <string>

/*!
 * @if jp
 * @namespace CORBA_IORUtil
 *
 * @brief CORBA IOR ヘルパー関数
 *
 *
 * @else
 *
 * @namespace CORBA_SeqUtil
 *
 * @brief CORBA IOR helper functions
 *
 * @endif
 */

namespace CORBA_IORUtil
{
  /*!
   * @if jp
   * @brief IOR 文字列をIOR構造体へ変換する
   *
   * @else
   * @brief Convert from IOR string to IOR structure
   *
   * @endif
   */
#if !defined(ORB_IS_ORBEXPRESS) && !defined(ORB_IS_TAO) && !defined(ORB_IS_RTORB)
  bool toIOR(const char* iorstr, IOP::IOR& ior);
#endif

  /*!
   * @if jp
   * @brief IOR構造体をIOR文字列へ変換する
   *
   * @else
   * @brief Convert from IOR structure to IOR string
   *
   * @endif
   */
#if !defined(ORB_IS_ORBEXPRESS) && !defined(ORB_IS_TAO) && !defined(ORB_IS_RTORB)
  bool toString(IOP::IOR& ior, std::string& iorstr);
#endif
  
  /*!
   * @if jp
   * @brief IOR内のエンドポイントを置換する
   * @else
   * @brief Replace endpoint address in IOR entry
   * @endif
   */
  bool replaceEndpoint(std::string& iorstr, const std::string& endpoint);

  /*!
   * @if jp
   * @brief IOR文字列から情報を抽出しフォーマット済みの文字列として返す
   * @else
   * @brief Extracts information from IOR string and returns formatted string
   * @endif
   */
  std::string formatIORinfo(const char* iorstr);
#if !defined(ORB_IS_ORBEXPRESS) && !defined(ORB_IS_TAO) && !defined(ORB_IS_RTORB)
  std::vector<IIOP::Address> getEndpoints(IOP::IOR& ior);


  void extractAddrs(IOP::MultipleComponentProfile& comp,
                    std::vector<IIOP::Address>& addr);
#endif

} // namespace CORBA_IORUtil
#endif // CORBA_IORUTIL_H

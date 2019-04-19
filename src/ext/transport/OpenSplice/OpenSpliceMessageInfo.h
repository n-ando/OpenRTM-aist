// -*- C++ -*-
/*!
 * @file  OpenSpliceMessageInfo.h
 * @brief OpenSplice Massage Type Info class
 * @date  $Date: 2019-02-05 03:08:03 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2019
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *
 *     All rights reserved.
 *
 *
 */

#ifndef RTC_OPENSPLICEMESSAGEINFO_H
#define RTC_OPENSPLICEMESSAGEINFO_H


#include <coil/Properties.h>
#include <coil/Factory.h>
#include <rtm/Manager.h>



namespace RTC
{
  /*!
   * @if jp
   *
   * @class OpenSpliceMessageInfo
   *
   * @brief OpenSpliceのメッセージ型に関する情報を格納する基底クラス
   *
   *
   * @since 2.0.0
   *
   * @else
   *
   * @class OpenSpliceessageInfo
   *
   * @brief 
   *
   *
   * @endif
   */
  
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef TRANSPORT_PLUGIN
    class __declspec(dllexport) OpenSpliceMessageInfoBase
#else
    class __declspec(dllimport) OpenSpliceMessageInfoBase
#endif
#else
    class OpenSpliceMessageInfoBase
#endif
  {
  public:
    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * @else
     *
     * @brief Destructor
     *
     * @endif
     */
    virtual ~OpenSpliceMessageInfoBase(void);
    /*!
     * @if jp
     *
     * @brief トピック名を装飾する
     *
     * @param topic 装飾前のトピック名
     * @return 装飾後のトピック名
     *
     * @else
     *
     * @brief 
     *
     * @param topic 
     * @return 
     *
     * @endif
     */
    virtual std::string topic_name(std::string topic) = 0;
    /*!
     * @if jp
     *
     * @brief データの型名取得
     *
     * @return 型名
     *
     * @else
     *
     * @brief
     *
     * @return
     *
     * @endif
     */
    virtual std::string data_type() = 0;
    /*!
     * @if jp
     *
     * @brief IDLファイルパスの取得
     *
     * @return IDLファイルのパス
     *
     * @else
     *
     * @brief
     *
     * @return
     *
     * @endif
     */
    virtual std::string idl_path() = 0;
  };


  typedef coil::GlobalFactory<OpenSpliceMessageInfoBase> OpenSpliceMessageInfoFactory;
}



#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef TRANSPORT_PLUGIN
  template class __declspec(dllexport) coil::GlobalFactory<RTC::OpenSpliceMessageInfoBase>;
#else
  extern template class __declspec(dllimport) coil::GlobalFactory<RTC::OpenSpliceMessageInfoBase>;
#endif
#endif

void OpenSpliceMessageInfoInit(const coil::Properties& prop);



#endif // RTC_OPENSPLICEMESSAGEINFO_H


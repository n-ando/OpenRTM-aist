// -*- C++ -*-
/*!
 * @file  FastRTPSMessageInfo.h
 * @brief Fast-RTPS Massage Type Info class
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

#ifndef RTC_FASTRTPSMESSAGEINFO_H
#define RTC_FASTRTPSMESSAGEINFO_H


#include <coil/Properties.h>
#include <coil/Factory.h>



namespace RTC
{
  /*!
   * @if jp
   *
   * @class FastRTPSMessageInfo
   *
   * @brief FastRTPSのメッセージ型に関する情報を格納する基底クラス
   *
   *
   * @since 2.0.0
   *
   * @else
   *
   * @class FastRTPSessageInfo
   *
   * @brief 
   *
   *
   * @endif
   */
  class FastRTPSMessageInfoBase
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
    virtual ~FastRTPSMessageInfoBase(void);
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
    virtual std::string topic_name(std::string topic);
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
    std::string data_type();
  protected:
    std::string m_dataType;

  };


  typedef coil::GlobalFactory<FastRTPSMessageInfoBase> FastRTPSMessageInfoFactory;
}



#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef TRANSPORT_PLUGIN
  template class __declspec(dllexport) coil::GlobalFactory<RTC::FastRTPSMessageInfoBase>;
#else
  extern template class __declspec(dllimport) coil::GlobalFactory<RTC::FastRTPSMessageInfoBase>;
#endif
#endif




#endif // RTC_FASTRTPSMESSAGEINFO_H


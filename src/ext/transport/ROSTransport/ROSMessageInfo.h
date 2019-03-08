// -*- C++ -*-
/*!
 * @file  ROSMessageInfo.h
 * @brief ROS Massage Type Info class
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

#ifndef RTC_ROSMESSAGEINFO_H
#define RTC_ROSMESSAGEINFO_H


#include <coil/Properties.h>
#include <coil/Factory.h>
#include <ros/builtin_message_traits.h>



namespace RTC
{
  /*!
   * @if jp
   *
   * @class ROSMessageInfo
   *
   * @brief ROSのメッセージ型に関する情報を格納する基底クラス
   *
   *
   * @since 2.0.0
   *
   * @else
   *
   * @class ROSMessageInfo
   *
   * @brief 
   *
   *
   * @endif
   */
  class ROSMessageInfoBase
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
    virtual ~ROSMessageInfoBase(void) {}
    std::string type();
    std::string md5sum();
    std::string message_definition();
  protected:
    std::string m_type;
    std::string m_md5sum;
    std::string m_message_definition;

  };

  template <class MessageType>
  class ROSMessageInfo : public ROSMessageInfoBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * @else
     *
     * @brief Constructor
     *
     * @endif
     */
    ROSMessageInfo()
    {
      m_type = ros::message_traits::DataType<MessageType>::value();
      m_md5sum = ros::message_traits::MD5Sum<MessageType>::value();
      m_message_definition = ros::message_traits::Definition<MessageType>::value();
    }

  };

  typedef coil::GlobalFactory<ROSMessageInfoBase> ROSMessageInfoFactory;
}


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef TRANSPORT_PLUGIN
  template class __declspec(dllexport) coil::GlobalFactory<RTC::ROSMessageInfoBase;
#else
  extern template class __declspec(dllimport) coil::GlobalFactory<RTC::ROSMessageInfoBase;
#endif
#endif




#endif // RTC_ROSMESSAGEINFO_H


// -*- C++ -*-
/*!
 * @file  ROS2MessageInfo.h
 * @brief ROS2 Massage Type Info class
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

#ifndef RTC_ROS2MESSAGEINFO_H
#define RTC_ROS2MESSAGEINFO_H


#include <coil/Properties.h>
#include <coil/Factory.h>
#include <coil/stringutil.h>
#include <FastRTPS/FastRTPSMessageInfo.h>

#include <std_msgs/msg/float32.hpp>
#include <std_msgs/msg/float64.hpp>
#include <std_msgs/msg/int8.hpp>
#include <std_msgs/msg/int16.hpp>
#include <std_msgs/msg/int32.hpp>
#include <std_msgs/msg/int64.hpp>
#include <std_msgs/msg/u_int8.hpp>
#include <std_msgs/msg/u_int16.hpp>
#include <std_msgs/msg/u_int32.hpp>
#include <std_msgs/msg/u_int64.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <std_msgs/msg/int8_multi_array.hpp>
#include <std_msgs/msg/int16_multi_array.hpp>
#include <std_msgs/msg/int32_multi_array.hpp>
#include <std_msgs/msg/int64_multi_array.hpp>
#include <std_msgs/msg/u_int8_multi_array.hpp>
#include <std_msgs/msg/u_int16_multi_array.hpp>
#include <std_msgs/msg/u_int32_multi_array.hpp>
#include <std_msgs/msg/u_int64_multi_array.hpp>
#include <std_msgs/msg/string.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <geometry_msgs/msg/quaternion_stamped.hpp>
#include <geometry_msgs/msg/vector3_stamped.hpp>
#include <sensor_msgs/msg/image.hpp>



namespace RTC
{
  /*!
   * @if jp
   *
   * @class ROS2MessageInfo
   *
   * @brief ROS2のメッセージ型に関する格納する基底クラス
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
  template <class MessageType>
  class ROS2MessageInfo : public FastRTPSMessageInfoBase
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
    ROS2MessageInfo() = default;
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
    ~ROS2MessageInfo(void) override = default;

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
    std::string topic_name(std::string topic) override
    {
        std::string ret = "rt/" + topic;
        return ret;
    }
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
    std::string data_type() override
    {
        std::string str = rosidl_generator_traits::data_type<MessageType>();
        coil::vstring str_list = coil::split(str, "::");
        if(str_list.size() != 3)
        {
            return "";
        }
        std::string package_name = str_list[0];
        std::string type_name = str_list[1];
        std::string data_name = str_list[2];
        std::string ret = str_list[0]+"::"+type_name+"::dds_"+"::"+data_name+"_";

        return ret;
    }

  };
}



#endif // RTC_ROS2MESSAGEINFO_H


// -*- C++ -*-
/*!
 * @file  ROS2Serializer.cpp
 * @brief ROS2Serializer class
 * @date  $Date: 2019-01-31 03:08:03 $
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


#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

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
#include <std_msgs/msg/string.h>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <geometry_msgs/msg/quaternion_stamped.hpp>
#include <geometry_msgs/msg/vector3_stamped.hpp>
#include <sensor_msgs/msg/image.hpp>

#include "ROS2Serializer.h"
#include "ROS2MessageInfo.h"


namespace RTC
{
  
  /*!
   * @if jp
   *
   * @brief 単純なデータ型のシリアライザを登録するテンプレート関数
   * 
   * @param name シリアライザの名前
   *
   * @else
   *
   * @brief 
   * 
   * @param name 
   *
   * @endif
   */
  template <class DataType, class MessageType, typename originalType, typename convertedType>
  void ROS2SimpleDataInitBaseFunc(const char* name)
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<DataType> >::
            instance().addFactory(name,
            ::coil::Creator< ::RTC::ByteDataStream<DataType>,
            RTC::ROS2SimpleData<DataType, MessageType, originalType, convertedType> >,
            ::coil::Destructor< ::RTC::ByteDataStream<DataType>,
            RTC::ROS2SimpleData<DataType, MessageType, originalType, convertedType> >);

    RTC::FastRTPSMessageInfoFactory::
            instance().addFactory(name,
            ::coil::Creator< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<MessageType> >,
            ::coil::Destructor< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<MessageType> >);
  }

  /*!
   * @if jp
   *
   * @brief 単純なデータ型のシリアライザを登録するテンプレート関数
   * 
   *
   * @else
   *
   * @brief 
   * 
   *
   * @endif
   */
  template <class DataType, typename originalType>
  void ROS2SimpleDataInit()
  {
    ROS2SimpleDataInitBaseFunc<DataType, std_msgs::msg::Float32, originalType, float>("ROS2Float32");
    ROS2SimpleDataInitBaseFunc<DataType, std_msgs::msg::Float64, originalType, float>("ROS2Float64");
    ROS2SimpleDataInitBaseFunc<DataType, std_msgs::msg::Int8, originalType, char>("ROS2Int8");
    ROS2SimpleDataInitBaseFunc<DataType, std_msgs::msg::Int16, originalType, short>("ROS2Int16");
    ROS2SimpleDataInitBaseFunc<DataType, std_msgs::msg::Int32, originalType, long>("ROS2Int32");
    ROS2SimpleDataInitBaseFunc<DataType, std_msgs::msg::Int64, originalType, long long>("ROS2Int64");
    ROS2SimpleDataInitBaseFunc<DataType, std_msgs::msg::UInt8, originalType, unsigned char>("ROS2UInt8");
    ROS2SimpleDataInitBaseFunc<DataType, std_msgs::msg::UInt16, originalType, unsigned short>("ROS2UInt16");
    ROS2SimpleDataInitBaseFunc<DataType, std_msgs::msg::UInt32, originalType, unsigned long>("ROS2UInt32");
    ROS2SimpleDataInitBaseFunc<DataType, std_msgs::msg::UInt64, originalType, unsigned long long>("ROS2UInt64");
    
  }

  /*!
   * @if jp
   *
   * @brief 配列データ型のシリアライザを登録するテンプレート関数
   * 
   * @param name シリアライザの名前
   *
   * @else
   *
   * @brief 
   * 
   * @param name 
   *
   * @endif
   */
  template <class DataType, class MessageType, typename originalType, typename convertedType>
  void ROS2SequenceDataInitBaseFunc(const char* name)
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<DataType> >::
            instance().addFactory(name,
            ::coil::Creator< ::RTC::ByteDataStream<DataType>,
            RTC::ROS2SequenceData<DataType, MessageType, originalType, convertedType> >,
            ::coil::Destructor< ::RTC::ByteDataStream<DataType>,
            RTC::ROS2SequenceData<DataType, MessageType, originalType, convertedType> >);

    RTC::FastRTPSMessageInfoFactory::
            instance().addFactory(name,
            ::coil::Creator< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<MessageType> >,
            ::coil::Destructor< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<MessageType> >);
  }

  /*!
   * @if jp
   *
   * @brief 配列データ型のシリアライザを登録するテンプレート関数
   * 
   *
   * @else
   *
   * @brief 
   * 
   *
   * @endif
   */
  template <class DataType, typename originalType>
  void ROS2SequenceDataInit()
  {
    ROS2SequenceDataInitBaseFunc<DataType, std_msgs::msg::Float32MultiArray, originalType, float>("ROSFloat32MultiArray");
    ROS2SequenceDataInitBaseFunc<DataType, std_msgs::msg::Float64MultiArray, originalType, float>("ROSFloat64MultiArray");
    ROS2SequenceDataInitBaseFunc<DataType, std_msgs::msg::Int8MultiArray, originalType, char>("ROSInt8MultiArray");
    ROS2SequenceDataInitBaseFunc<DataType, std_msgs::msg::Int16MultiArray, originalType, short>("ROSInt16MultiArray");
    ROS2SequenceDataInitBaseFunc<DataType, std_msgs::msg::Int32MultiArray, originalType, long>("ROSInt32MultiArray");
    ROS2SequenceDataInitBaseFunc<DataType, std_msgs::msg::Int64MultiArray, originalType, long long>("ROSInt64MultiArray");
    ROS2SequenceDataInitBaseFunc<DataType, std_msgs::msg::UInt8MultiArray, originalType, unsigned char>("ROSUInt8MultiArray");
    ROS2SequenceDataInitBaseFunc<DataType, std_msgs::msg::UInt16MultiArray, originalType, unsigned short>("ROSUInt16MultiArray");
    ROS2SequenceDataInitBaseFunc<DataType, std_msgs::msg::UInt32MultiArray, originalType, unsigned long>("ROSUInt32MultiArray");
    ROS2SequenceDataInitBaseFunc<DataType, std_msgs::msg::UInt64MultiArray, originalType, unsigned long long>("ROSUInt64MultiArray");
  }

#if !(defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
  /*!
   * @if jp
   *
   * @class ROS2StringData
   *
   * @brief RTC::TimedString<-->std_msgs::Stringのシリアライザ
   *
   *
   * @since 2.0.0
   *
   * @else
   *
   * @class ROS2StringData
   *
   * @brief 
   *
   *
   * @since 2.0.0
   *
   * @endif
   */
  class ROS2StringData : public ROS2SerializerBase<RTC::TimedString>
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
    ROS2StringData()
    {

    }
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
    virtual ~ROS2StringData()
    {

    }

    /*!
     * @if jp
     *
     * @brief データの符号化
     * 
     * @param data 符号化前のデータ
     * @return true：符号化成功、false：失敗
     *
     * @else
     *
     * @brief 
     * 
     * @param data 
     * @return 
     *
     * @endif
     */
    virtual bool serialize(const RTC::TimedString& data)
    {
        
      std_msgs::msg::String msg;
      msg.data = data.data;
      
      return ROS2SerializerBase<RTC::TimedString>::stdmsg_serialize(msg);
    };
    /*!
     * @if jp
     *
     * @brief データの復号化
     * 
     * @param data 復号化後のデータを格納する変数
     * @return true：復号化成功、false：失敗
     *
     * @else
     *
     * @brief 
     * 
     * @param data 
     * @return 
     *
     * @endif
     */
    virtual bool deserialize(RTC::TimedString& data)
    { 

      std_msgs::msg::String msg;
        
      bool ret = ROS2SerializerBase<RTC::TimedString>::stdmsg_deserialize(msg);

      data.data = CORBA::string_dup(msg.data.c_str());

      return ret;
    };
  };

  /*!
   * @if jp
   *
   * @brief RTC::TimedString<-->std_msgs::Stringのシリアライザを登録する
   * 
   *
   * @else
   *
   * @brief 
   * 
   *
   * @endif
   */
  void ROS2StringDataInit()
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedString> >::
            instance().addFactory("ROS2String",
            ::coil::Creator< ::RTC::ByteDataStream<RTC::TimedString>,
            RTC::ROS2StringData>,
            ::coil::Destructor< ::RTC::ByteDataStream<RTC::TimedString>,
            RTC::ROS2StringData>);

    RTC::FastRTPSMessageInfoFactory::
            instance().addFactory("ROS2String",
            ::coil::Creator< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<std_msgs::msg::String> >,
            ::coil::Destructor< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<std_msgs::msg::String> >);
  }
#endif
  /*!
   * @if jp
   *
   * @class ROS2Point3DData
   *
   * @brief RTC::TimedPoint3D<-->geometry_msgs::PointStampedのシリアライザ
   *
   *
   * @since 2.0.0
   *
   * @else
   *
   * @class ROS2Point3DData
   *
   * @brief 
   *
   *
   * @since 2.0.0
   *
   * @endif
   */
  class ROS2Point3DData : public ROS2SerializerBase<RTC::TimedPoint3D>
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
    ROS2Point3DData()
    {

    }

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
    virtual ~ROS2Point3DData()
    {

    }

    /*!
     * @if jp
     *
     * @brief データの符号化
     * 
     * @param data 符号化前のデータ
     * @return true：符号化成功、false：失敗
     *
     * @else
     *
     * @brief 
     * 
     * @param data 
     * @return 
     *
     * @endif
     */
    virtual bool serialize(const RTC::TimedPoint3D& data)
    {
        
      geometry_msgs::msg::PointStamped msg;
      msg.header.stamp.sec = data.tm.sec;
      msg.header.stamp.nanosec = data.tm.nsec;
      msg.point.x = data.data.x;
      msg.point.y = data.data.y;
      msg.point.z = data.data.z;
      
      return ROS2SerializerBase<RTC::TimedPoint3D>::geometrymsg_serialize(msg);
    }

    /*!
     * @if jp
     *
     * @brief データの復号化
     * 
     * @param data 復号化後のデータを格納する変数
     * @return true：復号化成功、false：失敗
     *
     * @else
     *
     * @brief 
     * 
     * @param data 
     * @return 
     *
     * @endif
     */
    virtual bool deserialize(RTC::TimedPoint3D& data)
    { 

      geometry_msgs::msg::PointStamped msg;
      
      bool ret = ROS2SerializerBase<RTC::TimedPoint3D>::geometrymsg_deserialize(msg);

      data.tm.sec = msg.header.stamp.sec;
      data.tm.nsec = msg.header.stamp.nanosec;
      data.data.x = msg.point.x;
      data.data.y = msg.point.y;
      data.data.z = msg.point.z;

      return ret;
    }
  };

  /*!
   * @if jp
   *
   * @brief RTC::TimedPoint3D<-->geometry_msgs::PointStampedのシリアライザを登録する
   * 
   *
   * @else
   *
   * @brief 
   * 
   *
   * @endif
   */
  void ROS2Pont3DDataInit()
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedPoint3D> >::
            instance().addFactory("ROS2PointStamped",
            ::coil::Creator< ::RTC::ByteDataStream<RTC::TimedPoint3D>,
            RTC::ROS2Point3DData>,
            ::coil::Destructor< ::RTC::ByteDataStream<RTC::TimedPoint3D>,
            RTC::ROS2Point3DData>);

    RTC::FastRTPSMessageInfoFactory::
            instance().addFactory("ROS2PointStamped",
            ::coil::Creator< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<geometry_msgs::msg::PointStamped> >,
            ::coil::Destructor< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<geometry_msgs::msg::PointStamped> >);
  }

  /*!
   * @if jp
   *
   * @class ROS2QuaternionData
   *
   * @brief RTC::TimedQuaternion<-->geometry_msgs::QuaternionStampedのシリアライザ
   *
   *
   * @since 2.0.0
   *
   * @else
   *
   * @class ROS2QuaternionData
   *
   * @brief 
   *
   *
   * @since 2.0.0
   *
   * @endif
   */
  class ROS2QuaternionData : public ROS2SerializerBase<RTC::TimedQuaternion>
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
    ROS2QuaternionData()
    {

    }
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
    virtual ~ROS2QuaternionData()
    {

    }

    /*!
     * @if jp
     *
     * @brief データの符号化
     * 
     * @param data 符号化前のデータ
     * @return true：符号化成功、false：失敗
     *
     * @else
     *
     * @brief 
     * 
     * @param data 
     * @return 
     *
     * @endif
     */
    virtual bool serialize(const RTC::TimedQuaternion& data)
    {
        
      geometry_msgs::msg::QuaternionStamped  msg;
      msg.header.stamp.sec = data.tm.sec;
      msg.header.stamp.nanosec = data.tm.nsec;
      msg.quaternion.x = data.data.x;
      msg.quaternion.y = data.data.y;
      msg.quaternion.z = data.data.z;
      msg.quaternion.w = data.data.w;
      
      
      return ROS2SerializerBase<RTC::TimedQuaternion>::geometrymsg_serialize(msg);
    };

    /*!
     * @if jp
     *
     * @brief データの復号化
     * 
     * @param data 復号化後のデータを格納する変数
     * @return true：復号化成功、false：失敗
     *
     * @else
     *
     * @brief 
     * 
     * @param data 
     * @return 
     *
     * @endif
     */
    virtual bool deserialize(RTC::TimedQuaternion& data)
    { 

      geometry_msgs::msg::QuaternionStamped msg;
      
      bool ret = ROS2SerializerBase<RTC::TimedQuaternion>::geometrymsg_deserialize(msg);
      data.tm.sec = msg.header.stamp.sec;
      data.tm.nsec = msg.header.stamp.nanosec;
      data.data.x = msg.quaternion.x;
      data.data.y = msg.quaternion.y;
      data.data.z = msg.quaternion.z;
      data.data.w = msg.quaternion.w;

      return ret;
    }
  };

  /*!
   * @if jp
   *
   * @brief RTC::TimedQuaternion<-->geometry_msgs::QuaternionStampedのシリアライザを登録する
   * 
   *
   * @else
   *
   * @brief 
   * 
   *
   * @endif
   */
  void ROS2QuaternionDataInit()
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedQuaternion> >::
            instance().addFactory("ROS2QuaternionStamped",
            ::coil::Creator< ::RTC::ByteDataStream<RTC::TimedQuaternion>,
            RTC::ROS2QuaternionData>,
            ::coil::Destructor< ::RTC::ByteDataStream<RTC::TimedQuaternion>,
            RTC::ROS2QuaternionData>);

    RTC::FastRTPSMessageInfoFactory::
            instance().addFactory("ROS2QuaternionStamped",
            ::coil::Creator< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<geometry_msgs::msg::QuaternionStamped > >,
            ::coil::Destructor< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<geometry_msgs::msg::QuaternionStamped > >);
  }

  /*!
   * @if jp
   *
   * @class ROS2Vector3DData
   *
   * @brief RTC::TimedVector3D<-->geometry_msgs::Vector3Stampedのシリアライザ
   *
   *
   * @since 2.0.0
   *
   * @else
   *
   * @class ROS2Vector3DData
   *
   * @brief 
   *
   *
   * @since 2.0.0
   *
   * @endif
   */
  class ROS2Vector3DData : public ROS2SerializerBase<RTC::TimedVector3D>
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
    ROS2Vector3DData()
    {

    }
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
    virtual ~ROS2Vector3DData()
    {

    }

    /*!
     * @if jp
     *
     * @brief データの符号化
     * 
     * @param data 符号化前のデータ
     * @return true：符号化成功、false：失敗
     *
     * @else
     *
     * @brief 
     * 
     * @param data 
     * @return 
     *
     * @endif
     */
    virtual bool serialize(const RTC::TimedVector3D& data)
    {
        
      geometry_msgs::msg::Vector3Stamped  msg;
      msg.header.stamp.sec = data.tm.sec;
      msg.header.stamp.nanosec = data.tm.nsec;
      msg.vector.x = data.data.x;
      msg.vector.y = data.data.y;
      msg.vector.z = data.data.z;

      
      return ROS2SerializerBase<RTC::TimedVector3D>::geometrymsg_serialize(msg);
    }

    /*!
     * @if jp
     *
     * @brief データの復号化
     * 
     * @param data 復号化後のデータを格納する変数
     * @return true：復号化成功、false：失敗
     *
     * @else
     *
     * @brief 
     * 
     * @param data 
     * @return 
     *
     * @endif
     */
    virtual bool deserialize(RTC::TimedVector3D& data)
    { 

      geometry_msgs::msg::Vector3Stamped msg;
      
      bool ret = ROS2SerializerBase<RTC::TimedVector3D>::geometrymsg_deserialize(msg);

      data.tm.sec = msg.header.stamp.sec;
      data.tm.nsec = msg.header.stamp.nanosec;
      data.data.x = msg.vector.x;
      data.data.y = msg.vector.y;
      data.data.z = msg.vector.z;

      return ret;
    }
  };

  /*!
   * @if jp
   *
   * @brief RTC::TimedVector3D<-->geometry_msgs::Vector3Stampedのシリアライザを登録する
   * 
   *
   * @else
   *
   * @brief 
   * 
   *
   * @endif
   */
  void ROS2Vector3DDataInit()
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedVector3D> >::
            instance().addFactory("ROS2Vector3Stamped",
            ::coil::Creator< ::RTC::ByteDataStream<RTC::TimedVector3D>,
            RTC::ROS2Vector3DData>,
            ::coil::Destructor< ::RTC::ByteDataStream<RTC::TimedVector3D>,
            RTC::ROS2Vector3DData>);

    RTC::FastRTPSMessageInfoFactory::
            instance().addFactory("ROS2Vector3Stamped",
            ::coil::Creator< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<geometry_msgs::msg::Vector3Stamped > >,
            ::coil::Destructor< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<geometry_msgs::msg::Vector3Stamped > >);
  }

  
  /*!
   * @if jp
   *
   * @class ROS2CameraImageData
   *
   * @brief RTC::CameraImage<-->sensor_msgs::Imageのシリアライザ
   *
   *
   * @since 2.0.0
   *
   * @else
   *
   * @class ROS2CameraImageData
   *
   * @brief 
   *
   *
   * @since 2.0.0
   *
   * @endif
   */
  class ROS2CameraImageData : public ROS2SerializerBase<RTC::CameraImage>
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
    ROS2CameraImageData()
    {

    }
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
    virtual ~ROS2CameraImageData()
    {

    }

    /*!
     * @if jp
     *
     * @brief データの符号化
     * 
     * @param data 符号化前のデータ
     * @return true：符号化成功、false：失敗
     *
     * @else
     *
     * @brief 
     * 
     * @param data 
     * @return 
     *
     * @endif
     */
    virtual bool serialize(const RTC::CameraImage& data)
    {
        
      sensor_msgs::msg::Image  msg;
      msg.header.stamp.sec = data.tm.sec;
      msg.header.stamp.nanosec = data.tm.nsec;
      msg.height = data.height;
      msg.width = data.width;
      if(std::string(data.format).empty())
      {
        msg.encoding = "rgb8";
      }
      else
      {
        msg.encoding = data.format;
      }
      msg.step = 1920;
      msg.data.resize(data.pixels.length());
      memcpy(&msg.data[0], &data.pixels[0], data.pixels.length());

      
      return ROS2SerializerBase<RTC::CameraImage>::sensormsg_serialize(msg);
    }
    /*!
     * @if jp
     *
     * @brief データの復号化
     * 
     * @param data 復号化後のデータを格納する変数
     * @return true：復号化成功、false：失敗
     *
     * @else
     *
     * @brief 
     * 
     * @param data 
     * @return 
     *
     * @endif
     */
    virtual bool deserialize(RTC::CameraImage& data)
    { 

      sensor_msgs::msg::Image msg;
      
      bool ret = ROS2SerializerBase<RTC::CameraImage>::sensormsg_deserialize(msg);
      
      
      data.tm.sec = msg.header.stamp.sec;
      data.tm.nsec = msg.header.stamp.nanosec;
      data.height = msg.height;
      data.width = msg.width;
      data.format = CORBA::string_dup(msg.encoding.c_str());


      data.pixels.length((CORBA::ULong)msg.data.size());
      
      memcpy(&data.pixels[0], &msg.data[0], data.pixels.length());

      return ret;
    }
  };

  /*!
   * @if jp
   *
   * @brief RTC::CameraImage<-->sensor_msgs::Imageのシリアライザを登録する
   * 
   *
   * @else
   *
   * @brief 
   * 
   *
   * @endif
   */
  void ROS2CameraImageDataInit()
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<RTC::CameraImage> >::
            instance().addFactory("ROS2Image",
            ::coil::Creator< ::RTC::ByteDataStream<RTC::CameraImage>,
            RTC::ROS2CameraImageData>,
            ::coil::Destructor< ::RTC::ByteDataStream<RTC::CameraImage>,
            RTC::ROS2CameraImageData>);

    RTC::FastRTPSMessageInfoFactory::
            instance().addFactory("ROS2Image",
            ::coil::Creator< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<sensor_msgs::msg::Image > >,
            ::coil::Destructor< ::RTC::FastRTPSMessageInfoBase,
            RTC::ROS2MessageInfo<sensor_msgs::msg::Image > >);
  }

}


extern "C"
{
  /*!
   * @if jp
   * @brief モジュール初期化関数
   * @else
   * @brief Module initialization
   * @endif
   */
  void ROS2SerializerInit(RTC::Manager* manager)
  {
    (void)manager;
    
    RTC::ROS2SimpleDataInit<RTC::TimedState, CORBA::Short>();
    RTC::ROS2SimpleDataInit<RTC::TimedShort, CORBA::Short>();
    RTC::ROS2SimpleDataInit<RTC::TimedLong, CORBA::Long>();
    RTC::ROS2SimpleDataInit<RTC::TimedUShort, CORBA::UShort>();
    RTC::ROS2SimpleDataInit<RTC::TimedULong, CORBA::ULong>();
    RTC::ROS2SimpleDataInit<RTC::TimedFloat, CORBA::Float>();
    RTC::ROS2SimpleDataInit<RTC::TimedDouble, CORBA::Double>();

    RTC::ROS2SequenceDataInit<RTC::TimedShortSeq, CORBA::Short>();
    RTC::ROS2SequenceDataInit<RTC::TimedLongSeq, CORBA::Long>();
    RTC::ROS2SequenceDataInit<RTC::TimedUShortSeq, CORBA::UShort>();
    RTC::ROS2SequenceDataInit<RTC::TimedULongSeq, CORBA::ULong>();
    RTC::ROS2SequenceDataInit<RTC::TimedFloatSeq, CORBA::Float>();
    RTC::ROS2SequenceDataInit<RTC::TimedDoubleSeq, CORBA::Double>();
#if !(defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
    RTC::ROS2StringDataInit();
#endif
    RTC::ROS2Pont3DDataInit();
    RTC::ROS2QuaternionDataInit();
    RTC::ROS2Vector3DDataInit();
    RTC::ROS2CameraImageDataInit();
  }
}



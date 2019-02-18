// -*- C++ -*-
/*!
 * @file  ROSSerializer.cpp
 * @brief ROSSerializer class
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
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int64.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt32.h>
#include <std_msgs/UInt64.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Int8MultiArray.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Int64MultiArray.h>
#include <std_msgs/UInt8MultiArray.h>
#include <std_msgs/UInt16MultiArray.h>
#include <std_msgs/UInt32MultiArray.h>
#include <std_msgs/UInt64MultiArray.h>
#include <std_msgs/String.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <sensor_msgs/Image.h>
#include "ROSSerializer.h"
#include "ROSMessageInfo.h"


namespace RTC
{
  

  template <class DataType, class MessageType>
  void ROSSimpleDataInitBaseFunc(const char* name)
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<DataType> >::
            instance().addFactory(name,
            ::coil::Creator< ::RTC::ByteDataStream<DataType>,
            RTC::ROSSimpleData<DataType, MessageType> >,
            ::coil::Destructor< ::RTC::ByteDataStream<DataType>,
            RTC::ROSSimpleData<DataType, MessageType> >);

    RTC::ROSMessageInfoFactory::
            instance().addFactory(name,
            ::coil::Creator< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<MessageType> >,
            ::coil::Destructor< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<MessageType> >);
  }

  template <class DataType>
  void ROSSimpleDataInit()
  {
    ROSSimpleDataInitBaseFunc<DataType, std_msgs::Float32>("ROSFloat32");
    ROSSimpleDataInitBaseFunc<DataType, std_msgs::Float64>("ROSFloat64");
    ROSSimpleDataInitBaseFunc<DataType, std_msgs::Int8>("ROSInt8");
    ROSSimpleDataInitBaseFunc<DataType, std_msgs::Int16>("ROSInt16");
    ROSSimpleDataInitBaseFunc<DataType, std_msgs::Int32>("ROSInt32");
    ROSSimpleDataInitBaseFunc<DataType, std_msgs::Int64>("ROSInt64");
    ROSSimpleDataInitBaseFunc<DataType, std_msgs::UInt8>("ROSUInt8");
    ROSSimpleDataInitBaseFunc<DataType, std_msgs::UInt16>("ROSUInt16");
    ROSSimpleDataInitBaseFunc<DataType, std_msgs::UInt32>("ROSUInt32");
    ROSSimpleDataInitBaseFunc<DataType, std_msgs::UInt64>("ROSUInt64");
  }


  template <class DataType, class MessageType>
  void ROSSequenceDataInitBaseFunc(const char* name)
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<DataType> >::
            instance().addFactory(name,
            ::coil::Creator< ::RTC::ByteDataStream<DataType>,
            RTC::ROSSequenceData<DataType, MessageType> >,
            ::coil::Destructor< ::RTC::ByteDataStream<DataType>,
            RTC::ROSSequenceData<DataType, MessageType> >);

    RTC::ROSMessageInfoFactory::
            instance().addFactory(name,
            ::coil::Creator< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<MessageType> >,
            ::coil::Destructor< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<MessageType> >);
  }

  template <class DataType>
  void ROSSequenceDataInit()
  {
    ROSSequenceDataInitBaseFunc<DataType, std_msgs::Float32MultiArray>("ROSFloat32MultiArray");
    ROSSequenceDataInitBaseFunc<DataType, std_msgs::Float64MultiArray>("ROSFloat64MultiArray");
    ROSSequenceDataInitBaseFunc<DataType, std_msgs::Int8MultiArray>("ROSInt8MultiArray");
    ROSSequenceDataInitBaseFunc<DataType, std_msgs::Int16MultiArray>("ROSInt16MultiArray");
    ROSSequenceDataInitBaseFunc<DataType, std_msgs::Int32MultiArray>("ROSInt32MultiArray");
    ROSSequenceDataInitBaseFunc<DataType, std_msgs::Int64MultiArray>("ROSInt64MultiArray");
    ROSSequenceDataInitBaseFunc<DataType, std_msgs::UInt8MultiArray>("ROSUInt8MultiArray");
    ROSSequenceDataInitBaseFunc<DataType, std_msgs::UInt16MultiArray>("ROSUInt16MultiArray");
    ROSSequenceDataInitBaseFunc<DataType, std_msgs::UInt32MultiArray>("ROSUInt32MultiArray");
    ROSSequenceDataInitBaseFunc<DataType, std_msgs::UInt64MultiArray>("ROSUInt64MultiArray");
  }


  class ROSStringData : public ROSSerializerBase<RTC::TimedString>
  {
  public:
    ROSStringData()
    {

    }
    virtual ~ROSStringData()
    {

    }


    virtual bool serialize(const RTC::TimedString& data)
    {
        
      std_msgs::String msg;
      msg.data = data.data;
      
      ROSSerializerBase<RTC::TimedString>::m_message = ros::serialization::serializeMessage<std_msgs::String>(msg);

      return true;
    };
    virtual bool deserialize(RTC::TimedString& data)
    { 

      std_msgs::String msg;
        
      ros::serialization::deserializeMessage(ROSSerializerBase<RTC::TimedString>::m_message, msg);
      data.data = CORBA::string_dup(msg.data.c_str());

      return true;
    };
  };

  void ROSStringDataInit()
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedString> >::
            instance().addFactory("ROSString",
            ::coil::Creator< ::RTC::ByteDataStream<RTC::TimedString>,
            RTC::ROSStringData>,
            ::coil::Destructor< ::RTC::ByteDataStream<RTC::TimedString>,
            RTC::ROSStringData>);

    RTC::ROSMessageInfoFactory::
            instance().addFactory("ROSString",
            ::coil::Creator< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<std_msgs::String> >,
            ::coil::Destructor< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<std_msgs::String> >);
  }

  class ROSPoint3DData : public ROSSerializerBase<RTC::TimedPoint3D>
  {
  public:
    ROSPoint3DData()
    {

    }
    virtual ~ROSPoint3DData()
    {

    }


    virtual bool serialize(const RTC::TimedPoint3D& data)
    {
        
      geometry_msgs::PointStamped msg;
      msg.header.stamp.sec = data.tm.sec;
      msg.header.stamp.nsec = data.tm.nsec;
      msg.point.x = data.data.x;
      msg.point.y = data.data.y;
      msg.point.z = data.data.z;
      
      ROSSerializerBase<RTC::TimedPoint3D>::m_message = ros::serialization::serializeMessage<geometry_msgs::PointStamped>(msg);

      return true;
    };
    virtual bool deserialize(RTC::TimedPoint3D& data)
    { 

      geometry_msgs::PointStamped msg;
      
      ros::serialization::deserializeMessage(ROSSerializerBase<RTC::TimedPoint3D>::m_message, msg);
      
      data.tm.sec = msg.header.stamp.sec;
      data.tm.nsec = msg.header.stamp.nsec;
      data.data.x = msg.point.x;
      data.data.y = msg.point.y;
      data.data.z = msg.point.z;

      return true;
    };
  };

  void ROSPont3DDataInit()
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedPoint3D> >::
            instance().addFactory("ROSPointStamped",
            ::coil::Creator< ::RTC::ByteDataStream<RTC::TimedPoint3D>,
            RTC::ROSPoint3DData>,
            ::coil::Destructor< ::RTC::ByteDataStream<RTC::TimedPoint3D>,
            RTC::ROSPoint3DData>);

    RTC::ROSMessageInfoFactory::
            instance().addFactory("ROSPointStamped",
            ::coil::Creator< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<geometry_msgs::PointStamped> >,
            ::coil::Destructor< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<geometry_msgs::PointStamped> >);
  }



  class ROSQuaternionData : public ROSSerializerBase<RTC::TimedQuaternion>
  {
  public:
    ROSQuaternionData()
    {

    }
    virtual ~ROSQuaternionData()
    {

    }


    virtual bool serialize(const RTC::TimedQuaternion& data)
    {
        
      geometry_msgs::QuaternionStamped  msg;
      msg.header.stamp.sec = data.tm.sec;
      msg.header.stamp.nsec = data.tm.nsec;
      msg.quaternion.x = data.data.x;
      msg.quaternion.y = data.data.y;
      msg.quaternion.z = data.data.z;
      msg.quaternion.w = data.data.w;
      
      ROSSerializerBase<RTC::TimedQuaternion>::m_message = ros::serialization::serializeMessage<geometry_msgs::QuaternionStamped>(msg);

      return true;
    };
    virtual bool deserialize(RTC::TimedQuaternion& data)
    { 

      geometry_msgs::QuaternionStamped msg;
      
      ros::serialization::deserializeMessage(ROSSerializerBase<RTC::TimedQuaternion>::m_message, msg);
      
      data.tm.sec = msg.header.stamp.sec;
      data.tm.nsec = msg.header.stamp.nsec;
      data.data.x = msg.quaternion.x;
      data.data.y = msg.quaternion.y;
      data.data.z = msg.quaternion.z;
      data.data.w = msg.quaternion.w;

      return true;
    };
  };

  void ROSQuaternionDataInit()
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedQuaternion> >::
            instance().addFactory("ROSQuaternion",
            ::coil::Creator< ::RTC::ByteDataStream<RTC::TimedQuaternion>,
            RTC::ROSQuaternionData>,
            ::coil::Destructor< ::RTC::ByteDataStream<RTC::TimedQuaternion>,
            RTC::ROSQuaternionData>);

    RTC::ROSMessageInfoFactory::
            instance().addFactory("ROSQuaternion",
            ::coil::Creator< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<geometry_msgs::QuaternionStamped > >,
            ::coil::Destructor< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<geometry_msgs::QuaternionStamped > >);
  }



  class ROSVector3DData : public ROSSerializerBase<RTC::TimedVector3D>
  {
  public:
    ROSVector3DData()
    {

    }
    virtual ~ROSVector3DData()
    {

    }


    virtual bool serialize(const RTC::TimedVector3D& data)
    {
        
      geometry_msgs::Vector3Stamped  msg;
      msg.header.stamp.sec = data.tm.sec;
      msg.header.stamp.nsec = data.tm.nsec;
      msg.vector.x = data.data.x;
      msg.vector.y = data.data.y;
      msg.vector.z = data.data.z;

      
      ROSSerializerBase<RTC::TimedVector3D>::m_message = ros::serialization::serializeMessage<geometry_msgs::Vector3Stamped>(msg);

      return true;
    };
    virtual bool deserialize(RTC::TimedVector3D& data)
    { 

      geometry_msgs::Vector3Stamped msg;
      
      ros::serialization::deserializeMessage(ROSSerializerBase<RTC::TimedVector3D>::m_message, msg);
      
      data.tm.sec = msg.header.stamp.sec;
      data.tm.nsec = msg.header.stamp.nsec;
      data.data.x = msg.vector.x;
      data.data.y = msg.vector.y;
      data.data.z = msg.vector.z;

      return true;
    };
  };

  void ROSVector3DDataInit()
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<RTC::TimedVector3D> >::
            instance().addFactory("ROSVector3D",
            ::coil::Creator< ::RTC::ByteDataStream<RTC::TimedVector3D>,
            RTC::ROSVector3DData>,
            ::coil::Destructor< ::RTC::ByteDataStream<RTC::TimedVector3D>,
            RTC::ROSVector3DData>);

    RTC::ROSMessageInfoFactory::
            instance().addFactory("ROSVector3D",
            ::coil::Creator< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<geometry_msgs::Vector3Stamped > >,
            ::coil::Destructor< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<geometry_msgs::Vector3Stamped > >);
  }


  class ROSCameraImageData : public ROSSerializerBase<RTC::CameraImage>
  {
  public:
    ROSCameraImageData()
    {

    }
    virtual ~ROSCameraImageData()
    {

    }


    virtual bool serialize(const RTC::CameraImage& data)
    {
        
      sensor_msgs::Image  msg;
      msg.header.stamp.sec = data.tm.sec;
      msg.header.stamp.nsec = data.tm.nsec;
      msg.height = data.height;
      msg.width = data.width;
      if(std::string(data.format) == "")
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

      
      ROSSerializerBase<RTC::CameraImage>::m_message = ros::serialization::serializeMessage<sensor_msgs::Image>(msg);

      return true;
    };
    virtual bool deserialize(RTC::CameraImage& data)
    { 

      sensor_msgs::Image msg;
      
      ros::serialization::deserializeMessage(ROSSerializerBase<RTC::CameraImage>::m_message, msg);
      
      
      data.tm.sec = msg.header.stamp.sec;
      data.tm.nsec = msg.header.stamp.nsec;
      data.height = msg.height;
      data.width = msg.width;
      data.format = CORBA::string_dup(msg.encoding.c_str());


      data.pixels.length(msg.data.size());
      
      memcpy(&data.pixels[0], &msg.data[0], data.pixels.length());

      return true;
    };
  };

  void ROSCameraImageDataInit()
  {
    coil::GlobalFactory < ::RTC::ByteDataStream<RTC::CameraImage> >::
            instance().addFactory("ROSCameraImage",
            ::coil::Creator< ::RTC::ByteDataStream<RTC::CameraImage>,
            RTC::ROSCameraImageData>,
            ::coil::Destructor< ::RTC::ByteDataStream<RTC::CameraImage>,
            RTC::ROSCameraImageData>);

    RTC::ROSMessageInfoFactory::
            instance().addFactory("ROSCameraImage",
            ::coil::Creator< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<sensor_msgs::Image > >,
            ::coil::Destructor< ::RTC::ROSMessageInfoBase,
            RTC::ROSMessageInfo<sensor_msgs::Image > >);
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
  void ROSSerializerInit(RTC::Manager* manager)
  {
    (void)manager;
    RTC::ROSSimpleDataInit<RTC::TimedState>();
    RTC::ROSSimpleDataInit<RTC::TimedShort>();
    RTC::ROSSimpleDataInit<RTC::TimedLong>();
    RTC::ROSSimpleDataInit<RTC::TimedUShort>();
    RTC::ROSSimpleDataInit<RTC::TimedULong>();
    RTC::ROSSimpleDataInit<RTC::TimedFloat>();
    RTC::ROSSimpleDataInit<RTC::TimedDouble>();

    RTC::ROSSequenceDataInit<RTC::TimedShortSeq>();
    RTC::ROSSequenceDataInit<RTC::TimedLongSeq>();
    RTC::ROSSequenceDataInit<RTC::TimedUShortSeq>();
    RTC::ROSSequenceDataInit<RTC::TimedULongSeq>();
    RTC::ROSSequenceDataInit<RTC::TimedFloatSeq>();
    RTC::ROSSequenceDataInit<RTC::TimedDoubleSeq>();

    RTC::ROSStringDataInit();
    RTC::ROSPont3DDataInit();
    RTC::ROSQuaternionDataInit();
    RTC::ROSVector3DDataInit();
    RTC::ROSCameraImageDataInit();
  };
}



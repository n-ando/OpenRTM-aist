// -*- C++ -*-
/*!
 * @file  ROSSerializer.h
 * @brief ROS Serializer 
 * @date  $Date: 2019-02-04 03:08:03 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2018
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *
 *     All rights reserved.
 *
 *
 */

#ifndef RTC_ROSSERIALIZER_H
#define RTC_ROSSERIALIZER_H

#include <rtm/ByteDataStreamBase.h>
#include <coil/Factory.h>
#include <rtm/Manager.h>
#include <ros/serialization.h>



namespace RTC
{
  template <class DataType>
  class ROSSerializerBase : public ByteDataStream<DataType>
  {
  public:
    ROSSerializerBase(){};
    virtual ~ROSSerializerBase(){};


    virtual void writeData(const unsigned char* buffer, unsigned long length)
    {
      boost::shared_array<uint8_t> buffer_(new uint8_t[length]);

      memcpy(buffer_.get(), buffer, length);

      m_message = ros::SerializedMessage(buffer_, length);
      m_message.message_start = buffer_.get()+4;

    }

    virtual void readData(unsigned char* buffer, unsigned long length) const
    {
      memcpy(buffer, m_message.buf.get(), length);

    }
    virtual unsigned long getDataLength() const
    {
      return m_message.num_bytes;
    };

    virtual bool serialize(const DataType& data)
    {
      (void)data;
      return false;
    };
    virtual bool deserialize(DataType& data)
    {
      (void)data;
      return true;
    };

  protected:
    ros::SerializedMessage m_message;
  };

  template <class DataType, class MessageType>
  class ROSSimpleData : public ROSSerializerBase<DataType>
  {
  public:
    ROSSimpleData()
    {

    }
    virtual ~ROSSimpleData()
    {

    }


    virtual bool serialize(const DataType& data)
    {
        
      MessageType msg;
      msg.data = data.data;
      
      ROSSerializerBase<DataType>::m_message = ros::serialization::serializeMessage<MessageType>(msg);

      return true;
    };
    virtual bool deserialize(DataType& data)
    { 

      MessageType msg;
        
      ros::serialization::deserializeMessage(ROSSerializerBase<DataType>::m_message, msg);
      data.data = msg.data;

      return true;
    };
  };


  template <class DataType, class MessageType>
  class ROSSequenceData : public ROSSerializerBase<DataType>
  {
  public:
    ROSSequenceData()
    {

    }
    virtual ~ROSSequenceData()
    {

    }


    virtual bool serialize(const DataType& data)
    {
        
      MessageType msg;
      for(size_t i=0;i < data.data.length();i++)
      {
        msg.data.push_back(data.data[i]);
      }
      
      
      ROSSerializerBase<DataType>::m_message = ros::serialization::serializeMessage<MessageType>(msg);

      return true;
    };
    virtual bool deserialize(DataType& data)
    { 

      MessageType msg;
      
      ros::serialization::deserializeMessage(ROSSerializerBase<DataType>::m_message, msg);

      data.data.length(msg.data.size());
      int count = 0;
      for(auto itr=msg.data.begin();itr != msg.data.end();++itr)
      {
        data.data[count] = *itr;
        count++;
      }

      return true;
    };
  };
}


extern "C"
{
  /*!
   * @if jp
   * @brief モジュール初期化関数
   *
   * ROSシリアライザ のファクトリを登録する初期化関数。
   *
   * @else
   * @brief Module initialization
   *
   * 
   *
   * @endif
   */
  DLL_EXPORT void ROSSerializerInit(RTC::Manager* manager);
};




#endif // RTC_ROSSERIALIZER_H


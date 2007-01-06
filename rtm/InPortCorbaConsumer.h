// -*- C++ -*-
/*!
 * @file  InPortCorbaConsumer.h
 * @brief InPortCorbaConsumer class
 * @date  $Date: 2007-01-06 17:50:57 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPortCorbaConsumer.h,v 1.2 2007-01-06 17:50:57 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/12/02 18:39:57  n-ando
 * InPortCorbaConsumer class was moved from InPortConsumer.h
 *
 */

#ifndef InPortCorbaConsumer_h
#define InPortCorbaConsumer_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/InPortConsumer.h>
#include <iostream>
 
namespace RTC
{
  template <class DataType>
  class InPortCorbaConsumer
    : public InPortConsumer,
      public CorbaConsumer<RTC::InPortAny>
  {
  public:
    InPortCorbaConsumer(BufferBase<DataType>& buffer)
      : m_buffer(buffer)
    {
    }


    InPortCorbaConsumer(const InPortCorbaConsumer<DataType>& consumer)
      : CorbaConsumer<RTC::InPortAny>(consumer), m_buffer(consumer.m_buffer)
    {
    }

    InPortCorbaConsumer&
    operator=(const InPortCorbaConsumer<DataType>& consumer)
    {
      if (this == &consumer) return *this;
      m_buffer = consumer.m_buffer;
    }


    virtual ~InPortCorbaConsumer()
    {}

    void put(DataType& data)
    {
      CORBA::Any tmp;
      tmp <<= data;
      _ptr()->put(tmp);
    }

    void push()
    {
      DataType data;
      CORBA::Any tmp;
      m_buffer.read(data);
      tmp <<= data;

      //hoge 本当はエラー処理をすべき
      if (CORBA::is_nil(_ptr())) return;
      try
	{
	  _ptr()->put(tmp);
	}
      catch(...)
	{
	  //hoge オブジェクトが無効になったらdisconnectすべき
	  return;
	}
    }

    virtual InPortCorbaConsumer* clone() const
    {
      return new InPortCorbaConsumer<DataType>(*this);
    }

    virtual bool subscribeInterface(const SDOPackage::NVList& properties)
    {
      if (!NVUtil::isStringValue(properties,
				 "dataport.dataflow_type",
				 "Push"))
	{
	  return false;
	}
      
      CORBA::Long index;
      index = NVUtil::find_index(properties,
				 "dataport.corba_any.inport_ref");
      if (index < 0)
	{
	  return false;
	}
      
      CORBA::Object_ptr obj;
      if (properties[index].value >>= CORBA::Any::to_object(obj))
	{
	  if (!CORBA::is_nil(obj))
	    {
	      setObject(obj);
	      return true;
	    }
	}
      return false;;
    }


    virtual void unsubscribeInterface(const SDOPackage::NVList& properties)
    {
      ;
    }


  private:
    BufferBase<DataType>& m_buffer;
  };
};     // namespace RTC
#endif // InPortCorbaConsumer_h


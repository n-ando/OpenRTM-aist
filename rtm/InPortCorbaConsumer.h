// -*- C++ -*-
/*!
 * @file  InPortCorbaConsumer.h
 * @brief InPortCorbaConsumer class
 * @date  $Date: 2006-12-02 18:39:57 $
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
 * $Id: InPortCorbaConsumer.h,v 1.1 2006-12-02 18:39:57 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef InPortCorbaConsumer_h
#define InPortCorbaConsumer_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/InPortConsumer.h>
 
namespace RTC
{
  template <class DataType>
  class InPortCorbaConsumer
    : public InPortConsumer,
      public Consumer<RTC::OutPortAny>
  {
  public:
    InPortCorbaConsumer(BufferBase<DataType>* buffer)
      : m_buffer(buffer)
    {}
    virtual ~InPortCorbaConsumer()
    {}

    void put(DataType& data)
    {
      CORBA::Any* tmp(new CORBA::Any());
      tmp <<= data;
      m_inport->put(tmp);
    }

    void push()
    {
      CORBA::Any* tmp(new CORBA::Any());
      tmp <<= m_buffer->get();
      m_inport->put(tmp);
    }

  private:
    RTC::InPortAny_var m_inport;
    BufferBase<DataType>* m_buffer;
  };
};     // namespace RTC
#endif // InPortCorbaConsumer_h


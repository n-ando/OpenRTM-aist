// -*- C++ -*-
/*!
 * @file  InPortConsumer.h
 * @brief InPortConsumer class
 * @date  $Date: 2006-11-27 09:44:39 $
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
 * $Id: InPortConsumer.h,v 1.1 2006-11-27 09:44:39 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef InPortConsumer_h
#define InPortConsumer_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/CorbaConsumer.h>

namespace RTC
{
  /*!
   * @if jp
   * @class InPortConsumer
   * @brief InPortConsumer クラス
   * @else
   * @class InPortConsumer
   * @brief InPortConsumer class
   * @endif
   */
  class InPortConsumer
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    InPortConsumer();

    /*!
     * @if jp
     *
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~InPortConsumer(){};

    virtual void push() = 0;

  protected:
  
  private:

  };


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
#endif // InPortConsumer_h


// -*- C++ -*-
/*!
 * @file  OutPortConsumer.h
 * @brief OutPortConsumer class
 * @date  $Date: 2006-11-27 09:44:41 $
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
 * $Id: OutPortConsumer.h,v 1.1 2006-11-27 09:44:41 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#ifndef OutPortConsumer_h
#define OutPortConsumer_h

#include <rtm/idl/DataPortSkel.h>
#include <rtm/BufferBase.h>
#include <rtm/CorbaConsumer.h>

namespace RTC
{
  /*!
   * @if jp
   * @class OutPortConsumer
   * @brief OutPortConsumer クラス
   * @else
   * @class OutPortConsumer
   * @brief OutPortConsumer class
   * @endif
   */
  class OutPortConsumer
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    OutPortConsumer();

    /*!
     * @if jp
     *
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~OutPortConsumer(){};

    virtual void pull() = 0;

  protected:
  
  private:

  };


  /*!
   * @if jp
   * @class OutPortCorbaConsumer
   * @brief OutPortCorbaConsumer クラス
   * @else
   * @class OutPortCorbaConsumer
   * @brief OutPortCorbaConsumer class
   * @endif
   */
  template <class DataType>
  class OutPortCorbaConsumer
    : public OutPortConsumer,
      public Consumer<RTC::OutPortAny>
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    OutPortCorbaConsumer(BufferBase<DataType>* buffer)
      : m_buffer(buffer)
    {}
    
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~OutPortCorbaConsumer(){} 
    
    bool get(DataType& data)
    {
      CORBA::Any* tmp;
      tmp = m_var->get();
      if (tmp >>= data)
	return true;
      return false;
    }

    virtual void pull()
    {
      DataType data;
      if (get(data))
	{
	  m_buffer->write(data);
	}
    }
    
  private:
    RTC::OutPortAny_var m_outport;
    BufferBase<DataType>* m_buffer;
  };
};     // namespace RTC
#endif // OutPortConsumer_h


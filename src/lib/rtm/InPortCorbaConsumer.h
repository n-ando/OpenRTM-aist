// -*- C++ -*-
/*!
 * @file  InPortCorbaConsumer.h
 * @brief InPortCorbaConsumer class
 * @date  $Date: 2007-12-31 03:08:03 $
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
 * $Id$
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
  /*!
   * @if jp
   *
   * @class InPortCorbaConsumer
   *
   * @brief InPortCorbaConsumer クラス
   *
   * 通信手段に CORBA を利用した入力ポートコンシューマの実装クラス。
   *
   * @param DataType 本ポートにて扱うデータ型
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortCorbaConsumer
   *
   * @brief InPortCorbaConsumer class
   *
   * This is an implementation class of the input port Consumer 
   * that uses CORBA for means of communication.
   *
   * @param DataType Data type for this port
   *
   * @since 0.4.0
   *
   * @endif
   */
  template <class DataType>
  class InPortCorbaConsumer
    : public InPortConsumer,
      public CorbaConsumer<RTC::InPortAny>
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param buffer 当該コンシューマに割り当てるバッファオブジェクト
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param buffer The buffer object that is attached to this Consumer
     *
     * @endif
     */
    InPortCorbaConsumer(BufferBase<DataType>& buffer)
      : m_buffer(buffer)
    {
    }
    
    /*!
     * @if jp
     * @brief コピーコンストラクタ
     *
     * コピーコンストラクタ
     *
     * @param consumer コピー元 InPortCorbaConsumer オブジェクト
     *
     * @else
     * @brief Copy constructor
     *
     * Copy constructor
     *
     * @param consumer InPortCorbaConsumer object of copy source
     *
     * @endif
     */
    InPortCorbaConsumer(const InPortCorbaConsumer<DataType>& consumer)
      : CorbaConsumer<RTC::InPortAny>(consumer), m_buffer(consumer.m_buffer)
    {
    }
    
    /*!
     * @if jp
     * @brief 代入演算子
     *
     * 代入演算子
     *
     * @param consumer 代入元 InPortCorbaConsumer オブジェクト
     *
     * @return 代入結果
     *
     * @else
     * @brief Assignment operator
     *
     * Assignment operator
     *
     * @param consumer InPortCorbaConsumer object of assignment source
     *
     * @return The assignment result
     *
     * @endif
     */
    InPortCorbaConsumer&
    operator=(const InPortCorbaConsumer<DataType>& consumer)
    {
      if (this == &consumer) return *this;
      m_buffer = consumer.m_buffer;
      m_var = consumer.m_var;  
    }
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~InPortCorbaConsumer()
    {}
    
    /*!
     * @if jp
     * @brief バッファへのデータ書込
     *
     * バッファにデータを書き込む
     *
     * @param data 書込対象データ
     *
     * @else
     * @brief Write data into the buffer
     *
     * Write data into the buffer.
     *
     * @param data The target data for writing
     *
     * @endif
     */
    void put(DataType& data)
    {
      CORBA::Any tmp;
      tmp <<= data;
      _ptr()->put(tmp);
    }
    
    /*!
     * @if jp
     * @brief バッファからのデータ取出
     *
     * バッファからデータを取り出して送出する。
     *
     * @else
     * @brief Read data from the buffer
     *
     * Read data from the buffer and send it.
     *
     * @endif
     */
    void push()
    {
      DataType data;
      CORBA::Any tmp;
      m_buffer.read(data);
      tmp <<= data;
      
      // 本当はエラー処理をすべき
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
    
    /*!
     * @if jp
     * @brief コピーの生成
     *
     * 当該InPortCorbaConsumerオブジェクトの複製を生成する。
     *
     * @return コピーされたInPortCorbaConsumerオブジェクト
     *
     * @else
     * @brief Generate clone
     *
     * Clone this InPortCorbaConsumer object.
     *
     * @return The clone InPortCorbaConsumer object
     *
     * @endif
     */
    virtual InPortCorbaConsumer* clone() const
    {
      return new InPortCorbaConsumer<DataType>(*this);
    }
    
    /*!
     * @if jp
     * @brief データ送信通知への登録
     *
     * 指定されたプロパティに基づいて、データ送出通知の受け取りに登録する。
     *
     * @param properties 登録情報
     *
     * @return 登録処理結果(登録成功:true、登録失敗:false)
     *
     * @else
     * @brief Subscribe to the data sending notification
     *
     * Subscribe to the data sending notification based on specified 
     * property information.
     *
     * @param properties Information for subscription
     *
     * @return Subscription result (Successful:true, Failed:false)
     *
     * @endif
     */
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
    
    /*!
     * @if jp
     * @brief データ送信通知からの登録解除
     *
     * データ送出通知の受け取りから登録を解除する。
     *
     * @param properties 登録解除情報
     *
     * @else
     * @brief Unsubscribe the data send notification
     *
     * Unsubscribe the data send notification.
     *
     * @param properties Information for unsubscription
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties)
    {
      ;
    }
    
  private:
    BufferBase<DataType>& m_buffer;
  };
};     // namespace RTC
#endif // InPortCorbaConsumer_h

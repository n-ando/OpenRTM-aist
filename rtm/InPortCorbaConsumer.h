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
 * $Id: InPortCorbaConsumer.h,v 1.3.4.3 2007-12-31 03:08:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3.4.2  2007/09/19 07:47:28  n-ando
 * A trivial fix.
 *
 * Revision 1.3.4.1  2007/08/20 06:31:10  n-ando
 * push() function was modified to detect buffer read error.
 *
 * Revision 1.3  2007/01/09 09:56:38  n-ando
 * Kanji-code has changed.
 *
 * Revision 1.2  2007/01/06 17:50:57  n-ando
 * Interface subscription/unsubscription functions (subscribeInterface()
 * and unsubscribeInterface()) are added.
 * The clone() function to clone the instance is added.
 *
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
   * @brief InPortCorbaConsumer class
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
     *
     * @endif
     */
    InPortCorbaConsumer&
    operator=(const InPortCorbaConsumer<DataType>& consumer)
    {
      if (this == &consumer) return *this;
      m_buffer = consumer.m_buffer;
    }
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
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

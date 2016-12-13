// -*- C++ -*-
/*!
 * @file  InPortCorbaCdrConsumer.h
 * @brief InPortCorbaCdrConsumer class
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
 * $Id: InPortCorbaCdrConsumer.h 1255 2009-04-07 01:09:47Z kurihara $
 *
 */

#ifndef RTC_INPORTCORBACDRCONSUMER_H
#define RTC_INPORTCORBACDRCONSUMER_H


//#include <rtm/BufferBase.h>

#include <rtm/idl/DataPortSkel.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/InPortConsumer.h>
#include <rtm/Manager.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class InPortCorbaCdrConsumer
   *
   * @brief InPortCorbaCdrConsumer クラス
   *
   * 通信手段に CORBA を利用した入力ポートコンシューマの実装クラス。
   *
   * @param DataType 本ポートにて扱うデータ型
   *
   * @since 1.0
   *
   * @else
   * @class InPortCorbaCdrConsumer
   *
   * @brief InPortCorbaCdrConsumer class
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
  class InPortCorbaCdrConsumer
    : public InPortConsumer,
      public CorbaConsumer< ::OpenRTM::InPortCdr >
  {
  public:
    DATAPORTSTATUS_ENUM
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
    InPortCorbaCdrConsumer(void);
    
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
    virtual ~InPortCorbaCdrConsumer(void);

    /*!
     * @if jp
     * @brief 設定初期化
     *
     * InPortConsumerの各種設定を行う
     *
     * @else
     * @brief Initializing configuration
     *
     * This operation would be called to configure this consumer
     * in initialization.
     *
     * @endif
     */
    virtual void init(coil::Properties& prop);

    /*!
     * @if jp
     * @brief 接続先へのデータ送信
     *
     * 接続先のポートへデータを送信するための純粋仮想関数。
     *
     * @else
     * @brief Send data to the destination port
     *
     * Pure virtual function to send data to the destination port.
     *
     * @endif
     */
    virtual ReturnCode put(const cdrMemoryStream& data);

    /*!
     * @if jp
     * @brief InterfaceProfile情報を公開する
     *
     * InterfaceProfile情報を公開する。
     * 引数で指定するプロパティ情報内の NameValue オブジェクトの
     * dataport.interface_type 値を調べ、当該ポートに設定されている
     * インターフェースタイプと一致する場合のみ情報を取得する。
     *
     * @param properties InterfaceProfile情報を受け取るプロパティ
     *
     * @else
     * @brief Publish InterfaceProfile information
     *
     * Publish interfaceProfile information.
     * Check the dataport.interface_type value of the NameValue object 
     * specified by an argument in property information and get information
     * only when the interface type of the specified port is matched.
     *
     * @param properties Properties to get InterfaceProfile information
     *
     * @endif
     */
    virtual void publishInterfaceProfile(SDOPackage::NVList& properties);

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
    virtual bool subscribeInterface(const SDOPackage::NVList& properties);
    
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
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties);

  private:
    /*!
     * @if jp
     * @brief IOR文字列からオブジェクト参照を取得する
     *
     * @return true: 正常取得, false: 取得失敗
     *
     * @else
     * @brief Getting object reference fromn IOR string
     *
     * @return true: succeeded, false: failed
     *
     * @endif
     */
    bool subscribeFromIor(const SDOPackage::NVList& properties);

    /*!
     * @if jp
     * @brief Anyから直接オブジェクト参照を取得する
     *
     * @return true: 正常取得, false: 取得失敗
     *
     * @else
     * @brief Getting object reference fromn Any directry
     *
     * @return true: succeeded, false: failed
     *
     * @endif
     */
    bool subscribeFromRef(const SDOPackage::NVList& properties);

    /*!
     * @if jp
     * @brief 接続解除(IOR版)
     *
     * @return true: 正常取得, false: 取得失敗
     *
     * @else
     * @brief ubsubscribing (IOR version)
     *
     * @return true: succeeded, false: failed
     *
     * @endif
     */
    bool unsubscribeFromIor(const SDOPackage::NVList& properties);

    /*!
     * @if jp
     * @brief 接続解除(Object reference版)
     *
     * @return true: 正常取得, false: 取得失敗
     *
     * @else
     * @brief ubsubscribing (Object reference version)
     *
     * @return true: succeeded, false: failed
     *
     * @endif
     */
    bool unsubscribeFromRef(const SDOPackage::NVList& properties);
    
  private:
    mutable Logger rtclog;
    coil::Properties m_properties;
  };
};     // namespace RTC

extern "C"
{
  void InPortCorbaCdrConsumerInit(void);
};

#endif // RTC_INPORTCORBACDRCONSUMER_H


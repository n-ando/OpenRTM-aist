// -*- C++ -*-
/*!
 * @file  OutPortCorbaCdrConsumer.h
 * @brief OutPortCorbaCdrConsumer class
 * @date  $Date: 2008-01-13 10:28:27 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: OutPortCorbaCdrConsumer.h 1254 2009-04-07 01:09:35Z kurihara $
 *
 */

#ifndef RTC_OUTPORTCORBACDRCONSUMER_H
#define RTC_OUTPORTCORBACDRCONSUMER_H

#include <rtm/idl/DataPortSkel.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/OutPortConsumer.h>
#include <rtm/ConnectorListener.h>
#include <rtm/ConnectorBase.h>

namespace RTC
{
  // forward decl

  /*!
   * @if jp
   * @class OutPortCorbaCdrConsumer
   *
   * @brief OutPortCorbaCdrConsumer クラス
   *
   * 通信手段に CORBA を利用した出力ポートコンシューマの実装クラス。
   *
   * @param DataType 本ポートにて扱うデータ型
   *
   * @since 1.0.0
   *
   * @else
   * @class OutPortCorbaCdrConsumer
   *
   * @brief OutPortCorbaCdrConsumer class
   *
   * This is an implementation class of the output Consumer 
   * that uses CORBA for means of communication.
   *
   * @param DataType Data type for this port
   *
   * @since 1.0.0
   *
   * @endif
   */
  class OutPortCorbaCdrConsumer
    : public OutPortConsumer,
      public CorbaConsumer< ::OpenRTM::OutPortCdr >
  {
  public:
    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param buffer 本ポートに割り当てるバッファ
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param buffer Buffer that is attached to this port
     *
     * @endif
     */
    OutPortCorbaCdrConsumer();

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
    virtual ~OutPortCorbaCdrConsumer(void); 

    /*!
     * @if jp
     * @brief 設定初期化
     *
     * OutPortConsumerの各種設定を行う。実装クラスでは、与えられた
     * Propertiesから必要な情報を取得して各種設定を行う。この init() 関
     * 数は、OutPortProvider生成直後および、接続時にそれぞれ呼ばれる可
     * 能性がある。したがって、この関数は複数回呼ばれることを想定して記
     * 述されるべきである。
     * 
     * @param prop 設定情報
     *
     * @else
     *
     * @brief Initializing configuration
     *
     * This operation would be called to configure in initialization.
     * In the concrete class, configuration should be performed
     * getting appropriate information from the given Properties data.
     * This function might be called right after instantiation and
     * connection sequence respectivly.  Therefore, this function
     * should be implemented assuming multiple call.
     *
     * @param prop Configuration information
     *
     * @endif
     */
    virtual void init(coil::Properties& prop);

    /*!
     * @if jp
     * @brief バッファをセットする
     *
     * OutPortConsumerがデータを取り出すバッファをセットする。
     * すでにセットされたバッファがある場合、以前のバッファへの
     * ポインタに対して上書きされる。
     * OutPortProviderはバッファの所有権を仮定していないので、
     * バッファの削除はユーザの責任で行わなければならない。
     *
     * @param buffer OutPortProviderがデータを取り出すバッファへのポインタ
     *
     * @else
     * @brief Setting outside buffer's pointer
     *
     * A pointer to a buffer from which OutPortProvider retrieve data.
     * If already buffer is set, previous buffer's pointer will be
     * overwritten by the given pointer to a buffer.  Since
     * OutPortProvider does not assume ownership of the buffer
     * pointer, destructor of the buffer should be done by user.
     * 
     * @param buffer A pointer to a data buffer to be used by OutPortProvider
     *
     * @endif
     */
    virtual void setBuffer(CdrBufferBase* buffer);
    /*!
     * @if jp
     * @brief リスナを設定する。
     * @else
     * @brief Set the listener. 
     * @endif
     */
    virtual void setListener(ConnectorInfo& info,
                             ConnectorListeners* listeners);

    /*!
     * @if jp
     * @brief データを読み出す
     *
     * 設定されたデータを読み出す。
     *
     * @param data 読み出したデータを受け取るオブジェクト
     *
     * @return データ読み出し処理結果(読み出し成功:true、読み出し失敗:false)
     *
     * @else
     * @brief Read data
     *
     * Read set data
     *
     * @param data Object to receive the read data
     *
     * @return Read result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual ReturnCode get(cdrMemoryStream& data);

    /*!
     * @if jp
     * @brief データ受信通知への登録
     *
     * 指定されたプロパティに基づいて、データ受信通知の受け取りに登録する。
     *
     * @param properties 登録情報
     *
     * @return 登録処理結果(登録成功:true、登録失敗:false)
     *
     * @else
     * @brief Subscribe the data receive notification
     *
     * Subscribe the data receive notification based on specified property
     * information
     *
     * @param properties Subscription information
     *
     * @return Subscription result (Successful:true, Failed:false)
     *
     * @endif
     */
    virtual bool subscribeInterface(const SDOPackage::NVList& properties);
    
    /*!
     * @if jp
     * @brief データ受信通知からの登録解除
     *
     * データ受信通知の受け取りから登録を解除する。
     *
     * @param properties 登録解除情報
     *
     * @else
     * @brief Unsubscribe the data receive notification
     *
     * Unsubscribe the data receive notification.
     *
     * @param properties Unsubscription information
     *
     * @endif
     */
    virtual void unsubscribeInterface(const SDOPackage::NVList& properties);
    
  private:
    /*!
     * @if jp
     * @brief リターンコード変換 (DataPortStatus -> BufferStatus)
     * @else
     * @brief Return codes conversion
     * @endif
     */
    OutPortConsumer::ReturnCode convertReturn(::OpenRTM::PortStatus status,
                                              const cdrMemoryStream& data);


    /*!
     * @brief Connector data listener functions
     */
    inline void onBufferWrite(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE].notify(m_profile, data);
    }

    inline void onBufferFull(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_FULL].notify(m_profile, data);
    }

//    inline void onBufferWriteTimeout(const cdrMemoryStream& data)
//    {
//      m_listeners->
//        connectorData_[ON_BUFFER_WRITE_TIMEOUT].notify(m_profile, data);
//    }

//    inline void onBufferWriteOverwrite(const cdrMemoryStream& data)
//    {
//      m_listeners->
//        connectorData_[ON_BUFFER_OVERWRITE].notify(m_profile, data);
//    }

//    inline void onBufferRead(const cdrMemoryStream& data)
//    {
//      m_listeners->
//        connectorData_[ON_BUFFER_READ].notify(m_profile, data);
//    }

//    inline void onSend(const cdrMemoryStream& data)
//    {
//      m_listeners->
//        connectorData_[ON_SEND].notify(m_profile, data);
//    }

    inline void onReceived(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVED].notify(m_profile, data);
    }

    inline void onReceiverFull(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_FULL].notify(m_profile, data);
    }

//    inline void onReceiverTimeout(const cdrMemoryStream& data)
//    {
//      m_listeners->
//        connectorData_[ON_RECEIVER_TIMEOUT].notify(m_profile, data);
//    }

//    inline void onReceiverError(const cdrMemoryStream& data)
//    {
//      m_listeners->
//        connectorData_[ON_RECEIVER_ERROR].notify(m_profile, data);
//    }

    /*!
     * @brief Connector listener functions
     */
//    inline void onBufferEmpty()
//    {
//      m_listeners->
//        connector_[ON_BUFFER_EMPTY].notify(m_profile);
//    }

//    inline void onBufferReadTimeout()
//    {
//      m_listeners->
//        connector_[ON_BUFFER_READ_TIMEOUT].notify(m_profile);
//    }

    inline void onSenderEmpty()
    {
      m_listeners->
        connector_[ON_SENDER_EMPTY].notify(m_profile);
    }

    inline void onSenderTimeout()
    {
      m_listeners->
        connector_[ON_SENDER_TIMEOUT].notify(m_profile);
    }

    inline void onSenderError()
    {
      m_listeners->
        connector_[ON_SENDER_ERROR].notify(m_profile);
    }

    //    RTC::OutPortCdr_var m_outport;
    CdrBufferBase* m_buffer;
    ConnectorListeners* m_listeners;
    ConnectorInfo m_profile;
  };
};     // namespace RTC

extern "C"
{
  void OutPortCorbaCdrConsumerInit(void);
};

#endif // RTC_OUTPORTCORBACDRCONSUMER_H

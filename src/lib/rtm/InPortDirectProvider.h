// -*- C++ -*-
/*!
 * @file  InPortDirectProvider.h
 * @brief InPortDirectProvider class
 * @date  $Date: 2008-01-14 07:49:59 $
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
 * $Id: InPortDirectProvider.h 1244 2009-03-13 07:25:42Z n-ando $
 *
 */

#ifndef RTC_INPORTDIRECTPROVIDER_H
#define RTC_INPORTDIRECTPROVIDER_H

#include <rtm/BufferBase.h>
#include <rtm/InPortProvider.h>
#include <rtm/Manager.h>
#include <rtm/ConnectorListener.h>
#include <rtm/ConnectorBase.h>

namespace RTC
{
  /*!
   * @if jp
   * @class InPortDirectProvider
   * @brief InPortDirectProvider クラス
   *
   * InPortProvider
   *
   * データ転送に CORBA の OpenRTM::InPortCdr インターフェースを利用し
   * た、push 型データフロー型を実現する InPort プロバイダクラス。
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortDirectProvider
   * @brief InPortDirectProvider class
   *
   * The InPort provider class which uses the OpenRTM::InPortCdr
   * interface in CORBA for data transfer and realizes a push-type
   * dataflow.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class InPortDirectProvider
    : public InPortProvider
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    InPortDirectProvider();

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
    ~InPortDirectProvider() override;

    /*!
     * @if jp
     * @brief 設定初期化
     *
     * InPortDirectProvider の各種設定を行う。与えられた
     * Propertiesから必要な情報を取得して各種設定を行う。この init() 関
     * 数は、InPortProvider生成直後および、接続時にそれぞれ呼ばれる可
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
    void init(coil::Properties& prop) override;

    /*!
     * @if jp
     * @brief バッファをセットする
     *
     * OutPortProvider がデータを取り出すバッファをセットする。
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
    void setBuffer(BufferBase<ByteData>* buffer) override;

    /*!
     * @if jp
     * @brief リスナを設定する。
     *
     * InPort はデータ送信処理における各種イベントに対して特定のリスナ
     * オブジェクトをコールするコールバック機構を提供する。詳細は
     * ConnectorListener.h の ConnectorDataListener, ConnectorListener
     * 等を参照のこと。InPortDirectProvider では、以下のコールバック
     * が提供される。
     *
     * - ON_BUFFER_WRITE
     * - ON_BUFFER_FULL
     * - ON_BUFFER_WRITE_TIMEOUT
     * - ON_BUFFER_OVERWRITE
     * - ON_RECEIVED
     * - ON_RECEIVER_FULL
     * - ON_RECEIVER_FULL
     * - ON_RECEIVER_TIMEOUT
     * - ON_RECEIVER_ERROR
     *
     * @param info 接続情報
     * @param listeners リスナオブジェクト
     *
     * @else
     * @brief Set the listener.
     *
     * InPort provides callback functionality that calls specific
     * listener objects according to the events in the data publishing
     * process. For details, see documentation of
     * ConnectorDataListener class and ConnectorListener class in
     * ConnectorListener.h. In this InPortDirectProvider provides
     * the following callbacks.
     *
     * - ON_BUFFER_WRITE
     * - ON_BUFFER_FULL
     * - ON_BUFFER_WRITE_TIMEOUT
     * - ON_BUFFER_OVERWRITE
     * - ON_RECEIVED
     * - ON_RECEIVER_FULL
     * - ON_RECEIVER_FULL
     * - ON_RECEIVER_TIMEOUT
     * - ON_RECEIVER_ERROR
     *
     * @param info Connector information
     * @param listeners Listener objects
     *
     * @endif
     */
    void setListener(ConnectorInfo& info,
                             ConnectorListenersBase* listeners) override;

    /*!
     * @if jp
     * @brief Connectorを設定する。
     *
     * InPort は接続確立時に InPortConnector オブジェクトを生成し、生
     * 成したオブジェクトのポインタと共にこの関数を呼び出す。所有権は
     * InPort が保持するので InPortProvider は InPortConnector を削
     * 除してはいけない。
     *
     * @param connector InPortConnector
     *
     * @else
     * @brief set Connector
     *
     * InPort creates InPortConnector object when it establishes
     * connection between InPort and InPort, and it calls this
     * function with a pointer to the connector object. Since the
     * InPort has the ownership of this connector, InPortProvider
     * should not delete it.
     *
     * @param connector InPortConnector
     *
     * @endif
     */
    void setConnector(InPortConnector* connector) override;

  private:
    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE のリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_WRITE event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWrite(ByteData& data)
    {
      m_listeners->notifyIn(ConnectorDataListenerType::ON_BUFFER_WRITE, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_FULL のリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_FULL event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferFull(ByteData& data)
    {
      m_listeners->notifyIn(ConnectorDataListenerType::ON_BUFFER_FULL, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE_TIMEOUT のリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_WRITE_TIMEOUT event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWriteTimeout(ByteData& data)
    {
      m_listeners->notifyIn(ConnectorDataListenerType::ON_BUFFER_WRITE_TIMEOUT, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE_OVERWRITE のリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_WRITE_OVERWRITE event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWriteOverwrite(ByteData& data)
    {
      m_listeners->notifyIn(ConnectorDataListenerType::ON_BUFFER_OVERWRITE, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVED のリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_RECEIVED event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceived(ByteData& data)
    {
      m_listeners->notifyIn(ConnectorDataListenerType::ON_RECEIVED, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_FULL のリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_RECEIVER_FULL event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverFull(ByteData& data)
    {
      m_listeners->notifyIn(ConnectorDataListenerType::ON_RECEIVER_FULL, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_TIMEOUT のリスナへ通知する。
     * @else
     * @brief Notify an ON_RECEIVER_TIMEOUT event to listeners
     * @endif
     */
    inline void onReceiverTimeout(ByteData& data)
    {
      m_listeners->notifyIn(ConnectorDataListenerType::ON_RECEIVER_TIMEOUT, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_ERRORのリスナへ通知する。
     * @else
     * @Brief Notify an ON_RECEIVER_ERROR event to listeners
     * @endif
     */
    inline void onReceiverError(ByteData& data)
    {
      m_listeners->notifyIn(ConnectorDataListenerType::ON_RECEIVER_ERROR, m_profile, data);
    }

  private:
    CdrBufferBase* m_buffer{nullptr};
    ConnectorListenersBase* m_listeners;
    ConnectorInfo m_profile;
    InPortConnector* m_connector;

  };  // class InPortCorCdrbaProvider
} // namespace RTC

extern "C"
{
  /*!
   * @if jp
   * @brief モジュール初期化関数
   *
   * InPortDirectConsumer のファクトリを登録する初期化関数。
   *
   * @else
   * @brief Module initialization
   *
   * This initialization function registers InPortDirectConsumer's factory.
   *
   * @endif
   */
  void InPortDirectProviderInit(void);
}

#endif  // RTC_INPORTDIRECTPROVIDER_H


// -*- C++ -*-
/*!
 * @file  OutPortSHMProvider.h
 * @brief OutPortSHMProvider class
 * @date  $Date: 2017-10-30 07:49:59 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2017 Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 */

#ifndef RTC_OUTPORTSHMPROVIDER_H
#define RTC_OUTPORTSHMPROVIDER_H

#include <rtm/SharedMemoryPort.h>
#include <rtm/BufferBase.h>
#include <rtm/OutPortProvider.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/Manager.h>
#include <rtm/ConnectorListener.h>
#include <rtm/ConnectorBase.h>

namespace RTC
{
  /*!
   * @if jp
   * @class OutPortSHMProvider
   * @brief OutPortSHMProvider クラス
   *
   * OutPortProvider 
   *
   * 通信手段に 共有メモリ を利用した出力ポートプロバイダの実装クラス。
   *
   * @since 1.2.0
   *
   * @else
   * @class OutPortSHMProvider
   * @brief OutPortSHMProvider class
   *
   * 
   *
   * @since 1.2.0
   *
   * @endif
   */
  class OutPortSHMProvider
    : public OutPortProvider,
      public virtual SharedMemoryPort
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
    OutPortSHMProvider();

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
    ~OutPortSHMProvider() override;

    /*!
     * @if jp
     * @brief 設定初期化
     *
     * 
     * 
     * @param prop 設定情報
     *
     * @else
     *
     * @brief Initializing configuration
     *
     * 
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
     * 
     *
     * @param buffer OutPortProviderがデータを取り出すバッファへのポインタ
     *
     * @else
     * @brief Setting outside buffer's pointer
     *
     * 
     * 
     * @param buffer A pointer to a data buffer to be used by OutPortProvider
     *
     * @endif
     */
    void setBuffer(CdrBufferBase* buffer) override;

    /*!
     * @if jp
     * @brief リスナを設定する。
     *
     * 
     *
     * @param info 接続情報
     * @param listeners リスナオブジェクト
     *
     * @else
     * @brief Set the listener. 
     *
     * 
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
     * 
     *
     * @param connector OutPortConnector
     *
     * @else
     * @brief set Connector
     *
     * 
     *
     * @param connector OutPortConnector
     *
     * @endif
     */
    void setConnector(OutPortConnector* connector) override;

    /*!
     * @if jp
     * @brief [CORBA interface] バッファからデータを取得する
     *
     * 設定された内部バッファからデータを取得する。
     *
     * @return 取得データ
     *
     * @else
     * @brief [CORBA interface] Get data from the buffer
     *
     * Get data from the internal buffer.
     *
     * @return Data got from the buffer.
     *
     * @endif
     */
    ::OpenRTM::PortStatus get() override;

    
  private:
    /*!
     * @if jp
     * @brief リターンコード変換
     * @else
     * @brief Return codes conversion
     * @endif
     */
    ::OpenRTM::PortStatus convertReturn(BufferStatus status,
                                        ByteData& data);


    /*!
     * @if jp
     * @brief ON_BUFFER_READ のリスナへ通知する。 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_READ event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferRead(ByteData& data)
    {
      m_listeners->notifyOut(ConnectorDataListenerType::ON_BUFFER_READ, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_SEND のリスナへ通知する。 
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_SEND event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onSend(ByteData& data)
    {
      m_listeners->notifyOut(ConnectorDataListenerType::ON_SEND, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_EMPTYのリスナへ通知する。 
     * @else
     * @brief Notify an ON_BUFFER_EMPTY event to listeners
     * @endif
     */
    inline void onBufferEmpty()
    {
      m_listeners->notify(ConnectorListenerType::ON_BUFFER_EMPTY, m_profile);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_READ_TIMEOUT のリスナへ通知する。 
     * @else
     * @brief Notify an ON_BUFFER_READ_TIMEOUT event to listeners
     * @endif
     */
    inline void onBufferReadTimeout()
    {
      m_listeners->notify(ConnectorListenerType::ON_BUFFER_READ_TIMEOUT, m_profile);
    }

    /*!
     * @if jp
     * @brief ON_SENDER_EMPTYのリスナへ通知する。 
     * @else
     * @brief Notify an ON_SENDER_EMPTY event to listeners
     * @endif
     */
    inline void onSenderEmpty()
    {
      m_listeners->notify(ConnectorListenerType::ON_SENDER_EMPTY, m_profile);
    }

    /*!
     * @if jp
     * @brief ON_SENDER_TIMEOUT のリスナへ通知する。 
     * @else
     * @brief Notify an ON_SENDER_TIMEOUT event to listeners
     * @endif
     */
    inline void onSenderTimeout()
    {
      m_listeners->notify(ConnectorListenerType::ON_SENDER_TIMEOUT, m_profile);
    }

    /*!
     * @if jp
     * @brief ON_SENDER_ERRORのリスナへ通知する。 
     * @else
     * @brief Notify an ON_SENDER_ERROR event to listeners
     * @endif
     */
    inline void onSenderError()
    {
      m_listeners->notify(ConnectorListenerType::ON_SENDER_ERROR, m_profile);
    }
    
  private:
    CdrBufferBase* m_buffer{nullptr};
    ::OpenRTM::PortSharedMemory_var m_objref;
    ConnectorListenersBase* m_listeners;
    ConnectorInfo m_profile;
    OutPortConnector* m_connector{nullptr};
    std::string m_shm_address;
    int m_memory_size{0};
    ByteData m_cdr;
  };  // class OutPortCorbaCdrProvider
} // namespace RTC

extern "C"
{
  /*!
   * @if jp
   * @brief モジュール初期化関数
   *
   * OutPortSHMProvider のファクトリを登録する初期化関数。
   *
   * @else
   * @brief Module initialization
   *
   * This initialization function registers OutPortSHMProvider's factory.
   *
   * @endif
   */
  void OutPortSHMProviderInit(void);
}

#endif // RTC_OUTPORTSHMPROVIDER_H

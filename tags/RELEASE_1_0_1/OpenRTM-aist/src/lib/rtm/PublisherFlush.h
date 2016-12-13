// -*- C++ -*-
/*!
 * @file  PublisherFlush.h
 * @brief PublisherFlush class
 * @date  $Date: 2007-12-31 03:08:06 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
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

#ifndef RTC_PUBLISHERFLUSH_H
#define RTC_PUBLISHERFLUSH_H

#include <coil/Condition.h>
#include <rtm/PublisherBase.h>
#include <rtm/SystemLogger.h>
#include <rtm/ConnectorBase.h>
#include <rtm/ConnectorListener.h>

namespace coil
{
  class Properties;
};

namespace RTC
{
  class InPortConsumer;

  /*!
   * @if jp
   * @class PublisherFlush
   * @brief PublisherFlush クラス
   *
   * Flush 型 Publisher クラス
   * バッファ内に格納されている未送信データを送信する。
   * データ送出を待つコンシューマを、送出する側と同じスレッドで動作させる。
   *
   * @else
   * @class PublisherFlush
   * @brief PublisherFlush class
   *
   * This is a Publisher class of Flush type.
   * This class sends unsend data that has been stored in the buffer.
   * This executes Consumer that waits for the data send timing in the same 
   * thread as its send side.
   *
   * @endif
   */
  class PublisherFlush
    : public PublisherBase
  {
  public:
    typedef coil::Mutex Mutex;
    typedef coil::Condition<Mutex> Condition;
    typedef coil::Guard<coil::Mutex> Guard;

    DATAPORTSTATUS_ENUM

    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param consumer データ送出を待つコンシューマ
     * @param property 本Publisherの駆動制御情報を設定したPropertyオブジェクト
     *
     * @else
     * @brief Constructor
     *
     * Consrtuctor.
     *
     * @param consumer Consumer to wait for the data sending
     * @param property Property object that have been set the control
     *                 information of this Publisher
     *
     * @endif
     */
    PublisherFlush();
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     * 当該Publisherを破棄する際に、PublisherFactoryにより呼び出される。
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     * This is invoked by PublisherFactory when this Publisher is destoroyed.
     *
     * @endif
     */
    virtual ~PublisherFlush(void);

    /*!
     * @if jp
     * @brief 初期化
     * @else
     * @brief initialization
     * @endif
     */
    virtual ReturnCode init(coil::Properties& prop);

    /*!
     * @if jp
     * @brief InPortコンシューマのセット
     *
     * @else
     * @brief Store InPort consumer
     * @endif
     */
    virtual ReturnCode setConsumer(InPortConsumer* consumer);
    /*!
     * @if jp
     * @brief バッファのセット
     * 
     * PublisherFlushでは、バッファを使用しないため、
     * 本メソッドはPORT_ERRORを返す。
     *
     * @param buffer CDRバッファ
     * @return PORT_ERROR
     * @else
     * @brief Setting buffer pointer
     *
     * This method returns PORT_ERROR 
     * because PublisherFlush doesn't use the buffer.
     *
     * @param buffer CDR buffer
     * @return PORT_ERROR
     * @endif
     */
    virtual ReturnCode setBuffer(CdrBufferBase* buffer);
    /*!
     * @if jp
     * @brief リスナを設定する。
     * @param info ConnectorInfo
     * @param listeners ConnectorListeners 
     * @return PORT_OK      正常終了
     *         INVALID_ARGS 不正な引数
     * @else
     * @brief Set the listener. 
     * @param info ConnectorInfo
     * @param listeners ConnectorListeners 
     * @return PORT_OK      Normal return
     *         INVALID_ARGS Invalid arguments
     * @endif
     */
    virtual ::RTC::DataPortStatus::Enum
    setListener(ConnectorInfo& profile,
                RTC::ConnectorListeners* listeners);
    /*!
     * @if jp
     * @brief データを書き込む
     * @param data 書き込むデータ 
     * @param sec タイムアウト時間
     * @param nsec タイムアウト時間
     * @return リターンコード
     * @else
     * @brief Write data 
     * @param data Data
     * @param sec Timeout period
     * @param nsec Timeout period
     * @return Return code
     * @endif
     */
    virtual ReturnCode write(const cdrMemoryStream& data,
                             unsigned long sec,
                             unsigned long usec);
    /*!
     * @if jp
     *
     * @brief アクティブ化確認
     * 
     * アクティブ化されているか確認する。
     *
     * @return 状態確認結果(アクティブ状態:true、非アクティブ状態:false)
     *
     * @else
     *
     * @brief Confirm to activate
     * 
     * Confirm that has been activated.
     *
     * @return Result of state confirmation
     *         (Active state:true, Inactive state:false)
     *
     * @endif
     */
    virtual bool isActive();
    /*!
     * @if jp
     * @brief アクティブ化
     * @return リターンコード
     *
     * @else
     *
     * @brief activation
     * @return Return code
     *
     * @endif
     */
    virtual ReturnCode activate();
    /*!
     * @if jp
     * @brief 非アクティブ化
     * @return リターンコード
     *
     * @else
     *
     * @brief deactivation
     * @return Return code
     *
     * @endif
     */
    virtual ReturnCode deactivate();

  protected:
    /*!
     * @brief Connector data listener functions
     */
    //    inline void onBufferWrite(const cdrMemoryStream& data)
    //    {
    //      m_listeners->
    //        connectorData_[ON_BUFFER_WRITE].notify(m_profile, data);
    //    }

    //    inline void onBufferFull(const cdrMemoryStream& data)
    //    {
    //      m_listeners->
    //        connectorData_[ON_BUFFER_FULL].notify(m_profile, data);
    //    }

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

    /*!
     * @if jp
     * @brief ON_SENDのリスナへ通知する。 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_SEND. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onSend(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_SEND].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVEDのリスナへ通知する。 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_RECEIVED. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceived(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVED].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_FULLのリスナへ通知する。 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_RECEIVER_FULL. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverFull(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_FULL].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_TIMEOUTのリスナへ通知する。 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_RECEIVER_TIMEOUT. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverTimeout(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_TIMEOUT].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_ERRORのリスナへ通知する。 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_RECEIVER_ERROR.
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverError(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_ERROR].notify(m_profile, data);
    }

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

    //    inline void onSenderEmpty()
    //    {
    //      m_listeners->
    //        connector_[ON_SENDER_EMPTY].notify(m_profile);
    //    }
    
    //    inline void onSenderTimeout()
    //    {
    //      m_listeners->
    //        connector_[ON_SENDER_TIMEOUT].notify(m_profile);
    //    }

    //    inline void onSenderError()
    //    {
    //      m_listeners->
    //        connector_[ON_SENDER_ERROR].notify(m_profile);
    //    }
    
    
  private:
    Logger rtclog;
    InPortConsumer* m_consumer;
    ConnectorInfo m_profile;
    ConnectorListeners* m_listeners;
    ReturnCode m_retcode;
    Mutex m_retmutex;
    bool m_active;
  };

};     // namespace RTC

extern "C"
{
  void DLL_EXPORT PublisherFlushInit();
};

#endif // RTC_PUBLISHERFLUSH_H


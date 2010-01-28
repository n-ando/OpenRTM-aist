// -*- C++ -*-
/*!
 * @file  PublisherPeriodic.h
 * @brief PublisherPeriodic class
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

#ifndef RTC_PUBLISHERPERIODIC_H
#define RTC_PUBLISHERPERIODIC_H

#include <coil/Task.h>
#include <coil/Mutex.h>
#include <coil/Condition.h>
#include <coil/PeriodicTask.h>

#include <rtm/RTC.h>
#include <rtm/PublisherBase.h>
#include <rtm/CdrBufferBase.h>
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
   * @class PublisherPeriodic
   * @brief PublisherPeriodic クラス
   *
   * 一定周期でコンシューマの送出処理を呼び出す Publisher
   * 定期的にデータ送信を実行する場合に使用する。
   *
   * @else
   * @class PublisherPeriodic
   * @brief PublisherPeriodic class
   *
   * Publisher that invokes the consumer's sending process periodically.
   * This is used when the data sending is regularly executed.
   *
   * @endif
   */
  class PublisherPeriodic
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
     * 送出処理の呼び出し間隔を、Propertyオブジェクトの
     * dataport.publisher.push_rateメンバに設定しておく必要がある。送出
     * 間隔は、Hz単位の浮動小数文字列で指定。たとえば、1000.0Hzの場合は、
     * 「1000.0」を設定。上記プロパティが未設定の場合は、「1000Hz」を設
     * 定。
     *
     * @param consumer データ送出を待つコンシューマ
     * @param property 本Publisherの駆動制御情報を設定したPropertyオブジェクト
     *
     * @else
     * @brief Constructor
     *
     * The intervals of invoking send processing needs to be set in
     * dataport.publisher.push_rate of Property object. The interval
     * is specified by floating point string in Hz.
     * For example, "1000.0" is set for 1000.0Hz.
     * If the above property is unset, "1000Hz" will be set.
     *
     * @param consumer Consumer which waits for data sending
     * @param property Property objects that are set the control information
     *                 of this Publisher
     *
     * @endif
     */
    PublisherPeriodic();
    
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
    virtual ~PublisherPeriodic(void);
    
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
     * @param buffer CDRバッファ
     * @return PORT_OK      正常終了
     *         INVALID_ARGS 不正な引数
     * @else
     * @brief Setting buffer pointer
     * @param buffer CDR buffer
     * @return PORT_OK      正常終了
     *         INVALID_ARGS 不正な引数
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
    virtual ReturnCode setListener(ConnectorInfo& info,
                                   ConnectorListeners* listeners);
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
    
    /*!
     * @if jp
     * @brief スレッド実行関数
     *
     * ACE_Task::svc() のオーバーライド
     *
     * @else
     * @brief Thread execution function
     *
     * ACE_Task::svc() override function.
     *
     * @endif
     */
    virtual int svc(void);
    
  protected:
    enum Policy
      {
        ALL,
        FIFO,
        SKIP,
        NEW
      };

    /*!
     * @if jp
     * @brief PushPolicy の設定
     * @else
     * @brief Setting PushPolicy
     * @endif
     */
    void setPushPolicy(const coil::Properties& prop);

    /*!
     * @if jp
     * @brief Task の設定
     * @else
     * @brief Setting Task
     * @endif
     */
    bool createTask(const coil::Properties& prop);

    /*!
     * @brief push "all" policy
     */
    ReturnCode pushAll();

    /*!
     * @brief push "fifo" policy
     */
    ReturnCode pushFifo();

    /*!
     * @brief push "skip" policy
     */
    ReturnCode pushSkip();

    /*!
     * @brief push "new" policy
     */
    ReturnCode pushNew();

    /*!
     * @brief return code conversion (BufferStatus -> DataPortStatus)
     */
    ReturnCode convertReturn(BufferStatus::Enum status,
                             const cdrMemoryStream& data);


    /*!
     * @if jp
     * @brief DataPortStatusに従ってリスナへ通知する関数を呼び出す。
     * @param status DataPortStatus
     * @param data cdrMemoryStream
     * @return リターンコード
     *
     * @else
     * @brief This method calls the function notified the listener 
     *        according to DataPortStatus.  
     * @param status DataPortStatus
     * @param data cdrMemoryStream
     * @return Return code
     *
     * @endif
     */
    ReturnCode invokeListener(DataPortStatus::Enum status,
                              const cdrMemoryStream& data);

    /*!
     * @brief Connector data listener functions
     */
    /*!
     * @if jp
     * @brief ON_BUFFER_WRITEのリスナへ通知する。 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_BUFFER_WRITE. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWrite(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_FULLのリスナへ通知する。 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_BUFFER_FULL. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferFull(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_FULL].notify(m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE_TIMEOUTのリスナへ通知する。 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_BUFFER_WRITE_TIMEOUT. 
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWriteTimeout(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_WRITE_TIMEOUT].notify(m_profile, data);
    }

//    inline void onBufferWriteOverwrite(const cdrMemoryStream& data)
//    {
//      m_listeners->
//        connectorData_[ON_BUFFER_OVERWRITE].notify(m_profile, data);
//    }

    /*!
     * @if jp
     * @brief ON_BUFFER_READのリスナへ通知する。 
     * @param data cdrMemoryStream
     * @else
     * @brief This method is notified to listeners of ON_BUFFER_READ.
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferRead(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_READ].notify(m_profile, data);
    }

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
    /*!
     * @if jp
     * @brief ON_BUFFER_EMPTYのリスナへ通知する。 
     * @else
     * @brief This method is notified to listeners of ON_BUFFER_EMPTY.
     * @endif
     */
    inline void onBufferEmpty()
    {
      m_listeners->
        connector_[ON_BUFFER_EMPTY].notify(m_profile);
    }

//    inline void onBufferReadTimeout()
//    {
//      m_listeners->
//        connector_[ON_BUFFER_READ_TIMEOUT].notify(m_profile);
//    }

    /*!
     * @if jp
     * @brief ON_SENDER_EMPTYのリスナへ通知する。 
     * @else
     * @brief This method is notified to listeners of ON_SENDER_EMPTY.
     * @endif
     */
    inline void onSenderEmpty()
    {
      m_listeners->
        connector_[ON_SENDER_EMPTY].notify(m_profile);
    }

//    inline void onSenderTimeout()
//    {
//      m_listeners->
//        connector_[ON_SENDER_TIMEOUT].notify(m_profile);
//    }

    /*!
     * @if jp
     * @brief ON_SENDER_ERRORのリスナへ通知する。 
     * @else
     * @brief This method is notified to listeners of ON_SENDER_ERROR.
     * @endif
     */
    inline void onSenderError()
    {
      m_listeners->
        connector_[ON_SENDER_ERROR].notify(m_profile);
    }


  private:
    bool bufferIsEmpty()
    {
      if (m_buffer->empty() && !m_readback)
        {
          RTC_DEBUG(("buffer empty"));
          onBufferEmpty();
          onSenderEmpty();
          return true;
        }
      return false;
    }

    Logger rtclog;
    InPortConsumer* m_consumer;
    CdrBufferBase* m_buffer;
    ConnectorInfo m_profile;
    coil::PeriodicTaskBase* m_task;
    ConnectorListeners* m_listeners;
    ReturnCode m_retcode;
    Mutex m_retmutex;
    Policy m_pushPolicy;
    int m_skipn;
    bool m_active;
    bool m_readback;
    int m_leftskip;
  };
};     // namespace RTC

extern "C"
{
  void DLL_EXPORT PublisherPeriodicInit();
};

#endif // RTC_PUBLISHERPERIODIC_H


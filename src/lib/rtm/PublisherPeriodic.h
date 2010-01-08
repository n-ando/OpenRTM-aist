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
    virtual ReturnCode setConsumer(InPortConsumer* consumer);
    virtual ReturnCode setBuffer(CdrBufferBase* buffer);
    virtual ReturnCode setListener(ConnectorInfo& info,
                                   ConnectorListeners* listeners);
    virtual ReturnCode write(const cdrMemoryStream& data,
                             unsigned long sec,
                             unsigned long usec);
    virtual bool isActive();
    virtual ReturnCode activate();
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


    ReturnCode invokeListener(DataPortStatus::Enum status,
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

    inline void onBufferRead(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_BUFFER_READ].notify(m_profile, data);
    }

    inline void onSend(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_SEND].notify(m_profile, data);
    }

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

    inline void onReceiverTimeout(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_TIMEOUT].notify(m_profile, data);
    }

    inline void onReceiverError(const cdrMemoryStream& data)
    {
      m_listeners->
        connectorData_[ON_RECEIVER_ERROR].notify(m_profile, data);
    }

    /*!
     * @brief Connector listener functions
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
    ConnectorListeners* m_listeners;
    coil::PeriodicTaskBase* m_task;
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


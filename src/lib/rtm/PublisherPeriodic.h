// -*- C++ -*-
/*!
 * @file  PublisherPeriodic.h
 * @brief PublisherPeriodic class
 * @date  $Date: 2007-12-31 03:08:06 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2010
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
#include <condition_variable>
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
} // namespace coil

namespace RTC
{
  class InPortConsumer;
  /*!
   * @if jp
   * @class PublisherPeriodic
   * @brief PublisherPeriodic クラス
   *
   * 周期的にデータを送信するための Publisher クラス。このクラスは、通
   * 常 Connector 内にあって、バッファおよびコンシューマに関連付けられ
   * る。一定周期ごとにバッファからデータを取り出しコンシューマに対して
   * データを送出する。
   *
   * @else
   * @class PublisherPeriodic
   * @brief PublisherPeriodic class
   *
   * Publisher for periodic data transmitting. Usually this class
   * object exists in a Connector object, and it is associated with a
   * buffer and a consumer. This publisher periodically gets data from
   * the buffer and publish it into the consumer.
   *
   * @endif
   */
  class PublisherPeriodic
    : public PublisherBase
  {
  public:

    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * @else
     * @brief Constructor
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
    ~PublisherPeriodic() override;

    /*!
     * @if jp
     * @brief 初期化
     *
     * このクラスのオブジェクトを使用するのに先立ち、必ずこの関数を呼び
     * 出す必要がある。引数には、このオブジェクトの各種設定情報を含む
     * Properties を与える。少なくとも、送出処理の呼び出し周期を単位
     * Hz の数値として Propertyオブジェクトの publisher.push_rate をキー
     * とする要素に設定する必要がある。周期 5ms すなわち、200Hzの場合、
     * 200.0 を設定する。 dataport.publisher.push_rate が未設定の場合、
     * false が返される。データをプッシュする際のポリシーとして
     * publisher.push_policy をキーとする値に、all, fifo, skip, new の
     * いずれかを与えることができる。
     *
     * 以下のオプションを与えることができる。
     *
     * - publisher.thread_type: スレッドのタイプ (文字列、デフォルト: default)
     * - publisher.push_rate: Publisherの送信周期 (数値)
     * - publisher.push_policy: Pushポリシー (all, fifo, skip, new)
     * - publisher.skip_count: 上記ポリシが skip のときのスキップ数
     * - measurement.exec_time: タスク実行時間計測 (enable/disable)
     * - measurement.exec_count: タスク関数実行時間計測周期 (数値, 回数)
     * - measurement.period_time: タスク周期時間計測 (enable/disable)
     * - measurement.period_count: タスク周期時間計測周期 (数値, 回数)
     *
     * @param property 本Publisherの駆動制御情報を設定したPropertyオブジェクト
     * @return DataPortStatus PORT_OK 正常終了
      *                       INVALID_ARGS Properties が不正な値を含む
     *
     * @else
     * @brief Initialization
     *
     * This function have to be called before using this class object.
     * Properties object that includes certain configuration
     * information should be given as an argument.  At least, a
     * numerical value of unit of Hz with the key of
     * "dataport.publisher.push_rate" has to be set to the Properties
     * object of argument.  The value is the invocation cycle of data
     * sending process.  In case of 5 ms period or 200 Hz, the value
     * should be set as 200.0. False will be returned, if there is no
     * value with the key of "dataport.publisher.push_rate".
     *
     * The following options are available.
     *
     * - publisher.thread_type: Thread type (string, default: default)
     * - publisher.push_rate: Publisher sending period (numberical)
     * - publisher.push_policy: Push policy (all, fifo, skip, new)
     * - publisher.skip_count: The number of skip count in the "skip" policy
     * - measurement.exec_time: Task execution time measurement (enable/disable)
     * - measurement.exec_count: Task execution time measurement count
     *                           (numerical, number of times)
     * - measurement.period_time: Task period time measurement (enable/disable)
     * - measurement.period_count: Task period time measurement count
     *                             (number, count)
     *
     * @param property Property objects that includes the control information
     *                 of this Publisher
     * @return DataPortStatus PORT_OK normal return
     *                        INVALID_ARGS Properties with invalid values.
     * @endif
     */
    DataPortStatus init(coil::Properties& prop) override;

    /*!
     * @if jp
     * @brief InPortコンシューマのセット
     *
     * この関数では、この Publisher に関連付けられるコンシューマをセットする。
     * コンシューマオブジェクトがヌルポインタの場合、INVALID_ARGSが返される。
     * それ以外の場合は、PORT_OK が返される。
     *
     * @param consumer Consumer へのポインタ
     * @return DataPortStatus PORT_OK 正常終了
     *                        INVALID_ARGS 引数に不正な値が含まれている
     *
     * @else
     * @brief Store InPort consumer
     *
     * This operation sets a consumer that is associated with this
     * object. If the consumer object is NULL, INVALID_ARGS will be
     * returned.
     *
     * @param consumer A pointer to a consumer object.
     * @return DataPortStatus PORT_OK normal return
     *                        INVALID_ARGS given argument has invalid value
     *
     * @endif
     */
    DataPortStatus setConsumer(InPortConsumer* consumer) override;

    /*!
     * @if jp
     * @brief バッファのセット
     *
     * この関数では、この Publisher に関連付けられるバッファをセットする。
     * バッファオブジェクトがヌルポインタの場合、INVALID_ARGSが返される。
     * それ以外の場合は、PORT_OK が返される。
     *
     * @param buffer CDR buffer へのポインタ
     * @return DataPortStatus PORT_OK 正常終了
     *                        INVALID_ARGS 引数に不正な値が含まれている
     *
     * @else
     * @brief Setting buffer pointer
     *
     * This operation sets a buffer that is associated with this
     * object. If the buffer object is NULL, INVALID_ARGS will be
     * returned.
     *
     * @param buffer A pointer to a CDR buffer object.
     * @return DataPortStatus PORT_OK normal return
     *                        INVALID_ARGS given argument has invalid value
     *
     * @endif
     */
    DataPortStatus setBuffer(CdrBufferBase* buffer) override;

    /*!
     * @if jp
     * @brief リスナを設定する。
     *
     * Publisher に対してリスナオブジェクト ConnectorListeners を設定する。
     * 各種リスナオブジェクトを含む ConnectorListeners をセットすることで、
     * バッファの読み書き、データの送信時等にこれらのリスナをコールする。
     * ConnectorListeners オブジェクトの所有権はポートまたは RTObject が持ち
     * Publisher 削除時に ConnectorListeners は削除されることはない。
     * ConnectorListeners がヌルポインタの場合 INVALID_ARGS を返す。
     *
     * @param info ConnectorProfile をローカル化したオブジェクト ConnectorInfo
     * @param listeners リスナを多数保持する ConnectorListeners オブジェクト
     * @return PORT_OK      正常終了
     *         INVALID_ARGS 不正な引数
     * @else
     * @brief Set the listener.
     *
     * This function sets ConnectorListeners listener object to the
     * Publisher. By setting ConnectorListeners containing various
     * listeners objects, these listeners are called at the time of
     * reading and writing of a buffer, and transmission of data
     * etc. Since the ownership of the ConnectorListeners object is
     * owned by Port or RTObject, the Publisher never deletes the
     * ConnectorListeners object. If the given ConnectorListeners'
     * pointer is NULL, this function returns INVALID_ARGS.
     *
     * @param info ConnectorInfo that is localized object of ConnectorProfile
     * @param listeners ConnectorListeners that holds various listeners
     * @return PORT_OK      Normal return
     *         INVALID_ARGS Invalid arguments
     * @endif
     */
    DataPortStatus setListener(ConnectorInfo& info,
                                   ConnectorListenersBase* listeners) override;
    /*!
     * @if jp
     * @brief データを書き込む
     *
     * Publisher が保持するバッファに対してデータを書き込む。コンシュー
     * マ、バッファ、リスナ等が適切に設定されていない等、Publisher オブ
     * ジェクトが正しく初期化されていない場合、この関数を呼び出すとエラー
     * コード PRECONDITION_NOT_MET が返され、バッファへの書き込み等の操
     * 作は一切行われない。
     *
     * バッファへの書き込みと、InPortへのデータの送信は非同期的に行われ
     * るため、この関数は、InPortへのデータ送信の結果を示す、
     * CONNECTION_LOST, BUFFER_FULL などのリターンコードを返すことがあ
     * る。この場合、データのバッファへの書き込みは行われない。
     *
     * バッファへの書き込みに対して、バッファがフル状態、バッファのエ
     * ラー、バッファへの書き込みがタイムアウトした場合、バッファの事前
     * 条件が満たされない場合にはそれぞれ、エラーコード BUFFER_FULL,
     * BUFFER_ERROR, BUFFER_TIMEOUT, PRECONDITION_NOT_MET が返される。
     *
     * これら以外のエラーの場合、PORT_ERROR が返される。
     *
     *
     * @param data 書き込むデータ
     * @param timeout タイムアウト時間
     *
     * @return PORT_OK             正常終了
     *         PRECONDITION_NO_MET consumer, buffer, listener等が適切に設定
     *                             されていない等、このオブジェクトの事前条件
     *                             を満たさない場合。
     *         CONNECTION_LOST     接続が切断されたことを検知した。
     *         BUFFER_FULL         バッファがフル状態である。
     *         BUFFER_ERROR        バッファに何らかのエラーが生じた場合。
     *         NOT_SUPPORTED       サポートされない操作が行われた。
     *         TIMEOUT             タイムアウトした。
     *
     * @else
     * @brief Write data
     *
     * This function writes data into the buffer associated with this
     * Publisher.  If a Publisher object calls this function, without
     * initializing correctly such as a consumer, a buffer, listeners,
     * etc., error code PRECONDITION_NOT_MET will be returned and no
     * operation of the writing to a buffer etc. will be performed.
     *
     * Since writing into the buffer and sending data to InPort are
     * performed asynchronously, occasionally this function returns
     * return-codes such as CONNECTION_LOST and BUFFER_FULL that
     * indicate the result of sending data to InPort. In this case,
     * writing data into buffer will not be performed.
     *
     * When publisher writes data to the buffer, if the buffer is
     * filled, returns error, is returned with timeout and returns
     * precondition error, error codes BUFFER_FULL, BUFFER_ERROR,
     * BUFFER_TIMEOUT and PRECONDITION_NOT_MET will be returned
     * respectively.
     *
     * In other cases, PROT_ERROR will be returned.
     *
     * @param data Data to be wrote to the buffer
     * @param timeout Timeout time in unit nano-seconds
     * @return PORT_OK             Normal return
     *         PRECONDITION_NO_MET Precondition does not met. A consumer,
     *                             a buffer, listenes are not set properly.
     *         CONNECTION_LOST     detected that the connection has been lost
     *         BUFFER_FULL         The buffer is full status.
     *         BUFFER_ERROR        Some kind of error occurred in the buffer.
     *         NOT_SUPPORTED       Some kind of operation that is not supported
     *                             has been performed.
     *         TIMEOUT             Timeout occurred when writing to the buffer.
     *
     * @endif
     */
    DataPortStatus write(ByteDataStreamBase* data,
                     std::chrono::nanoseconds timeout) override;
    /*!
     * @if jp
     *
     * @brief アクティブ化確認
     *
     * Publisher はデータポートと同期して activate/deactivate される。
     * activate() / deactivate() 関数によって、アクティブ状態と非アクティ
     * ブ状態が切り替わる。この関数により、現在アクティブ状態か、非アク
     * ティブ状態かを確認することができる。
     *
     * @return 状態確認結果(アクティブ状態:true、非アクティブ状態:false)
     *
     * @else
     *
     * @brief If publisher is active state
     *
     * A Publisher can be activated/deactivated synchronized with the
     * data port.  The active state and the non-active state are made
     * transition by the "activate()" and the "deactivate()" functions
     * respectively. This function confirms if the publisher is in
     * active state.
     *
     * @return Result of state confirmation
     *         (Active state:true, Inactive state:false)
     *
     * @endif
     */
    bool isActive() override;

    /*!
     * @if jp
     * @brief アクティブ化する
     *
     * Publisher をアクティブ化する。この関数を呼び出すことにより、
     * Publisherが持つ、データを送信するスレッドが動作を開始する。初期
     * 化が行われていないなどにより、事前条件を満たさない場合、エラーコー
     * ド PRECONDITION_NOT_MET を返す。
     *
     * @return PORT_OK 正常終了
     *         PRECONDITION_NOT_MET 事前条件を満たさない
     *
     * @else
     * @brief activation
     *
     * This function activates the publisher. By calling this
     * function, this publisher starts the thread that pushes data to
     * InPort. If precondition such as initialization process and so
     * on is not met, the error code PRECONDITION_NOT_MET is returned.
     *
     * @return PORT_OK normal return
     *         PRECONDITION_NOT_MET precondition is not met
     *
     * @endif
     */
    DataPortStatus activate() override;

    /*!
     * @if jp
     * @brief 非アクティブ化する
     *
     * Publisher を非アクティブ化する。この関数を呼び出すことにより、
     * Publisherが持つ、データを送信するスレッドが動作を停止する。初期
     * 化が行われていないなどにより、事前条件を満たさない場合、エラーコー
     * ド PRECONDITION_NOT_MET を返す。
     *
     * @return PORT_OK 正常終了
     *         PRECONDITION_NOT_MET 事前条件を満たさない
     *
     * @else
     * @brief deactivation
     *
     * This function deactivates the publisher. By calling this
     * function, this publisher stops the thread that pushes data to
     * InPort. If precondition such as initialization process and so
     * on is not met, the error code PRECONDITION_NOT_MET is returned.
     *
     * @return PORT_OK normal return
     *         PRECONDITION_NOT_MET precondition is not met
     *
     * @endif
     */
    DataPortStatus deactivate() override;

    /*!
     * @if jp
     * @brief スレッド実行関数
     *
     * coil::PeriodicTask により周期実行されるタスク実行関数。
     *
     * @else
     * @brief Thread execution function
     *
     * A task execution function to be executed by coil::PeriodicTask.
     *
     * @endif
     */
    virtual int svc();

  protected:
    enum Policy
      {
        PUBLISHER_POLICY_ALL,
        PUBLISHER_POLICY_FIFO,
        PUBLISHER_POLICY_SKIP,
        PUBLISHER_POLICY_NEW
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
    DataPortStatus pushAll();

    /*!
     * @brief push "fifo" policy
     */
    DataPortStatus pushFifo();

    /*!
     * @brief push "skip" policy
     */
    DataPortStatus pushSkip();

    /*!
     * @brief push "new" policy
     */
    DataPortStatus pushNew();

    /*!
     * @if jp
     * @brief BufferStatus から DataPortStatus への変換
     *
     * バッファからの戻り値を DataPortStatus 型へ変換する関数。そ
     * れぞれ、以下のように変換される。変換時にコールバックを呼ぶ場合、
     * コールバク関数も付記する。
     *
     * - BUFFER_OK: PORT_OK
     *  - None
     * - BUFFER_ERROR: BUFFER_ERROR
     *  - None
     * - BUFFER_FULL: BUFFER_FULL
     *  - onBufferFull()
     * - NOT_SUPPORTED: PORT_ERROR
     *  - None
     * - TIMEOUT: BUFFER_TIMEOUT
     *  - onBufferWriteTimeout()
     * - PRECONDITION_NOT_MET: PRECONDITION_NOT_MET
     *  - None
     * - other: PORT_ERROR
     *  - None
     *
     * @param status BufferStatus
     * @param data cdrMemoryStream
     * @return DataPortStatu 型のリターンコード
     *
     * @else
     * @brief Convertion from BufferStatus to DataPortStatus
     *
     * This function converts return value from the buffer to
     * DataPortStatus typed return value. The conversion rule is
     * as follows. Callback functions are also shown, if it exists.
     *
     * - BUFFER_OK: PORT_OK
     *  - None
     * - BUFFER_ERROR: BUFFER_ERROR
     *  - None
     * - BUFFER_FULL: BUFFER_FULL
     *  - onBufferFull()
     * - NOT_SUPPORTED: PORT_ERROR
     *  - None
     * - TIMEOUT: BUFFER_TIMEOUT
     *  - onBufferWriteTimeout()
     * - PRECONDITION_NOT_MET: PRECONDITION_NOT_MET
     *  - None
     * - other: PORT_ERROR
     *  - None
     *
     * @param status BufferStatus
     * @param data cdrMemoryStream
     * @return DataPortStatus typed return code
     *
     * @endif
     */
    DataPortStatus convertReturn(BufferStatus status,
                                 ByteData& data);


    /*!
     * @if jp
     * @brief DataPortStatusに従ってリスナへ通知する関数を呼び出す。
     *
     * @param status DataPortStatus
     * @param data cdrMemoryStream
     * @return リターンコード
     *
     * @else
     * @brief Call listeners according to the DataPortStatus
     *
     * @param status DataPortStatus
     * @param data cdrMemoryStream
     * @return Return code
     *
     * @endif
     */
    DataPortStatus invokeListener(DataPortStatus status,
                              ByteData& data);

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITEのリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_WRITE event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWrite(ByteData& data)
    {
      m_listeners->notifyOut(ConnectorDataListenerType::ON_BUFFER_WRITE,
                            m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_FULLリスナへイベントを通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_FULL event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferFull(ByteData& data)
    {
      m_listeners->notifyOut(
        ConnectorDataListenerType::ON_BUFFER_FULL, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_WRITE_TIMEOUTのリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_BUFFER_WRITE_TIMEOUT event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onBufferWriteTimeout(ByteData& data)
    {
      m_listeners->notifyOut(
        ConnectorDataListenerType::ON_BUFFER_WRITE_TIMEOUT, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_BUFFER_READのリスナへ通知する。
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
     * @brief ON_SENDのリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_SEND event to listners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onSend(ByteData& data)
    {
      m_listeners->notifyOut(ConnectorDataListenerType::ON_SEND, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVEDのリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_RECEIVED event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceived(ByteData& data)
    {
      m_listeners->notifyOut(ConnectorDataListenerType::ON_RECEIVED, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_FULLのリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_RECEIVER_FULL event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverFull(ByteData& data)
    {
      m_listeners->notifyOut(ConnectorDataListenerType::ON_RECEIVER_FULL, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_TIMEOUTのリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_RECEIVER_TIMEOUT event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverTimeout(ByteData& data)
    {
      m_listeners->notifyOut(ConnectorDataListenerType::ON_RECEIVER_TIMEOUT, m_profile, data);
    }

    /*!
     * @if jp
     * @brief ON_RECEIVER_ERRORのリスナへ通知する。
     * @param data cdrMemoryStream
     * @else
     * @brief Notify an ON_RECEIVER_ERROR event to listeners
     * @param data cdrMemoryStream
     * @endif
     */
    inline void onReceiverError(ByteData& data)
    {
      m_listeners->notifyOut(ConnectorDataListenerType::ON_RECEIVER_ERROR, m_profile, data);
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

    Logger rtclog{"PublisherPeriodic"};
    InPortConsumer* m_consumer{nullptr};
    CdrBufferBase* m_buffer{nullptr};
    ConnectorInfo m_profile;
    coil::PeriodicTaskBase* m_task{nullptr};
    ConnectorListenersBase* m_listeners{nullptr};
    DataPortStatus m_retcode{DataPortStatus::PORT_OK};
    std::mutex m_retmutex;
    Policy m_pushPolicy{PUBLISHER_POLICY_NEW};
    int m_skipn{0};
    bool m_active{false};
    bool m_readback{false};
    int m_leftskip{0};
    ByteData m_data;
  };
} // namespace RTC

extern "C"
{
  void PublisherPeriodicInit();
}

#endif  // RTC_PUBLISHERPERIODIC_H

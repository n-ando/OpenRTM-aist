// -*- C++ -*-
/*!
 * @file  PublisherNew.h
 * @brief PublisherNew class
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

#ifndef PublisherNew_h
#define PublisherNew_h

#include <rtm/RTC.h>

#include <ace/Task.h>
#include <ace/Synch.h>
#include <rtm/PublisherBase.h>

namespace RTC
{
  class InPortConsumer;
  class Properties;
  /*!
   * @if jp
   * @class PublisherNew
   * @brief PublisherNew クラス
   *
   * バッファ内に新規データが格納されたタイミングで、その新規データを送信する。
   * データ送出タイミングを待つコンシューマを、送出する側とは異なるスレッドで
   * 動作させる場合に使用。
   * Publisherの駆動は、データ送出のタイミングになるまでブロックされ、
   * 送出タイミングの通知を受けると、即座にコンシューマの送出処理を呼び出す。
   *
   * @else
   * @class PublisherNew
   * @brief PublisherNew class
   *
   * Send new data at timing of when it is stored into the buffer.
   * This class is used when operating Consumer that waits for the data send
   * timing in different thread from one of the send side.
   * Publisher's driven is blocked until the data send timing reaches, if the
   * send timing notification is received, the Consumer's send processing will
   * be invoked immediately.
   *
   * @endif
   */
  class PublisherNew
    : public PublisherBase,
      public ACE_Task<ACE_MT_SYNCH>
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     * 本 Publisher 用新規スレッドを生成する。
     *
     * @param consumer データ送出を待つコンシューマ
     * @param property 本Publisherの駆動制御情報を設定したPropertyオブジェクト
     *                 (本Publisherでは未使用)
     * @else
     * @brief Constructor
     *
     * Constructor
     * Create new thread for this Publisher.
     *
     * @param consumer Consumer that waits for the data sending
     * @param property Property object that is configured this Publisher's
     *                 control information.(Unused in this Publisher)
     * @endif
     */
    PublisherNew(InPortConsumer* consumer,
		 const Properties& property);
    
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
    virtual ~PublisherNew();
    
    /*!
     * @if jp
     * @brief Observer関数
     *
     * 送出タイミング時に呼び出す。
     * ブロックしている当該Publisherの駆動が開始され、コンシューマへの送出処理が
     * 行われる。
     *
     * @else
     * @brief Observer function
     *
     * Invoke at send timing.
     * Start this Publisher's control that has been blocked and do the send
     * processing to Consumer.
     *
     * @endif
     */
    virtual void update();
    
    /*!
     * @if jp
     * @brief スレッド実行関数
     *
     * ACE_Task::svc() のオーバーライド
     * バッファ内のデータが更新されるまでスレッドを待機させる。
     *
     * @return 実行結果
     *
     * @else
     * @brief Thread execution function
     *
     * ACE_Task::svc() override function.
     * Make thread stand by until data in the buffer is updated.
     *
     * @return Execution result
     *
     * @endif
     */
    virtual int svc(void);
    
    /*!
     * @if jp
     * @brief タスク開始
     *
     * ACE_Task::open() のオーバーライド
     * 本 publisher 用新規スレッドを生成する。
     *
     * @param args スレッド生成用引数(本Publisherでは未使用)
     *
     * @return 実行結果
     *
     * @else
     * @brief Task start function
     *
     * ACE_Task::open() override function.
     * Create newly thread for this Publisher.
     *
     * @param args Thread creation arguments (Unused in this Publisher)
     *
     * @return Execution result
     *
     * @endif
     */
    virtual int open(void *args);
    
    /*!
     * @if jp
     * @brief タスク終了関数
     *
     * ACE_Task::release() のオーバーライド
     * 駆動フラグをfalseに設定し、本 Publisher の駆動を停止する。
     * ただし、駆動スレッドがブロックされている場合には、
     * 最大１回コンシューマの送出処理が呼び出される場合がある。
     *
     * @else
     * @brief Task terminate function
     *
     * ACE_Task::release() override function.
     * Set driven flag to false, and terminate this Publisher's operation.
     * However, if the driven thread is blocked, Consumer's send
     * processing may be invoked maximum once.
     *
     * @endif
     */
    virtual void release();
    
  protected:
    
  private:
    InPortConsumer* m_consumer;
    bool m_running;
    unsigned long m_usec;
    
    // NewData condition struct
    struct NewData
    {
      NewData() : _cond(_mutex), _updated(false) {};
      ACE_Thread_Mutex _mutex;
      ACE_Condition<ACE_Thread_Mutex> _cond;
      bool _updated;
    };
    
    // A condition variable for data update notification 
    NewData m_data;
  };
};     // namespace RTC
#endif // PublisherNew_h


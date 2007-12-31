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
 * $Id: PublisherNew.h,v 1.3.2.1 2007-12-31 03:08:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/04/26 15:32:45  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.2  2007/01/06 18:00:54  n-ando
 * Some trivial fixes.
 *
 * Revision 1.1  2006/11/27 09:44:49  n-ando
 * The first commitment.
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
     * @endif
     */
    PublisherNew(InPortConsumer* consumer,
		 const Properties& property);
    
    /*!
     * @if jp
     * @brief デストラクタ
     * デストラクタ
     * @else
     * @brief Destructor
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
     * ACE_Task::svc() override function
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
     * ACE_Task::open() override function
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
     * ACE_Task::release() override function
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


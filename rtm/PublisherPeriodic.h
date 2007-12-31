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
 * $Id: PublisherPeriodic.h,v 1.3.2.1 2007-12-31 03:08:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/04/26 15:32:52  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.2  2007/01/06 18:01:06  n-ando
 * Some trivial fixes.
 *
 * Revision 1.1  2006/11/27 09:44:51  n-ando
 * The first commitment.
 *
 */

#ifndef PublisherPeriodic_h
#define PublisherPeriodic_h

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
   * @class PublisherPeriodic
   * @brief PublisherPeriodic クラス
   *
   * 一定周期でコンシューマの送出処理を呼び出す Publisher
   * 定期的にデータ送信を実行する場合に使用する。
   *
   * @else
   * @class PublisherPeriodic
   * @brief PublisherPeriodic class
   * @endif
   */
  class PublisherPeriodic
    : public PublisherBase,
      public ACE_Task<ACE_MT_SYNCH>
  {
    //    class InPortConsumer;
    
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     * 送出処理の呼び出し間隔を、Propertyオブジェクトのdataport.push_rateメンバ
     * に設定しておく必要がある。送出間隔は、Hz単位の浮動小数文字列で指定。
     * たとえば、1000.0Hzの場合は、「1000.0」を設定。
     * 上記プロパティが未設定の場合は、「1000Hz」を設定。
     *
     * @param consumer データ送出を待つコンシューマ
     * @param property 本Publisherの駆動制御情報を設定したPropertyオブジェクト
     *
     * @else
     * @brief Constructor
     * @endif
     */
    PublisherPeriodic(InPortConsumer* consumer,
		      const Properties& property);
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PublisherPeriodic();
    
    /*!
     * @if jp
     * @brief Observer関数
     *
     * 本 Publisher では何も実行しない。
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
     * ただし、最大１回コンシューマの送出処理が呼び出される場合がある。
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
    unsigned int m_usec;
  };
};     // namespace RTC
#endif // PublisherPeriodic_h

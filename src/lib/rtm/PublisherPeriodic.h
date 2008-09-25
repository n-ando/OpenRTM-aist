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

#ifndef PublisherPeriodic_h
#define PublisherPeriodic_h

#include <rtm/RTC.h>

#include <coil/Task.h>

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
   *
   * Publisher that invokes the consumer's sending process periodically.
   * This is used when the data sending is regularly executed.
   *
   * @endif
   */
  class PublisherPeriodic
    : public PublisherBase,
      public coil::Task
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
     *
     * Constructor.
     * The intervals of invoking send processing needs to be set in
     * dataport.push_rate of Property object. The interval is specified by
     * floating point string in Hz.
     * For example, "1000.0" is set for 1000.0Hz.
     * If the above property is unset, "1000Hz" will be set.
     *
     * @param consumer Consumer which waits for data sending
     * @param property Property objects that are set the control information
     *                 of this Publisher
     *
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
     *
     * Destructor
     *
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
     *
     * Execute nothing in this Publisher.
     *
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
     * ACE_Task::svc() override function.
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
     * @brief Start task
     *
     * ACE_Task::open() override function.
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
     * ACE_Task::release() override function.
     * Set driven flag to false, and terminate the operation of this Publisher.
     * However, the consumer's sending process may be invoked once or less.
     *
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


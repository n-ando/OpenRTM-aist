// -*- C++ -*-
/*!
 * @file  PublisherPeriodic.h
 * @brief PublisherPeriodic class
 * @date  $Date: 2007-04-26 15:32:52 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PublisherPeriodic.h,v 1.3 2007-04-26 15:32:52 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
     * @else
     * @brief Constructor
     * @endif
     */
    PublisherPeriodic(InPortConsumer* consumer,
		      const Properties& property);

    /*!
     * @if jp
     *
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PublisherPeriodic();
    /*!
     * @if jp
     * @brief Observer関数
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


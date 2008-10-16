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

#ifndef PublisherFlush_h
#define PublisherFlush_h

#include <rtm/PublisherBase.h>

namespace RTC
{
  class InPortConsumer;
  class Properties;
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
    PublisherFlush(InPortConsumer* consumer,
		   const coil::Properties& property);
    
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
    virtual ~PublisherFlush();
    
    /*!
     * @if jp
     * @brief Observer関数
     *
     * 送出タイミング時に呼び出す。
     * 即座に同一スレッドにてコンシューマの送出処理が呼び出される。
     *
     * @else
     * @brief Observer function
     *
     * This is invoked at the send timing.
     * Immediately, the Consumer's sending process is invoked in the same thread.
     *
     * @endif
     */
    virtual void update();
  protected:
    
  private:
    InPortConsumer* m_consumer;
    
  };
};     // namespace RTC
#endif // PublisherFlush_h


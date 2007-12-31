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
 * $Id: PublisherFlush.h,v 1.2.4.1 2007-12-31 03:08:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/06 18:00:44  n-ando
 * Some trivial fixes.
 *
 * Revision 1.1  2006/11/27 09:44:47  n-ando
 * The first commitment.
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
     * @endif
     */
    PublisherFlush(InPortConsumer* consumer,
		   const Properties& property);
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     * 当該Publisherを破棄する際に、PublisherFactoryにより呼び出される。
     *
     * @else
     * @brief Destructor
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
     * @endif
     */
    virtual void update();
  protected:
    
  private:
    InPortConsumer* m_consumer;
    
  };
};     // namespace RTC
#endif // PublisherFlush_h

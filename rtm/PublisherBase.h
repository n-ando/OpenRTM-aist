// -*- C++ -*-
/*!
 * @file PublisherBase.h
 * @brief Publisher base class
 * @date $Date: 2007-12-31 03:08:06 $
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
 * $Id: PublisherBase.h,v 1.1.4.2 2007-12-31 03:08:06 n-ando Exp $
 *
 */

#ifndef PublisherBase_h
#define PublisherBase_h

namespace RTC
{
  /*!
   * @if jp
   *
   * @class PublisherBase
   *
   * @brief Publisher 基底クラス
   * 
   * データ送出タイミングを管理して送出を駆動するPublisher* の基底クラス。
   * 各種 Publisher はこのクラスを継承して詳細を実装する。
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class PublisherBase
   *
   * @brief Base class of Publisher.
   *
   * This is a base class of Publisher*. This class manages data send timing.
   * Variation of Publisher* which implements details of Publisher inherits
   * this PublisherBase class.
   *
   * @endif
   */
  class PublisherBase
  {
  public:
    /*!
     * @if jp
     *
     * @brief 送出タイミングを通知する。
     *
     * 送出を待つオブジェクトに、送出タイミングを通知するための純粋仮想関数。
     * 
     * @else
     *
     * @brief Notify the data send timing
     *
     * Pure virtual function to notify the send timing to the object 
     * that waits for the send.
     * 
     * @endif
     */
    virtual void update() = 0;
    
    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * @else
     *
     * @brief Destructor
     *
     * @endif
     */
    virtual ~PublisherBase(){};
    
    /*!
     * @if jp
     *
     * @brief Publisher を破棄する。
     *
     * 当該 Publisher を破棄する。
     * 当該 Publisher が不要になった場合に PublisherFactory から呼び出される。
     *
     * @else
     *
     * @brief Release the Publisher
     *
     * Release this Publisher.
     * When Publisher becomes unnecessary, this is invoked from
     * PublisherFactory. 
     *
     * @endif
     */
    virtual void release(){}
  };
};
#endif // PublisherBase_h

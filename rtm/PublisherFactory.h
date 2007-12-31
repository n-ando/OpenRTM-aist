// -*- C++ -*-
/*!
 * @file  PublisherFactory.h
 * @brief PublisherFactory class
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
 * $Id: PublisherFactory.h,v 1.2.4.2 2007-12-31 03:08:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2.4.1  2007/06/22 10:55:11  n-ando
 * The bug of OutPort's disconnect operation was fixed.
 *
 * Revision 1.2  2007/01/06 18:00:31  n-ando
 * Some trivial fixes.
 *
 * Revision 1.1  2006/11/27 09:44:45  n-ando
 * The first commitment.
 *
 */

#ifndef PublisherFactory_h
#define PublisherFactory_h

#include <rtm/Properties.h>

namespace RTC
{
  class PublisherBase;
  class InPortConsumer;
  class Properties;
  
  /*!
   * @if jp
   * @class PublisherFactory
   * @brief PublisherFactory クラス
   *
   * 各種Publisherオブジェクトの生成・破棄を管理するファクトリクラス
   * ※テンポラリな実装
   *   将来的には任意のPublisherを生成できるようにする。
   *
   * @else
   * @class PublisherFactory
   * @brief PublisherFactory class
   * @endif
   */
  class PublisherFactory
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * デフォルトコンストラクタ
     *
     * @else
     * @brief Constructor
     * @endif
     */
    PublisherFactory(){};
    
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
    virtual ~PublisherFactory(){};
    
    /*!
     * @if jp
     * @brief Publisherの生成
     *
     * Publisherオブジェクトを生成する。
     * 指定された引数に応じた適切なPublisher実装のオブジェクトが生成される。
     * 生成するPublisherの種別を、指定されたPropertyオブジェクトの
     * dataport.subscription_typeメンバに設定しておく必要がある。
     * また、種別によっては、Publisherの駆動を制御する情報をさらに設定する必要が
     * ある。
     * これらの具体的な内容は、それぞれのPublisher実装を参照のこと。
     *
     * @param consumer Publisherによってデータ送出を駆動されるコンシューマ
     * @param property 生成すべきPublisherを特定するための情報や、Publisherの
     *                 駆動を制御するための情報が設定されているPropertyオブジェ
     *                 クト
     *
     * @return 生成したPublisherオブジェクト。生成に失敗した場合はNullを返す。
     *
     * @else
     * @brief Create Publisher
     * @endif
     */
    PublisherBase* create(InPortConsumer* consumer, Properties& property);
    
    /*!
     * @if jp
     * @brief Publisherの破棄
     *
     * 設定されたPublisherオブジェクトを破棄する。
     *
     * @param publisher 破棄対象Publisherオブジェクト
     *
     * @else
     * @brief Destroy Publisher
     * @endif
     */
    void destroy(PublisherBase *publisher);
  protected:
    
  private:
    
  };
};     // namespace RTC
#endif // PublisherFactory_h

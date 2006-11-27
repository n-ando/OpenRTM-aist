// -*- C++ -*-
/*!
 * @file  PublisherFactory.h
 * @brief PublisherFactory class
 * @date  $Date: 2006-11-27 09:44:45 $
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
 * $Id: PublisherFactory.h,v 1.1 2006-11-27 09:44:45 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
     * @else
     * @brief Constructor
     * @endif
     */
    PublisherFactory(){};

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PublisherFactory(){};

    /*!
     * @if jp
     * @brief Publisherの生成
     * @else
     * @brief Create Publisher
     * @endif
     */
    PublisherBase* create(const char* name,
			  InPortConsumer& consumer,
			  const Properties& property);
  protected:
  
  private:

  };
 
};     // namespace RTC
#endif // PublisherFactory_h


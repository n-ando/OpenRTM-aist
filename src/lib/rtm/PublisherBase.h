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
 * $Id$
 *
 */

#ifndef RTC_PUBLISHERBASE_H
#define RTC_PUBLISHERBASE_H

#include <coil/Properties.h>
#include <coil/Factory.h>
#include <rtm/RTC.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/DataPortStatus.h>

namespace coil
{
  class Properties;
}
namespace RTC
{
  class InPortConsumer;
  class ConnectorListeners;
  class ConnectorInfo;

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
    : public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM
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
    virtual ~PublisherBase(void){};

    /*!
     * @if jp
     * @brief 設定初期化
     *
     * InPortConsumerの各種設定を行う。実装クラスでは、与えられた
     * Propertiesから必要な情報を取得して各種設定を行う。この init() 関
     * 数は、OutPortProvider生成直後および、接続時にそれぞれ呼ばれる可
     * 能性がある。したがって、この関数は複数回呼ばれることを想定して記
     * 述されるべきである。
     * 
     * @param prop 設定情報
     *
     * @else
     *
     * @brief Initializing configuration
     *
     * This operation would be called to configure in initialization.
     * In the concrete class, configuration should be performed
     * getting appropriate information from the given Properties data.
     * This function might be called right after instantiation and
     * connection sequence respectivly.  Therefore, this function
     * should be implemented assuming multiple call.
     *
     * @param prop Configuration information
     *
     * @endif
     */
    virtual ReturnCode init(coil::Properties& prop) = 0;
    virtual ReturnCode setConsumer(InPortConsumer* consumer) = 0;
    virtual ReturnCode setBuffer(BufferBase<cdrMemoryStream>* buffer) = 0;
    virtual ReturnCode setListener(ConnectorInfo& info,
                                   ConnectorListeners* listeners) = 0;
    virtual ReturnCode write(const cdrMemoryStream& data,
                             unsigned long sec,
                             unsigned long usec) = 0;

    virtual bool isActive() = 0;
    virtual ReturnCode activate() = 0;
    virtual ReturnCode deactivate() = 0;


    

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

  typedef coil::GlobalFactory<PublisherBase> PublisherFactory;

};
#endif // RTC_PUBLISHERBASE_H

// -*- C++ -*-
/*!
 * @file SdoServiceAdmin.h
 * @brief SDO service administration class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2011
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: SdoConfiguration.cpp 1971 2010-06-03 08:46:40Z n-ando $
 *
 */

#ifndef RTC_SDOSERVICEADMIN_H
#define RTC_SDOSERVICEADMIN_H

#include <coil/Mutex.h>
#include <coil/Factory.h>

#include <rtm/idl/SDOPackageStub.h>
#include <rtm/SystemLogger.h>

namespace RTC
{
  class RTObject_impl;
  class SdoServiceConsumerBase;

  /*!
   * @if jp
   *
   * @class SDO service administration class
   * @brief SDO service 管理クラス
   *
   * このクラスは、SDO Service を管理するためのクラスである。SDO
   * Service は OMG SDO Specification において定義されている、SDOが特定
   * の機能のために提供また要求するサービスの一つである。詳細は仕様にお
   * いて定義されていないが、本クラスでは以下のように振る舞うサービスで
   * あるものとし、これらを管理するためのクラスが本クラスである。
   *
   * SDO Service においては、SDO/RTCに所有され、ある種のサービスを提供
   * するものを SDO Service Provider、他のSDO/RTCやアプリケーションが提
   * 供するサービスオブジェクトの参照を受け取り、それらの機能を利用する
   * ものを、SDO Service Consumer と呼ぶ。
   *
   * SDO Service Provider は他のアプリケーションから呼ばれ、SDO/RTC内部
   * の機能にアクセスするために用いられる。他のSDO/RTCまたはアプリケー
   * ションは、
   *
   * - SDO::get_service_profiles ()
   * - SDO::get_service_profile (in UniqueIdentifier id)
   * - SDO::get_sdo_service (in UniqueIdentifier id) 
   *
   * のいずれかのオペレーションにより、ServiceProfile または SDO
   * Service の参照を取得し、機能を利用するためのオペレーションを呼び出
   * す。他のSDO/RTCまたはアプリケーション上での参照の破棄は任意のタイ
   * ミングで行われ、サービス提供側では、どこからどれだけ参照されている
   * かは知ることはできない。一方で、SDO/RTC側も、任意のタイミングでサー
   * ビスの提供を停止することもできるため、サービスの利用側では、常にい
   * サービスが利用できるとは限らないものとしてサービスオペレーションを
   * 呼び出す必要がある。
   *
   * 一方、SDO Service Consumer は当該SDO/RTC以外のSDO/RTCまたはアプリ
   * ケーションがサービスの実体を持ち、当該SDO/RTCにオブジェクト参照を
   * 含むプロファイルを与えることで、SDO/RTC側からサービスオペレーショ
   * ンが呼ばれ外部のSDO/RTCまたはアプリケーションが提供する機能を利用
   * できる。また、オブザーバ的なオブジェクトを与えることで、SDO/RTC側
   * からのコールバックを実現するためにも利用することができる。コンシュー
   * マは、プロバイダとは異なり、SDO Configurationインターフェースから
   * 追加、削除が行われる。関連するオペレーションは以下のとおりである。
   *
   * - Configuration::add_service_profile (in ServiceProfile sProfile)
   * - Configuration::remove_service_profile (in UniqueIdentifier id)
   *
   * 外部のSDO/RTCまたはアプリケーションは、自身が持つSDO Servcie
   * Provider の参照をIDおよびinterface type、プロパティとともに
   * ServcieProfile にセットしたうえで、add_service_profile() の引数と
   * して与えることで、当該SDO/RTCにサービスを与える。この際、IDはUUID
   * など一意なIDでなければならない。また、削除する際にはIDにより対象と
   * するServiceProfileを探索するため、サービス提供側では削除時までIDを
   * 保持しておかなければならない。
   *
   * 
   *
   *
   *
   * @since 1.1.0
   *
   * @else
   *
   * @class SDO service administration class
   * @brief SDO service administration class
   *
   *
   * @since 1.1.0
   *
   * @endif
   */
  class SdoServiceAdmin
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     * 
     * コンストラクタ
     *
     * @param 
     * 
     * @else
     *
     * @brief Constructor
     * 
     * Constructor
     *
     * @param 
     *
     * @endif
     */
    SdoServiceAdmin(::RTC::RTObject_impl& rtobj);

    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     * 
     * 仮想デストラクタ。
     * 
     * @else
     *
     * @brief Virtual destractor
     *
     * Virtual destractor.
     *
     * @endif
     */
    virtual ~SdoServiceAdmin();
    
    /*!
     * @if jp
     *
     * @brief Service Consumer Factory を登録する
     * 
     * @else
     *
     * @brief Add Service Consumer Factory
     *
     * @endif
     */
    bool addSdoServiceConsumerFactory();

    /*!
     * @if jp
     *
     * @brief Service Consumer Factory を削除する
     * 
     * @else
     *
     * @brief Remove Service Consumer Factory
     *
     * @endif
     */
    bool removeSdoServiceConsumerFactory();
    
    /*!
     * @if jp
     *
     * @brief Service Consumer を追加する
     * 
     * @else
     *
     * @brief Add Service Consumer
     *
     * @endif
     */
    bool addSdoServiceConsumer(const SDOPackage::ServiceProfile& sProfile);
    
    /*!
     * @if jp
     *
     * @brief Service Consumer を削除する
     * 
     * @else
     *
     * @brief Remove Service Consumer
     *
     * @endif
     */
    bool removeSdoServiceConsumer(const char* id);
    
protected:
    /*!
     * @if jp
     *
     * @brief 許可されたサービス型かどうか調べる
     * 
     * @else
     *
     * @brief If it is allowed service type
     *
     * @endif
     */
    bool isAllowedConsumerType(const SDOPackage::ServiceProfile& sProfile);

    /*!
     * @if jp
     *
     * @brief 存在するサービス型かどうか調べる
     * 
     * @else
     *
     * @brief If it is existing service type
     *
     * @endif
     */
    bool isExistingConsumerType(const SDOPackage::ServiceProfile& sProfile);

    const std::string getUUID() const;
    

  private:
    RTC::RTObject_impl& m_rtobj;
    coil::vstring m_consumerTypes;
    bool m_allConsumerAllowed;
    
    /*!
     * @if jp
     * @brief Lock 付き SDO ServiceProfileList
     * @else
     * @brief SDO ServiceProfileList with mutex lock
     * @endif
     */
    SDOPackage::ServiceProfileList m_providerProfiles;
    coil::Mutex m_provider_mutex;
    
    /*!
     * @if jp
     * @brief Lock 付き SDO ServiceProfileList
     * @else
     * @brief SDO ServiceProfileList with mutex lock
     * @endif
     */
    std::vector<SdoServiceConsumerBase*> m_consumers;
    coil::Mutex m_consumer_mutex;

    /*!
     * @if jp
     * @brief logger
     * @else
     * @brief logger
     * @endif
     */
    ::RTC::Logger rtclog;
  };


};

#endif // RTC_SDOSERVICEADMIN_H

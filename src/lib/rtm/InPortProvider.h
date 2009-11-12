// -*- C++ -*-
/*!
 * @file  InPortProvider.h
 * @brief InPortProvider class
 * @date  $Date: 2007-12-31 03:08:03 $
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

#ifndef RTC_INPORTPROVIDER_H
#define RTC_INPORTPROVIDER_H

#include <string>

#include <coil/Factory.h>

#include <rtm/BufferBase.h>
#include <rtm/NVUtil.h>
#include <rtm/SystemLogger.h>
#include <rtm/DataPortStatus.h>

namespace RTC
{
  class ConnectorListeners;
  class ConnectorInfo;

  /*!
   * @if jp
   * @class InPortProvider
   * @brief InPortProvider クラス
   *
   * InPortの情報を保持するためのクラス。
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortProvider
   * @brief InPortProvider class
   *
   * Class to hold InPort information.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class InPortProvider
    : public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @endif
     */
    InPortProvider();
    
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
    virtual ~InPortProvider(void);

    /*!
     * @if jp
     * @brief 設定初期化
     *
     * InPortConsumerの各種設定を行う
     *
     * @else
     * @brief Initializing configuration
     *
     * This operation would be called to configure this consumer
     * in initialization.
     *
     * @endif
     */
    virtual void init(coil::Properties& prop) = 0;

    /*!
     * @if jp
     * @brief バッファを設定する
     *
     * バッファを設定する。InPortConsumerは外部から到着した
     * データをこのバッファに対して書き込む
     *
     * @else
     * @brief Initializing configuration
     *
     * This operation would be called to configure this consumer
     * in initialization.
     *
     * @endif
     */
    virtual void setBuffer(BufferBase<cdrMemoryStream>* buffer) = 0;

    virtual void setListener(ConnectorInfo& info,
                             ConnectorListeners* listeners) = 0;
    
    /*!
     * @if jp
     * @brief InterfaceProfile情報を公開する
     *
     * InterfaceProfile情報を公開する。
     *
     * @param properties InterfaceProfile情報を受け取るプロパティ
     *
     * @else
     * @brief Publish InterfaceProfile information
     *
     * Publish InterfaceProfile information.
     *
     * @param properties Properties to receive InterfaceProfile information
     *
     * @endif
     */
    virtual void publishInterfaceProfile(SDOPackage::NVList& properties);
    
    /*!
     * @if jp
     * @brief Interface情報を公開する
     *
     * Interface情報を公開する。
     *
     * @param properties Interface情報を受け取るプロパティ
     *
     * @else
     * @brief Publish interface information
     *
     * Publish interface information.
     *
     * @param properties Properties to receive interface information
     *
     * @endif
     */
    virtual bool publishInterface(SDOPackage::NVList& properties);
    
  protected:
    /*!
     * @if jp
     * @brief インタフェースタイプを設定する
     *
     * インタフェースタイプを設定する。
     *
     * @param interface_type 設定対象インタフェースタイプ
     *
     * @else
     * @brief Set the interface type
     *
     * Set the interface type.
     *
     * @param interface_type The target interface type for set
     *
     * @endif
     */
    void setInterfaceType(const char* interface_type);
    
    /*!
     * @if jp
     * @brief データフロータイプを設定する
     *
     * データフロータイプを設定する。
     *
     * @param dataflow_type 設定対象データフロータイプ
     *
     * @else
     * @brief Set the dataflow type
     *
     * Set the dataflow type.
     *
     * @param dataflow_type The target data flow type for set
     *
     * @endif
     */
    void setDataFlowType(const char* dataflow_type);
    
    /*!
     * @if jp
     * @brief サブスクリプションタイプを設定する
     *
     * サブスクリプションタイプを設定する。
     *
     * @param subs_type 設定対象サブスクリプションタイプ
     *
     * @else
     * @brief Set the subscription type
     *
     * Set the subscription type.
     *
     * @param subs_type The target subscription type for set
     *
     * @endif
     */
    void setSubscriptionType(const char* subs_type);


  protected:
    /*!
     * @if jp
     * @brief ポートプロファイルを保持するプロパティ
     * @else
     * @brief Properties to hold port profile
     * @endif
     */
    SDOPackage::NVList m_properties;
    mutable Logger rtclog;

  private:
    std::string m_interfaceType;
    std::string m_dataflowType;
    std::string m_subscriptionType;

  public:
    // functors
    /*!
     * @if jp
     * @brief インターフェースプロファイルを公開するたのファンクタ
     * @else
     * @brief Functor to publish interface profile
     * @endif
     */
    struct publishInterfaceProfileFunc
    {
      publishInterfaceProfileFunc(SDOPackage::NVList& prop) : m_prop(prop) {}
      void operator()(InPortProvider* provider)
      {
	provider->publishInterfaceProfile(m_prop);
      }
      SDOPackage::NVList& m_prop;
    };

    /*!
     * @if jp
     * @brief インターフェースプロファイルを公開するたのファンクタ
     * @else
     * @brief Functor to publish interface profile
     * @endif
     */
    struct publishInterfaceFunc
    {
      publishInterfaceFunc(SDOPackage::NVList& prop)
        : m_prop(prop), provider_(0) {}
      void operator()(InPortProvider* provider)
      {
	if (provider->publishInterface(m_prop))
          {
            provider_ = provider;
          }
      }
      SDOPackage::NVList& m_prop;
      InPortProvider* provider_;
    };


  };

  typedef ::coil::GlobalFactory<InPortProvider> InPortProviderFactory;

};     // namespace RTC
#endif // RTC_INPORTPROVIDER_H

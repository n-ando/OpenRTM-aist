// -*- C++ -*-
/*!
 * @file InPortBase.h
 * @brief RTC::Port implementation for InPort
 * @date $Date: 2008-01-13 15:06:40 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2009
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

#ifndef RTC_INPORTBASE_H
#define RTC_INPORTBASE_H

#include <rtm/PortBase.h>
#include <rtm/DataPortStatus.h>
#include <rtm/CdrBufferBase.h>

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RTコンポーネント
 *
 * @else
 *
 * @namespace RTC
 *
 * @brief RT-Component
 *
 * @endif
 */
namespace RTC
{
  class InPortProvider;
  class OutPortConsumer;
  class InPortConnector;

  /*!
   * @if jp
   * @class InPortBase
   * @brief InPort 用 Port
   *
   * データ入力ポートの実装クラス。
   *
   * @since 0.4.0
   *
   * @else
   * @class InPortBase
   * @brief Port for InPort
   *
   * This is an implementation class for the data input port.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class InPortBase
    : public PortBase, public DataPortStatus
  {
  public:
    DATAPORTSTATUS_ENUM
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param name ポート名称
     * @param inport 当該データ入力ポートに関連付けるInPortオブジェクト
     *               InPortオブジェクトで扱うデータ型、バッファタイプも指定する
     * @param prop ポート設定用プロパティ
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Port name
     * @param inport InPort object that is associated with this data input port.
     *               Specify also the data type and the buffer type used in 
     *               the InPort object.
     * @param prop Property for setting ports
     *
     * @endif
     */
    InPortBase(const char* name, const char* data_type);
    
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
    virtual ~InPortBase(void);
    
    coil::Properties& properties();

    void init();

    /*!
     * @if jp
     *
     * @brief InPortを activates する
     *
     * InPortを activate する。
     *
     * @else
     *
     * @brief Activate all Port interfaces
     *
     * This operation activate all interfaces that is registered in the
     * ports.
     *
     * @endif
     */
    virtual void activateInterfaces();

    /*!
     * @if jp
     *
     * @brief 全ての Port のインターフェースを deactivates する
     *
     * Port に登録されている全てのインターフェースを deactivate する。
     *
     * @else
     *
     * @brief Deactivate all Port interfaces
     *
     * This operation deactivate all interfaces that is registered in the
     * ports.
     *
     * @endif
     */
    virtual void deactivateInterfaces();

  protected:
    /*!
     * @if jp
     * @brief Interface情報を公開する
     *
     * Interface情報を公開する。
     * 引数の ConnectorProfile に格納されている dataflow_type が push 型
     * の場合は、指定された interface_type の InPortProvider に関する情報
     * を ConnectorProfile::properties に書込み呼び出し側に戻す。
     *
     *  dataport.dataflow_type
     *
     * @param connector_profile コネクタプロファイル
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     * @brief Publish interface information
     *
     * Publish interface information.
     * Assign the Provider information that owned by this port
     * to ConnectorProfile#properties
     *
     * @param connector_profile The connector profile
     *
     * @return The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    publishInterfaces(ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interfaceに接続する
     *
     * Interfaceに接続する。
     * Portが所有するConsumerに適合するProviderに関する情報を 
     * ConnectorProfile#properties から抽出し、
     * ConsumerにCORBAオブジェクト参照を設定する。
     *
     * @param connector_profile コネクタ・プロファイル
     *
     * @return ReturnCode_t 型のリターンコード
     *
     * @else
     * @brief Subscribe to the interface
     *
     * Subscribe to interface.
     * Derive Provider information that matches Consumer owned by the Port 
     * from ConnectorProfile#properties and 
     * set the Consumer to the reference of the CORBA object.
     *
     * @param connector_profile The connector profile
     *
     * @return ReturnCode_t The return code of ReturnCode_t type
     *
     * @endif
     */
    virtual ReturnCode_t
    subscribeInterfaces(const ConnectorProfile& connector_profile);
    
    /*!
     * @if jp
     * @brief Interfaceへの接続を解除する
     *
     * Interfaceへの接続を解除する。
     * 与えられたConnectorProfileに関連するConsumerに設定された全てのObjectを
     * 解放し接続を解除する。
     *
     * @param connector_profile コネクタ・プロファイル
     *
     * @else
     * @brief Disconnect the interface connection
     *
     * Disconnect the interface connection.
     * Release all objects set in Consumer associated with 
     * given ConnectorProfile and unscribe the interface.
     *
     * @param connector_profile The connector profile
     *
     * @endif
     */
    virtual void
    unsubscribeInterfaces(const ConnectorProfile& connector_profile);


    /*!
     * @if jp
     * @brief InPort provider の初期化
     * @else
     * @brief InPort provider initialization
     * @endif
     */
    void initProviders();

    /*!
     * @if jp
     * @brief OutPort consumer の初期化
     * @else
     * @brief OutPort consumer initialization
     * @endif
     */
    void initConsumers();

    /*!
     * @if jp
     * @brief InPort provider の生成
     * @else
     * @brief InPort provider creation
     * @endif
     */
    InPortProvider* createProvider(const std::string& iface_type);
    
    /*!
     * @if jp
     * @brief InPort provider の削除
     * @else
     * @brief InPort provider deletion
     * @endif
     */
    void deleteProvider(InPortProvider* provider);
    
  protected:
    bool m_singlebuffer;
    CdrBufferBase* m_thebuffer;

    coil::Properties m_properties;
    std::vector<InPortProvider*> m_providers;
    std::vector<OutPortConsumer*> m_consumers;
    std::vector<InPortConnector*> m_connectors;
    coil::vstring m_consumerTypes;


  };
}; // namespace RTC

#endif // RTC_INPORTBASE_H

// -*- C++ -*-
/*!
 * @file DataInPort.h
 * @brief RTC::Port implementation for Data InPort
 * @date $Date: 2008-01-13 15:06:40 $
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
 * $Id$
 *
 */

#ifndef DataInPort_h
#define DataInPort_h

#include <rtm/PortBase.h>
#include <rtm/BufferBase.h>
#include <rtm/InPortCorbaProvider.h>
#include <rtm/OutPortCorbaConsumer.h>
#include <rtm/NVUtil.h>
#include <rtm/InPort.h>

#ifdef RTC_SOCK_DATAPORT
#include <rtm/InPortTcpSockProvider.h>
#endif

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
  /*!
   * @if jp
   * @class DataInPort
   * @brief InPort 用 Port
   *
   * データ入力ポートの実装クラス。
   *
   * @since 0.4.0
   *
   * @else
   * @class DataInPort
   * @brief Port for InPort
   *
   * This is an implementation class for the data input port.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class DataInPort
    : public virtual PortBase
  {
  public:
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
    template <class DataType, template <class DataType> class Buffer>
//    DataInPort(const char* name, InPort<DataType, Buffer>& inport,
//	       Properties& prop)
    DataInPort(const char* name, InPort<DataType, Buffer>& inport,
	       coil::Properties& prop)
      : PortBase(name)
    {
      // PortProfile::properties を設定
      addProperty("port.port_type", "DataInPort");
      
      // CORBA InPort Provider
      m_providers.push_back(new InPortCorbaProvider<DataType>(inport));
      m_providers.back()->publishInterfaceProfile(m_profile.properties);
      
      // TCP Socket InPort Provider
#ifdef RTC_SOCK_DATAPORT
      m_providers.push_back(new InPortTcpSockProvider<DataType>(inport, prop));
      m_providers.back()->publishInterfaceProfile(m_profile.properties);
#endif
      
      // CORBA OutPort Consumer
      m_consumers.push_back(new OutPortCorbaConsumer<DataType>(inport));
      
      // dummy var
      m_dummy.push_back(1);
    }
    
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
    virtual ~DataInPort(void);
    
  protected:
    /*!
     * @if jp
     * @brief Interface情報を公開する
     *
     * Interface情報を公開する。
     * このPortが所有しているプロバイダ(Provider)に関する情報を、
     * ConnectorProfile#propertiesに代入する。
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
     * @brief Interface公開用Functor
     *
     * Interface公開処理を実行するためのFunctor。
     *
     * @else
     * @brief Functor to publish the interface
     *
     * Functor to publish the interface
     *
     * @endif
     */
    struct publish;
    
    /*!
     * @if jp
     * @brief Interface接続用Functor
     *
     * Interface接続処理を実行するためのFunctor。
     *
     * @else
     * @brief Functor to subscribe the interface
     *
     * Functor to subscribe the interface
     *
     * @endif
     */
    struct subscribe;
    
    /*!
     * @if jp
     * @brief Interface接続解除用Functor
     *
     * Interface接続解除処理を実行するためのFunctor。
     *
     * @else
     * @brief Functor to unsubscribe the interface
     *
     * Functor to unsubscribe the interface
     *
     * @endif
     */
    struct unsubscribe;
    
  private:
    /*
     * Bug
     *
     * Fedora5/gcc4.1.1. にて DataInPort の先頭領域のメモリ破壊が
     * 起こっている模様。
     * (gdbでかなり粘って追ってみたが断念)
     * もともともは std::vector<InPortProvider*> m_providers が先頭
     * このままだと、
     * $vec->_M_impl._M_start:  begin() に相当？
     * $vec->_M_impl._M_finish: end() に相当？
     * においてい _M_start が不可解な位置を指すため、
     * m_providers に対して for_each を適用するとSegvで落ちる。
     *
     * FreeBSD6.0/gcc3.4.4ではこの現象は発生せず。
     */
    std::vector<int> m_dummy;
    std::vector<InPortProvider*> m_providers;
    std::vector<OutPortConsumer*> m_consumers;
  };
}; // namespace RTC

#endif // DataInPort_h

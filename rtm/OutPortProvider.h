// -*- C++ -*-
/*!
 * @file  OutPortProvider.h
 * @brief OutPortProvider class
 * @date  $Date: 2007-12-31 03:08:05 $
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
 * $Id: OutPortProvider.h,v 1.2.4.1 2007-12-31 03:08:05 n-ando Exp $
 *
 */

#ifndef OutPortProvider_h
#define OutPortProvider_h

#include <rtm/NVUtil.h>
#include <string>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class OutPortProvider
   * @brief OutPortProvider
   *
   * - Port に対して何を提供しているかを宣言する。
   *   PortProfile の properties に Provider に関する情報を追加する。
   *
   * (例) OutPort を Provide する場合
   *
   * OutPortCorbaProvider が以下を宣言
   *  - dataport.interface_type = CORBA_Any
   *  - dataport.dataflow_type = Push, Pull
   *  - dataport.subscription_type = Once, New, Periodic
   * 
   * OutPortRawTCPProvider が以下を宣言
   *  - dataport.interface_type = RawTCP
   *  - dataport.dataflow_type = Push, Pull
   *  - dataport.subscription_type = Once, New, Periodic
   * 
   * 最終的に PortProfile::properties は
   *  - dataport.interface_type = CORBA_Any, RawTCP
   *  - dataport.dataflow_type = Push, Pull
   *  - dataport.subscription_type = Once, New, Periodic
   *
   * @since 0.4.0
   *
   * @else
   *
   * @class OutPortProvider
   * @brief OutPortProvider
   *
   * - Declare what is provided to the port.
   *   Add information associated with Provider to the properties of PortProfile.
   *
   * (Example) When OutPort is provided:
   *
   * OutPortCorbaProvider declares the following:
   *  - dataport.interface_type = CORBA_Any
   *  - dataport.dataflow_type = Push, Pull
   *  - dataport.subscription_type = Once, New, Periodic
   * 
   * OutPortRawTCPProvider declares the following:
   *  - dataport.interface_type = RawTCP
   *  - dataport.dataflow_type = Push, Pull
   *  - dataport.subscription_type = Once, New, Periodic
   * 
   * Finally, PortProfile::properties declares the following:
   *  - dataport.interface_type = CORBA_Any, RawTCP
   *  - dataport.dataflow_type = Push, Pull
   *  - dataport.subscription_type = Once, New, Periodic
   *
   * @since 0.4.0
   *
   * @endif
   */
  class OutPortProvider
  {
  public:
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
    virtual ~OutPortProvider(){};
    
    /*!
     * @if jp
     * @brief InterfaceProfile情報を公開する
     *
     * InterfaceProfile情報を公開する。
     * 引数で指定するプロパティ情報内の NameValue オブジェクトの
     * dataport.interface_type 値を調べ、当該ポートに設定されている
     * インターフェースタイプと一致する場合のみ情報を取得する。
     *
     * @param properties InterfaceProfile情報を受け取るプロパティ
     *
     * @else
     * @brief Publish InterfaceProfile information
     *
     * Publish interfaceProfile information.
     * Check the dataport.interface_type value of the NameValue object 
     * specified by an argument in property information and get information
     * only when the interface type of the specified port is matched.
     *
     * @param properties Properties to get InterfaceProfile information
     *
     * @endif
     */
    virtual void publishInterfaceProfile(SDOPackage::NVList& properties);
    
    /*!
     * @if jp
     * @brief Interface情報を公開する
     *
     * Interface情報を公開する
     * 引数で指定するプロパティ情報内の NameValue オブジェクトの
     * dataport.interface_type 値を調べ、当該ポートに設定されていなければ
     * NameValue に情報を追加する。
     * すでに同一インターフェースが登録済みの場合は何も行わない。
     *
     * @param properties Interface情報を受け取るプロパティ
     *
     * @else
     * @brief Publish interface information
     *
     * Publish interface information.
     * Check the dataport.interface_type value of the NameValue object specified 
     * by an argument in the property information, and add the information to the
     * NameValue if this port is not specified.
     * This does not do anything if the same interface is already subscribed.
     *
     * @param properties Properties to receive interface information
     *
     * @endif
     */
    virtual void publishInterface(SDOPackage::NVList& properties);
    
  protected:
    /*!
     * @if jp
     * @brief ポートタイプを設定する
     *
     * 引数で指定したポートタイプを設定する。
     *
     * @param port_type 設定対象ポートタイプ
     *
     * @else
     * @brief Set the port type
     *
     * Set the port type specified by the argument.
     *
     * @param port_type The target port type to set
     *
     * @endif
     */
    void setPortType(const char* port_type);
    
    /*!
     * @if jp
     * @brief データタイプを設定する
     *
     * 引数で指定したデータタイプを設定する。
     *
     * @param data_type 設定対象データタイプ
     *
     * @else
     * @brief Set the data type
     *
     * Set the data type specified by the argument.
     *
     * @param data_type The target data type to set
     *
     * @endif
     */
    void setDataType(const char* data_type);
    
    /*!
     * @if jp
     * @brief インターフェースタイプを設定する
     *
     * 引数で指定したインターフェースタイプを設定する。
     *
     * @param interface_type 設定対象インターフェースタイプ
     *
     * @else
     * @brief Set the interface type
     *
     * Set theinterface type specified by the argument.
     *
     * @param interface_type The target interface type to set
     *
     * @endif
     */
    void setInterfaceType(const char* interface_type);
    
    /*!
     * @if jp
     * @brief データフロータイプを設定する
     *
     * 引数で指定したデータフロータイプを設定する。
     *
     * @param dataflow_type 設定対象データフロータイプ
     *
     * @else
     * @brief Set the data flow type
     *
     * Set the data flow type specified by the argument.
     *
     * @param dataflow_type The target data flow type to set
     *
     * @endif
     */
    void setDataFlowType(const char* dataflow_type);
    
    /*!
     * @if jp
     * @brief サブスクリプションタイプを設定する
     *
     * 引数で指定したサブスクリプションタイプを設定する。
     *
     * @param subs_type 設定対象サブスクリプションタイプ
     *
     * @else
     * @brief Set the subscription type
     *
     * Set the subscription type specified by the argument.
     *
     * @param subs_type The target subscription type to set
     *
     * @endif
     */
    void setSubscriptionType(const char* subs_type);
    
    /*!
     * @if jp
     * @brief ポートプロファイルを保持するプロパティ
     * @else
     * @brief Properties to hold the port profiles
     * @endif
     */
    SDOPackage::NVList m_properties;
    
  private:
    std::string m_portType;
    std::string m_dataType;
    std::string m_interfaceType;
    std::string m_dataflowType;
    std::string m_subscriptionType;
  };
}; // namespace RTC
#endif // OutPortProvider_h

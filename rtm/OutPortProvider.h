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

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2007/01/06 17:58:52  n-ando
 * Interface and its profile publish functions (publishInterfaceProfile()
 * and publishInterface()) are added.
 *
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
   * @brief OutPort
   *
   * - Port に対して何を提供しているかを宣言する。
   *   PortProfile の properties に Provider に関する情報を追加する。
   *
   * (例) OutPort を Provide する場合
   *
   * OutPortCorbaProvider が以下を宣言
   * dataport.interface_type = CORBA_Any
   * dataport.dataflow_type = Push, Pull
   * dataport.subscription_type = Once, New, Periodic
   * 
   * OutPortRawTCPProviderが以下を宣言
   * dataport.interface_type = RawTCP
   * dataport.dataflow_type = Push, Pull
   * dataport.subscription_type = Once, New, Periodic
   * 
   * 最終的に PortProfile::properties は
   * dataport.interface_type = CORBA_Any, RawTCP
   * dataport.dataflow_type = Push, Pull
   * dataport.subscription_type = Once, New, Periodic
   *
   * @since 0.4.0
   *
   * @else
   *
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
     *
     * @endif
     */
    virtual void publishInterfaceProfile(SDOPackage::NVList& properties);
    
    /*!
     * @if jp
     * @brief Interface情報を公開する
     *
     * Interface情報を公開する。
     * 引数で指定するプロパティ情報内の NameValue オブジェクトの
     * dataport.interface_type 値を調べ、当該ポートに設定されていなければ
     * NameValue に情報を追加する。
     * すでに同一インターフェースが登録済みの場合は何も行わない。
     *
     * @param properties InterfaceProfile情報を受け取るプロパティ
     *
     * @else
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
     *
     * @endif
     */
    void setSubscriptionType(const char* subs_type);
    
    /*!
     * @if jp
     * @brief ポートプロファイルを保持するプロパティ
     * @else
     *
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

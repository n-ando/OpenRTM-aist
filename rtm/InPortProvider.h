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

#ifndef InPortProvider_h
#define InPortProvider_h

#include <rtm/NVUtil.h>
#include <string>

namespace RTC
{
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
  {
  public:
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
    //    InPortProvider();
    
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
    virtual ~InPortProvider();
    
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
    virtual void publishInterface(SDOPackage::NVList& properties);
    
  protected:
    /*!
     * @if jp
     * @brief データタイプを設定する
     *
     * データタイプを設定する。
     *
     * @param data_type 設定対象データタイプ
     *
     * @else
     * @brief Set the data type
     *
     * Set the data type.
     *
     * @param data_type The target data type for set
     *
     * @endif
     */
    void setDataType(const char* data_type);
    
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
    
    /*!
     * @if jp
     * @brief ポートプロファイルを保持するプロパティ
     * @else
     * @brief Properties to hold port profile
     * @endif
     */
    SDOPackage::NVList m_properties;
    
  private:
    std::string m_dataType;
    std::string m_interfaceType;
    std::string m_dataflowType;
    std::string m_subscriptionType;
  };
};     // namespace RTC
#endif // InPortProvider_h

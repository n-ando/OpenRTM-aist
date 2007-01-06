// -*- C++ -*-
/*!
 * @file  OutPortProvider.h
 * @brief OutPortProvider class
 * @date  $Date: 2007-01-06 17:58:52 $
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
 * $Id: OutPortProvider.h,v 1.2 2007-01-06 17:58:52 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
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
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~OutPortProvider(){};

    virtual void publishInterfaceProfile(SDOPackage::NVList& properties);

    virtual void publishInterface(SDOPackage::NVList& properties);
    
  protected:
    void setPortType(const char* port_type);
    void setDataType(const char* data_type);
    void setInterfaceType(const char* interface_type);
    void setDataFlowType(const char* dataflow_type);
    void setSubscriptionType(const char* subs_type);

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

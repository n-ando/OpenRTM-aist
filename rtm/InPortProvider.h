// -*- C++ -*-
/*!
 * @file  InPortProvider.h
 * @brief InPortProvider class
 * @date  $Date: 2007-01-21 09:49:52 $
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
 * $Id: InPortProvider.h,v 1.4 2007-01-21 09:49:52 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/01/06 17:53:42  n-ando
 * Interface and its profile publish functions (publishInterfaceProfile()
 * and publishInterface()) are added.
 *
 * Revision 1.2  2006/12/02 18:41:51  n-ando
 * A trivial fix.
 *
 * Revision 1.1  2006/11/27 09:44:40  n-ando
 * The first commitment.
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
   * @else
   * @class InPortProvider
   * @brief InPortProvider class
   * @endif
   */
  class InPortProvider
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    //    InPortProvider();

    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~InPortProvider();

    virtual void publishInterfaceProfile(SDOPackage::NVList& properties);

    virtual void publishInterface(SDOPackage::NVList& properties);
    
  protected:
    void setDataType(const char* data_type);
    void setInterfaceType(const char* interface_type);
    void setDataFlowType(const char* dataflow_type);
    void setSubscriptionType(const char* subs_type);

    SDOPackage::NVList m_properties;

  private:
    std::string m_dataType;
    std::string m_interfaceType;
    std::string m_dataflowType;
    std::string m_subscriptionType;

  };
 
};     // namespace RTC
#endif // InPortProvider_h


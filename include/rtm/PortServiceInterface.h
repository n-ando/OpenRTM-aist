// -*- C++ -*-
/*!
 * @file  PortServiceInterface.h
 * @brief PortServiceInterface interface class
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
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

#ifndef PortServiceInterface_h
#define PortServiceInterface_h

#include <vector>
#include <rtm/RTCInterface.h>

namespace RTC
{
  namespace Interface
  {
    enum PortInterfacePolarity
      {
        PROVIDED,
        REQUIRED
      };
    
    struct  PortInterfaceProfile
    {
      char* instance_name;
      char* type_name;
      PortInterfacePolarity polarity;
    };
    
    typedef std::vector<PortInterfaceProfile*> PortInterfaceProfileList;
    class PortService;
    typedef std::vector<PortService*> PortServiceList;
    
    struct  ConnectorProfile
    {
      char* name;
      UniqueIdentifier connector_id;
      PortServiceList ports;
      NVList properties;
    };
    
    typedef std::vector<ConnectorProfile*> ConnectorProfileList;
    class RTObjectInterface;
    
    struct PortProfile
    {
      char* name;
      PortInterfaceProfileList interfaces;
      PortService* port_ref;
      ConnectorProfileList connector_profiles;
      RTObjectInterface* owner;
      NVList properties;
    };
    
    typedef std::vector<PortProfile*> PortProfileList;
    
    /*!
     * @if jp
     * @class PortServiceInterface
     * @brief PortServiceInterface インターフェースクラス
     * @else
     * @class PortServiceInterface
     * @brief PortServiceInterface itnerface class
     * @endif
     */
    class PortServiceInterface
    {
    public:
      virtual ~PortServiceInterface() {};
      virtual PortProfile& get_port_profile() const = 0;
      virtual ConnectorProfileList& get_connector_profiles() const = 0;
      virtual ConnectorProfile&
      get_connector_profile(const UniqueIdentifier connector_id) const = 0;
      virtual ReturnCode_t connect(ConnectorProfile& connector_profile) = 0;
      virtual ReturnCode_t disconnect(const UniqueIdentifier connector_id) = 0;
      virtual ReturnCode_t
      notify_connect(ConnectorProfile& connector_profile) = 0;
      virtual ReturnCode_t
      notify_disconnect(const UniqueIdentifier connector_id) = 0;
      virtual ReturnCode_t disconnect_all() = 0;
    };
  };   // namespace Interface
};     // namespace RTC
#endif // PortServiceInterface_h


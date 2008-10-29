// -*- C++ -*-
/*!
 * @file  RTObjectInterface.h
 * @brief RTObjectInterface interface class
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

#ifndef RTObjectInterface_h
#define RTObjectInterface_h

#include <vector>
#include <rtm/RTCInterface.h>
#include <rtm/LightweightRTObjectInterface.h>

namespace RTC
{
  namespace Interface
  {
    class PortProfile;
    typedef std::vector<PortProfile*> PortProfileList;
    
    class PortService;
    typedef std::vector<PortService*> PortServiceList;
    
    class RTObjectInterface;
    
    struct  ComponentProfile
    {
      char* instance_name;
      char* type_name;
      char* description;
      char* version;
      char* vendor;
      char* category;
      PortProfileList port_profiles;
      RTObjectInterface* parent;
      NVList properties;
    };
    
    /*!
     * @if jp
     * @class RTObjectInterface
     * @brief RTObjectInterface インターフェースクラス
     * @else
     * @class RTObjectInterface
     * @brief RTObjectInterface interface class
     * @endif
     */
    class RTObjectInterface
      : public virtual LightweightRTObjectInterface
    //        public SDOPackage::SDO
    {
    public:
      virtual ~RTObjectInterface() {};
      virtual const ComponentProfile& get_component_profile() = 0;
      virtual PortServiceList& get_ports() = 0;
    };
  };   // namespace Interface
};     // namespace RTC
#endif // RTObjectInterface_h


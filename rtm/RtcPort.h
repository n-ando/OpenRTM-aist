// -*- C++ -*-
/*!
 * @file RTObject.cpp
 * @brief RT component base class
 * @date $Date: 2006-09-11 19:05:29 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcPort.h,v 1.1 2006-09-11 19:05:29 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RtcPort_h
#define RtcPort_h

// CORBA header include
#include "rtm/RTC.h"
#include "rtm/Util.h"

// local includes
#include "rtm/idl/RTCSkel.h"

namespace RTC
{
  class Port_impl
    : public virtual POA_RTC::Port,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    Port_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    virtual ~Port_impl(){};

    virtual PortProfile* get_port_profile();
    virtual ConnectorProfileList* get_connector_profiles();
    virtual ConnectorProfile* get_connector_profile(const char* connector_id);
    virtual ReturnCode_t connect(const ConnectorProfile& connector_profile);
    virtual ReturnCode_t disconnect(const char* connector_id);
    virtual ReturnCode_t disconnect_all();

  protected:
    CORBA::ORB_var m_varORB;
    PortableServer::POA_var m_varPOA;
    
    // Partial specialization
    template <class T, class X>
    class SeqEx
      : public SequenceEx <T, X, ACE_Thread_Mutex> {};
    
    RTC::PortProfile m_portProfile;
    SeqEx<ConnectorProfileList, ConnectorProfile> m_connectorProfiles;

    // functor for ConfigurationSet
    struct connector_name
    {
      connector_name(const char* name) :  m_name(name) {};
      bool operator()(const ConnectorProfile& c)
      {
	std::string name(c.name);
	return m_name == name;
      }
      const std::string m_name;
    };
      
  };
};

#endif // RtcPort_h

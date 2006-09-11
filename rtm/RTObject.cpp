// -*- C++ -*-
/*!
 * @file RTObject.cpp
 * @brief RT component base class
 * @date $Date: 2006-09-11 19:04:29 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTObject.cpp,v 1.1 2006-09-11 19:04:29 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#include "rtm/RTObject.h"

namespace RTC
{
  RTObject_impl::RTObject_impl(CORBA::ORB_ptr orb,
			       PortableServer::POA_ptr poa)
  {
  }

  ComponentProfile* RTObject_impl::get_component_profile()
  {
    ComponentProfile_var prof(&m_componentProfile);
    return prof._retn();
  }


  PortList* RTObject_impl::get_ports()
  {
    PortList_var ports(&m_Ports);
    return ports._retn();
  }


  ExecutionContextAdminList* RTObject_impl::get_execution_context_admins()
  {
    ExecutionContextAdminList_var exec_cxt_list(0);
    return exec_cxt_list._retn();
  }

};

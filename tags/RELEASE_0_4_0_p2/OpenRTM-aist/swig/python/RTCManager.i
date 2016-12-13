// -*- C++ -*-
/*!
 * @file RTCManager.i
 * @brief swig interface file for RTCManager
 * @date $Date: 2005-05-12 09:06:19 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTCManager.i,v 1.1.1.1 2005-05-12 09:06:19 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

%module RTCManager


%{
#include "rtm/idl/RTCManagerSkel.h"
%}

//%import "RTComponent.i"

namespace RTM
{
  class RTCManager
  {
  public:
    RTM::RtmRes load(const char* pathname, const char* initfunc);
    RTM::RtmRes unload(const char* pathname);
    //    RTM::RTComponent_ptr create_component(const char* comp_name,
    //					  CORBA::String_out instance_name);
    RTM::RtmRes delete_component(const char* instance_name,
								 const char* category_name);
    RTM::RTCFactoryList* factory_list();
    RTM::RTCBaseList* component_list();
    //    RTM::RtmRes command(const char* cmd, CORBA::String_out ret);

  protected:
    RTCManager();
    virtual ~RTCManager();
  };
};

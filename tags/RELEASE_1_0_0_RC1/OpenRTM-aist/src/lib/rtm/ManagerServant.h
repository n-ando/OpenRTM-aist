// -*- C++ -*-
/*!
 * @file ManagerServant.h
 * @brief RTComponent manager servant implementation class
 * @date $Date: 2007-12-31 03:08:04 $
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

#ifndef RTM_MANAGERSERVANT_H
#define RTM_MANAGERSERVANT_H

#include <iostream>
#include <rtm/idl/ManagerSkel.h>
#include <rtm/Manager.h>

namespace RTM
{
  class ManagerServant
    : public virtual POA_RTM::Manager,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    // standard constructor
    ManagerServant();
    virtual ~ManagerServant(void);
    
    RTC::ReturnCode_t load_module(const char* pathname, const char* initfunc);
    RTC::ReturnCode_t unload_module(const char* pathname);
    RTM::ModuleProfileList* get_loadable_modules();
    RTM::ModuleProfileList* get_loaded_modules();
    RTM::ModuleProfileList* get_factory_profiles();
    RTC::RTObject_ptr create_component(const char* module_name);
    RTC::ReturnCode_t delete_component(const char* instance_name);
    RTC::RTCList* get_components();
    RTC::ComponentProfileList* get_component_profiles();
    RTM::ManagerProfile* get_profile();
    RTM::NVList* get_configuration();
    RTC::ReturnCode_t set_configuration(const char* name, const char* value);
    RTM::Manager_ptr get_owner();
    RTM::Manager_ptr set_owner(RTM::Manager_ptr mgr);
    RTM::Manager_ptr get_child();
    RTM::Manager_ptr set_child(RTM::Manager_ptr mgr);
    RTC::ReturnCode_t fork();
    RTC::ReturnCode_t shutdown();
    RTC::ReturnCode_t restart();
    CORBA::Object_ptr get_service(const char* name);
    RTM::Manager_ptr getObjRef() const;

  private:
    ::RTC::Manager& m_mgr;
    ::RTM::Manager_ptr m_objref;
  };
}; // namespace RTM
#endif // RTM_MANAGERSERVANT_H

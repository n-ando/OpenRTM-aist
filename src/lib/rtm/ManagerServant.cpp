// -*- C++ -*-
/*!
 * @file ManagerServant.cpp
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
#include <rtm/Manager.h>
#include <rtm/ManagerServant.h>
#include <rtm/NVUtil.h>
#include <rtm/RTObject.h>

namespace RTM
{
  //
  // Example implementational code for IDL interface RTM::Manager
  //
  ManagerServant::ManagerServant()
    : m_mgr(::RTC::Manager::instance())
  {
    m_objref = this->_this();
  }
  ManagerServant::~ManagerServant()
  {
  }

  RTC::ReturnCode_t
  ManagerServant::load_module(const char* pathname, const char* initfunc)
  {
    m_mgr.load(pathname, initfunc);
    return ::RTC::RTC_OK;
  }
  
  RTC::ReturnCode_t ManagerServant::unload_module(const char* pathname)
  {
    m_mgr.unload(pathname);
    return ::RTC::RTC_OK;
  }
  
  RTM::ModuleProfileList* ManagerServant::get_loadable_modules()
  {
    ::RTM::ModuleProfileList* cprof = new ::RTM::ModuleProfileList();
    std::vector<coil::Properties> prof(m_mgr.getLoadableModules());

    cprof->length((CORBA::Long)prof.size());
    for (int i(0), len(prof.size()); i < len; ++i)
      {
        NVUtil::copyFromProperties((*cprof)[(CORBA::Long)i].properties,
                                   prof[i]);
      }
    return cprof;
  }
  
  RTM::ModuleProfileList* ManagerServant::get_loaded_modules()
  {
    ::RTM::ModuleProfileList* cprof = new RTM::ModuleProfileList();
    std::vector<coil::Properties> prof(m_mgr.getLoadedModules());
    
    cprof->length(prof.size());
    for (int i(0), len(prof.size()); i < len; ++i)
      {
        NVUtil::copyFromProperties((*cprof)[(CORBA::Long)i].properties,
                                   prof[i]);
      }
    return cprof;
  }
  
  RTM::ModuleProfileList* ManagerServant::get_factory_profiles()
  {
    ::RTM::ModuleProfileList* cprof = new RTM::ModuleProfileList();
    std::vector<coil::Properties> prof(m_mgr.getFactoryProfiles());
    
    cprof->length(prof.size());
    for (int i(0), len(prof.size()); i < len; ++i)
      {
        NVUtil::copyFromProperties((*cprof)[(CORBA::Long)i].properties,
                                   prof[i]);
      }
    return cprof;
  }

  RTC::RTObject_ptr ManagerServant::create_component(const char* module_name)
  {
    RTC::RTObject_impl* rtc = m_mgr.createComponent(module_name);
    if (rtc == NULL)
      {
        return RTC::RTObject::_nil();
      }
    return rtc->getObjRef();
  }
  
  RTC::ReturnCode_t ManagerServant::delete_component(const char* instance_name)
  {
    m_mgr.deleteComponent(instance_name);
    return ::RTC::RTC_OK;
  }
  
  RTC::RTCList* ManagerServant::get_components()
  {
    std::vector<RTC::RTObject_impl*> rtcs = m_mgr.getComponents();
    ::RTC::RTCList* crtcs = new ::RTC::RTCList();
    crtcs->length((CORBA::Long)rtcs.size());
    for (int i(0), len(rtcs.size()); i < len; ++i)
      {
        (*crtcs)[(CORBA::Long)i] = RTC::RTObject::_duplicate(rtcs[i]->getObjRef());
      }
    return crtcs;
  }
  
  RTC::ComponentProfileList* ManagerServant::get_component_profiles()
  {
    ::RTC::ComponentProfileList* cprofs = new ::RTC::ComponentProfileList();
    std::vector<RTC::RTObject_impl*> rtcs = m_mgr.getComponents();
    cprofs->length(rtcs.size());
    for (int i(0), len(rtcs.size()); i < len; ++i)
      {
        ::RTC::ComponentProfile_var prof = rtcs[i]->get_component_profile();
        (*cprofs)[(CORBA::Long)i] = prof;
      }
    return cprofs;
  }
  
  RTM::ManagerProfile* ManagerServant::get_profile()
  {
    RTM::ManagerProfile* prof = new RTM::ManagerProfile();
    NVUtil::copyFromProperties(prof->properties,
                               m_mgr.getConfig().getNode("manager"));
    return prof;
  }
  
  RTM::NVList* ManagerServant::get_configuration()
  {
    ::RTC::NVList* nvlist = new ::RTC::NVList();
    NVUtil::copyFromProperties(*nvlist, m_mgr.getConfig());
    return nvlist;
  }
  
  RTC::ReturnCode_t
  ManagerServant::set_configuration(const char* name, const char* value)
  {
    m_mgr.getConfig().setProperty(name, value);
    return ::RTC::RTC_OK;
  }
  
  RTM::Manager_ptr ManagerServant::get_owner()
  {
    return ::RTM::Manager::_nil();
  }
  
  RTM::Manager_ptr ManagerServant::set_owner(RTM::Manager_ptr mgr)
  {
    return ::RTM::Manager::_nil();
  }
  
  RTM::Manager_ptr ManagerServant::get_child()
  {
    return ::RTM::Manager::_nil();
  }
  
  RTM::Manager_ptr ManagerServant::set_child(RTM::Manager_ptr mgr)
  {
    return ::RTM::Manager::_nil();
  }
  
  RTC::ReturnCode_t ManagerServant::fork()
  {
    //    m_mgr.fork();
    return ::RTC::RTC_OK;
  }
  
  RTC::ReturnCode_t ManagerServant::shutdown()
  {
    m_mgr.terminate();
    return ::RTC::RTC_OK;
  }
  
  RTC::ReturnCode_t ManagerServant::restart()
  {
    //    m_mgr.restart();
    return ::RTC::RTC_OK;
  }
  
  CORBA::Object_ptr ManagerServant::get_service(const char* name)
  {
    return ::CORBA::Object::_nil();
  }
  
  RTM::Manager_ptr ManagerServant::getObjRef() const
  {
    return m_objref;
  }
};

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
#include <coil/Process.h>
#include <rtm/Manager.h>
#include <rtm/ManagerServant.h>
#include <rtm/NVUtil.h>
#include <rtm/RTObject.h>
#include <rtm/CORBA_SeqUtil.h>

namespace RTM
{
  //
  // Example implementational code for IDL interface RTM::Manager
  //
  ManagerServant::ManagerServant()
    : m_mgr(::RTC::Manager::instance())
  {
    rtclog.setName("ManagerServant");
    coil::Properties config(m_mgr.getConfig());    
    if (coil::toBool(config["manager.is_master"], "YES", "NO", true))
      {
        // this is master manager
        CORBA::Object_var obj;
        obj = m_mgr.getORB()->resolve_initial_references("omniINSPOA");
        PortableServer::POA_ptr poa = PortableServer::POA::_narrow(obj);
        poa->the_POAManager()->activate();
        PortableServer::ObjectId_var id; 
        id = PortableServer::string_to_ObjectId(config["manager.name"].c_str());
        poa->activate_object_with_id(id.in(), this);
        CORBA::Object_var mgrobj = poa->id_to_reference(id);
        m_objref = ::RTM::Manager::_narrow(mgrobj);
      }
    else
      {
        // this is slave manager
        try
          {
            std::string mgrloc("corbaloc:iiop:");
            mgrloc += config["corba.master_manager"]
              + "/" + config["manager.name"];
            
            CORBA::Object_var mobj;
            mobj = m_mgr.getORB()->string_to_object(mgrloc.c_str());
            RTM::Manager_var owner = ::RTM::Manager::_narrow(mobj);
            add_master_manager(owner);
            m_objref = this->_this();
            owner->add_slave_manager(m_objref.in());
          }
        catch(CORBA::SystemException& e)
          {
            RTC_DEBUG(("CORBA SystemException cought (CORBA::%s)",
                       e._name()));
          }
        catch (...)
          {
            RTC_DEBUG(("Unknown exception cought."));
          }
      }
  }
  
  ManagerServant::~ManagerServant()
  {
  }
  
  /*!
   * @if jp
   * @brief モジュールをロードする
   * @else
   * @brief Loading a module
   * @endig
   */
  RTC::ReturnCode_t
  ManagerServant::load_module(const char* pathname, const char* initfunc)
  {
    RTC_TRACE(("ManagerServant::load_module(%s, %s)", pathname, initfunc));
    
    m_mgr.load(pathname, initfunc);
    
    return ::RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief モジュールをアンロードする
   * @else
   * @brief Unloading a module
   * @endig
   */  
  RTC::ReturnCode_t ManagerServant::unload_module(const char* pathname)
  {
    RTC_TRACE(("ManagerServant::unload_module(%s)", pathname));
    
    m_mgr.unload(pathname);
    
    return ::RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief ロード可能なモジュールのプロファイルを取得する
   * @else
   * @brief Getting loadable module profiles
   * @endig
   */
  RTM::ModuleProfileList* ManagerServant::get_loadable_modules()
  {
    RTC_TRACE(("get_loadable_modules()"));
    
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
  
  /*!
   * @if jp
   * @brief ロード済みのモジュールのプロファイルを取得する
   * @else
   * @brief Getting loaded module profiles
   * @endig
   */
  RTM::ModuleProfileList* ManagerServant::get_loaded_modules()
  {
    RTC_TRACE(("get_loaded_modules()"));
    
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
  
  /*!
   * @if jp
   * @brief コンポーネントファクトリのプロファイルを取得する
   * @else
   * @brief Getting component factory profiles
   * @endig
   */
  RTM::ModuleProfileList* ManagerServant::get_factory_profiles()
  {
    RTC_TRACE(("get_factory_profiles()"));
    
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
  
  /*!
   * @if jp
   * @brief コンポーネントを生成する
   * @else
   * @brief Creating an RT-Component
   * @endig
   */
  RTC::RTObject_ptr ManagerServant::create_component(const char* module_name)
  {
    RTC_TRACE(("create_component(%s)", module_name));
    
    RTC::RTObject_impl* rtc = m_mgr.createComponent(module_name);
    if (rtc == NULL)
      {
        return RTC::RTObject::_nil();
      }
    return rtc->getObjRef();
  }
  
  /*!
   * @if jp
   * @brief コンポーネントを削除する
   * @else
   * @brief Deleting an RT-Component
   * @endig
   */
  RTC::ReturnCode_t ManagerServant::delete_component(const char* instance_name)
  {
    RTC_TRACE(("delete_component(%s)", instance_name));
    
    m_mgr.deleteComponent(instance_name);
    return ::RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief 起動中のコンポーネントのリストを取得する
   * @else
   * @brief Getting RT-Component list running on this manager
   * @endig
   */
  RTC::RTCList* ManagerServant::get_components()
  {
    RTC_TRACE(("get_components()"));
    
    std::vector<RTC::RTObject_impl*> rtcs = m_mgr.getComponents();
    ::RTC::RTCList* crtcs = new ::RTC::RTCList();
    crtcs->length((CORBA::Long)rtcs.size());
    for (int i(0), len(rtcs.size()); i < len; ++i)
      {
        (*crtcs)[(CORBA::Long)i] = RTC::RTObject::_duplicate(rtcs[i]->getObjRef());
      }
    return crtcs;
  }
  
  /*!
   * @if jp
   * @brief 起動中のコンポーネントプロファイルのリストを取得する
   * @else
   * @brief Getting RT-Component's profile list running on this manager
   * @endig
   */  
  RTC::ComponentProfileList* ManagerServant::get_component_profiles()
  {
    RTC_TRACE(("get_component_profiles()"));
    
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
  
  // manager 基本
  /*!
   * @if jp
   * @brief マネージャのプロファイルを取得する
   * @else
   * @brief Getting this manager's profile.
   * @endig
   */
  RTM::ManagerProfile* ManagerServant::get_profile()
  {
    RTM::ManagerProfile* prof = new RTM::ManagerProfile();
    NVUtil::copyFromProperties(prof->properties,
                               m_mgr.getConfig().getNode("manager"));
    return prof;
  }
  
  /*!
   * @if jp
   * @brief マネージャのコンフィギュレーションを取得する
   * @else
   * @brief Getting this manager's configuration.
   * @endig
   */
  RTM::NVList* ManagerServant::get_configuration()
  {
    ::RTC::NVList* nvlist = new ::RTC::NVList();
    NVUtil::copyFromProperties(*nvlist, m_mgr.getConfig());
    return nvlist;
  }
  
  /*!
   * @if jp
   * @brief マネージャのコンフィギュレーションを設定する
   * @else
   * @brief Setting manager's configuration
   * @endig
   */
  RTC::ReturnCode_t
  ManagerServant::set_configuration(const char* name, const char* value)
  {
    m_mgr.getConfig().setProperty(name, value);
    return ::RTC::RTC_OK;
  }
  /*!
   * @if jp
   * @brief マネージャがマスターかどうか
   * @else
   * @brief Whether this manager is master or not
   * @endig
   */
  CORBA::Boolean ManagerServant::is_master()
  {
    return m_isMaster;
  }
  
  /*!
   * @if jp
   * @brief マスターマネージャの取得
   * @else
   * @brief Getting master managers
   * @endig
   */
  RTM::ManagerList* ManagerServant::get_master_managers()
  {
    RTC_TRACE(("get_master_managers()"));
    
    return new ManagerList(m_masters);
  }
  
  /*!
   * @if jp
   * @brief マスターマネージャの追加
   * @else
   * @brief Getting a master manager
   * @endig
   */
  RTC::ReturnCode_t ManagerServant::add_master_manager(RTM::Manager_ptr mgr)
  {
    RTC_TRACE(("add_master_manager()"));
    
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_masters, is_equiv(mgr));
    
    if (!(index < 0))
      {
        return RTC::BAD_PARAMETER;
      }
    
    CORBA_SeqUtil::push_back(m_masters, RTM::Manager::_duplicate(mgr));
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief マスターマネージャの削除
   * @else
   * @brief Removing a master manager
   * @endig
   */
  RTC::ReturnCode_t
  ManagerServant::remove_master_manager(RTM::Manager_ptr mgr)
  {
    RTC_TRACE(("remove_master_manager()"));
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_masters, is_equiv(mgr));
    
    if (index < 0)
      {
        return RTC::BAD_PARAMETER;
      }
    
    CORBA_SeqUtil::erase(m_masters, index);
    return RTC::RTC_OK;
  }
  
  /*!
   * @if jp
   * @brief スレーブマネージャの取得
   * @else
   * @brief Getting slave managers
   * @endig
   */
  ManagerList* ManagerServant::get_slave_managers()
  {
    RTC_TRACE(("get_slave_managers()"));
    
    return new ManagerList(m_slaves);
  }
  /*!
   * @if jp
   * @brief スレーブマネージャの追加
   * @else
   * @brief Getting a slave manager
   * @endig
   */
  RTC::ReturnCode_t ManagerServant::add_slave_manager(RTM::Manager_ptr mgr)
  {
    RTC_TRACE(("add_slave_manager()"));
    
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_slaves, is_equiv(mgr));
    
    if (!(index < 0))
      {
        return RTC::BAD_PARAMETER;
      }
    
    CORBA_SeqUtil::push_back(m_slaves, RTM::Manager::_duplicate(mgr));
    return RTC::RTC_OK;;
  }
  
  /*!
   * @if jp
   * @brief スレーブマネージャの削除
   * @else
   * @brief Removing a slave manager
   * @endig
   */
  RTC::ReturnCode_t ManagerServant::remove_slave_manager(RTM::Manager_ptr mgr)
  {
    RTC_TRACE(("remove_slave_manager()"));
    CORBA::Long index;
    index = CORBA_SeqUtil::find(m_slaves, is_equiv(mgr));
    
    if (index < 0)
      {
        return RTC::BAD_PARAMETER;
      }
    
    CORBA_SeqUtil::erase(m_slaves, index);
    return RTC::RTC_OK;
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

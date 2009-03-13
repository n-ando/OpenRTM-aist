// -*- C++ -*-
/*!
 * @file PeriodicECSharedComposite.cpp
 * @brief DataFlowParticipant RT-Component base class
 * @date $Date: 2007-04-13 15:44:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PeriodicECSharedComposite.cpp 1034 2008-11-10 10:32:16Z kojima $
 *
 */

#include <rtm/RTC.h>
#include <rtm/PeriodicECSharedComposite.h>
#include <rtm/Manager.h>
#include <string>
#include <iostream>


static const char* periodicecsharedcomposite_spec[] =
  {
    "implementation_id", "PeriodicECSharedComposite",
    "type_name",         "PeriodicECSharedComposite",
    "description",       "PeriodicECSharedComposite",
    "version",           "1.0",
    "vendor",            "jp.go.aist",
    "category",          "composite.PeriodicECShared",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    "exported_ports",    "",
    "conf.default.members", "",
    "conf.default.exported_ports", "",
    ""
  };

namespace SDOPackage
{
  PeriodicECOrganization::PeriodicECOrganization(::RTC::RTObject_impl* rtobj)
    : Organization_impl(rtobj->getObjRef()),
      rtclog("organization"),
      m_rtobj(rtobj),
      m_ec(::RTC::ExecutionContext::_nil())
  {
  }

  PeriodicECOrganization::~PeriodicECOrganization()
  {
    ;
  }

  /*!
   * @if jp
   * @brief [CORBA interface] Organizationメンバーを追加する
   * @else
   * @brief [CORBA interface] Add Organization member
   * @endif
   */
  CORBA::Boolean PeriodicECOrganization::add_members(const SDOList& sdo_list)
    throw (CORBA::SystemException,
           InvalidParameter, NotAvailable, InternalError)
  {
    RTC_DEBUG(("add_members()"));
    updateExportedPortsList();
    for (::CORBA::ULong i(0), len(sdo_list.length()); i < len; ++i)
      {
        const SDO_ptr sdo  = sdo_list[i];
        //        ::OpenRTM::DataFlowComponent_ptr dfc;
        //        if (!sdoToDFC(sdo, dfc)) continue;
        ::RTC::RTObject_var dfc;
        dfc = ::RTC::RTObject::_narrow(sdo);
        if (CORBA::is_nil(dfc)) { continue; }

        //        Member member(::OpenRTM::DataFlowComponent::_duplicate(dfc));
        Member member(dfc);
        stopOwnedEC(member);
        addOrganizationToTarget(member);
        addParticipantToEC(member);
        addPort(member, m_expPorts);
        m_rtcMembers.push_back(member);
      }

    CORBA::Boolean result;
    result = ::SDOPackage::Organization_impl::add_members(sdo_list);

    return result;
  }

  /*!
   * @if jp
   * @brief [CORBA interface] Organizationメンバーをセットする
   * @else
   * @brief [CORBA interface] Set Organization member
   * @endif
   */
  CORBA::Boolean PeriodicECOrganization::set_members(const SDOList& sdo_list)
    throw (CORBA::SystemException,
           InvalidParameter, NotAvailable, InternalError)
  {

    RTC_DEBUG(("set_members()"));
    removeAllMembers();
    updateExportedPortsList();

    for (::CORBA::ULong i(0), len(sdo_list.length()); i < len; ++i)
      {
        
        const SDO_var sdo  = sdo_list[i];
        ::RTC::RTObject_var dfc;
        dfc = ::RTC::RTObject::_narrow(sdo);
        if (CORBA::is_nil(dfc)) { continue; }
        //        if (!sdoToDFC(sdo, dfc)) continue;
        //        CORBA::release(sdo);
        //        CORBA::release(dfc);
        //        Member member(::OpenRTM::DataFlowComponent::_duplicate(dfc));
        //        Member member(dfc);
        //        RTC::ComponentProfile_var p;
        //        p = dfc->get_component_profile();
        //        delete p;
//        stopOwnedEC(member);
//        addOrganizationToTarget(member);
//        addParticipantToEC(member);
//        addPort(member, m_expPorts);
        
        //        m_rtcMembers.push_back(member);
      }

    CORBA::Boolean result;
    result = ::SDOPackage::Organization_impl::set_members(sdo_list);

    return result;
  }

  /*!
   * @if jp
   * @brief [CORBA interface] Organizationメンバーを削除する
   * @else
   * @brief [CORBA interface] Remove a member of Organization
   * @endif
   */
  CORBA::Boolean PeriodicECOrganization::remove_member(const char* id)
    throw (CORBA::SystemException,
           InvalidParameter, NotAvailable, InternalError)
  {
    RTC_DEBUG(("remove_member(id = %s)", id));
    for (MemIt it(m_rtcMembers.begin()), it_end(m_rtcMembers.end());
         it != it_end; ++it)
      {
        Member& member(*it);
        if (strncmp(id, member.profile_->instance_name, strlen(id))) continue;
        
        removePort(member, m_expPorts);
        m_rtobj->getProperties()["conf.default.exported_ports"] =
          ::coil::flatten(m_expPorts);

        removeParticipantFromEC(member);
        removeOrganizationFromTarget(member);
        startOwnedEC(member);
        it = m_rtcMembers.erase(it);
        --it;
      }

    CORBA::Boolean result;
    result = ::SDOPackage::Organization_impl::remove_member(id);
    return result;
  }

  
  void PeriodicECOrganization::removeAllMembers()
  {
    RTC_TRACE(("removeAllMembers()"));
    updateExportedPortsList();
    MemIt it(m_rtcMembers.begin());
    MemIt it_end(m_rtcMembers.end());
    while (it != it_end)
      {
        Member& member(*it);
        removePort(member, m_expPorts);
        removeParticipantFromEC(member);
        removeOrganizationFromTarget(member);
        startOwnedEC(member);
        ::SDOPackage::Organization_impl::remove_member(member.profile_->instance_name); 
        ++it;
     }
    m_rtcMembers.clear();
    m_expPorts.clear();
  }

  /*!
   * @if jp
   * @brief SDOからDFCへの変換
   * @else
   * @brief Conversion from SDO to DFC
   * @endif
   */
  bool
  PeriodicECOrganization::sdoToDFC(const SDO_ptr sdo,
                                   ::OpenRTM::DataFlowComponent_var& dfc)
  {
    if (::CORBA::is_nil(sdo)) return false;
    
    // narrowing: SDO -> RTC (DataFlowComponent)
    dfc = ::OpenRTM::DataFlowComponent::_narrow(sdo);
    if (::CORBA::is_nil(dfc)) return false;
    return true;
  }
  
  /*!
   * @if jp
   * @brief Owned ExecutionContext を停止させる
   * @else
   * @brief Stop Owned ExecutionContexts
   * @endif
   */
  void PeriodicECOrganization::stopOwnedEC(Member& member)
  {
    // stop target RTC's ExecutionContext
    ::RTC::ExecutionContextList_var ecs;
    ecs = new ::RTC::ExecutionContextList(member.eclist_);
    for (::CORBA::ULong i(0), len(ecs->length()); i < len; ++i)
      {
        ecs[i]->stop();
      }
    return;
  }

  /*!
   * @if jp
   * @brief Owned ExecutionContext を起動する
   * @else
   * @brief Start Owned ExecutionContexts
   * @endif
   */
  void PeriodicECOrganization::startOwnedEC(Member& member)
  {
    // start target RTC's ExecutionContext
    ::RTC::ExecutionContextList_var ecs;
    ecs = new ::RTC::ExecutionContextList(member.eclist_);
    for (::CORBA::ULong i(0), len(ecs->length()); i < len; ++i)
      {
        ecs[i]->start();
      }
    return;
  }

  /*!
   * @if jp
   * @brief DFC に Organization オブジェクトを与える
   * @else
   * @brief Set Organization object to target DFC 
   * @endif
   */
  void PeriodicECOrganization::addOrganizationToTarget(Member& member)
  {
    // get given RTC's configuration object
    Configuration_ptr conf(member.config_);
    if (::CORBA::is_nil(conf)) return;
    
    // set organization to target RTC's conf
    conf->add_organization(::SDOPackage::Organization::_duplicate(m_objref));
  }

  /*!
   * @if jp
   * @brief Organization オブジェクトを DFCから削除する
   * @else
   * @brief Remove Organization object from a target DFC 
   * @endif
   */
  void PeriodicECOrganization::removeOrganizationFromTarget(Member& member)
  {
    // get given RTC's configuration object
    Configuration_ptr conf(member.config_);
    if (::CORBA::is_nil(conf)) return;
    
    // set organization to target RTC's conf
    conf->remove_organization(CORBA::string_dup(m_pId));
  }

  /*!
   * @if jp
   * @brief Composite の ExecutionContext を DFC にセットする
   * @else
   * @brief Set CompositeRTC's ExecutionContext to the given DFC
   * @endif
   */
  void PeriodicECOrganization::addParticipantToEC(Member& member)
  {
    if (::CORBA::is_nil(m_ec))
      {
        ::RTC::ExecutionContextList_var ecs = m_rtobj->get_owned_contexts();
        if (ecs->length() > 0)
          {
            m_ec = ::RTC::ExecutionContext::_duplicate(ecs[0]);
          }
        else
          {
            return;
          }
      }
    // set ec to target RTC
    m_ec->add_component(RTC::RTObject::_duplicate(member.rtobj_));
  }

  /*!
   * @if jp
   * @brief Composite の ExecutionContext から DFC を削除する
   * @else
   * @brief Remove participant DFC from CompositeRTC's ExecutionContext
   * @endif
   */
  void PeriodicECOrganization::removeParticipantFromEC(Member& member)
  { 
    if (::CORBA::is_nil(m_ec))
      {
        ::RTC::ExecutionContextList_var ecs = m_rtobj->get_owned_contexts();
        if (ecs->length() > 0)
          {
            m_ec = ::RTC::ExecutionContext::_duplicate(ecs[0]);
          }
        else
          {
            return;
          }
      }
    m_ec->remove_component(RTC::RTObject::_duplicate(member.rtobj_));
  }

  /*!
   * @if jp
   * @brief ポートを委譲する
   * @else
   * @brief Delegate given RTC's ports to the Composite
   * @endif
   */
  void
  PeriodicECOrganization::addPort(Member& member,
                                  PortList& portlist)
  {
    RTC_TRACE(("addPort(%s)", ::coil::flatten(portlist).c_str()));
    if (portlist.size() == 0) { return; }

    std::string comp_name(member.profile_->instance_name);
    ::RTC::PortProfileList& plist(member.profile_->port_profiles);
    
    // port delegation
    for (::CORBA::ULong i(0), len(plist.length()); i < len; ++i)
      {
        // port name -> comp_name.port_name
        std::string port_name(comp_name);
        port_name += "."; port_name += plist[i].name;

        RTC_DEBUG(("port_name: %s is in %s?",
                   port_name.c_str(),
                   ::coil::flatten(portlist).c_str()));

        std::vector<std::string>::iterator pos = 
          std::find(portlist.begin(), portlist.end(), port_name);
        if (pos == portlist.end()) 
          {
            RTC_DEBUG(("Not found: %s is in %s?",
                       port_name.c_str(),
                       ::coil::flatten(portlist).c_str()));
            continue;
          }

        RTC_DEBUG(("Found: %s is in %s",
                   port_name.c_str(),
                   ::coil::flatten(portlist).c_str()));

        m_rtobj->registerPort(::RTC::PortService::_duplicate(plist[i].port_ref));

        RTC_DEBUG(("Port %s was delegated.", port_name.c_str()));

      }
  }

  /*!
   * @if jp
   * @brief 委譲していたポートを削除する
   * @else
   * @brief Remove delegated participatns's ports from the composite
   * @endif
   */
  void PeriodicECOrganization::removePort(Member& member,
                                          PortList& portlist)
  {
    RTC_TRACE(("removePort(%s)", coil::flatten(portlist).c_str()));
    if (portlist.size() == 0) { return; }

    std::string comp_name(member.profile_->instance_name);
    ::RTC::PortProfileList& plist(member.profile_->port_profiles);

    // port delegation
    for (::CORBA::ULong i(0), len(plist.length()); i < len; ++i)
      {
        // port name -> comp_name.port_name
        std::string port_name(comp_name);
        port_name += "."; port_name += plist[i].name;

        RTC_DEBUG(("port_name: %s is in %s?",
                   port_name.c_str(),
                   ::coil::flatten(portlist).c_str()));

        std::vector<std::string>::iterator pos = 
          std::find(portlist.begin(), portlist.end(), port_name);
        if (pos == portlist.end()) 
          {
            RTC_DEBUG(("Not found: %s is in %s?",
                       port_name.c_str(),
                       ::coil::flatten(portlist).c_str()));
            continue;
          }

        RTC_DEBUG(("Found: %s is in %s",
                   port_name.c_str(),
                   ::coil::flatten(portlist).c_str()));

        m_rtobj->deletePort(::RTC::PortService::_duplicate(plist[i].port_ref));
        portlist.erase(pos);
        
        RTC_DEBUG(("Port %s was deleted.", port_name.c_str()));
      }
   }

  void PeriodicECOrganization::updateExportedPortsList()
  {
    std::string plist(m_rtobj->getProperties()["conf.default.exported_ports"]);
    m_expPorts = ::coil::split(plist, ",");
  }


  void PeriodicECOrganization::updateDelegatedPorts()
  {
    std::vector<std::string>& oldPorts(m_expPorts);
    std::vector<std::string>
      newPorts(coil::split(m_rtobj->getProperties()["conf.default.exported_ports"], ","));

    std::vector<std::string> removedPorts; // oldPorts - interPorts
    std::vector<std::string> createdPorts;   // newPorts - interPorts

    set_difference(oldPorts.begin(), oldPorts.end(),
    		   newPorts.begin(), newPorts.end(),
    		   std::back_inserter(removedPorts));
    set_difference(newPorts.begin(), newPorts.end(),
    		   oldPorts.begin(), oldPorts.end(),
    		   std::back_inserter(createdPorts));

    RTC_VERBOSE(("old    ports: %s", ::coil::flatten(oldPorts).c_str()));
    RTC_VERBOSE(("new    ports: %s", ::coil::flatten(newPorts).c_str()));
    RTC_VERBOSE(("remove ports: %s", ::coil::flatten(removedPorts).c_str()));
    RTC_VERBOSE(("add    ports: %s", ::coil::flatten(createdPorts).c_str()));

    for (int i(0), len(m_rtcMembers.size()); i < len; ++i)
      {
        removePort(m_rtcMembers[i], removedPorts);
        addPort(m_rtcMembers[i], createdPorts);
      }

    m_expPorts = newPorts;
  }

};



bool stringToStrVec(std::vector<std::string>& v, const char* is)
{
  std::string s(is);
  v = coil::split(s ,",");
  return true;
}

namespace RTC
{
  class setCallback
    : public OnSetConfigurationSetCallback
  {
  public:
    setCallback(::SDOPackage::PeriodicECOrganization* org) : m_org(org) {}
    virtual ~setCallback(){};
    virtual void operator()(const coil::Properties& config_set)
    {
      m_org->updateDelegatedPorts();
    }
  private:
    ::SDOPackage::PeriodicECOrganization* m_org;
  };


  class addCallback
    : public OnAddConfigurationAddCallback
  {
  public:
    addCallback(::SDOPackage::PeriodicECOrganization* org) : m_org(org) {}
    virtual ~addCallback(){};
    virtual void operator()(const coil::Properties& config_set)
    {
      m_org->updateDelegatedPorts();
    }
  private:
    ::SDOPackage::PeriodicECOrganization* m_org;
  };

  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  PeriodicECSharedComposite::PeriodicECSharedComposite(Manager* manager)
    : RTObject_impl(manager)
  {
    m_ref = OpenRTM::DataFlowComponent::_duplicate(this->_this());
    m_objref = RTC::RTObject::_duplicate(m_ref);
    m_org = new SDOPackage::PeriodicECOrganization(this);
    ::CORBA_SeqUtil::push_back(m_sdoOwnedOrganizations,
                               ::SDOPackage::Organization::_duplicate(m_org->getObjRef()));
    bindParameter("members", m_members, "", stringToStrVec);

    m_configsets.setOnSetConfigurationSet(new setCallback(m_org));
    m_configsets.setOnAddConfigurationSet(new addCallback(m_org));

  }


  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  PeriodicECSharedComposite::~PeriodicECSharedComposite()
  {
    RTC_TRACE(("~PeriodicECSharedComposite()"));
  }


  /*!
   * @if jp
   * @brief 初期化
   * @else
   * @brief Initialization
   * @endif
   */
  ReturnCode_t PeriodicECSharedComposite::onInitialize()
  {
    RTC_TRACE(("onInitialize()"));
    ::RTC::Manager& mgr(::RTC::Manager::instance());

    std::vector<RTObject_impl*> comps = mgr.getComponents();
    for (int i(0), len(comps.size()); i < len; ++i)
      {
        std::cout << comps[i]->getInstanceName() << std::endl;
      }

    ::SDOPackage::SDOList sdos;
    for (int i(0), len(m_members.size()); i < len; ++i)
      {
        RTObject_impl* rtc = mgr.getComponent(m_members[i].c_str());
        if (rtc == NULL) {
          continue;
        }

        ::SDOPackage::SDO_ptr sdo;
        sdo = ::SDOPackage::SDO::_duplicate(rtc->getObjRef());
        if (::CORBA::is_nil(sdo)) continue;

        ::CORBA_SeqUtil::push_back(sdos, sdo);
      }
    
    try
      {
        m_org->set_members(sdos);
      }
    catch (...)
      {
      }
    return ::RTC::RTC_OK;
  }

  /*!
   * @if jp
   * @brief 初期化
   * @else
   * @brief Initialization
   * @endif
   */
  ReturnCode_t PeriodicECSharedComposite::onActivated(RTC::UniqueId exec_handle)
  {
    RTC_TRACE(("onActivated(%d)", exec_handle));
    ::RTC::ExecutionContextList_var ecs = get_owned_contexts();
    ::SDOPackage::SDOList_var sdos = m_org->get_members();

    for (::CORBA::ULong i(0), len(sdos->length()); i < len; ++i)
      {
        ::RTC::RTObject_var rtc = ::RTC::RTObject::_narrow(sdos[i]);
        ecs[0]->activate_component(rtc);
      }
    RTC_DEBUG(("%d member RTC%s activated.", sdos->length(),
               sdos->length() == 1 ? " was" : "s were"));
    return ::RTC::RTC_OK;
  }

  /*!
   * @if jp
   * @brief 初期化
   * @else
   * @brief Initialization
   * @endif
   */
  ReturnCode_t PeriodicECSharedComposite::onDeactivated(RTC::UniqueId exec_handle)
  {
    RTC_TRACE(("onDeactivated(%d)", exec_handle));
    ::RTC::ExecutionContextList_var ecs = get_owned_contexts();
    ::SDOPackage::SDOList_var sdos = m_org->get_members();

    for (::CORBA::ULong i(0), len(sdos->length()); i < len; ++i)
      {
        ::RTC::RTObject_var rtc = ::RTC::RTObject::_narrow(sdos[i]);
        ecs[0]->deactivate_component(rtc);
      }
    return ::RTC::RTC_OK;
  }

  /*!
   * @if jp
   * @brief 初期化
   * @else
   * @brief Initialization
   * @endif
   */  ReturnCode_t PeriodicECSharedComposite::onReset(RTC::UniqueId exec_handle)
  {
    RTC_TRACE(("onReset(%d)", exec_handle));
    ::RTC::ExecutionContextList_var ecs = get_owned_contexts();
    ::SDOPackage::SDOList_var sdos = m_org->get_members();

    for (::CORBA::ULong i(0), len(sdos->length()); i < len; ++i)
      {
        ::RTC::RTObject_var rtc = ::RTC::RTObject::_narrow(sdos[i]);
        ecs[0]->reset_component(rtc);
      }
    return ::RTC::RTC_OK;
  }

  /*!
   * @if jp
   * @brief 初期化
   * @else
   * @brief Initialization
   * @endif
   */
  ReturnCode_t PeriodicECSharedComposite::onFinalize()
  {
    RTC_TRACE(("onFinalize()"));
    m_org->removeAllMembers();
    std::cout << "onFinalize done" << std::endl;
    return RTC::RTC_OK;
  }

}; // namespace RTC

extern "C"
{
  void PeriodicECSharedCompositeInit(RTC::Manager* manager)
  {
    coil::Properties profile(periodicecsharedcomposite_spec);
    manager->registerFactory(profile,
                             RTC::Create<RTC::PeriodicECSharedComposite>,
                             RTC::Delete<RTC::PeriodicECSharedComposite>);
  }
};

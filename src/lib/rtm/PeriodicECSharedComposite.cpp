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
    : Organization_impl(rtobj->getObjRef()), m_rtobj(rtobj),
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
    std::cout << "add_members() number of memner-> " << sdo_list.length() << std::endl;
    CORBA::Boolean result;
    result = ::SDOPackage::Organization_impl::add_members(sdo_list);


    for (::CORBA::ULong i(0), len(sdo_list.length()); i < len; ++i)
      {
        const SDO_ptr sdo  = sdo_list[i];
        ::OpenRTM::DataFlowComponent_ptr dfc;
        if (!sdoToDFC(sdo, dfc)) continue;

        stopOwnedEC(dfc);
        setOrganizationToTarget(dfc);
        setCompositeECToTarget(dfc);
        delegatePort(dfc);

      }


    //    ::CORBA_SeqUtil::for_each(sdo_list,
    //                              set_member(m_objref, m_rtcMembers, m_rtobj)); 
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
    std::cout << "set_members() number of memner-> " << sdo_list.length() << std::endl;
    std::cout << "PeriodicECOrganization::set_members()" << std::endl;
    CORBA::Boolean result;
    result = ::SDOPackage::Organization_impl::set_members(sdo_list);
    std::cout << "done" << std::endl;
    m_rtcMembers.length(0);
    std::cout << "length = 0 and given: " << sdo_list.length() << std::endl;


    for (::CORBA::ULong i(0), len(sdo_list.length()); i < len; ++i)
      {
        const SDO_ptr sdo  = sdo_list[i];
        ::OpenRTM::DataFlowComponent_ptr dfc;
        if (!sdoToDFC(sdo, dfc))
          {
            std::cout << "SDO is not DFC" << std::endl;
            continue;
          }
        std::cout << "0" << std::endl;
        stopOwnedEC(dfc);
        std::cout << "1" << std::endl;
        setOrganizationToTarget(dfc);
        std::cout << "2" << std::endl;
        setCompositeECToTarget(dfc);
        std::cout << "3" << std::endl;
        delegatePort(dfc);
        std::cout << "4" << std::endl;
        ::CORBA_SeqUtil::push_back(m_rtcMembers,
                                   ::RTC::RTObject::_duplicate(dfc));
        std::cout << "5" << std::endl;
      }
    //    ::CORBA_SeqUtil::for_each(sdo_list,
    //                              set_member(m_objref, m_rtcMembers, m_rtobj)); 
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
    CORBA::Boolean result;
    remove_member_f(m_objref, m_rtcMembers, id, m_rtobj);
    result = ::SDOPackage::Organization_impl::remove_member(id);
    return result;
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
                                   ::OpenRTM::DataFlowComponent_ptr& dfc)
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
  void PeriodicECOrganization::stopOwnedEC(::OpenRTM::DataFlowComponent_ptr dfc)
  {
    if (::CORBA::is_nil(dfc)) return;
    // stop target RTC's ExecutionContext
    ::RTC::ExecutionContextList_var ecs;
    ecs = dfc->get_owned_contexts();
    for (::CORBA::ULong i(0), len(ecs->length()); i < len; ++i)
      {
        ecs[i]->stop();
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
  void PeriodicECOrganization::setOrganizationToTarget(::OpenRTM::DataFlowComponent_ptr dfc)
  {
    // get given RTC's configuration object
    Configuration_var conf;
    conf = dfc->get_configuration();
    if (::CORBA::is_nil(conf)) return;
    
    // set organization to target RTC's conf
    conf->add_organization(::SDOPackage::Organization::_duplicate(m_objref));
  }

  /*!
   * @if jp
   * @brief Composite の ExecutionContext を DFC にセットする
   * @else
   * @brief Set CompositeRTC's ExecutionContext to the given DFC
   * @endif
   */
  void PeriodicECOrganization::setCompositeECToTarget(::OpenRTM::DataFlowComponent_ptr dfc)
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
    m_ec->add_component(dfc);
  }
  
  /*!
   * @if jp
   * @brief ポートを委譲する
   * @else
   * @brief Delegate given RTC's ports to the Composite
   * @endif
   */
  void
  PeriodicECOrganization::delegatePort(::OpenRTM::DataFlowComponent_ptr dfc)
  {
    std::string exported_ports = m_rtobj->getProperties()["exported_ports"];
      
    // get comp's/ports's profile
    ::RTC::ComponentProfile_var cprof = dfc->get_component_profile();
    ::RTC::PortProfileList& plist(cprof->port_profiles);

    // port delegation
    for (::CORBA::ULong i(0), len(plist.length()); i < len; ++i)
      {
        // port name -> comp_name.port_name
        std::string port_name(cprof->instance_name);
        port_name += "."; port_name += plist[i].name;

        std::string::size_type pos = exported_ports.find(port_name);
        if (pos == exported_ports.npos) continue;

        m_rtobj->registerPort(
                        ::RTC::PortService::_duplicate(plist[i].port_ref));

      }
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
    std::cout << "G0" << std::endl;
    m_ref = OpenRTM::DataFlowComponent::_duplicate(this->_this());
    std::cout << "G1" << std::endl;
    m_objref = RTC::RTObject::_duplicate(m_ref);
    std::cout << "G2" << std::endl;
    m_org = new SDOPackage::PeriodicECOrganization(this);
    std::cout << "G3" << std::endl;
    ::CORBA_SeqUtil::push_back(m_sdoOwnedOrganizations,
                                ::SDOPackage::Organization::_duplicate(m_org->getObjRef()));
    std::cout << "G4" << std::endl;
    std::cout << "created..............." << std::endl;
    bindParameter("members", m_members, "", stringToStrVec);
    std::cout << "G5" << std::endl;
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
    std::cout << "onInitialize()" << std::endl;
    std::cout << "number of member: " << m_members.size() << std::endl;
    ::RTC::Manager& mgr(::RTC::Manager::instance());

    std::vector<RtcBase*> comps = mgr.getComponents();
    for (int i(0), len(comps.size()); i < len; ++i)
      {
        std::cout << comps[i]->getInstanceName() << std::endl;
      }

    ::SDOPackage::SDOList sdos;
    for (int i(0), len(m_members.size()); i < len; ++i)
      {
         std::cout << "member: " << m_members[i] << std::endl;
        RtcBase* rtc = mgr.getComponent(m_members[i].c_str());
        if (rtc == NULL) {
          std::cout << "no RTC found: " << m_members[i] << std::endl;
          continue;
        }

        std::cout << "RTC found: " << rtc->getInstanceName() << std::endl;
        ::SDOPackage::SDO_ptr sdo;
        sdo = ::SDOPackage::SDO::_duplicate(rtc->getObjRef());
        if (::CORBA::is_nil(sdo)) continue;

        ::CORBA_SeqUtil::push_back(sdos, sdo);
        std::cout << "rtc added to list" << std::endl;
      }
    
    std::cout << "set_members start: " << m_org->get_organization_id() << std::endl;
    try
      {
        m_org->set_members(sdos);
        std::cout << "set_members" << std::endl;
      }
    catch (...)
      {
        std::cout << "exception cought" << std::endl;
      }
    return ::RTC::RTC_OK;
  }

  ReturnCode_t PeriodicECSharedComposite::onActivated(RTC::UniqueId exec_handle)
  {
    ::RTC::ExecutionContextList_var ecs = get_owned_contexts();
    ::SDOPackage::SDOList_var sdos = m_org->get_members();

    for (::CORBA::ULong i(0), len(sdos->length()); i < len; ++i)
      {
        ::RTC::RTObject_var rtc = ::RTC::RTObject::_narrow(sdos[i]);
        ecs[0]->activate_component(rtc);
      }
    std::cout << "num of mem:" << m_members.size() << std::endl;
    return ::RTC::RTC_OK;
  }

  ReturnCode_t PeriodicECSharedComposite::onDeactivated(RTC::UniqueId exec_handle)
  {
    ::RTC::ExecutionContextList_var ecs = get_owned_contexts();
    ::SDOPackage::SDOList_var sdos = m_org->get_members();

    for (::CORBA::ULong i(0), len(sdos->length()); i < len; ++i)
      {
        ::RTC::RTObject_var rtc = ::RTC::RTObject::_narrow(sdos[i]);
        ecs[0]->deactivate_component(rtc);
      }
    return ::RTC::RTC_OK;
  }

  ReturnCode_t PeriodicECSharedComposite::onReset(RTC::UniqueId exec_handle)
  {
    ::RTC::ExecutionContextList_var ecs = get_owned_contexts();
    ::SDOPackage::SDOList_var sdos = m_org->get_members();

    for (::CORBA::ULong i(0), len(sdos->length()); i < len; ++i)
      {
        ::RTC::RTObject_var rtc = ::RTC::RTObject::_narrow(sdos[i]);
        ecs[0]->reset_component(rtc);
      }
    return ::RTC::RTC_OK;
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

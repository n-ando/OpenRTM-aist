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
#include <iostream>


static const char* periodicecsharedcomposite_spec[] =
  {
    "implementation_id", "PeriodicECSharedComposite",
    "type_name",         "PeriodicECSharedComposite",
    "description",       "PeriodicECSharedComposite",
    "version",           "1.0",
    "vendor",            "jp.go.aist",
    "category",          "composite",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    "conf.default.members", "",
    ""
  };

namespace SDOPackage
{
  PeriodicECOrganization::PeriodicECOrganization(::RTC::RTObject_impl* rtobj)
    : Organization_impl(rtobj->getObjRef()), m_rtobj(rtobj)
  {
    // std::cout << "PeriodicECOrganization created" << std::endl;
    // std::cout << "ID: " << get_organization_id() << std::endl;
  }

  PeriodicECOrganization::~PeriodicECOrganization()
  {
    ;
  }

  CORBA::Boolean PeriodicECOrganization::add_members(const SDOList& sdo_list)
    throw (CORBA::SystemException,
           InvalidParameter, NotAvailable, InternalError)
  {
    CORBA::Boolean result;
    result = ::SDOPackage::Organization_impl::add_members(sdo_list);

    ::CORBA_SeqUtil::for_each(sdo_list,
                              set_member(m_objref, m_rtcMembers, m_rtobj)); 
    return result;
  }

  CORBA::Boolean PeriodicECOrganization::set_members(const SDOList& sdo_list)
    throw (CORBA::SystemException,
           InvalidParameter, NotAvailable, InternalError)
  {
    // std::cout << "PeriodicECOrganization::set_members()" << std::endl;
    CORBA::Boolean result;
    result = ::SDOPackage::Organization_impl::set_members(sdo_list);
    // std::cout << "done" << std::endl;
    m_rtcMembers.length(0);
    // std::cout << "length = 0 and given: " << sdo_list.length() << std::endl;
    ::CORBA_SeqUtil::for_each(sdo_list,
                              set_member(m_objref, m_rtcMembers, m_rtobj)); 
    return result;
  }

  CORBA::Boolean PeriodicECOrganization::remove_member(const char* id)
    throw (CORBA::SystemException,
           InvalidParameter, NotAvailable, InternalError)
  {
    CORBA::Boolean result;
    remove_member_f(m_objref, m_rtcMembers, id, m_rtobj);
    result = ::SDOPackage::Organization_impl::remove_member(id);
    return result;
  }
};


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
    m_ref = OpenRTM::DataFlowComponent::_duplicate(this->_this());
    m_objref = RTC::RTObject::_duplicate(m_ref);
    m_org = new SDOPackage::PeriodicECOrganization(this);
    ::CORBA_SeqUtil::push_back(m_sdoOwnedOrganizations,
                                ::SDOPackage::Organization::_duplicate(m_org->getObjRef()));
    // std::cout << "created..............." << std::endl;
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
    bindParameter("members", m_members, "");
    // std::cout << "onInitialize()" << std::endl;
    // std::cout << "number of member: " << m_members.size() << std::endl;
    ::RTC::Manager& mgr(::RTC::Manager::instance());

    std::vector<RtcBase*> comps = mgr.getComponents();
    for (int i(0), len(comps.size()); i < len; ++i)
      {
        // std::cout << comps[i]->getInstanceName() << std::endl;
      }

    ::SDOPackage::SDOList sdos;
    for (int i(0), len(m_members.size()); i < len; ++i)
      {
        // std::cout << "member: " << m_members[i] << std::endl;
        RtcBase* rtc = mgr.getComponent(m_members[i].c_str());
        if (rtc == NULL) {
          // std::cout << "no RTC found: " << m_members[i] << std::endl;
          continue;
        }

        // std::cout << "RTC found: " << rtc->getInstanceName() << std::endl;
        ::SDOPackage::SDO_ptr sdo;
        sdo = ::SDOPackage::SDO::_duplicate(rtc->getObjRef());
        if (::CORBA::is_nil(sdo)) continue;

        ::CORBA_SeqUtil::push_back(sdos, sdo);
        // std::cout << "rtc added to list" << std::endl;
      }
    
    // std::cout << "set_members start: " << m_org->get_organization_id() << std::endl;
    m_org->set_members(sdos);
    // std::cout << "set_members" << std::endl;
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

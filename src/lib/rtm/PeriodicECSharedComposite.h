// -*- C++ -*-
/*!
 * @file PeriodicECSharedComposite.h
 * @brief Periodic Execution Context Shared Composite Component class
 * @date $Date$
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

#ifndef PeriodicECSharedComposite_h
#define PeriodicECSharedComposite_h

#include <rtm_corba/idl/RTCSkel.h>
#include <rtm_corba/idl/OpenRTMSkel.h>
#include <rtm/RTObject.h>
#include <rtm/PeriodicExecutionContext.h>
#include <rtm/SdoOrganization.h>
#include <coil/stringutil.h>

/*!
 * @if jp
 * @namespace SDOPacakge
 *
 * @brief SDO
 *
 * @else
 *
 * @namespace SDOPackage
 *
 * @brief SDO
 *
 * @endif
 */
namespace SDOPackage
{
  class PeriodicECOrganization
    : public Organization_impl
  {
  public:
    PeriodicECOrganization(::RTC::RTObject_impl* rtobj);
    virtual ~PeriodicECOrganization();
    virtual ::CORBA::Boolean add_members(const SDOList& sdo_list)
      throw (::CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);
    virtual ::CORBA::Boolean set_members(const SDOList& sdos)
      throw (::CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);
    virtual ::CORBA::Boolean remove_member(const char* id)
      throw (::CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);

  protected:
    ::RTC::RTObject_impl* m_rtobj;
    ::RTC::RTCList m_rtcMembers;

  private:
    class set_member
    {
    public:
      set_member(Organization_ptr org, ::RTC::RTCList& rtcs,
                 ::RTC::RTObject_impl* rtobj)
        : m_org(org), m_rtcMembers(rtcs), m_rtobj(rtobj)
      {
        // std::cout << "set_member() ctor" << std::endl;
        ::RTC::ExecutionContextList_var ecs = m_rtobj->get_owned_contexts();
        // std::cout << "m_rtobj->get_owned_contexts(): " << ecs->length() << std::endl;
        m_ec = ecs[0];
      }
      ~set_member(){}

      void operator()(const SDO_ptr sdo)
      {
        // std::cout << "set_member::operator()(const SDO_ptr sdo)" << std::endl;
        if (::CORBA::is_nil(sdo)) return;

        // std::cout << "operator()" << std::endl;
        ::OpenRTM::DataFlowComponent_var dfc;
        dfc = ::OpenRTM::DataFlowComponent::_narrow(sdo);
        if (::CORBA::is_nil(dfc)) return;

        // std::cout << "DataFlowComp" << std::endl;

        // stop target RTC's ec
        ::RTC::ExecutionContextList_var ecs;
        ecs = dfc->get_owned_contexts();

        // std::cout << "EC: " << ecs->length() << std::endl;

        for (::CORBA::ULong i(0), len(ecs->length()); i < len; ++i)
          {
            // std::cout << "no. " << i << " EC stopped" << std::endl;
            ecs[i]->stop();
          }

        // get configuration object
        Configuration_var conf;
        conf = dfc->get_configuration();
        if (::CORBA::is_nil(conf)) return;
        // std::cout << "getConf" << std::endl;

        // set organization to target RTC's conf
        conf->add_organization(m_org);
        // std::cout << "add_org()" << std::endl;

        // set ec to target RTC
        m_ec->add_component(dfc);
        // std::cout << "add_cmop" << std::endl;

        // port
        ::RTC::PortServiceList_var plist = dfc->get_ports();
        //        ::RTC::ComponentProfile_var prof = m_rtobj->get_component_profile();
        //        prof->port_profile
        // std::cout << "port attach,,, no. " << plist->length() << std::endl;
        for (::CORBA::ULong i(0), len(plist->length()); i < len; ++i)
          {
            // std::cout << "port no.: " << i << std::endl;
            m_rtobj->registerPort(::RTC::PortService::_duplicate(plist[i]));
          }

        // finally store target RTC to member list
        ::CORBA_SeqUtil::push_back(m_rtcMembers,
                                   ::RTC::RTObject::_duplicate(dfc));
        // std::cout << "set_member done" << std::endl;
      }
    private:
      Organization_ptr m_org;
      ::RTC::RTCList& m_rtcMembers;
      ::RTC::RTObject_impl* m_rtobj;
      ::RTC::ExecutionContext_ptr m_ec;
    };

    class erase_pred
    {
    public:
      erase_pred(::RTC::RTObject_ptr rtobj)
        : m_rtobj(rtobj)
      {
      }

      bool operator()(::RTC::RTObject_ptr rtobj)
      {
        return m_rtobj->_is_equivalent(rtobj);
      }
      ::RTC::RTObject_ptr m_rtobj;
    };

    class remove_member_f
    {
    public:
      remove_member_f(Organization_ptr org, ::RTC::RTCList& rtcs, const char* id,
                 ::RTC::RTObject_impl* rtobj)
        : m_org(org), m_rtcMembers(rtcs), m_id(id), m_rtobj(rtobj)
      {
        ::RTC::ExecutionContextList_var ecs = m_rtobj->get_owned_contexts();
        m_ec = ecs[0];
      }
      ~remove_member_f(){}

      void operator()(const SDO_ptr sdo)
      {
        if (::CORBA::is_nil(sdo)) return;

        ::OpenRTM::DataFlowComponent_var dfc;
        dfc = ::OpenRTM::DataFlowComponent::_narrow(sdo);
        if (::CORBA::is_nil(dfc)) return;

        ::RTC::ComponentProfile_var prof = dfc->get_component_profile();
        const char* name = prof->instance_name;
        if (!(m_id == name)) return;


        // stop target RTC's ec
        ::RTC::ExecutionContextList_var ecs;
        ecs = dfc->get_owned_contexts();

        for (::CORBA::ULong i(0), len(ecs->length()); i < len; ++i)
          {
            ecs[i]->start();
          }

        // get configuration object
        Configuration_var conf;
        conf = dfc->get_configuration();
        if (::CORBA::is_nil(conf)) return;

        // set organization to target RTC's conf
        conf->remove_organization(m_org->get_organization_id());

        // set ec to target RTC
        m_ec->remove_component(dfc);

        // port
        ::RTC::PortServiceList_var plist = dfc->get_ports();
        for (::CORBA::ULong i(0), len(plist->length()); i < len; ++i)
          {
            m_rtobj->deletePort(::RTC::PortService::_duplicate(plist[i]));
          }

        ::CORBA_SeqUtil::erase_if(m_rtcMembers, erase_pred(dfc));
      }
    private:
      Organization_ptr m_org;
      ::RTC::RTCList& m_rtcMembers;
      std::string m_id;
      ::RTC::RTObject_impl* m_rtobj;
      ::RTC::ExecutionContext_ptr m_ec;
    };
  };
};

template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v)
{
  std::string s;
  std::vector<std::string> sv;
  is >> s;
  sv = coil::split(s ,",");
  v.resize(sv.size());
  for (int i(0), len(sv.size()); i < len; ++i)
    {
      T tv;
      if (coil::stringTo(tv, sv[i].c_str()))
	{
	  v[i] = tv;
	}
    }
  return is;
}


/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RTコンポーネント
 *
 * @else
 *
 * @namespace RTC
 *
 * @brief RT-Component
 *
 * @endif
 */
namespace RTC
{
  class Manager;

  /*!
   * @if jp
   * @class PeriodicECSharedComposite
   * @brief PeriodicECSharedComposite クラス
   *
   * データフロー型RTComponentの基底クラス。
   * 各種データフロー型RTComponentを実装する場合は、本クラスを継承する形で実装
   * する。
   *
   * @since 0.4.0
   *
   * @else
   * @class PeriodicECSharedComposite
   * @brief PeriodicECSharedComposite class
   *
   * This is a base class of the data flow type RT-Component.
   * Inherit this class when implementing various data flow type RT-Components.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class PeriodicECSharedComposite
    : public RTObject_impl
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     *
     * @param manager マネージャオブジェクト
     *
     * @else
     * @brief Constructor
     *
     * Constructor
     *
     * @param manager Manager object
     *
     * @endif
     */
    PeriodicECSharedComposite(Manager* manager);
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    virtual ~PeriodicECSharedComposite();
    
    /*!
     * @if jp
     * @brief 初期化
     *
     * データフロー型 RTComponent の初期化を実行する。
     * 実際の初期化処理は、各具象クラス内に記述する。
     *
     * @else
     * @brief Initialization
     *
     * Initialization the data flow type RT-Component.
     * Write the actual initialization code in each concrete class.
     *
     * @endif
     */
    virtual ReturnCode_t onInitialize();
    virtual ReturnCode_t onActivated(RTC::UniqueId exec_handle);
    virtual ReturnCode_t onDeactivated(RTC::UniqueId exec_handle);
    virtual ReturnCode_t onReset(RTC::UniqueId exec_handle);

  protected:
    std::vector<std::string> m_members;

    OpenRTM::DataFlowComponent_var m_ref;
    PeriodicExecutionContext* m_pec;
    ExecutionContextService_var m_ecref;
    SDOPackage::PeriodicECOrganization* m_org;
  };
}; // namespace RTC

extern "C"
{
  DLL_EXPORT void PeriodicECSharedCompositeInit(RTC::Manager* manager);
};

#endif // PeriodicECSharedComposite_h

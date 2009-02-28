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

#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>
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
    typedef std::vector<std::string> PortList;

  public:
    PeriodicECOrganization(::RTC::RTObject_impl* rtobj);
    virtual ~PeriodicECOrganization(void);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organizationメンバーを追加する
     *
     * Organization が保持するメンバーリストに与えられたSDOListを追加する。
     * 
     * @param sdo_list 追加される SDO メンバーのリスト
     * @return 追加が成功したかどうかがboolで返される
     *
     * @else
     * 
     * @brief [CORBA interface] Add Organization member
     *
     * This operation adds the given SDOList to the existing organization's 
     * member list
     * 
     * @param sdo_list SDO member list to be added
     * @return boolean will returned if the operation succeed
     *
     * @endif
     */
    virtual ::CORBA::Boolean add_members(const SDOList& sdo_list)
      throw (::CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organizationメンバーをセットする
     *
     * Organization が保持するメンバーリストを削除し、与えられた
     * SDOListを新規にセットする。
     * 
     * @param sdo_list 新規にセットされる SDO メンバーのリスト
     * @return 追加が成功したかどうかがboolで返される
     *
     * @else
     * 
     * @brief [CORBA interface] Set Organization member
     *
     * This operation removes existing member list and sets the given
     * SDOList to the existing organization's member list
     * 
     * @param sdo_list SDO member list to be set
     * @return boolean will returned if the operation succeed
     *
     * @endif
     */
    virtual ::CORBA::Boolean set_members(const SDOList& sdos)
      throw (::CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);

    /*!
     * @if jp
     * 
     * @brief [CORBA interface] Organizationメンバーを削除する
     *
     * Organization が保持するメンバーリスト内の特定のSDOを削除する。
     * 
     * @param id 削除される SDO の ID
     * @return 追加が成功したかどうかがboolで返される
     *
     * @else
     * 
     * @brief [CORBA interface] Remove a member of Organization
     *
     * This operation removes a SDO from existing member list by specified ID.
     * 
     * @param id The ID of the SDO to be removed
     * @return boolean will returned if the operation succeed
     *
     * @endif
     */
    virtual ::CORBA::Boolean remove_member(const char* id)
      throw (::CORBA::SystemException,
	     InvalidParameter, NotAvailable, InternalError);

    void removeAllMembers(void);
    void updateDelegatedPorts(void);
  protected:
    class Member;
    /*!
     * @if jp
     * @brief SDOからDFCへの変換
     * @else
     * @brief Conversion from SDO to DFC
     * @endif
     */
    bool sdoToDFC(const SDO_ptr sdo, ::OpenRTM::DataFlowComponent_ptr& dfc);

    /*!
     * @if jp
     * @brief Owned ExecutionContext を停止させる
     * @else
     * @brief Stop Owned ExecutionContexts
     * @endif
     */
    void stopOwnedEC(Member& member);

    /*!
     * @if jp
     * @brief Owned ExecutionContext を起動する
     * @else
     * @brief Start Owned ExecutionContexts
     * @endif
     */
    void startOwnedEC(Member& member);

    /*!
     * @if jp
     * @brief DFC に Organization オブジェクトを与える
     * @else
     * @brief Set Organization object to target DFC 
     * @endif
     */
    void addOrganizationToTarget(Member& member);

    /*!
     * @if jp
     * @brief Organization オブジェクトを DFCから削除する
     * @else
     * @brief Remove Organization object from a target DFC 
     * @endif
     */
    void removeOrganizationFromTarget(Member& member);

    /*!
     * @if jp
     * @brief Composite の ExecutionContext を DFC にセットする
     * @else
     * @brief Set CompositeRTC's ExecutionContext to the given DFC
     * @endif
     */
    void addParticipantToEC(Member& member);

    /*!
     * @if jp
     * @brief Composite の ExecutionContext から DFC を削除する
     * @else
     * @brief Remove participant DFC from CompositeRTC's ExecutionContext
     * @endif
     */
    void removeParticipantFromEC(Member& member);

    /*!
     * @if jp
     * @brief ポートを委譲する
     * @else
     * @brief Delegate given RTC's ports to the Composite
     * @endif
     */
    void delegatePort(Member& member, PortList& portlist);

    /*!
     * @if jp
     * @brief 委譲していたポートを削除する
     * @else
     * @brief Remove delegated participatns's ports from the composite
     * @endif
     */
    void removePort(Member& member, PortList& portlist);


    void updateExportedPortsList(void);

  protected:
    ::RTC::RTObject_impl* m_rtobj;
    ::RTC::ExecutionContext_ptr m_ec;

    class Member
    {
    public:
      Member(RTC::RTObject_ptr rtobj)
        : rtobj_(rtobj),
          profile_(rtobj->get_component_profile()),
          eclist_(rtobj->get_owned_contexts()),
          config_(rtobj->get_configuration())
      {}

      virtual ~Member(void){}
      
      Member(const Member& x)
        : rtobj_(RTC::RTObject::_duplicate(x.rtobj_)),
          profile_(new RTC::ComponentProfile(x.profile_)),
          eclist_(new RTC::ExecutionContextList(x.eclist_)),
          config_(SDOPackage::Configuration::_duplicate(x.config_))
      {
      }

      Member& operator=(const Member& x)
      {
        Member tmp(x);
        tmp.swap(*this);
        return *this;
      }

      void swap(Member& x)
      {
        RTC::RTObject_var rtobj= x.rtobj_;
        RTC::ComponentProfile_var profile = x.profile_;
        RTC::ExecutionContextList_var eclist = x.eclist_;
        SDOPackage::Configuration_var config = x.config_;

        x.rtobj_ = this->rtobj_;
        x.profile_ = this->profile_;
        x.eclist_ = this->eclist_;
        x.config_ = this->config_;

        this->rtobj_ = rtobj;
        this->profile_ = profile;
        this->eclist_ = eclist;
        this->config_ = config;
      }
      
      RTC::RTObject_var rtobj_;
      RTC::ComponentProfile_var profile_;
      RTC::ExecutionContextList_var eclist_;
      SDOPackage::Configuration_var config_;

    };

    std::vector<Member> m_rtcMembers;
    typedef std::vector<Member>::iterator MemIt;
    PortList m_expPorts;

    void print(PortList p)
    {
      for (int i(0), len(p.size()); i < len; ++i)
        {
          std::cout << p[i] << std::endl;
        }
    }
  };
};


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
    virtual ~PeriodicECSharedComposite(void);
    
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
    virtual ReturnCode_t onInitialize(void);
    virtual ReturnCode_t onActivated(RTC::UniqueId exec_handle);
    virtual ReturnCode_t onDeactivated(RTC::UniqueId exec_handle);
    virtual ReturnCode_t onReset(RTC::UniqueId exec_handle);
    virtual ReturnCode_t onFinalize(void);
    
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

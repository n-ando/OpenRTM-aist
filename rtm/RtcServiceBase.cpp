// -*- C++ -*-
/*!
 * @file RtcServiceBase.cpp
 * @brief RT component service classes
 * @date $Date: 2006-07-18 03:01:22 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcServiceBase.cpp,v 1.2 2006-07-18 03:01:22 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2005/09/07 05:05:14  n-ando
 * RTComponent's service management feature was added.
 *
 *
 */

#include "rtm/RtcServiceBase.h"
#include <iostream>
#include <algorithm>
#include <string>

namespace RTM {
  /*!
   * @if jp
   *
   * @class RtcServiceProfile
   *
   * @brief RtcServiceProfile クラス
   *
   * RTCServiceProfile ラッパークラス。
   *
   * @else
   *
   * @class RtcServiceProfile
   *
   * @brief RtcServiceProfile class.
   *
   * RtcServiceProfile wrapper class.
   *
   * @endif
   */

  RtcServiceProfile::RtcServiceProfile(const char* name,
									   const char* interfaceType,
									   const char* idlDefinition)
  {
	this->name          = CORBA::string_dup(name);
	this->interfaceType = CORBA::string_dup(interfaceType);
	this->idlDefinition = CORBA::string_dup(idlDefinition);
  }


  //============================================================
  /*!
   * @if jp
   *
   * @class RtcServiceBase
   *
   * @brief RtcServiceBase 基底クラス
   *
   * ユーザ定義のRtcServiceの基底クラス。
   *
   * @else
   *
   * @class RtcServiceBase
   *
   * @brief RtcServiceBase class.
   *
   * Super class of user defined RtcService object.
   *
   * @endif
   */






  //============================================================
  /*!
   * @if jp
   *
   * @class RtcServiceAdmin
   *
   * @brief RtcService 管理クラス
   *
   * RtcService をリストに保持し管理するクラス。
   *
   * @else
   *
   * @class RtcServiceAdmin
   *
   * @brief RtcService administration class.
   *
   * Keeping RtcService in a list and administrating it.
   *
   * @endif
   */

  /*!
   * @if jp
   * @brief RtcServiceAdmin コンストラクタ
   * @else
   * @brief RtcServiceAdmin constractor
   * @endif
   */
  RtcServiceAdmin::RtcServiceAdmin(CORBA::ORB_ptr orb,
								   PortableServer::POA_ptr poa)
	: m_pORB(orb), m_pPOA(poa)
  {
  }


  /*!
   * @if jp
   * @brief RtcServiceAdmin デストラクタ
   * @else
   * @brief RtcServiceAdmin destractor
   * @endif
   */
  RtcServiceAdmin::~RtcServiceAdmin()
  {
	deactivateServices();
  }


  /*!
   * @if jp
   * @brief Service の活性化と登録
   * @else
   * @brief Activation and registration of Service
   * @endif
   */
  void RtcServiceAdmin::registerService(RtcServiceBase& service,
										RtcServiceProfile& profile)
  {
	//	ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
	
	if (isRegistered(profile.getName()))
	  {
		throw;
	  }
	
	// Activate RTCService
	m_pPOA->activate_object(&service);
	RTCService_var objref;
	objref = RTCService::_narrow(m_pPOA->servant_to_reference(&service));
	
	// Service profile has a its object reference itself
	profile.setServiceRef(objref);
	service.setProfile(profile);
	
	m_Services.push_back(&service);
  }


  /*!
   * @if jp
   * @brief Service の非活性化と登録削除
   * @else
   * @brief Deactivation and erasing registration of Service
   * @endif
   */
  void RtcServiceAdmin::deactivateService(const char* name)
  {
	//	ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);

	Services_it it;
	
	it = std::find_if(m_Services.begin(), m_Services.end(),
				 eq_name(name));
	
	if (it == m_Services.end())
	  {
		throw RTM::NotFound::NotFound(name);
	  }
	else
	  {
		m_pPOA->deactivate_object(*m_pPOA->servant_to_id(*it));
		m_Services.erase(it);
	  }
  }


  /*!
   * @if jp
   * @brief 全Service の非活性化と登録削除
   * @else
   * @brief Deactivation and erasing registration of all Service
   * @endif
   */
  void RtcServiceAdmin::deactivateServices()
  {

	//	ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);
	if (m_Services.empty()) return;

	Services_it it(m_Services.begin());
	Services_it it_end(m_Services.end());

	while (it != it_end)
	  {
		m_pPOA->deactivate_object(*(m_pPOA->servant_to_id(*it)));
		it = m_Services.erase(it);
	  }
  }


  /*!
   * @if jp
   * @brief Service 登録状態の確認
   * @else
   * @brief Confirmation of service registration
   * @endif
   */
  bool RtcServiceAdmin::isRegistered(const char* name)
  {
	//	ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);

	Services_it it;
	
	it = std::find_if(m_Services.begin(), m_Services.end(),
				 eq_name(name));
	
	if (it == m_Services.end())
	  {
		return false;
	  }
	return true;
  }

  
  /*!
   * @if jp
   * @brief Service のオブジェクトリファレンスの取得
   * @else
   * @brief Get object reference of the Service
   * @endif
   */
  RTCService_ptr RtcServiceAdmin::getService(const char* name)
  {
	//	ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);

	Services_it it;

	it = std::find_if(m_Services.begin(), m_Services.end(), eq_name(name));
	
	if (it == m_Services.end())
	  {
		throw RTM::NotFound::NotFound(name);
	  }
	
	return (*it)->getObjRef();
  }


  /*!
   * @if jp
   * @brief Service のプロファイルの取得
   * @else
   * @brief Get profile of the Service
   * @endif
   */
  RTCServiceProfile* RtcServiceAdmin::getServiceProfile(const char* name)
  {
	//	ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);

	Services_it it;
	
	it = std::find_if(m_Services.begin(), m_Services.end(),
				 eq_name(name));
	
	if (it == m_Services.end())
	  {
		throw RTM::NotFound::NotFound(name);
	  }

	return (*it)->profile();
  }


  /*!
   * @if jp
   * @brief Service のプロファイルリストの取得
   * @else
   * @brief Get profile list of the Service
   * @endif
   */
  RTCServiceProfileList* RtcServiceAdmin::getServiceProfileList()
  {
	//	ACE_Guard<ACE_Thread_Mutex> guard(m_Mutex);

	RTM::RTCServiceProfileList_var list(new RTM::RTCServiceProfileList());
	list->length(m_Services.size());
	
	Services_it it(m_Services.begin());
	Services_it it_end(m_Services.end());
	
	CORBA::ULong i(0);
	while (it != it_end)
	  {
		list[i] = *((*it)->profile());
		++it; ++i;
	  }

	return list._retn();
  }
  

};

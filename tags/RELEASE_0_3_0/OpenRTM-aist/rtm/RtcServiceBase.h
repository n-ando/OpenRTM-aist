// -*- C++ -*-
/*!
 * @file RtcServiceBase.h
 * @brief RT component service classes
 * @date $Date: 2005-09-07 05:05:24 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcServiceBase.h,v 1.1 2005-09-07 05:05:24 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RtcServiceBase_h
#define RtcServiceBase_h

// CORBA header include
#include "rtm/RTC.h"

// STL includes
#include <list>
#include <string>


// ACE
#include <ace/Thread.h>
#include <ace/Task.h>

// local includes 
#include "rtm/idl/RTCServiceSkel.h"

namespace RTM {
  //============================================================
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
  class RtcServiceProfile
  	: public RTCServiceProfile
  {
  public:

	/*!
	 * @if jp
	 * @brief RtcServiceProfile コンストラクタ
	 * @else
	 * @brief RtcServiceProfile constractor
	 * @endif
	 */
	RtcServiceProfile(){};

	/*!
	 * @if jp
	 * @brief RtcServiceProfile コンストラクタ
	 * @else
	 * @brief RtcServiceProfile constractor
	 * @endif
	 */
	RtcServiceProfile(const char* name, const char* interfaceType,
					  const char* idlDefinition);


	/*!
	 * @if jp
	 * @brief CORBA 構造体 RTCServiceProfile を取得する
	 * @else
	 * @brief Getting RTCServiceProfile of CORBA structure
	 * @endif
	 */
	inline const RTCServiceProfile getProfile()
	{
	  return *this;
	}

	/*!
	 * @if jp
	 * @brief RTCServiceProfile.name をセットする
	 * @else
	 * @brief Setting RTCServiceProfile.name
	 * @endif
	 */
	inline void setName(char* name)
	{
	  // this->name is CORBA::string member of the struct
	  this->name = name;
	}

	/*!
	 * @if jp
	 * @brief RTCServiceProfile.name を取得
	 * @else
	 * @brief Getting RTCServiceProfile.name
	 * @endif
	 */
	inline const char* getName() const
	{
	  return this->name;
	}

	/*!
	 * @if jp
	 * @brief RTCServiceProfile.interfaceType をセットする
	 * @else
	 * @brief Setting RTCServiceProfile.interfaceType
	 * @endif
	 */
	inline void setInterfaceType(char* interfaceType)
	{
	  this->interfaceType = interfaceType;
	}

	/*!
	 * @if jp
	 * @brief RTCServiceProfile.interfaceType を取得する
	 * @else
	 * @brief Getting RTCServiceProfile.interfaceType
	 * @endif
	 */
	inline const char* getInterfaceType() const
	{
	  return this->interfaceType;
	}

	/*!
	 * @if jp
	 * @brief RTCServiceProfile.idlDefinition をセットする
	 * @else
	 * @brief Setting RTCServiceProfile.idlDefnition
	 * @endif
	 */
	inline void setIdlDefinition(char* idlDefinition)
	{
	  this->idlDefinition = idlDefinition;
	}

	/*!
	 * @if jp
	 * @brief RTCServiceProfile.idlDefinition を取得する
	 * @else
	 * @brief Getting RTCServiceProfile.idlDefnition
	 * @endif
	 */
	inline const char* getIdlDefinition() const
	{
	  return this->idlDefinition;
	}

	/*!
	 * @if jp
	 * @brief RTCServiceProfile.properties をセットする
	 * @else
	 * @brief Setting RTCServiceProfile.properties
	 * @endif
	 */
	inline void setProperties(NVList properties)
	{
	  this->properties = properties;
	}

	/*!
	 * @if jp
	 * @brief RTCServiceProfile.properties を取得する
	 * @else
	 * @brief Getting RTCServiceProfile.properties
	 * @endif
	 */
	inline const NVList getProperties() const
	{
	  return this->properties;
	}

	//	bool addProperty(char* name, CORBA::Any data);

	/*!
	 * @if jp
	 * @brief RTCServiceProfile.serviceRef をセットする
	 * @else
	 * @brief Setting RTCServiceProfile.serviceRef
	 * @endif
	 */
	inline void setServiceRef(RTCService_ptr serviceRef)
	{
	  this->serviceRef = serviceRef;
	}

	/*!
	 * @if jp
	 * @brief RTCServiceProfile.serviceRef を取得する
	 * @else
	 * @brief Getting RTCServiceProfile.serviceRef
	 * @endif
	 */
	RTCService_ptr getServiceRef() const
	{
	  return this->serviceRef;
	}
  };


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
  class RtcServiceBase
	: public virtual POA_RTM::RTCService, 
      public virtual PortableServer::RefCountServantBase
  {
  public:
	/*!
	 * @if jp
	 * @brief RtcServiceBase コンストラクタ
	 * @else
	 * @brief RtcServiceBase constractor
	 * @endif
	 */
	RtcServiceBase(){};

	/*!
	 * @if jp
	 * @brief RtcServiceBase デストラクタ
	 * @else
	 * @brief RtcServiceBase destractor
	 * @endif
	 */
	virtual ~RtcServiceBase(){};

	/*!
	 * @if jp
	 * @brief [CORBA interface] RtcService のプロファイルの取得
	 * @else
	 * @brief Getting profile of RtcService
	 * @endif
	 */
	virtual RTCServiceProfile* profile()
	{
	  RTCServiceProfile_var profile;
	  profile = new RTCServiceProfile(m_Profile.getProfile());
	  return profile._retn();
	}


	/*!
	 * @if jp
	 * @brief RtcService にプロファイルをセットする
	 * @else
	 * @brief Setting profile to RtcService
	 * @endif
	 */
	bool setProfile(RtcServiceProfile& profile)
	{
	  m_Profile = profile;
	}

	/*!
	 * @if jp
	 * @brief RtcService のプロファイルを取得する
	 * @else
	 * @brief Setting profile to RtcService
	 * @endif
	 */
	const RtcServiceProfile& getProfile()
	{
	  return m_Profile;
	}

	/*!
	 * @if jp
	 * @brief RtcService のオブジェクトリファレンスをセットする
	 * @else
	 * @brief Setting object reference to RtcService profile
	 * @endif
	 */
	bool setObjRef(RTCService_ptr service)
	{
	  m_Profile.setServiceRef(RTM::RTCService::_duplicate(service));
	}

	/*!
	 * @if jp
	 * @brief RtcService のオブジェクトリファレンスを取得
	 * @else
	 * @brief Getting object reference to RtcService profile
	 * @endif
	 */
	RTCService_ptr getObjRef()
	{
	  return m_Profile.getServiceRef();
	}

  protected:
	/*!
	 * @if jp
	 * @brief Profile 変数
	 * @else
	 * @brief Profile
	 * @endif
	 */
	RtcServiceProfile m_Profile;
  };


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
  class RtcServiceAdmin
  {
  public:
	/*!
	 * @if jp
	 * @brief RtcServiceAdmin コンストラクタ
	 * @else
	 * @brief RtcServiceAdmin constractor
	 * @endif
	 */
	RtcServiceAdmin(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);

	/*!
	 * @if jp
	 * @brief RtcServiceAdmin デストラクタ
	 * @else
	 * @brief RtcServiceAdmin destractor
	 * @endif
	 */
	virtual ~RtcServiceAdmin();

	/*!
	 * @if jp
	 * @brief Service の活性化と登録
	 * @else
	 * @brief Activation and registration of Service
	 * @endif
	 */
	void registerService(RtcServiceBase& service, RtcServiceProfile& profile);

	/*!
	 * @if jp
	 * @brief Service の非活性化と登録削除
	 * @else
	 * @brief Deactivation and erasing registration of Service
	 * @endif
	 */
	void deactivateService(const char* name);
	
	/*!
	 * @if jp
	 * @brief 全Service の非活性化と登録削除
	 * @else
	 * @brief Deactivation and erasing registration of all Service
	 * @endif
	 */
	void deactivateServices();

	/*!
	 * @if jp
	 * @brief Service 登録状態の確認
	 * @else
	 * @brief Confirmation of service registration
	 * @endif
	 */
	bool isRegistered(const char* name);
	  
	/*!
	 * @if jp
	 * @brief Service のオブジェクトリファレンスの取得
	 * @else
	 * @brief Get object reference of the Service
	 * @endif
	 */
	RTCService_ptr getService(const char* name);

	/*!
	 * @if jp
	 * @brief Service のプロファイルの取得
	 * @else
	 * @brief Get profile of the Service
	 * @endif
	 */
	RTCServiceProfile* getServiceProfile(const char* name);

	/*!
	 * @if jp
	 * @brief Service のプロファイルリストの取得
	 * @else
	 * @brief Get profile list of the Service
	 * @endif
	 */
	RTCServiceProfileList* getServiceProfileList();


  protected:
	/*!
	 * @if jp
	 * @brief ORB ポインタ変数
	 * @else
	 * @brief pointer to ORB
	 * @endif
	 */
	class eq_name
	{
	public:
	  const std::string m_name;
	  eq_name(const char* name) : m_name(name){};
	  bool operator()(RtcServiceBase* svc)
	  {
		std::string _name(svc->getProfile().getName());
		return m_name == _name;
	  };
	};

	/*!
	 * @if jp
	 * @brief Service リスト
	 * @else
	 * @brief Service list
	 * @endif
	 */
	std::list<RtcServiceBase*> m_Services;

	/*!
	 * @if jp
	 * @brief Service list イテレータ
	 * @else
	 * @brief Service list iterator
	 * @endif
	 */
	typedef std::list<RtcServiceBase*>::iterator Services_it;

	/*!
	 * @if jp
	 * @brief Service list の Mutex
	 * @else
	 * @brief Mutex of Service list
	 * @endif
	 */
	ACE_Thread_Mutex m_Mutex;

	/*!
	 * @if jp
	 * @brief ORB ポインタ変数
	 * @else
	 * @brief pointer to ORB
	 * @endif
	 */
	CORBA::ORB_ptr m_pORB;

	/*!
	 * @if jp
	 * @brief POA ポインタ変数
	 * @else
	 * @brief pointer to POA
	 * @endif
	 */
	PortableServer::POA_ptr m_pPOA;
  };
};

#endif // RtcServiceBase_h

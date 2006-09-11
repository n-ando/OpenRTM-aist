// -*- C++ -*-
/*!
 * @file RTObject.h
 * @brief RT component base class
 * @date $Date: 2006-09-11 19:04:38 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTObject.h,v 1.1 2006-09-11 19:04:38 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RTObject_h
#define RTObject_h

// CORBA header include
#include "rtm/RTC.h"
#include "rtm/Util.h"

#include "rtm/idl/RTCSkel.h"

namespace RTC
{
  class RTObject_impl
	: public virtual POA_RTC::RTObject, 
	  public virtual PortableServer::RefCountServantBase
  {
  public:
    RTObject_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    virtual ~RTObject_impl();


    // RTC::RTObject
    /*!
     * @if jp
     *
     * @brief コンポーネントプロファイルの取得
     *
     * 当該コンポーネントのプロファイル情報を返す。 
     *
     * @else
     *
     * @brief Getting RTC's profile
     *
     * This operation returns the ComponentProfile of the RTC
     *
     * @endif
     */
    virtual ComponentProfile* get_component_profile();


    /*!
     * @if jp
     *
     * @brief ポートの取得
     *
     * 当該コンポーネントが保有するポートの参照を返す。
     *
     * @else
     *
     * @brief Get Ports
     *
     * This operation returns a list of the RTCs ports.
     *
     * @endif
     */
    virtual PortList* get_ports();


    /*!
     * @if jp
     *
     * @brief ExecutionContextAdmin の取得
     *
     * このオペレーションは当該　RTC が所属する ExecutionContextに関連した
     * ExecutionContextAdmin のリストを返す。
     *
     * @else
     *
     * @brief Get ExecutionContextAdmin
     *
     * This operation returns a list containing an ExecutionContextAdmin for
     * every ExecutionContext owned by the RTC.	
     *
     * @endif
     */
    virtual ExecutionContextAdminList* get_execution_context_admins();

  protected:
    // Partial specialization
    template <class T, class X>
    class SeqEx
      : public SequenceEx <T, X, ACE_Thread_Mutex> {};
    
    RTC::ComponentProfile m_componentProfile;
    SeqEx<PortList, Port_ptr>  m_Ports;

  };
};
#endif // RTObject

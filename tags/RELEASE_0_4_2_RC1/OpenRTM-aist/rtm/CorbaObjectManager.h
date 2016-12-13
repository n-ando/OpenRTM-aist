// -*- C++ -*-
/*!
 * @file CorbaObjManager.h
 * @brief CORBA Object manager class
 * @date $Date: 2006-11-04 19:57:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: CorbaObjectManager.h,v 1.2 2006-11-04 19:57:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/04 19:54:48  n-ando
 * CORBA object activation class was created.
 *
 */

#ifndef CorbaObjectManager_h
#define CorbaObjectManager_h

#include <rtm/RTC.h>
#include <rtm/RTObject.h>

namespace RTC
{
  /*!
   * @if jp
   * @class CorbaObjectManager
   * @brief CORBA オブジェクトをアクティブ化、非アクティブ化する
   * @else
   * @class CorbaObjectManager
   * @brief Activate and deactivate CORBA objects
   * @endif
   */
  class CorbaObjectManager
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    CorbaObjectManager(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);


    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~CorbaObjectManager() {};


    /*!
     * @if jp
     * @brief CORBA オブジェクトをアクティブ化する
     * @else
     * @brief Activate CORBA object
     * @endif
     */
    void activate(RTObject_impl* comp);


    /*!
     * @if jp
     * @brief CORBA オブジェクトを非アクティブ化する
     * @else
     * @brief Deactivate CORBA object
     * @endif
     */
    void deactivate(RTObject_impl* comp);
    
  private:
    CORBA::ORB_var m_pORB;
    PortableServer::POA_var m_pPOA;
  };
}; // namespace RTC

#endif // CoabrObjectManager



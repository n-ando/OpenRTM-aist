// -*- C++ -*-
/*!
 * @file CorbaObjManager.h
 * @brief CORBA Object manager class
 * @date $Date: 2007-12-31 03:08:02 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
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

#ifndef CorbaObjectManager_h
#define CorbaObjectManager_h

#include <rtm/RTC.h>
#include <rtm/RTObject.h>

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
  /*!
   * @if jp
   * @class CorbaObjectManager
   * @brief CORBA オブジェクトをアクティブ化、非アクティブ化する
   *
   * RTObjectのアクティブ化，非アクティブ化を行うクラスである。
   * 保持しているORB，POAを用いて CORBA オブジェクトのアクティブ化，
   * 非アクティブ化を行う。
   *
   * @since 0.4.0
   *
   * @else
   * @class CorbaObjectManager
   * @brief Activate and deactivate CORBA objects
   *
   * This is a class to activate and deactivate RTObjects.
   * Activate and deactivate the CORBA objects using ORB, POA held.
   *
   * @since 0.4.0
   *
   * @endif
   */
  class CorbaObjectManager
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * @param orb ORB
     * @param poa POA
     *
     * @else
     *
     * @brief Consructor
     *
     * @param orb ORB
     * @param poa POA
     *
     * @endif
     */
    CorbaObjectManager(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    
    /*!
     * @if jp
     *
     * @brief 仮想デストラクタ
     * 
     * @else
     * 
     * @brief Virtual destructor
     * 
     * @endif
     */
    virtual ~CorbaObjectManager() {};
    
    /*!
     * @if jp
     * @brief CORBA オブジェクトをアクティブ化する
     *
     * 指定されたRTObjectを CORBA オブジェクトとしてアクティブ化し、
     * オブジェクトリファレンスを設定する。
     *
     * @param comp アクティブ化対象RTObject
     *
     * @else
     * @brief Activate the CORBA object
     *
     * Activate specified RTObject as CORBA object and 
     * specify its object reference
     *
     * @param comp The target RTObject to activate
     *
     * @endif
     */
    void activate(RTObject_impl* comp);
    
    /*!
     * @if jp
     * @brief CORBA オブジェクトを非アクティブ化する
     *
     * 指定されたRTObjectの非アクティブ化を行う
     *
     * @param comp 非アクティブ化対象RTObject
     *
     * @else
     * @brief Deactivate the CORBA object
     *
     * Deactivate specified RTObject as CORBA object
     *
     * @param comp The target RTObject to deactivate
     *
     * @endif
     */
    void deactivate(RTObject_impl* comp);
    
  private:
    CORBA::ORB_var m_pORB;
    PortableServer::POA_var m_pPOA;
  };
}; // namespace RTC

#endif // CoabrObjectManager

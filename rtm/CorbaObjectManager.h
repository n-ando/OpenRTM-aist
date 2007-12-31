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
 * $Id: CorbaObjectManager.h,v 1.2.4.1 2007-12-31 03:08:02 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/11/04 19:57:05  n-ando
 * Kanji-code was converted into EUC.
 *
 * Revision 1.1  2006/11/04 19:54:48  n-ando
 * CORBA object activation class was created.
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
     * @brief virtual destructor
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
     * @brief Activate CORBA object
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

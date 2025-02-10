// -*- C++ -*-
/*!
 * @file ManagerActionListener.h
 * @brief component action listener class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2011
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTM_MANAGERACTIONLISTENER_H
#define RTM_MANAGERACTIONLISTENER_H

#include <mutex>
#include <coil/Properties.h>
#include <coil/stringutil.h>
#include <rtm/ListenerHolder.h>

#include <string>
#include <vector>
#include <utility>

// forward decl
namespace RTC
{
  class RTObject_impl;
} // namespace RTC

namespace RTM
{
  // forward decl
  class LocalServiceBase;

  //============================================================
  /*!
   * @if jp
   * @class ManagerActionListener
   *
   * - マネージャShutdownの直前: void onPreShutdown()
   * - マネージャShutdownの直後: void onPostShutdown()
   * - マネージャの再初期化直前: void onPreReinit()
   * - マネージャの再初期化直後: void onPostReinit()
   *
   * TODO: Documentation
   *
   * @else
   * @class ManagerActionListener
   *
   * TODO: Documentation
   *
   * @endif
   */
  class ManagerActionListener
  {
  public:
    /*!
     * @if jp
     * @brief ManagerActinListener dtor
     * TODO: Documentation
     * @else
     * @brief ManagerActionListener dtor
     * TODO: Documentation
     * @endif
     */
    virtual ~ManagerActionListener();

    /*!
     * @if jp
     * @brief preShutdown コールバック関数
     * TODO: Documentation
     * @else
     * @brief preShutdown callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preShutdown() = 0;

    /*!
     * @if jp
     * @brief postShutdown コールバック関数
     * TODO: Documentation
     * @else
     * @brief postShutdown callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postShutdown() = 0;

    /*!
     * @if jp
     * @brief preReinit コールバック関数
     * TODO: Documentation
     * @else
     * @brief preReinit callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preReinit() = 0;

    /*!
     * @if jp
     * @brief postReinit コールバック関数
     * TODO: Documentation
     * @else
     * @brief postReinit callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postReinit() = 0;
  };


  /*!
   * @if jp
   * @class ManagerActionListenerHolder クラス
   * @else
   * @class ManagerActionListenerHolder class
   * @endif
   */
  class ManagerActionListenerHolder
    : public ::RTM::util::ListenerHolder<ManagerActionListener>
  {
  public:
    ~ManagerActionListenerHolder() override;

    /*!
     * @if jp
     * @brief preShutdown コールバック関数
     * TODO: Documentation
     * @else
     * @brief preShutdown callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preShutdown();

    /*!
     * @if jp
     * @brief postShutdown コールバック関数
     * TODO: Documentation
     * @else
     * @brief postShutdown callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postShutdown();

    /*!
     * @if jp
     * @brief preReinit コールバック関数
     * TODO: Documentation
     * @else
     * @brief preReinit callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preReinit();

    /*!
     * @if jp
     * @brief postReinit コールバック関数
     * TODO: Documentation
     * @else
     * @brief postReinit callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postReinit();
  };


  //============================================================
  /*!
   * @if jp
   * @class ModuleActionListener クラス
   * @brief ModuleActionListener クラス
   *
   * @else
   * @class ModuleActionListener class
   * @brief ModuleActionListener class
   *
   * @endif
   */
  class ModuleActionListener
  {
  public:
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ModuleActionListener();

    /*!
     * @if jp
     * @brief preLoad コールバック関数
     * TODO: Documentation
     * @else
     * @brief preLoad callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preLoad(std::string& modname,
                         std::string& funcname) = 0;

    /*!
     * @if jp
     * @brief postLoad コールバック関数
     * TODO: Documentation
     * @else
     * @brief postLoad callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postLoad(std::string& modname,
                          std::string& funcname) = 0;

    /*!
     * @if jp
     * @brief preUnload コールバック関数
     * TODO: Documentation
     * @else
     * @brief preUnload callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preUnload(std::string& modname) = 0;

    /*!
     * @if jp
     * @brief postUnload コールバック関数
     * TODO: Documentation
     * @else
     * @brief postUnload callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postUnload(std::string& modname) = 0;
  };


  /*!
   * @if jp
   * @class ModuleActionListenerHolder クラス
   * @brief ModuleActionListenerHolder クラス
   *
   * @else
   * @class ModuleActionListenerHolder class
   * @brief ModuleActionListenerHolder class
   *
   * @endif
   */
  class ModuleActionListenerHolder
    : public ::RTM::util::ListenerHolder<ModuleActionListener>
  {
  public:
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    ~ModuleActionListenerHolder() override;

    /*!
     * @if jp
     * @brief preLoad コールバック関数
     * TODO: Documentation
     * @else
     * @brief preLoad callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preLoad(std::string& modname,
                         std::string& funcname);

    /*!
     * @if jp
     * @brief postLoad コールバック関数
     * TODO: Documentation
     * @else
     * @brief postLoad callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postLoad(std::string& modname,
                          std::string& funcname);

    /*!
     * @if jp
     * @brief preUnload コールバック関数
     * TODO: Documentation
     * @else
     * @brief preUnload callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preUnload(std::string& modname);

    /*!
     * @if jp
     * @brief postUnload コールバック関数
     * TODO: Documentation
     * @else
     * @brief postUnload callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postUnload(std::string& modname);
  };



  //============================================================
  /*!
   * @if jp
   * @class RtcLifecycleActionListener クラス
   * @brief RtcLifecycleActionListener クラス
   *
   * RTC系
   * - RTC生成の直前 bool (std::string&)
   *   void preCreate(std::string& args) = 0;
   * - RTC生成の直後 bool (RTObject_impl*)
   *   void postCreate(RTObject_impl*) = 0;
   * - RTCのコンフィグ直前 bool (coil::Properties& prop)
   *   void preConfigure(coil::Properties& prop) = 0;
   * - RTCのコンフィグ直後 bool (coil::Properties& prop)
   *   void postConfigure(coil::Properties& prop) = 0;
   * - RTCの初期化の直前 bool (void)
   *   void preInitialize(void) = 0;
   * - RTCの初期化の直後 bool (void)
   *   void postInitialize(void) = 0;
   *
   * @else
   * @class RtcLifecycleActionListener class
   * @brief RtcLifecycleActionListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class RtcLifecycleActionListener
  {
  public:
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~RtcLifecycleActionListener();

    /*!
     * @if jp
     * @brief preCreate コールバック関数
     * TODO: Documentation
     * @else
     * @brief preCreate callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preCreate(std::string& args) = 0;

    /*!
     * @if jp
     * @brief postCreate コールバック関数
     * TODO: Documentation
     * @else
     * @brief postCreate callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postCreate(RTC::RTObject_impl*) = 0;

    /*!
     * @if jp
     * @brief preConfigure コールバック関数
     * TODO: Documentation
     * @else
     * @brief preConfigure callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preConfigure(coil::Properties& prop) = 0;

    /*!
     * @if jp
     * @brief postConfigure コールバック関数
     * TODO: Documentation
     * @else
     * @brief postConfigure callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postConfigure(coil::Properties& prop) = 0;

    /*!
     * @if jp
     * @brief preInitialize コールバック関数
     * TODO: Documentation
     * @else
     * @brief preInitialize callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preInitialize() = 0;

    /*!
     * @if jp
     * @brief postInitialize コールバック関数
     * TODO: Documentation
     * @else
     * @brief postInitialize callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postInitialize() = 0;
  };


  /*!
   * @if jp
   * @class RtcLifecycleActionListenerHolder クラス
   * @brief RtcLifecycleActionListenerHolder クラス
   *
   * @else
   * @class RtcLifecycleActionListenerHolder class
   * @brief RtcLifecycleActionListenerHolder class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class RtcLifecycleActionListenerHolder
    : public RTM::util::ListenerHolder<RtcLifecycleActionListener>
  {
  public:
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    ~RtcLifecycleActionListenerHolder() override;


    /*!
     * @if jp
     * @brief preCreate コールバック関数
     * TODO: Documentation
     * @else
     * @brief preCreate callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preCreate(std::string& args);

    /*!
     * @if jp
     * @brief postCreate コールバック関数
     * TODO: Documentation
     * @else
     * @brief postCreate callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postCreate(RTC::RTObject_impl* rtobj);

    /*!
     * @if jp
     * @brief preConfigure コールバック関数
     * TODO: Documentation
     * @else
     * @brief preConfigure callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preConfigure(coil::Properties& prop);

    /*!
     * @if jp
     * @brief postConfigure コールバック関数
     * TODO: Documentation
     * @else
     * @brief postConfigure callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postConfigure(coil::Properties& prop);

    /*!
     * @if jp
     * @brief preInitialize コールバック関数
     * TODO: Documentation
     * @else
     * @brief preInitialize callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preInitialize();

    /*!
     * @if jp
     * @brief postInitialize コールバック関数
     * TODO: Documentation
     * @else
     * @brief postInitialize callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postInitialize();
  };


  //============================================================
  /*!
   * @if jp
   * @class NamingActionListener クラス
   * @brief NamingActionListener クラス
   *
   * 各アクションに対応するユーザーコードが呼ばれる直前のタイミング
   * でコールされるリスなクラスの基底クラス。
   *
   * Registration系
   * - PRE_NS_REGISTER:    RTCの名前の登録の直前 bool (coil::vstring&)
   * - POST_NS_REGISTER:   RTCの名前の登録の直後 bool (coil::vstring&)
   * - PRE_NS_UNREGISTER:  RTCの名前の登録の直前 bool (coil::vstring&)
   * - POST_NS_UNREGISTER: RTCの名前の登録の直後 bool (coil::vstring&)
   *
   * - ADD_PORT:
   * - REMOVE_PORT:
   *
   * @else
   * @class NamingActionListener class
   * @brief NamingActionListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class NamingActionListener
  {
  public:
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~NamingActionListener();

    /*!
     * @if jp
     * @brief preBind コールバック関数
     * TODO: Documentation
     * @else
     * @brief preBind callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preBind(RTC::RTObject_impl* rtobj,
                         coil::vstring& name) = 0;
    /*!
     * @if jp
     * @brief postBind コールバック関数
     * TODO: Documentation
     * @else
     * @brief postBind callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postBind(RTC::RTObject_impl* rtobj,
                          coil::vstring& name) = 0;

    /*!
     * @if jp
     * @brief preUnbind コールバック関数
     * TODO: Documentation
     * @else
     * @brief preUnbind callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preUnbind(RTC::RTObject_impl* rtobj,
                           coil::vstring& name) = 0;

    /*!
     * @if jp
     * @brief postUnbind コールバック関数
     * TODO: Documentation
     * @else
     * @brief postUnbind callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postUnbind(RTC::RTObject_impl* rtobj,
                            coil::vstring& name) = 0;
  };


  /*!
   * @if jp
   * @class NamingActionListenerHolder クラス
   * @brief NamingActionListenerHolder クラス
   *
   * @else
   * @class NamingActionListenerHolder class
   * @brief NamingActionListenerHolder class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class NamingActionListenerHolder
    : public RTM::util::ListenerHolder<NamingActionListener>
  {
  public:
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    ~NamingActionListenerHolder() override;

    /*!
     * @if jp
     * @brief preBind コールバック関数
     * TODO: Documentation
     * @else
     * @brief preBind callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preBind(RTC::RTObject_impl* rtobj,
                         coil::vstring& name);
    /*!
     * @if jp
     * @brief postBind コールバック関数
     * TODO: Documentation
     * @else
     * @brief postBind callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postBind(RTC::RTObject_impl* rtobj,
                          coil::vstring& name);

    /*!
     * @if jp
     * @brief preUnbind コールバック関数
     * TODO: Documentation
     * @else
     * @brief preUnbind callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preUnbind(RTC::RTObject_impl* rtobj,
                           coil::vstring& name);

    /*!
     * @if jp
     * @brief postUnbind コールバック関数
     * TODO: Documentation
     * @else
     * @brief postUnbind callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postUnbind(RTC::RTObject_impl* rtobj,
                            coil::vstring& name);
  };


  //============================================================
  /*!
   * @if jp
   * @class LocalServiceActionListener クラス
   * @brief LocalServiceActionListener クラス
   *
   * 各アクションに対応するユーザーコードが呼ばれる直前のタイミング
   * でコールされるリスなクラスの基底クラス。
   *
   * - ADD_PORT:
   * - REMOVE_PORT:
   *
   * @else
   * @class LocalServiceActionListener class
   * @brief LocalServiceActionListener class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class LocalServiceActionListener
  {
  public:
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~LocalServiceActionListener();

    /*!
     * @if jp
     * @brief preServiceRegister コールバック関数
     * TODO: Documentation
     * @else
     * @brief preServiceRegister callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preServiceRegister(std::string service_name) = 0;

    /*!
     * @if jp
     * @brief postServiceRegister コールバック関数
     * TODO: Documentation
     * @else
     * @brief postServiceRegister callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postServiceRegister(std::string service_name,
                                     RTM::LocalServiceBase* service) = 0;

    /*!
     * @if jp
     * @brief preServiceInit コールバック関数
     * TODO: Documentation
     * @else
     * @brief preServiceInit callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preServiceInit(coil::Properties& prop,
                                RTM::LocalServiceBase* service) = 0;

    /*!
     * @if jp
     * @brief postServiceInit コールバック関数
     * TODO: Documentation
     * @else
     * @brief postServiceInit callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postServiceInit(coil::Properties& prop,
                                 RTM::LocalServiceBase* service) = 0;

    /*!
     * @if jp
     * @brief preServiceReinit コールバック関数
     * TODO: Documentation
     * @else
     * @brief preServiceReinit callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preServiceReinit(coil::Properties& prop,
                                  RTM::LocalServiceBase* service) = 0;

    /*!
     * @if jp
     * @brief postServiceReinit コールバック関数
     * TODO: Documentation
     * @else
     * @brief postServiceReinit callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postServiceReinit(coil::Properties& prop,
                                   RTM::LocalServiceBase* service) = 0;

    /*!
     * @if jp
     * @brief postServiceFinalize コールバック関数
     * TODO: Documentation
     * @else
     * @brief postServiceFinalize callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postServiceFinalize(std::string service_name,
                                     RTM::LocalServiceBase* service) = 0;

    /*!
     * @if jp
     * @brief preServiceFinalize コールバック関数
     * TODO: Documentation
     * @else
     * @brief preServiceFinalize callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preServiceFinalize(std::string service_name,
                                    RTM::LocalServiceBase* service) = 0;
  };


  /*!
   * @if jp
   * @class LocalServiceActionListenerHolder クラス
   * @brief LocalServiceActionListenerHolder クラス
   *
   * 各アクションに対応するユーザーコードが呼ばれる直前のタイミング
   * でコールされるリスなクラスの基底クラス。
   *
   * - ADD_PORT:
   * - REMOVE_PORT:
   *
   * @else
   * @class LocalServiceActionListenerHolder class
   * @brief LocalServiceActionListenerHolder class
   *
   * This class is abstract base class for listener classes that
   * provides callbacks for various events in rtobject.
   *
   * @endif
   */
  class LocalServiceActionListenerHolder
    : public RTM::util::ListenerHolder<LocalServiceActionListener>
  {
  public:
    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    ~LocalServiceActionListenerHolder() override;

    // registration instance of service to svc admin
    /*!
     * @if jp
     * @brief preServiceRegister コールバック関数
     * TODO: Documentation
     * @else
     * @brief preServiceRegister callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preServiceRegister(std::string service_name);

    /*!
     * @if jp
     * @brief postServiceRegister コールバック関数
     * TODO: Documentation
     * @else
     * @brief postServiceRegister callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postServiceRegister(std::string service_name,
                                     RTM::LocalServiceBase* service);

    /*!
     * @if jp
     * @brief preServiceInit コールバック関数
     * TODO: Documentation
     * @else
     * @brief preServiceInit callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preServiceInit(coil::Properties& prop,
                                RTM::LocalServiceBase* service);
    /*!
     * @if jp
     * @brief postServiceInit コールバック関数
     * TODO: Documentation
     * @else
     * @brief postServiceInit callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postServiceInit(coil::Properties& prop,
                                 RTM::LocalServiceBase* service);

    /*!
     * @if jp
     * @brief preServiceReinit コールバック関数
     * TODO: Documentation
     * @else
     * @brief preServiceReinit callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preServiceReinit(coil::Properties& prop,
                                  RTM::LocalServiceBase* service);
    /*!
     * @if jp
     * @brief postServiceReinit コールバック関数
     * TODO: Documentation
     * @else
     * @brief postServiceReinit callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postServiceReinit(coil::Properties& prop,
                                   RTM::LocalServiceBase* service);

    /*!
     * @if jp
     * @brief postServiceFinalize コールバック関数
     * TODO: Documentation
     * @else
     * @brief postServiceFinalize callback function
     * TODO: Documentation
     * @endif
     */
    virtual void postServiceFinalize(std::string service_name,
                                     RTM::LocalServiceBase* service);
    /*!
     * @if jp
     * @brief preServiceFinalize コールバック関数
     * TODO: Documentation
     * @else
     * @brief preServiceFinalize callback function
     * TODO: Documentation
     * @endif
     */
    virtual void preServiceFinalize(std::string service_name,
                                    RTM::LocalServiceBase* service);
  };



  /*!
   * @if jp
   * @class ManagerActionListeners
   * @brief ManagerActionListeners クラス
   *
   *
   * @else
   * @class ManagerActionListeners
   * @brief ManagerActionListeners class
   *
   *
   * @endif
   */
  class ManagerActionListeners
  {
  public:
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
    ~ManagerActionListeners();
    ManagerActionListenerHolder manager_;
    ModuleActionListenerHolder module_;
    RtcLifecycleActionListenerHolder rtclifecycle_;
    NamingActionListenerHolder naming_;
    LocalServiceActionListenerHolder localservice_;
  };
} // namespace RTM

#endif  // RTC_MANAGERACTIONLISTENER_H

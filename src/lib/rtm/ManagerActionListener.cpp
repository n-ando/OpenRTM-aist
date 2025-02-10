// -*- C++ -*-
/*!
 * @file ManagerActionListener.cpp
 * @brief Component action listener class
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

#include <rtm/ManagerActionListener.h>

namespace RTM
{

  //============================================================
  /*!
   * @if jp
   * @class ManagerActionListener クラス
   * @else
   * @class ManagerActionListener class
   * @endif
   */
  ManagerActionListener::~ManagerActionListener() = default;

  /*!
   * @if jp
   * @class ManagerActionListenerHolder クラス
   * @else
   * @class ManagerActionListenerHolder class
   * @endif
   */
  ManagerActionListenerHolder::~ManagerActionListenerHolder() = default;

  /*!
   * @if jp
   * @class ManagerActionListeners クラス
   * @else
   * @class ManagerActionListeners class
   * @endif
   */
  ManagerActionListeners::~ManagerActionListeners() = default;

  /*!
   * @if jp
   * @brief preShutdown コールバック関数
   * TODO: Documentation
   * @else
   * @brief preShutdown callback function
   * TODO: Documentation
   * @endif
   */
  void ManagerActionListenerHolder::preShutdown()
  {
    LISTENERHOLDER_CALLBACK(preShutdown, ());
  }

  /*!
   * @if jp
   * @brief postShutdown コールバック関数
   * TODO: Documentation
   * @else
   * @brief postShutdown callback function
   * TODO: Documentation
   * @endif
   */
  void ManagerActionListenerHolder::postShutdown()
  {
    LISTENERHOLDER_CALLBACK(postShutdown, ());
  }

  /*!
   * @if jp
   * @brief preReinit コールバック関数
   * TODO: Documentation
   * @else
   * @brief preReinit callback function
   * TODO: Documentation
   * @endif
   */
  void ManagerActionListenerHolder::preReinit()
  {
    LISTENERHOLDER_CALLBACK(preReinit, ());
  }

  /*!
   * @if jp
   * @brief postReinit コールバック関数
   * TODO: Documentation
   * @else
   * @brief postReinit callback function
   * TODO: Documentation
   * @endif
   */
  void ManagerActionListenerHolder::postReinit()
  {
    LISTENERHOLDER_CALLBACK(postReinit, ());
  }


  //============================================================
  /*!
   * @if jp
   * @class ModuleActionListener クラス
   * @else
   * @class ModuleActionListener class
   * @endif
   */
  ModuleActionListener::~ModuleActionListener() = default;

  /*!
   * @if jp
   * @class ModuleActionListener ホルダクラス
   * @else
   * @class ModuleActionListener holder class
   * @endif
   */
  ModuleActionListenerHolder::~ModuleActionListenerHolder() = default;

  /*!
   * @if jp
   * @brief preLoad コールバック関数
   * TODO: Documentation
   * @else
   * @brief preLoad callback function
   * TODO: Documentation
   * @endif
   */
  void ModuleActionListenerHolder::preLoad(std::string& modname,
                                           std::string& funcname)
  {
    LISTENERHOLDER_CALLBACK(preLoad, (modname, funcname));
  }

  /*!
   * @if jp
   * @brief postLoad コールバック関数
   * TODO: Documentation
   * @else
   * @brief postLoad callback function
   * TODO: Documentation
   * @endif
   */
  void ModuleActionListenerHolder::postLoad(std::string& modname,
                                            std::string& funcname)
  {
    LISTENERHOLDER_CALLBACK(postLoad, (modname, funcname));
  }

  /*!
   * @if jp
   * @brief preUnload コールバック関数
   * TODO: Documentation
   * @else
   * @brief preUnload callback function
   * TODO: Documentation
   * @endif
   */
  void ModuleActionListenerHolder::preUnload(std::string& modname)
  {
    LISTENERHOLDER_CALLBACK(preUnload, (modname));
  }

  /*!
   * @if jp
   * @brief postUnload コールバック関数
   * TODO: Documentation
   * @else
   * @brief postUnload callback function
   * TODO: Documentation
   * @endif
   */
  void ModuleActionListenerHolder::postUnload(std::string& modname)
  {
    LISTENERHOLDER_CALLBACK(postUnload, (modname));
  }


  //============================================================
  /*!
   * @if jp
   * @class RtcLifecycleActionListener クラス
   * @brief RtcLifecycleActionListener クラス
   * @else
   * @class RtcLifecycleActionListener class
   * @brief RtcLifecycleActionListener class
   * @endif
   */
  RtcLifecycleActionListener::~RtcLifecycleActionListener() = default;

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  RtcLifecycleActionListenerHolder::~RtcLifecycleActionListenerHolder() = default;

  /*!
   * @if jp
   * @brief preCreate コールバック関数
   * TODO: Documentation
   * @else
   * @brief preCreate callback function
   * TODO: Documentation
   * @endif
   */
  void RtcLifecycleActionListenerHolder::preCreate(std::string& args)
  {
    LISTENERHOLDER_CALLBACK(preCreate, (args));
  }

  /*!
   * @if jp
   * @brief postCreate コールバック関数
   * TODO: Documentation
   * @else
   * @brief postCreate callback function
   * TODO: Documentation
   * @endif
   */
  void RtcLifecycleActionListenerHolder::postCreate(RTC::RTObject_impl* rtobj)
  {
    LISTENERHOLDER_CALLBACK(postCreate, (rtobj));
  }

  /*!
   * @if jp
   * @brief preConfigure コールバック関数
   * TODO: Documentation
   * @else
   * @brief preConfigure callback function
   * TODO: Documentation
   * @endif
   */
  void RtcLifecycleActionListenerHolder::preConfigure(coil::Properties& prop)
  {
    LISTENERHOLDER_CALLBACK(preConfigure, (prop));
  }

  /*!
   * @if jp
   * @brief postConfigure コールバック関数
   * TODO: Documentation
   * @else
   * @brief postConfigure callback function
   * TODO: Documentation
   * @endif
   */
  void RtcLifecycleActionListenerHolder::postConfigure(coil::Properties& prop)
  {
    LISTENERHOLDER_CALLBACK(postConfigure, (prop));
  }

  /*!
   * @if jp
   * @brief preInitialize コールバック関数
   * TODO: Documentation
   * @else
   * @brief preInitialize callback function
   * TODO: Documentation
   * @endif
   */
  void RtcLifecycleActionListenerHolder::preInitialize()
  {
    LISTENERHOLDER_CALLBACK(preInitialize, ());
  }

  /*!
   * @if jp
   * @brief postInitialize コールバック関数
   * TODO: Documentation
   * @else
   * @brief postInitialize callback function
   * TODO: Documentation
   * @endif
   */
  void RtcLifecycleActionListenerHolder::postInitialize()
  {
    LISTENERHOLDER_CALLBACK(postInitialize, ());
  }


  //============================================================
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  NamingActionListener::~NamingActionListener() = default;

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  NamingActionListenerHolder::~NamingActionListenerHolder() = default;

  /*!
   * @if jp
   * @brief preBind コールバック関数
   * TODO: Documentation
   * @else
   * @brief preBind callback function
   * TODO: Documentation
   * @endif
   */
  void NamingActionListenerHolder::preBind(RTC::RTObject_impl* rtobj,
                                           coil::vstring& name)
  {
    LISTENERHOLDER_CALLBACK(preBind, (rtobj, name));
  }

  /*!
   * @if jp
   * @brief postBind コールバック関数
   * TODO: Documentation
   * @else
   * @brief postBind callback function
   * TODO: Documentation
   * @endif
   */
  void NamingActionListenerHolder::postBind(RTC::RTObject_impl* rtobj,
                                            coil::vstring& name)
  {
    LISTENERHOLDER_CALLBACK(postBind, (rtobj, name));
  }

  /*!
   * @if jp
   * @brief preUnbind コールバック関数
   * TODO: Documentation
   * @else
   * @brief preUnbind callback function
   * TODO: Documentation
   * @endif
   */
  void NamingActionListenerHolder::preUnbind(RTC::RTObject_impl* rtobj,
                                             coil::vstring& name)
  {
    LISTENERHOLDER_CALLBACK(preUnbind, (rtobj, name));
  }

  /*!
   * @if jp
   * @brief postUnbind コールバック関数
   * TODO: Documentation
   * @else
   * @brief postUnbind callback function
   * TODO: Documentation
   * @endif
   */
  void NamingActionListenerHolder::postUnbind(RTC::RTObject_impl* rtobj,
                                              coil::vstring& name)
  {
    LISTENERHOLDER_CALLBACK(postUnbind, (rtobj, name));
  }


  //============================================================
  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  LocalServiceActionListener::~LocalServiceActionListener() = default;

  /*!
   * @if jp
   * @brief デストラクタ
   * @else
   * @brief Destructor
   * @endif
   */
  LocalServiceActionListenerHolder::~LocalServiceActionListenerHolder() = default;

  /*!
   * @if jp
   * @brief preServiceRegister コールバック関数
   * TODO: Documentation
   * @else
   * @brief preServiceRegister callback function
   * TODO: Documentation
   * @endif
   */
  void LocalServiceActionListenerHolder::
  preServiceRegister(std::string service_name)
  {
    LISTENERHOLDER_CALLBACK(preServiceRegister, (service_name));
  }

  /*!
   * @if jp
   * @brief postServiceRegister コールバック関数
   * TODO: Documentation
   * @else
   * @brief postServiceRegister callback function
   * TODO: Documentation
   * @endif
   */
  void LocalServiceActionListenerHolder::
  postServiceRegister(std::string service_name, RTM::LocalServiceBase* service)
  {
    LISTENERHOLDER_CALLBACK(postServiceRegister, (service_name, service));
  }

  /*!
   * @if jp
   * @brief preServiceInit コールバック関数
   * TODO: Documentation
   * @else
   * @brief preServiceInit callback function
   * TODO: Documentation
   * @endif
   */
  void LocalServiceActionListenerHolder::
  preServiceInit(coil::Properties& prop, RTM::LocalServiceBase* service)
  {
    LISTENERHOLDER_CALLBACK(preServiceInit, (prop, service));
  }

  /*!
   * @if jp
   * @brief postServiceInit コールバック関数
   * TODO: Documentation
   * @else
   * @brief postServiceInit callback function
   * TODO: Documentation
   * @endif
   */
  void LocalServiceActionListenerHolder::
  postServiceInit(coil::Properties& prop, RTM::LocalServiceBase* service)
  {
    LISTENERHOLDER_CALLBACK(postServiceInit, (prop, service));
  }

  /*!
   * @if jp
   * @brief preServiceReinit コールバック関数
   * TODO: Documentation
   * @else
   * @brief preServiceReinit callback function
   * TODO: Documentation
   * @endif
   */
  void LocalServiceActionListenerHolder::
  preServiceReinit(coil::Properties& prop, RTM::LocalServiceBase* service)
  {
    LISTENERHOLDER_CALLBACK(preServiceReinit, (prop, service));
  }

  /*!
   * @if jp
   * @brief postServiceReinit コールバック関数
   * TODO: Documentation
   * @else
   * @brief postServiceReinit callback function
   * TODO: Documentation
   * @endif
   */
  void LocalServiceActionListenerHolder::
  postServiceReinit(coil::Properties& prop, RTM::LocalServiceBase* service)
  {
    LISTENERHOLDER_CALLBACK(postServiceReinit, (prop, service));
  }

  /*!
   * @if jp
   * @brief postServiceFinalize コールバック関数
   * TODO: Documentation
   * @else
   * @brief postServiceFinalize callback function
   * TODO: Documentation
   * @endif
   */
  void LocalServiceActionListenerHolder::
  postServiceFinalize(std::string service_name, RTM::LocalServiceBase* service)
  {
    LISTENERHOLDER_CALLBACK(postServiceFinalize, (service_name, service));
  }

  /*!
   * @if jp
   * @brief preServiceFinalize コールバック関数
   * TODO: Documentation
   * @else
   * @brief preServiceFinalize callback function
   * TODO: Documentation
   * @endif
   */
  void LocalServiceActionListenerHolder::
  preServiceFinalize(std::string service_name, RTM::LocalServiceBase* service)
  {
    LISTENERHOLDER_CALLBACK(preServiceFinalize, (service_name, service));
  }

} // namespace RTM

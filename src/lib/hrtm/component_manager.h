// -*- C++ -*-
/*!
 * @file component_manager.h
 * @brief RTC::Manager wrapper class for hrtm::ComponentManager
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2016
 *     Noriaki Ando
 *     National Institute of
 *     Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef HRTM_COMPONENT_MANAGER_H
#define HRTM_COMPONENT_MANAGER_H

#include <rtm/Manager.h>
#include <rtm/Factory.h>
//#include <rtm/RTObject.h>
#include <coil/Guard.h>
#include <coil/Mutex.h>
//#include <hrtm/data_flow_component.h>
//#include <hrtm/logger.h>

namespace RTC
{
  class RTObject_impl;
};
namespace hrtm
{
  //------------------------------------------------------------
  // Creator and Destructor tempaltes for RTC factory
  //
  template <class _New>
  RTC::RTObject_impl* Create(RTC::Manager* manager)
  {
    return new _New();
  }

  template <class _Delete>
  void Delete(RTC::RTObject_impl* rtc)
  {
    delete rtc;
  }
  //------------------------------------------------------------

  // forward decl
  class DataFlowComponent;
  class ComponentManager;
  typedef void (*ModuleInitProc)(hrtm::ComponentManager*);

  /*!
   * @class RTC::Manager wrapper for hrtm::ComponentManager
   */
  class ComponentManager
    : public RTC::Manager
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;

  public:
    template<typename CompType>
    bool regist(coil::Properties* profile, const char*, const char*)
    {
      return RTC::Manager::
        registerFactory(*profile,
                        (RTC::RtcNewFunc)hrtm::Create<CompType>,
                        (RTC::RtcDeleteFunc)hrtm::Delete<CompType> );
    }

    virtual DataFlowComponent* create_component(const char* component_name);
    virtual void set_init_proc(void(*init_proc)(hrtm::ComponentManager*));
    virtual bool activate();
    virtual void run(bool non_block = false);

    // static members
    static void init_proc(RTC::Manager* mgr);
    static ComponentManager& instance(int argc, char** argv);

  protected:
    ComponentManager();

  protected:
    static ModuleInitProc initProc;
    static ComponentManager* manager;
    static coil::Mutex mutex;
  };
};

#endif // HRTM_COMPONENT_MANAGER_H

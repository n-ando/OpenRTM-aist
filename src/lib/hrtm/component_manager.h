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
#include <mutex>

namespace RTC
{
  class RTObject_impl;
} // namespace RTC
namespace hrtm
{
  //------------------------------------------------------------
  // Creator and Destructor tempaltes for RTC factory
  //
  template <class T_New>
  RTC::RTObject_impl* Create(RTC::Manager* /* manager */)
  {
    return new T_New();
  }

  template <class T_Delete>
  void Delete(RTC::RTObject_impl* rtc)
  {
    delete rtc;
  }
  //------------------------------------------------------------

  // forward decl
  class DataFlowComponent;
  class ComponentManager;
  using ModuleInitProc = void (*)(hrtm::ComponentManager*);

  /*!
   * @class RTC::Manager wrapper for hrtm::ComponentManager
   */
  class ComponentManager
    : public RTC::Manager
  {

  public:
    template<typename CompType>
    bool regist(coil::Properties* profile, const char* /*unused*/, const char* /*unused*/)
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
    virtual ~ComponentManager();

  protected:
    static ModuleInitProc initProc;
    static ComponentManager* manager;
    static std::mutex mutex;
  };
} // namespace hrtm

#endif // HRTM_COMPONENT_MANAGER_H

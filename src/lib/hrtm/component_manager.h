#ifndef HRTM_COMPONENT_MANAGER_H
#define HRTM_COMPONENT_MANAGER_H

#include <rtm/Manager.h>
#include <rtm/Factory.h>
#include <rtm/RTObject.h>
#include <coil/Guard.h>
#include <coil/Mutex.h>
//#include <hrtm/data_flow_component.h>
#include <hrtm/logger.h>

namespace hrtm
{
  class DataFlowComponent;


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
  class ComponentManager;
  typedef void (*ModuleInitProc)(hrtm::ComponentManager*);
//  class MyModuleInit
//  {
//    ModuleInitProc m_initProc;
//  public:
//    MyModuleInit(ModuleInitProc proc)
//      : m_initProc(proc)
//    {
//    }
//    void operator()(RTC::Manager* mgr)
//    {
//      m_initProc(dynamic_cast<hrtm::ComponentManager*>(mgr));
//    }
//  };
//  ModuleInitProc g_m;
//  void Proc(RTC::Manager* mgr)
//  {
//    g_m(dynamic_cast<hrtm::ComponentManager*>(mgr));
//  }

  //void ModuleInit(hrtm::ComponentManager* manager)
  
  class ComponentManager
    : public RTC::Manager
  {
    typedef coil::Mutex Mutex;
    typedef coil::Guard<Mutex> Guard;
  public:
    template<typename CompType>
    bool regist(coil::Properties* profile,  const char*, const char*)
    {
      return RTC::Manager::
        registerFactory(*profile,
                        (RTC::RtcNewFunc)hrtm::Create<CompType>,
                        (RTC::RtcDeleteFunc)hrtm::Delete<CompType> );
    }

    virtual DataFlowComponent* create_component(const char* component_name)
    {
      return NULL; // createComponent(component_name);
    }
    static void init_proc(RTC::Manager* mgr)
    {
      ::hrtm::ComponentManager::initProc(manager);
    }
    virtual void set_init_proc(void(*init_proc)(hrtm::ComponentManager*))
    {
      initProc = init_proc;
      setModuleInitProc(hrtm::ComponentManager::init_proc);
    }
    virtual bool activate()
    {
      return activateManager();
    }
    virtual void run(bool non_block = false)
    {
      runManager(non_block);
    }
    static ComponentManager& instance(int argc, char** argv)
    {
      // DCL for singleton
      if (!manager)
        {
          Guard guard(mutex);
          if (!manager)
            {
              manager = new ComponentManager();
              manager->initManager(argc, argv);
              manager->initLogger();
              manager->initORB();
              manager->initNaming();
              manager->initFactories();
              manager->initExecContext();
              manager->initComposite();
              manager->initTimer();
              manager->initManagerServant();
            }
        }
      return *manager;
    }
  protected:
    ComponentManager()
      : RTC::Manager()
    {
    }
    static ModuleInitProc initProc;
    static ComponentManager* manager;
    static coil::Mutex mutex;
  };
};

#endif // HRTM_COMPONENT_MANAGER_H

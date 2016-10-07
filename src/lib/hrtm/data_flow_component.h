#ifndef HRTM_DATA_FLOW_COMPONENT_H
#define HRTM_DATA_FLOW_COMPONENT_H

#include <rtm/DataFlowComponentBase.h>
#include <hrtm/component_manager.h>
#include <hrtm/defs.h>
#include <hrtm/in_port.h>

namespace RTC
{
  enum StatusKind
    {
      FSM_STATUS
    };
};
namespace hrtm
{
#define COMPONENT_NAME(comp_name) #comp_name

  //  typedef RTC::DataFlowComponent DataFlowComponent;
  //  using DataFlowComponent = RTC::DataFlowComponentBase;
  class DataFlowComponent
    : public RTC::DataFlowComponentBase
  {
  public:
    DataFlowComponent()
      : RTC::DataFlowComponentBase(&RTC::Manager::instance())
    {
    }
//    DataFlowComponent(RTC::Manager* mgr)
//      : RTC::DataFlowComponentBase(mgr)
//    {
//    }
    virtual RTC::ReturnCode_t initialize(hrtm::ComponentManager* mgr)
    {
      return RTC::RTC_OK;
    }
    void updateFsmStatus(RTC::StatusKind status_kind, const char* state)
    {
    }
  };
};

#endif // HRTM_DATA_FLOW_COMPONENT_H

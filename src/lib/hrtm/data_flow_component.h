// -*- C++ -*-
/*!
 * @file data_flow_component.h
 * @brief RTC::DataFlowComponent wrapper class for hrtm::DataFlowComponent
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
#ifndef HRTM_DATA_FLOW_COMPONENT_H
#define HRTM_DATA_FLOW_COMPONENT_H

#include <rtm/DataFlowComponentBase.h>
#include <hrtm/defs.h>
#include <hrtm/properties.h>
#include <hrtm/logger.h>
#include <hrtm/component_manager.h>
#include <hrtm/in_port.h>
#include <hrtm/out_port.h>

#define COMPONENT_NAME(comp_name) #comp_name

namespace RTC
{
  enum StatusKind
    {
      FSM_STATUS
    };
} // namespace RTC

namespace hrtm
{
  class ComponentManager;
  class DataFlowComponent
    : public RTC::DataFlowComponentBase
  {
  public:
    DataFlowComponent();
    ~DataFlowComponent() override;
    RTC::ReturnCode_t initialize() override;
    virtual void updateFsmStatus(RTC::StatusKind status_kind,
                                 const char* state);
  };
} // namespace hrtm

#endif // HRTM_DATA_FLOW_COMPONENT_H

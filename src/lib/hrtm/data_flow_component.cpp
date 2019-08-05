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
#include <hrtm/data_flow_component.h>

namespace hrtm
{
  DataFlowComponent::DataFlowComponent()
    : RTC::DataFlowComponentBase(&RTC::Manager::instance())
  {
  }
  DataFlowComponent::~DataFlowComponent() = default;
  RTC::ReturnCode_t DataFlowComponent::initialize()
  {
    return RTC::RTC_OK;
  }

  void DataFlowComponent::updateFsmStatus(RTC::StatusKind /*status_kind*/,
                                          const char* state)
  {
    postOnFsmStateChange(state, RTC::RTC_OK);
  }
} // namespace hrtm

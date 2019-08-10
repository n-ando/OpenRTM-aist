// -*- C++ -*-
/*!
 * @file out_port.h
 * @brief RTC::OutPort wrapper class for hrtm::OutPort 
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
#ifndef HRTM_OUT_PORT_H
#define HRTM_OUT_PORT_H

#include <rtm/OutPort.h>

namespace hrtm
{
#ifndef CXX11
  template <class DataType>
  class OutPort
    : public RTC::OutPort<DataType>
  {
  public:
    OutPort(const char* name, DataType& data)
      : RTC::OutPort<DataType>(name, data)
    {
    }
    virtual ~OutPort() = default;
  };
#else
  template<class DataType>
  using OutPort = RTC::OutPort<DataType>;
#endif
} // namespace hrtm

#endif // HRT_OUT_PORT_H

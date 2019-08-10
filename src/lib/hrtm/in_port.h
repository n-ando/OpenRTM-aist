// -*- C++ -*-
/*!
 * @file in_port.h
 * @brief RTC::InPort wrapper class for hrtm::InPort 
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
#ifndef HRTM_IN_PORT_H
#define HRTM_IN_PORT_H

#include <rtm/InPort.h>

namespace hrtm
{
#ifndef CXX11
  template <class DataType>
  class InPort
    : public RTC::InPort<DataType>
  {
  public:
    InPort(const char* name, DataType& data)
      : RTC::InPort<DataType>(name, data)
    {
    }
    virtual ~InPort() = default;
  };
#else
  template<class DataType>
  using InPort = RTC::InPort<DataType>;
#endif
} // namespace hrtm

#endif // HRTM_IN_PORT_H

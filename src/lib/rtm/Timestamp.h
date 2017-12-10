// -*- C++ -*-
/*!
 * @file Timestamp.h
 * @brief Timestamp listener class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2017
 *     Noriaki Ando
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTM_TIMESTAMP_H
#define RTM_TIMESTAMP_H

#include <rtm/ConnectorListener.h>

namespace RTC
{
  template <class DataType>
  class Timestamp
    : public ConnectorDataListenerT<DataType>
  {
    USE_CONNLISTENER_STATUS;
  public:
    Timestamp(const char* ts_type) : m_tstype(ts_type) {}
    virtual ~Timestamp() {}
    virtual ReturnCode operator()(ConnectorInfo& info, DataType& data)
    {
      if (info.properties["timestamp_policy"] != m_tstype)
        {
          return NO_CHANGE;
        }
      coil::TimeValue tm(coil::gettimeofday());
      data.tm.sec  = tm.sec();
      data.tm.nsec = tm.usec() * 1000;
      return DATA_CHANGED;
    }
    std::string m_tstype;
  };
}; // End of namesepace RTM

#endif // RTM_TIMESTAMP_H

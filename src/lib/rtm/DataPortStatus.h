/*! -*- C++ -*-
 *
 * @file PushConnector.h
 * @brief Push type connector class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef RTC_DATAPORTSTATUS_H
#define RTC_DATAPORTSTATUS_H

namespace RTC
{
  class DataPortStatus
  {
  public:
    enum Enum
      {
        PORT_OK = 0,
        PORT_ERROR,
        BUFFER_FULL,
        BUFFER_EMPTY,
        BUFFER_TIMEOUT,
        SEND_FULL,
        SEND_TIMEOUT,
        RECV_EMPTY,
        RECV_TIMEOUT,
        INVALID_ARGS,
        PRECONDITION_NOT_MET,
        CONNECTION_LOST,
        CORBA_ERROR,
        UNKNOWN_ERROR
      };

    static const char* toString(DataPortStatus::Enum status)
    {
      const char* str[] = {
        "PORT_OK",
        "PORT_ERROR",
        "BUFFER_FULL",
        "BUFFER_EMPTY",
        "BUFFER_TIMEOUT",
        "SEND_FULL",
        "SEND_TIMEOUT",
        "RECV_EMPTY",
        "RECV_TIMEOUT",
        "INVALID_ARGS",
        "PRECONDITION_NOT_MET",
        "CONNECTION_LOST",
        "CORBA_ERROR",
        "UNKNOWN_ERROR"
      };
      return str[status];
    }
  };
};

#define DATAPORTSTATUS_ENUM \
  typedef ::RTC::DataPortStatus::Enum ReturnCode;       \
  using ::RTC::DataPortStatus::PORT_OK;                 \
  using ::RTC::DataPortStatus::PORT_ERROR;              \
  using ::RTC::DataPortStatus::BUFFER_FULL;             \
  using ::RTC::DataPortStatus::BUFFER_EMPTY;            \
  using ::RTC::DataPortStatus::BUFFER_TIMEOUT;          \
  using ::RTC::DataPortStatus::SEND_FULL;               \
  using ::RTC::DataPortStatus::SEND_TIMEOUT;            \
  using ::RTC::DataPortStatus::RECV_EMPTY;              \
  using ::RTC::DataPortStatus::RECV_TIMEOUT;            \
  using ::RTC::DataPortStatus::INVALID_ARGS;            \
  using ::RTC::DataPortStatus::PRECONDITION_NOT_MET;    \
  using ::RTC::DataPortStatus::CONNECTION_LOST;         \
  using ::RTC::DataPortStatus::CORBA_ERROR;


#endif // RTC_DATAPORTSTATUS_H

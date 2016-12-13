// -*- C++ -*-
/*!
 *
 * @file BufferStatus.h
 * @brief Buffer status enum definition
 * @date $Date: 2007-12-31 03:06:12 $
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
 * $Id: BufferBase.h 1226 2009-02-28 02:31:22Z n-ando $
 */

#ifndef RTC_BUFFERSTATUS_H
#define RTC_BUFFERSTATUS_H

namespace RTC
{
  class BufferStatus
  {
  public:
    enum Enum
      {
        BUFFER_OK = 0,
        BUFFER_ERROR,
        BUFFER_FULL,
        BUFFER_EMPTY,
        NOT_SUPPORTED,
        TIMEOUT,
        PRECONDITION_NOT_MET
      };

    static const char* toString(Enum status)
    {
      const char* str[] = {
        "BUFFER_OK",
        "BUFFER_ERROR",
        "BUFFER_FULL",
        "BUFFER_EMPTY",
        "NOT_SUPPORTED",
        "TIMEOUT",
        "PRECONDITION_NOT_MET"
      };
      return str[status];
    }
  };
}; // namespace RTC

#define BUFFERSTATUS_ENUM \
  typedef ::RTC::BufferStatus::Enum ReturnCode;       \
  using ::RTC::BufferStatus::BUFFER_OK;               \
  using ::RTC::BufferStatus::BUFFER_ERROR;            \
  using ::RTC::BufferStatus::BUFFER_FULL;             \
  using ::RTC::BufferStatus::BUFFER_EMPTY;            \
  using ::RTC::BufferStatus::NOT_SUPPORTED;           \
  using ::RTC::BufferStatus::TIMEOUT;                 \
  using ::RTC::BufferStatus::PRECONDITION_NOT_MET;

#endif // RTC_BUFFERSTATUS_H

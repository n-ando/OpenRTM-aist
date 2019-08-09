// -*- C++ -*-
/*!
 * @file logger.h
 * @brief RTC::Logger wrapper class for hrtm::Logger
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
#ifndef HRTM_LOGGER_H
#define HRTM_LOGGER_H

#include <rtm/SystemLogger.h>

#define HRTM_ERROR(name, text)
#define HRTM_ERROR_STR RTC_ERROR_STR
#define HRTM_WARNING(name, text)
#define HRTM_WARN_STR RTC_WARN_STR
#define HRTM_NORMAL(name, text)
#define HRTM_NORMAL_STR RTC_NORMAL_STR
#define HRTM_INFO(name, text)
#define HRTM_INFO_STR RTC_INFO_STR
#define HRTM_DEBUG(name, text)
#define HRTM_DEBUG_STR RTC_DEBUG_STR
#define HRTM_TRACE(name, text)
#define HRTM_TRACE_STR RTC_TRACE_STR
#define HRTM_VERBOSE(name, text)
#define HRTM_VERBOSE_STR RTC_VERBOSE_STR
#define HRTM_PARANOID(name, text)
#define HRTM_PARANOID_STR RTC_PARANOID_STR

namespace hrtm
{
  namespace utils
  {
#ifndef CXX11
    class Logger
      : public RTC::Logger
    {
    public:
    };
#else
    using Logger = RTC::Logger;
#endif // CXX11
  } // namespace utils
} // namespace hrtm
#endif // HRTM_LOGGER_H


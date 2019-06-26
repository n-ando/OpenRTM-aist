// -*- C++ -*-
/*!
 * @file ClockManager.cpp
 * @brief Global clock management class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2012
 *     Noriaki Ando
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <coil/Time.h>
#include <coil/ClockManager.h>
#include <mutex>

#include <string>

namespace coil
{
  //============================================================
  // System Clock
  //============================================================
  SystemClock::~SystemClock()
  {
  }
  coil::TimeValue SystemClock::gettime() const
  {
    auto now = std::chrono::system_clock::now().time_since_epoch();
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(now);
    auto usec = std::chrono::duration_cast<std::chrono::microseconds>(now - sec);
    return coil::TimeValue(static_cast<long>(sec.count()),
                           static_cast<long>(usec.count()));
  }
  bool SystemClock::settime(coil::TimeValue /* clocktime */)
  {
      // OpenRTM-aist do not set the System Clock.
      return true;
  }
  //
  //============================================================

  //============================================================
  // Logical Time Clock
  //============================================================
  LogicalClock::LogicalClock()
    : m_currentTime(0.0)
  {
  }

  LogicalClock::~LogicalClock()
  {
  }

  coil::TimeValue LogicalClock::gettime() const
  {
    std::lock_guard<std::mutex> guard(m_currentTimeMutex);
    return m_currentTime;
  }

  bool LogicalClock::settime(coil::TimeValue clocktime)
  {
    std::lock_guard<std::mutex> guard(m_currentTimeMutex);
    m_currentTime = clocktime;
    return true;
  }
  //
  //============================================================

  //============================================================
  // Adjusted Clock
  //============================================================
  AdjustedClock::AdjustedClock()
  {
  }

  AdjustedClock::~AdjustedClock()
  {
  }

  coil::TimeValue AdjustedClock::gettime() const
  {
    std::lock_guard<std::mutex> guard(m_offsetMutex);
    auto time = std::chrono::steady_clock::now() - m_offset;
    return TimeValue(std::chrono::duration<double>(time).count());
  }

  bool AdjustedClock::settime(coil::TimeValue clocktime)
  {
    std::lock_guard<std::mutex> guard(m_offsetMutex);
    m_offset = std::chrono::steady_clock::now() - clocktime.microseconds();
    return true;
  }

  IClock& ClockManager::getClock(const std::string& clocktype)
  {
    if (clocktype == "logical")
      {
        return m_logicalClock;
      }
    else if (clocktype == "adjusted")
      {
        return m_adjustedClock;
      }
    else if (clocktype == "system")
      {
        return m_systemClock;
      }
    else
      {
      }
    return m_systemClock;
  }

#ifdef WIN32
  ClockManager* ClockManager::clockmgr = nullptr;
  std::mutex ClockManager::clockmgr_mutex;
  ClockManager& ClockManager::instance()
  {
    if (clockmgr == nullptr)
      {
        std::lock_guard<std::mutex> guard(clockmgr_mutex);
        if (clockmgr == nullptr)
          {
            clockmgr = new ClockManager();
          }
      }
    return *clockmgr;
  }
#endif
} // namespace coil

// -*- C++ -*-
/*!
 * @file Timer.cpp
 * @brief Timer class
 * @date $Date: 2007-07-20 16:12:58 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: Timer.cpp 826 2008-08-26 08:13:39Z n-ando $
 *
 */

#include <coil/Timer.h>

namespace coil
{
  /*!
   * @if jp
   * @brief 1回の時間経過
   * @else
   * @brief Tick
   * @endif
   */
  bool DelayedFunction::tick(std::chrono::nanoseconds interval)
  {
    m_remains -= interval;
    bool is_expired = m_remains <= std::chrono::seconds::zero();
    if (is_expired) { m_fn(); }
    return is_expired;
  }

  /*!
   * @if jp
   * @brief 1回の時間経過
   * @else
   * @brief Tick
   * @endif
   */
  bool PeriodicFunction::tick(std::chrono::nanoseconds interval)
  {
    std::lock_guard<std::mutex> guard(m_lock);
    if (m_isRemoved) { return true; }
    m_remains -= interval;
    if (m_remains <= std::chrono::seconds::zero())
      {
        m_fn();
        m_remains = m_period;
      }
    return false;
  }

  /*!
   * @if jp
   * @brief 周期実行を停止する
   * @else
   * @brief Stop to execute function
   * @endif
   */
  void PeriodicFunction::stop()
  {
    std::lock_guard<std::mutex> guard(m_lock);
    m_isRemoved = true;
  }
} // namespace coil

// -*- C++ -*-
/*!
 * @file Timevalue.cpp
 * @brief Timevalue class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <coil/TimeValue.h>

namespace coil
{
  /*!
   * @if jp
   * @brief ƒRƒ“ƒXƒgƒ‰ƒNƒ^
   * @else
   * @brief Constructor
   * @endif
   */
  TimeValue::TimeValue(long sec, long usec)
  {
    m_sec = sec;
    m_usec = usec;
    normalize();
  }
  
  TimeValue::TimeValue(double timeval)
  {
    double dbHalfAdj;
    if ( timeval >= 0 ) 
    {
        dbHalfAdj = +0.5;
    }
    else
    {
        dbHalfAdj = -0.5;
    }
    m_sec = (long int)timeval;
    m_usec = (long)((timeval - (double)m_sec)*TIMEVALUE_ONE_SECOND_IN_USECS + dbHalfAdj );
    normalize();
  }
  
  /*!
   * @if jp
   * @brief ŽžŠÔŒ¸ŽZ
   * @else
   * @brief Time subtraction
   * @endif
   */
  TimeValue TimeValue::operator-(TimeValue& tm)
  {
    TimeValue res;
    if (m_sec >= tm.m_sec) // +
      {
        if (m_usec >= tm.m_usec) // ŒJ‚è‰º‚ª‚è–³‚µ
          {
            res.m_sec  = m_sec  - tm.m_sec;  // -
            res.m_usec = m_usec - tm.m_usec; // +
          }
        else // m_usec < tm.m_usec ŒJ‚è‰º‚ª‚è—L‚è
          {
            res.m_sec  = m_sec  - tm.m_sec - 1;
            res.m_usec = (m_usec + 1000000) - tm.m_usec;
          }
      }
    else // m_sec < tm.m_sec // -
      {
          if (tm.m_usec >= m_usec) // ŒJ‚è‰º‚ª‚è–³‚µ
            {
              res.m_sec  = - (tm.m_sec  - m_sec); // +
              res.m_usec = - (tm.m_usec - m_usec);  // +
            }
          else // tm.m_usec < m_usec ŒJ‚è‰º‚ª‚è—L‚è
            {
              res.m_sec  = - (tm.m_sec - m_sec  - 1);
              res.m_usec = - (tm.m_usec + 1000000) + m_usec;
            }
      }
    res.normalize();
    return res;
  }
  
  /*!
   * @if jp
   * @brief ŽžŠÔ‰ÁŽZ
   * @else
   * @brief Time addition
   * @endif
   */
  TimeValue TimeValue::operator+(TimeValue& tm)
  {
    TimeValue res;
    res.m_sec  = m_sec  + tm.m_sec;
    res.m_usec = m_usec + tm.m_usec;
    if (res.m_usec >= 1000000)
      {
        ++res.m_sec;
        res.m_usec -= 1000000;
      }
    res.normalize();
    return res;
  }
  
  /*!
   * @if jp
   * @brief doubleŒ^¨ŽžŠÔŒ^•ÏŠ·
   * @else
   * @brief Convert double type into time type
   * @endif
   */
  TimeValue TimeValue::operator=(double time)
  {
   double dbHalfAdj;
   if ( time >= 0 ) 
   {
       dbHalfAdj = +0.5;
   }
   else
   {
       dbHalfAdj = -0.5;
   }

    m_sec = (long)time;
    m_usec = (long)((time - (double)m_sec)*TIMEVALUE_ONE_SECOND_IN_USECS + dbHalfAdj);
    normalize();
    return *this;
  }
  
  /*!
   * @if jp
   * @brief ŽžŠÔŒ^¨doubleŒ^•ÏŠ·
   * @else
   * @brief Convert time type into double type
   * @endif
   */
  TimeValue::operator double() const
  {
    return (double)m_sec + ((double)m_usec/TIMEVALUE_ONE_SECOND_IN_USECS);
  }
  
  /*!
   * @if jp
   * @brief •„†”»’è
   * @else
   * @brief Sign judgment
   * @endif
   */
  int TimeValue::sign() const
  {
    if (m_sec > 0) return 1;
    if (m_sec < 0) return -1;
    if (m_usec > 0) return 1;
    if (m_usec < 0) return -1;
    return 0;
  }
  
  /*!
   * @if jp
   * @brief ³‹K‰»
   * @else
   * @brief Normalize
   * @endif
   */
  void TimeValue::normalize()
  {
    if (m_usec >= TIMEVALUE_ONE_SECOND_IN_USECS)
      {
        do
          {
            ++m_sec;
            m_usec -= TIMEVALUE_ONE_SECOND_IN_USECS;
          }
        while (m_usec >= TIMEVALUE_ONE_SECOND_IN_USECS);
      }
    else if (m_usec <= -TIMEVALUE_ONE_SECOND_IN_USECS)
      {
        do
          {
            --m_sec;
            m_usec += TIMEVALUE_ONE_SECOND_IN_USECS;
          }
        while (m_usec <= -TIMEVALUE_ONE_SECOND_IN_USECS);
      }
    
    if (m_sec >= 1 && m_usec < 0)
      {
        --m_sec;
        m_usec += TIMEVALUE_ONE_SECOND_IN_USECS;
      }
    else if (m_sec < 0 && m_usec > 0)
      {
        ++m_sec;
        m_usec -= TIMEVALUE_ONE_SECOND_IN_USECS;
      }
  }
  
};

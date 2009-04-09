// -*- C++ -*-
/*!
 * @file TimeMeasure.cpp
 * @brief Periodic time measurement class
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

#include <coil/Time.h>
#include <math.h>
#include <coil/TimeMeasure.h>

//#define RDTSC(X) __asm__ __volatile__ ("rdtsc" : "=A" (X))
//#define NSEC_PER_SEC 1000000000

#ifndef ULLONG_MAX
#define ULLONG_MAX 0xffffffffffffffffULL
#endif 

namespace coil
{
  
  //============================================================
  // Time statictics object
  //============================================================
  TimeMeasure::TimeMeasure(int buflen)
    : m_count(0), m_countMax(buflen + 1), m_recurred(false)
  {
    m_record.reserve(m_countMax);
    for (unsigned long i(0); i < m_countMax; ++i)
      {
        m_record.push_back(TimeValue(0, 0));
      }
  }
  
  
  //============================================================
  // Begin time measurement for time statistics
  //============================================================
  void TimeMeasure::tick()
  {
    m_begin = gettimeofday(); // [TimeValue]
  }
  
  
  //============================================================
  // End time measurement for time statistics
  //============================================================
  void TimeMeasure::tack()
  {
    m_end = gettimeofday(); // [TimeValue]
    
    //	long long interval;
    //	interval = m_EndTime - m_BeginTime; // [ns]
    m_record.at(m_count % m_countMax) = m_end - m_begin;
    ++m_count;
    if (m_count > m_countMax)
      {
        m_count = 0;
        m_recurred = true;
      }
  }
  
  
  void TimeMeasure::reset()
  {
    m_count = 0;
    m_recurred = false;
  }
  
  unsigned long int TimeMeasure::count() const
  {
    return m_recurred ? m_record.size() : m_count;
  }

  //============================================================
  // Get total statistics
  //============================================================
  bool TimeMeasure::getStatistics(double &max_interval,
                                  double &min_interval,
                                  double &mean_interval,
                                  double &stddev)
  {
    max_interval = (double)0;
    min_interval = (double)ULLONG_MAX;

    double sum = 0;
    double sq_sum = 0;
    unsigned long int len(count());

    if (len == 0) return false;

    for (unsigned long int i(0); i < len; ++i)
      {
        double trecord(m_record[i]);
        sum += trecord;
        sq_sum += trecord * trecord;
        
        if (trecord > max_interval) max_interval = trecord;
        if (trecord < min_interval) min_interval = trecord;
      }
    
    mean_interval = sum / m_count;
    stddev = sqrt(sq_sum / m_count - (mean_interval * mean_interval));

    return true;
  }

}; // namespace coil

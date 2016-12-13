// -*- C++ -*-
/*!
 * @file TimeMeasure.h
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

#ifndef COIL_TIMEMEASURE_H
#define COIL_TIMEMEASURE_H

#include <vector>
#include <coil/TimeValue.h>

namespace coil
{
  
  /*!
   * TimeMeasure object
   *
   * This object is used for getting statistics of code execution time. 
   * Using get_stat you can get maximum, minimum, mean and standard
   * deviation time for code execution.
   */
  class TimeMeasure
  {
  public:
    struct Statistics
    {
      double max_interval;
      double min_interval;
      double mean_interval;
      double std_deviation;
    };
    /*!
     * @brief Time statictics object for profiling.
     * 
     * Constructor
     */
    TimeMeasure(int buflen = 100);
    
    /*!
     * @brief Begin time measurement for time statistics.
     *
     * Begin time measurement for time statistics
     */
    void tick();
    
    /*!
     * @brief Finish time measurement for time statistics.
     *
     * End of time measurement for time statistics
     */
    void tack();

    coil::TimeValue& interval();

    void reset();
    
    /*!
     * Get number of time measurement buffer
     *
     * @brief Get number of time measurement buffer.
     *
     */
    unsigned long int count() const;
    
    /*!
     * @brief Get total statistics.
     * Get total statistics
     * max_interval, min_interval, mean_interval [ns]
     */
    bool getStatistics(double &max_interval,
                       double &min_interval,
                       double &mean_interval,
                       double &stddev);
    
    Statistics getStatistics();

  private:
    std::vector<coil::TimeValue> m_record;
    coil::TimeValue m_begin;
    coil::TimeValue m_interval;

    unsigned long int m_count;
    const unsigned long int m_countMax;
    unsigned long long int m_cpuClock;

    bool m_recurred;
  };
}; // namespace coil
#endif // COIL_TIMEMEASURE_H

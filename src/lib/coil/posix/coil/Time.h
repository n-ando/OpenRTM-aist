// -*- C++ -*-
/*!
 * @file Time_posix.h
 * @brief Time functions
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

#ifndef COIL_TIME_H
#define COIL_TIME_H

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <iostream>
#include <coil/config_coil.h>
#include <coil/TimeValue.h>

namespace coil
{

  inline unsigned int sleep(unsigned int seconds)
  {
    return ::sleep(seconds);
  }

  inline int sleep(TimeValue interval)
  {
    timeval tv;
    tv.tv_sec = interval.sec();
    tv.tv_usec = interval.usec();
    return ::select(0, 0, 0, 0, &tv);
  }

  inline int usleep(useconds_t usec)
  {
    return ::usleep(usec);
  }

  inline int gettimeofday(struct timeval *tv, struct timezone *tz)
  {
    return ::gettimeofday(tv, tz);
  }

  inline TimeValue gettimeofday()
  {
    timeval tv;
    ::gettimeofday(&tv, 0);
    return TimeValue(tv.tv_sec, tv.tv_usec);
  }

  inline int settimeofday(const struct timeval *tv , const struct timezone *tz)
  {
    return ::settimeofday(tv, tz);
  }


};

#endif // COIL_TIME_H

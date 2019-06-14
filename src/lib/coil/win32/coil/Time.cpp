// -*- C++ -*-
/*!
 * @file Timevalue.h
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

#include <coil/Time.h>

namespace coil
{
  int gettimeofday(struct timeval *tv, struct timezone *tz)
  {
      FILETIME        ftime;
      LARGE_INTEGER   lint;
      __int64         val64;
      static int      tzflag;
      if (tv != nullptr)
      {
          ::GetSystemTimeAsFileTime(&ftime);
          lint.LowPart = ftime.dwLowDateTime;
          lint.HighPart = static_cast<LONG>(ftime.dwHighDateTime);
          val64 = lint.QuadPart;
          val64 = val64 - EPOCHFILETIME;
          val64 = val64 / 10;
          tv->tv_sec = static_cast<long>(val64 / 1000000);
          tv->tv_usec = static_cast<long>(val64 % 1000000);
      }
      if (tz != nullptr)
      {
          if (tzflag == 0)
          {
             ::_tzset();
              ++tzflag;
          }
          long tzone = 0;
          ::_get_timezone(&tzone);
          tz->tz_minuteswest = tzone / 60;
          int dlight = 0;
          ::_get_daylight(&dlight);
          tz->tz_dsttime = dlight;
      }
      return 0;
  }

  int settimeofday(const struct timeval *tv , const struct timezone *tz)
  {

    SYSTEMTIME systime;
    FILETIME ftime;
    LARGE_INTEGER lint;
    __int64 val64;

    // tv,tz -> ftime
    if (tv != nullptr)
      {
        int bias(0);
        if (tz != nullptr)
          {
            bias = tz->tz_minuteswest;
          }

        val64 = (tv->tv_sec + bias * 60) * 1000000;
        val64 = val64 + tv->tv_usec;
        lint.QuadPart = val64;
        ftime.dwHighDateTime = static_cast<DWORD>(lint.LowPart);
        ftime.dwHighDateTime = static_cast<DWORD>(lint.HighPart);
        ::FileTimeToSystemTime(&ftime, &systime);
        ::SetSystemTime(&systime);
      }

    return 0;
  }

  int clock(TimeValue &tv)
  {
      LARGE_INTEGER frequency;
      BOOL ret = QueryPerformanceFrequency(&frequency);

      if (ret == 0)
      {
          return 1;
      }
      else
      {
          LARGE_INTEGER current;
          QueryPerformanceCounter(&current);
          LONGLONG current_time = (current.QuadPart * 1000000) / frequency.QuadPart;
          tv = TimeValue(static_cast<long>(current_time / 1000000), static_cast<long>(current_time % 1000000));
          return 0;
      }
  }

  TimeValue clock()
  {
    TimeValue ret;
    if(coil::clock(ret) != 0)
    {
      timeval tv;
      coil::gettimeofday(&tv, nullptr);
      return TimeValue(tv.tv_sec, tv.tv_usec);
    }
    else
    {
      return ret;
    }
  }
} // namespace coil

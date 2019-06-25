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
} // namespace coil

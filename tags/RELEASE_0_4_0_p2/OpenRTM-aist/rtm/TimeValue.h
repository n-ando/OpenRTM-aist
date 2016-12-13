// -*- C++ -*-
/*!
 * @file TimeValue.h
 * @brief TimeValue class
 * @date $Date: 2007-07-20 16:11:00 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: TimeValue.h,v 1.1.2.1 2007-07-20 16:11:00 n-ando Exp $
 *
 */

#ifndef TimeValue_h
#define TimeValue_h

#include <iostream>
#include <ace/OS_NS_time.h>


struct TimeValue
  : public timeval
{
  TimeValue(long sec=0, long usec=0)
  {
    tv_sec = sec;
    tv_usec = usec;
  }

  TimeValue operator-(TimeValue& tm)
  {
    TimeValue res;
    if (tv_sec >= tm.tv_sec) // +
      {
	if (tv_usec >= tm.tv_usec)
	  {
	    res.tv_sec  = tv_sec  - tm.tv_sec;  // -
	    res.tv_usec = tv_usec - tm.tv_usec; // +
	  }
	else // tv_usec < tm.tv_usec
	  {
	    res.tv_sec  = tv_sec  - tm.tv_sec - 1;
	    res.tv_usec = (tv_usec + 1000000) - tm.tv_usec;
	  }
      }
    else // tv_sec < tm.tv_sec // -
      {
	if (tm.tv_usec >= tv_usec)
	  {
	    res.tv_sec  = - (tm.tv_sec  - tv_sec); // +
	    res.tv_usec = - (tm.tv_usec - tv_usec);  // +
	  }
	else // tm.tv_usec < tv_usec
	  {
	    res.tv_sec  = tm.tv_sec - tv_sec  - 1;
	    res.tv_usec = - (tm.tv_usec + 1000000) + tv_usec;
	  }
      }
    return res;
  }

  TimeValue operator+(TimeValue& tm)
  {
    TimeValue res;
    res.tv_sec  = tv_sec  + tm.tv_sec;
    res.tv_usec = tv_usec + tm.tv_usec;
    if (res.tv_usec > 1000000)
      {
	++res.tv_sec;
	res.tv_usec -= 1000000;
      }
    return res;
  }

  TimeValue operator=(double time)
  {
    tv_sec = (long)time;
    tv_usec = (long)((time - (double)tv_sec)*1000000);
    return *this;
  }

  double toDouble()
  {
    return (double)tv_sec + ((double)tv_usec/1000000.0);
  }

  //  friend std::ostream& operator<<(std::ostream& lhs, const TimeValue& rhs);
};

/*
std::ostream& operator<<(std::ostream& lhs, const TimeValue& rhs)
{
  double res;
  res = (double)rhs.tv_sec + ((double)rhs.tv_usec/1000000.0);
  lhs << res;
  return lhs;
}
*/

#endif // TimeValue_h

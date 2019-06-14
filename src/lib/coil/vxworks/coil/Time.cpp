// -*- C++ -*-
/*!
 * @file Timevalue.h
 * @brief Timevalue class
 * @date $Date$
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2017
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#include <coil/Time.h>

#if defined(__powerpc__) && !defined(__RTP__)
#define CLOCK_RATE_PPC 75000000
#include <vxLib.h>
#endif

namespace coil
{
#if defined(__powerpc__) && !defined(__RTP__)
  int gettimeofday(UINT32 &s, UINT32 &ns)
  {
    UINT32 tbu, tbl;
    vxTimeBaseGet(&tbu, &tbl);
    UINT64 t = ((UINT64)tbu << 32) | (UINT64)tbl;
    s = t/CLOCK_RATE_PPC;
    ns = ((t-s*CLOCK_RATE_PPC)*1000000000)/CLOCK_RATE_PPC;
    return 0;
  }
  TimeValue gettimeofday()
  {
    UINT32 tbu, tbl;
    vxTimeBaseGet(&tbu, &tbl);
    UINT64 t = ((UINT64)tbu << 32) | (UINT64)tbl;
    UINT32 s = t/CLOCK_RATE_PPC;
    UINT32 us = ((t-s*CLOCK_RATE_PPC)*1000000)/CLOCK_RATE_PPC;
    return TimeValue(s, us);
  }
  int settimeofday(UINT32 s, UINT32 ns)
  {
    UINT64 t = s*CLOCK_RATE_PPC + (ns*CLOCK_RATE_PPC)/1000000000;
    UINT32 tbu = t >> 32;
    UINT32 tbl = (UINT32)t;
    vxTimeBaseSet(tbu,tbl);
  }
#endif
  // no implementation
};

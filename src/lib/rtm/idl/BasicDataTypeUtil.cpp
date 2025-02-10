// -*- C++ -*-
/*!
 * @file BasicDataTypeUtil.cpp
 * @brief Data type utility function
 * @date $Date: 2020-03-17 15:06:58 $
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2006-2020
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */



#include "BasicDataTypeUtil.h"
#include <cstring>

namespace CORBA_Util
{
  template <>
  void copyData(RTC::TimedOctetSeq& data1, const RTC::TimedOctetSeq& data2)
  {
    data1.tm = data2.tm;
    data1.data.length(data2.data.length());
    if (data2.data.length() > 0)
    {
        std::memcpy(&data1.data[0], &data2.data[0], data1.data.length());
    }
  }
} // namespace CORBA_Util


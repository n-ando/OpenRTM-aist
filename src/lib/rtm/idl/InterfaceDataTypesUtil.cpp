// -*- C++ -*-
/*!
 * @file DataTypeUtil.cpp
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



#include "InterfaceDataTypesUtil.h"
#include <cstring>

namespace CORBA_Util
{
  template <>
  void copyData(RTC::CameraImage& data1, const RTC::CameraImage& data2)
  {
    data1.tm = data2.tm;
    data1.width = data2.width;
    data1.height = data2.height;
    data1.bpp = data2.bpp;
    data1.fDiv = data2.fDiv;
    data1.pixels.length(data2.pixels.length());
    if (data2.pixels.length() > 0)
    {
        std::memcpy(&data1.pixels[0], &data2.pixels[0], data1.pixels.length());
    }
  }
} // namespace CORBA_Util


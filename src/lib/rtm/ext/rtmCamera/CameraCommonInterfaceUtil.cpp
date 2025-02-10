// -*- C++ -*-
/*!
 * @file CameraCommonInterfaceUtil.cpp
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
  void copyData(Img::ImageData& data1, const Img::ImageData& data2)
  {
    data1.width = data2.width;
    data1.height = data2.height;
    data1.format = data2.format;
    data1.raw_data.length(data2.raw_data.length());
    if (data2.raw_data.length() > 0)
    {
        std::memcpy(&data1.raw_data[0], &data2.raw_data[0], data1.raw_data.length());
    }
  }
  template <>
  void copyData(Img::CameraImage& data1, const Img::CameraImage& data2)
  {
    data1.captured_time = data2.captured_time;
    copyData(data1.image, data2.image);
    data1.intrinsic = data2.intrinsic;
    for (_CORBA_ULong i = 0; i < 4; i++) {
        for (_CORBA_ULong j = 0; j < 4; j++) {
            data1.extrinsic[i][j] = data2.extrinsic[i][j];
        }
    }
  }
  template <>
  void copyData(Img::TimedCameraImage& data1, const Img::TimedCameraImage& data2)
  {
    data1.tm = data2.tm;
    copyData(data1.data, data2.data);
    data1.error_code = data2.error_code;
  }
} // namespace CORBA_Util


// -*- C++ -*-
/*!
 * @file CameraCommonInterfaceUtil.h
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

#ifndef RTC_CAMERACOMMONINTERFACEUTIL_H
#define RTC_CAMERACOMMONINTERFACEUTIL_H

#include "CameraCommonInterfaceSkel.h"
#include <rtm/DataTypeUtil.h>

namespace CORBA_Util
{
  template <>
  void copyData(Img::ImageData& data1, const Img::ImageData& data2);
  template <>
  void copyData(Img::CameraImage& data1, const Img::CameraImage& data2);
  template <>
  void copyData(Img::TimedCameraImage& data1, const Img::TimedCameraImage& data2);
} // namespace CORBA_Util


#endif  // RTC_CAMERACOMMONINTERFACEUTIL_H

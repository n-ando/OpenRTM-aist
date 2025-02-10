// -*- C++ -*-
/*!
 * @file InterfaceDataTypesUtil.h
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

#ifndef RTC_INTERFACEDATATYPESUTIL_H
#define RTC_INTERFACEDATATYPESUTIL_H

#include "InterfaceDataTypesSkel.h"
#include <rtm/DataTypeUtil.h>

namespace CORBA_Util
{
  template <>
  void copyData(RTC::CameraImage& data1, const RTC::CameraImage& data2);
} // namespace CORBA_Util


#endif  // RTC_INTERFACEDATATYPESUTIL_H

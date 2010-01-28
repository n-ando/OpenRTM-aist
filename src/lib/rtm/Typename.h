// -*- C++ -*-
/*!
 * @file Typename.h
 * @brief Typename function
 * @date $Date: 2007-12-31 03:08:03 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2009
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPort.h 1225 2009-02-28 02:30:25Z n-ando $
 *
 */

#ifndef RTC_TYPENAME_H
#define RTC_TYPENAME_H

#include <rtm/RTC.h>

template <class T>
const char* toTypename()
{
  CORBA::Any any_var;
  T   tmp_var;
  any_var <<= tmp_var;
  return any_var.type()->name();
}

#endif // RTC_TYPENAME_H

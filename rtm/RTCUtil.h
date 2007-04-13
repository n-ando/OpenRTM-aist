// -*- C++ -*-
/*!
 * @file RTCUtil.h
 * @brief RTComponent utils
 * @date $Date: 2007-04-13 18:15:57 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTCUtil.h,v 1.1 2007-04-13 18:15:57 n-ando Exp $
 *
 */

#ifndef RTCUtil_h
#define RTCUtil_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>

namespace RTC
{
  bool isDataFlowParticipant(CORBA::Object_ptr obj);

  bool isFsmParticipant(CORBA::Object_ptr obj);

  bool isFsmObject(CORBA::Object_ptr obj);

  bool isMultiModeObject(CORBA::Object_ptr obj);

}; // namespace RTC
#endif // RTCUtil_h

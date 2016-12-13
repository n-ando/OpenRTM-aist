// -*- C++ -*-
/*!
 * @file RTCUtil.h
 * @brief RTComponent utils
 * @date $Date: 2007-04-13 18:15:52 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTCUtil.cpp,v 1.1 2007-04-13 18:15:52 n-ando Exp $
 *
 */

#include <rtm/RTCUtil.h>

namespace RTC
{
  bool isDataFlowParticipant(CORBA::Object_ptr obj)
  {
    DataFlowParticipant_var dfp;
    dfp = DataFlowParticipant::_narrow(obj);
    return !CORBA::is_nil(dfp);
  }

  bool isFsmParticipant(CORBA::Object_ptr obj)
  {
    FsmParticipant_var fsmp;
    fsmp = FsmParticipant::_narrow(obj);
    return !CORBA::is_nil(fsmp);
  }

  bool isFsmObject(CORBA::Object_ptr obj)
  {
    FsmObject_var fsm;
    fsm = FsmObject::_narrow(obj);
    return !CORBA::is_nil(fsm);
  }

  bool isMultiModeObject(CORBA::Object_ptr obj)
  {
    MultiModeObject_var mmc;
    mmc = MultiModeObject::_narrow(obj);
    return !CORBA::is_nil(mmc);
  }
}; // namespace RTC


// -*- C++ -*-
/*!
 * @file RTCUtil.h
 * @brief RTComponent utils
 * @date $Date: 2007-12-31 03:08:06 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTCUtil.cpp,v 1.1.2.1 2007-12-31 03:08:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <rtm/RTCUtil.h>

namespace RTC
{
  /*!
   * @if jp
   * @brief DataFlowParticipant であるか判定する
   * @else
   * @endif
   */
  bool isDataFlowParticipant(CORBA::Object_ptr obj)
  {
    DataFlowParticipant_var dfp;
    dfp = DataFlowParticipant::_narrow(obj);
    return !CORBA::is_nil(dfp);
  }
  
  /*!
   * @if jp
   * @brief FsmParticipant であるか判定する
   * @else
   * @endif
   */
  bool isFsmParticipant(CORBA::Object_ptr obj)
  {
    FsmParticipant_var fsmp;
    fsmp = FsmParticipant::_narrow(obj);
    return !CORBA::is_nil(fsmp);
  }
  
  /*!
   * @if jp
   * @brief Fsm であるか判定する
   * @else
   * @endif
   */
  bool isFsmObject(CORBA::Object_ptr obj)
  {
    FsmObject_var fsm;
    fsm = FsmObject::_narrow(obj);
    return !CORBA::is_nil(fsm);
  }
  
  /*!
   * @if jp
   * @brief multiModeComponent であるか判定する
   * @else
   * @endif
   */
  bool isMultiModeObject(CORBA::Object_ptr obj)
  {
    MultiModeObject_var mmc;
    mmc = MultiModeObject::_narrow(obj);
    return !CORBA::is_nil(mmc);
  }
}; // namespace RTC


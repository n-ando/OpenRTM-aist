// -*- C++ -*-
/*!
 * @file RTCUtil.h
 * @brief RTComponent utils
 * @date $Date: 2007-12-31 03:08:06 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2007-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RTCUtil.h,v 1.1.2.1 2007-12-31 03:08:06 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */
#ifndef RTCUtil_h
#define RTCUtil_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>

/*!
 * @if jp
 * @namespace RTC
 *
 * @brief RTコンポーネント用ユーティリティ関数
 *
 * RTコンポーネントに対して以下のユーティリティ関数を提供する。
 * 
 * - isDataFlowParticipant
 * - isFsmParticipant
 * - isFsmObject
 * - isMultiModeObject
 *
 * @else
 *
 * @endif
 */
namespace RTC
{
  /*!
   * @if jp
   *
   * @brief DataFlowComponent であるか判定する
   *
   * 指定されたRTコンポーネントが DataFlowComponent であるか判定する。
   * DataFlowComponent、 ExecutionContext の Semantics が
   * Periodic Sampled Data Processing の場合に利用されるRTコンポーネントの型
   * である。
   *
   * @param obj 判定対象の CORBA オブジェクト
   *
   * @return DataFlowComponent 判定結果
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  bool isDataFlowParticipant(CORBA::Object_ptr obj);
  
  /*!
   * @if jp
   *
   * @brief FsmParticipant であるか判定する
   *
   * 指定されたRTコンポーネントが FsmParticipant であるか判定する。
   * FsmParticipant は、 ExecutionContext の Semantics が
   * Stimulus Response Processing の場合に、状態内のアクションを定義するために
   * 利用されるRTコンポーネントの型である。
   *
   * @param obj 判定対象の CORBA オブジェクト
   *
   * @return FsmParticipant 判定結果
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  bool isFsmParticipant(CORBA::Object_ptr obj);
  
  /*!
   * @if jp
   *
   * @brief Fsm であるか判定する
   *
   * 指定されたRTコンポーネントが Fsm であるか判定する。
   * Fsm は、 ExecutionContext の Semantics が Stimulus Response Processing の
   * 場合に、状態遷移を定義するために利用されるRTコンポーネントの型である。
   *
   * @param obj 判定対象の CORBA オブジェクト
   *
   * @return Fsm 判定結果
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  bool isFsmObject(CORBA::Object_ptr obj);
  
  /*!
   * @if jp
   *
   * @brief multiModeComponent であるか判定する
   *
   * 指定されたRTコンポーネントが multiModeComponent であるか判定する。
   * Fsm は、 ExecutionContext の Semantics が Modes of Operatin の場合に、
   * Mode を定義するために利用されるRTコンポーネントの型である。
   *
   * @param obj 判定対象の CORBA オブジェクト
   *
   * @return multiModeComponent 判定結果
   *
   * @since 0.4.0
   *
   * @else
   *
   * @endif
   */
  bool isMultiModeObject(CORBA::Object_ptr obj);
}; // namespace RTC
#endif // RTCUtil_h

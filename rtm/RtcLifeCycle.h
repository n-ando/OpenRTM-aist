// -*- C++ -*-
/*!
 * @file RtcLifeCycle.h
 * @brief RTC Life Cycle management interface
 * @date $Date: 2006-09-11 19:05:12 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcLifeCycle.h,v 1.1 2006-09-11 19:05:12 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RtcLifeCycle_h
#define RtcLifeCycle_h

// CORBA header include
#include "rtm/RTC.h"
#include "rtm/Util.h"

// local includes
#include "rtm/idl/RTCSkel.h"

namespace RTC
{
  /*!
   * @if jp
   *
   * @class LifeCycle_imple
   * @brief 
   *
   *
   * @else
   *
   * @class LifeCycle_impl
   * @brief 
   * 
   * The LifeCycle interface defines the states and transitions through which
   * all RTCs will pass from the time they are created until the time they are
   * destroyed.
   *
   * An RTC begins in the Created state; at this point, it has been
   * instantiated but not yet fully initialized. Note that this state is highly
   * implementation-dependent. For example, it may correspond to the invocation
   * of a constructor in languages that support that concept, but not all
   * languages do. Furthermore, how soon this state is entered before
   * LifeCycle::initialize is invoked is implementation-dependent. Therefore,
   * it should be relied on by RTC implementers only to the minimum extent
   * possible.
   * An RTC that has completed its initialization and has not been finalized
   * is said to be Alive. This composite state incorporates a number of
   * concurrent and non-concurrent sub-states described below.
   *
   * [Execution Context]
   * An RTC may participate in any number of execution contexts (see section
   * 2.2.2.6 of RTC spec). These contexts are represented as concurrent regions
   * within the Alive state and are represented to an RTC as distinct instances
   * of the ExecutionContext class.
   * Relative to a given execution context, an RTC may either be Active,
   * Inactive, or in Error. When the RTC is Active in a Running execution
   * context, the ComponentAction callbacks (see section 2.2.2.5) shall be
   * invoked as appropriate for the context's ExecutionKind. The callbacks
   * shall not be invoked relative to that context when either the RTC is
   * Inactive in that context or the context is Stopped. (Note that starting
   * and stopping an execution context shall not impact whether its
   * participating RTCs are Active or Inactive.)
   * It may be that a given RTC does not directly participate in any execution
   * contexts. Such an RTC is referred to as passive. A passive RTC may
   * provide services to other components upon request. At any other time, it
   * shall not be required to performs any ongoing activity of its own;
   * therefore, instances of such an RTC typically exist only as parts
   * (directly or indirectly) of a containing active RTC.
   * The Alive state of a passive RTC shall consist of a single region, and
   * within that region the Active and Error sub-states shall never be observed.
   * [Error Handling]
   * If an operation fails while the RTC is Active in a given execution
   * context, the RTC will transition to the Error state corresponding to that
   * context. While the RTC is in Error, the ComponentAction::on_error callback
   * will be invoked in place of those callbacks that would otherwise have been
   * invoked according to the context's ExecutionKind. For example, if the kind
   * is PERIODIC, on_error shall be invoked instead of the pair of on_execute
   * and on_state_update.
   * When an RTC is in Error, it may be reset. If resetting is successful, the
   * RTC shall return to the Inactive state. If resetting is unsuccessful, it
   * shall remain in the Error state.
   *
   * @endif
   */
  class LifeCycle_impl
    : public virtual POA_RTC::LifeCycle,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    LifeCycle_impl(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
    virtual ~LifeCycle_impl(){};

    //============================================================
    //
    // <<< CORBA interfaces >>>
    //
    //============================================================
    /*!
     * @if jp
     *
     * @breif RTCを初期化する
     *
     * このオペレーション呼び出しの結果として、ComponentAction::on_initialize
     * コールバック関数が呼ばれる。
     * 制約
     * Created状態にいるときにのみ、初期化が行われる。他の状態にいる場合には
     * ReturnCode_t::PRECONDITION_NOT_MET が返され呼び出しは失敗する。
     * このオペレーションはRTCのミドルウエアから呼ばれることを想定しており、
     * アプリケーション開発者は直接このオペレーションを呼ぶことは想定
     * されていない。
     * 
     * @else
     *
     * @breif Initialize the RTC that realizes this interface.
     *
     * The invocation of this operation shall result in the invocation of the
     * callback ComponentAction::on_initialize.
     *
     * Constraints
     * - An RTC may be initialized only while it is in the Created state. Any
     *   attempt to invoke this operation while in another state shall fail
     *   with ReturnCode_t::PRECONDITION_NOT_MET.
     * - Application developers are not expected to call this operation
     *   directly; it exists for use by the RTC infrastructure.
     *
     * @endif
     */
    virtual ReturnCode_t initialize();

    /*!
     * @if jp
     *
     * @brief 
     *
     * @else
     *
     * @brief Finalize the RTC for preparing it for destruction
     * 
     * This invocation of this operation shall result in the invocation of the
     * callback ComponentAction::on_finalize.
     *
     * Constraints
     * - An RTC may not be finalized while it is Active in any Running
     *   execution context. Any attempt to invoke this operation at such a time
     *   shall fail with ReturnCode_t::PRECONDITION_NOT_MET.
     * - An RTC may not be finalized while it is in the Created state.
     *   Any attempt to invoke this operation while in that state shall fail
     *   with ReturnCode_t::PRECONDITION_NOT_MET.
     * - Application developers are not expected to call this operation
     *   directly; it exists for use by the RTC infrastructure.
     *
     * @endif
     */
    virtual ReturnCode_t finalize();

    /*!
     * @if jp
     *
     * @brief
     *
     * @else
     *
     * @brief Attempt to recover the RTC when it is in Error.
     * 
     * The ComponentAction::on_reset callback shall be invoked. If possible,
     * the RTC developer should implement that callback such that the RTC may
     * be returned to a valid state.
     * If this operation fails, the RTC will remain in Error.
     *
     * Constraints
     * - An RTC may only be reset in an execution context in which it is in
     *   error. If the RTC is not in Error in the identified context, this
     *   operation shall fail with ReturnCode_t::PRECONDITION_NOT_MET.
     *   However, that failure shall not cause the RTC to enter the Error
     *   state.
     * - An RTC may not be reset while in the Created state. Any attempt to
     *   invoke this operation while the RTC is in that state shall fail with
     *   ReturnCode_t::PRECONDITION_NOT_MET. However, that failure shall not
     *   cause the RTC to enter the Error state.
     *
     * @endif
     */
    virtual ReturnCode_t reset();

    /*!
     * @if jp
     *
     * @brief
     *
     * @else
     *
     * @brief Stop the RTC's and finalize it along with its contents.
     * 
     * Any execution contexts for which the RTC is the owner shall be stopped. 
     * If the RTC participates in any execution contexts belonging to another
     * RTC that contains it, directly or indirectly (i.e. the containing RTC
     * is the owner of the ExecutionContext), it shall be deactivated in those
     * contexts.
     * After the RTC is no longer Active in any Running execution context, it
     * and any RTCs contained transitively within it shall be finalized.
     *
     * Constraints
     * - An RTC cannot be exited if it has not yet been initialized. Any
     *   attempt to exit an RTC that is in the Created state shall fail with
     *   ReturnCode_t::PRECONDITION_NOT_MET.
     *
     * @endif
     */
    virtual ReturnCode_t exit(); 

    /*!
     * @if jp
     *
     * @brief
     *
     * @else
     *
     * @brief
     *
     * A component is alive or not regardless of the execution context from
     * which it is observed. However, whether or not it is Active, Inactive,
     * or in Error is dependent on the execution context(s) in which it is
     * running. That is, it may be Active in one context but Inactive in
     * another. Therefore, this operation shall report whether this RTC is
     * either Active, Inactive or in Error; which of those states a component
     * is in with respect to a particular context may be queried from the
     * context itself.
     *
     * @endif
     */
    virtual CORBA::Boolean is_alive();
    // end of CORBA interface definition
    //============================================================

  protected:
    CORBA::ORB_var m_varORB;
    PortableServer::POA_var m_varPOA;

    RTC::LifeCycleState m_preState;
    RTC::LifeCycleState m_curState;
    RTC::LifeCycleState m_nxtState;




  };
};

#endif // RtcLifeCycle_h

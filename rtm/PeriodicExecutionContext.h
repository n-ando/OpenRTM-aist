// -*- C++ -*-
/*!
 * @file PeriodicExecutionContext.h
 * @brief PeriodicExecutionContext class
 * @date $Date: 2008-01-14 07:53:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PeriodicExecutionContext.h,v 1.4.2.5 2008-01-14 07:53:05 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4.2.4  2007/12/31 03:08:05  n-ando
 * Class reference by doxygen comment was revised.
 *
 * Revision 1.4.2.3  2007/09/20 11:22:08  n-ando
 * Some fixes.
 * - Template parameter "Result" is deleted.
 *   Now listener return type is void instead of the Result.
 *
 * Revision 1.4.2.2  2007/09/19 07:44:35  n-ando
 * The usleep() in the execution loop will be skipped, if wait-time is 0.
 *
 * Revision 1.4.2.1  2007/07/20 15:59:18  n-ando
 * ACE header include was added.
 *
 * Revision 1.4  2007/04/26 15:30:46  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.3  2007/04/13 15:52:34  n-ando
 * RTC::OK was changed to RTC::RTC_OK.
 * Initialization function was added to make it an external module.
 *
 * Revision 1.2  2007/01/21 10:27:00  n-ando
 * Object reference count related bugs were fixed.
 *
 * Revision 1.1  2007/01/09 15:29:35  n-ando
 * PeriodicExecutionContext class
 *
 */

#ifndef PeriodicExecutionContext_h
#define PeriodicExecutionContext_h

#include <rtm/RTC.h>
#include <rtm/idl/RTCSkel.h>
#include <rtm/idl/OpenRTMSkel.h>
#include <rtm/Manager.h>
#include <rtm/StateMachine.h>
#include <rtm/ExecutionContextBase.h>

// ACE
#include <ace/Task.h>
#include <ace/OS_NS_unistd.h>
#include <vector>
#include <iostream>

namespace RTC
{
  /*!
   * @if jp
   * @class PeriodicExecutionContext
   * @brief PeriodicExecutionContext クラス
   *
   * Periodic Sampled Data Processing(周期実行用)ExecutionContextクラス。
   *
   * @since 0.4.0
   *
   * @else
   * @class PeriodicExecutionContext
   * @brief PeriodicExecutionContext class
   * @endif
   */
  class PeriodicExecutionContext
    : public virtual ExecutionContextBase,
      public ACE_Task<ACE_MT_SYNCH>
  {
  public:
    /*!
     * @if jp
     * @brief デフォルトコンストラクタ
     *
     * デフォルトコンストラクタ
     * プロファイルに以下の項目を設定する。
     * 　kind : PERIODIC
     * 　rate : 0.0
     *
     * @else
     * @brief Constructor
     * @endif
     */
    PeriodicExecutionContext();
    
    /*!
     * @if jp
     * @brief コンストラクタ
     *
     * コンストラクタ
     * 設定された値をプロファイルに設定する。
     *
     * @param owner 当該 Executioncontext の owner
     * @param rate 動作周期(Hz)(デフォルト値:1000)
     *
     * @else
     * @brief Constructor
     * @endif
     */
    PeriodicExecutionContext(DataFlowComponent_ptr owner,
			     double rate = 1000.0);
    
    /*!
     * @if jp
     * @brief デストラクタ
     *
     * デストラクタ
     *
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~PeriodicExecutionContext();
    
    /*!
     * @if jp
     * @brief CORBA オブジェクト参照の取得
     *
     * 本オブジェクトの ExecutioncontextService としての CORBA オブジェクト参照
     * を取得する。
     *
     * @return CORBA オブジェクト参照
     *
     * @else
     *
     * @endif
     */
    ExecutionContextService_ptr getRef() {return m_ref;}
    
    /*!
     * @if jp
     * @brief ExecutionContext用アクティビティスレッドを生成する
     *
     * Executioncontext 用の内部アクティビティスレッドを生成し起動する。
     * これは ACE_Task サービスクラスメソッドのオーバーライド。
     *
     * @param args 通常は0
     *
     * @return 生成処理実行結果
     *
     * @else
     *
     * @brief Create internal activity thread
     *
     * Create internal activity thread. This is ACE_Task class method over ride.
     *
     * @param args usually give 0
     *
     * @endif
     */     
    virtual int open(void *args);
    
    /*!
     * @if jp
     * @brief ExecutionContext 用のスレッド実行関数
     *
     * ExecutionContext 用のスレッド実行関数。
     * 登録されたコンポーネントの処理を呼び出す。
     *
     * @return 実行結果
     *
     * @else
     *
     * Run by a daemon thread to handle deferred processing.
     * ACE_Task class method override.
     *
     * @endif
     */     
    virtual int svc(void);
    
    /*!
     * @if jp
     * @brief ExecutionContext 用のスレッド終了関数
     *
     * ExecutionContext 用のスレッド終了時に呼ばれる。
     * コンポーネントオブジェクトの非アクティブ化、マネージャへの通知を行う。
     * これは ACE_Task サービスクラスメソッドのオーバーライド。
     *
     * @param flags 終了処理フラグ
     *
     * @return 終了処理結果
     *
     * @else
     *
     * @brief Close activity thread
     *
     * close() method is called when activity thread svc() is returned.
     * This method deactivate this object and notify it to manager.
     * ACE_Task class method override.
     *
     * @endif
     */     
    virtual int close(unsigned long flags);
    
    //============================================================
    // ExecutionContext
    //============================================================
    /*!
     * @if jp
     * @brief ExecutionContext 実行状態確認関数
     *
     * この操作は ExecutionContext が Runnning 状態の場合に true を返す。
     * Executioncontext が Running の間、当該 Executioncontext に参加している
     * 全てのアクティブRTコンポーネントが、 ExecutionContext の実行種類に応じて
     * 実行される。
     *
     * @return 状態確認関数(動作中:true、停止中:false)
     *
     * @else
     *
     * @brief Check for ExecutionContext running state
     *
     * This operation shall return true if the context is in the Running state.
     * While the context is Running, all Active RTCs participating
     * in the context shall be executed according to the context’s execution
     * kind.
     *
     * @endif
     */
    virtual CORBA::Boolean is_running()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContext の実行を開始
     *
     * ExecutionContext の実行状態を Runnning とするためのリクエストを発行する。			 * ExecutionContext の状態が遷移すると ComponentAction::on_startup が
     * 呼び出される。
     * 参加しているRTコンポーネントが、初期化されるまで ExecutionContext を開始
     * することはできない。
     * ExecutionContext は複数回開始/停止を繰り返すことができる。
     *
     * @return 処理実行結果
     *
     * @else
     *
     * @brief Start ExecutionContext
     *
     * Request that the context enter the Running state. 
     * Once the state transition occurs, the ComponentAction::on_startup 
     * operation will be invoked.
     * An execution context may not be started until the RT components that
     * participate in it have been initialized.
     * An execution context may be started and stopped multiple times.
     *
     * @endif
     */
    virtual ReturnCode_t start()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContext の実行を停止
     *
     * ExecutionContext の状態を Stopped とするためのリクエストを発行する。
     * 遷移が発生した場合は、 ComponentAction::on_shutdown が呼び出される。
     * 参加しているRTコンポーネントが終了する前に ExecutionContext を停止する
     * 必要がある。
     * ExecutionContext は複数回開始/停止を繰り返すことができる。
     *
     * @return 処理実行結果
     *
     * @else
     *
     * @brief Stop ExecutionContext
     *
     * Request that the context enter the Stopped state. 
     * Once the transition occurs, the ComponentAction::on_shutdown operation
     * will be invoked.
     * An execution context must be stopped before the RT components that
     * participate in it are finalized.
     * An execution context may be started and stopped multiple times.
     *
     * @endif
     */
    virtual ReturnCode_t stop()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContext の実行周期を取得
     *
     * Active 状態にてRTコンポーネントが実行される周期(単位:Hz)を取得する。
     *
     * @return 処理周期(単位:Hz)
     *
     * @else
     *
     * @brief Get ExecutionRate
     *
     * This operation shall return the rate (in hertz) at which its Active
     * participating RTCs are being invoked.
     *
     * @endif
     */
    virtual CORBA::Double get_rate()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContext の実行周期を設定
     *
     * Active 状態にてRTコンポーネントが実行される周期(単位:Hz)を設定する。
     * 実行周期の変更は、 DataFlowComponentAction の on_rate_changed によって
     * 各RTコンポーネントに伝達される。
     *
     * @param rate 処理周期(単位:Hz)
     *
     * @return 処理実行結果
     *
     * @else
     *
     * @brief Set ExecutionRate
     *
     * This operation shall set the rate (in hertz) at which this context’s 
     * Active participating RTCs are being called.
     * If the execution kind of the context is PERIODIC, a rate change shall
     * result in the invocation of on_rate_changed on any RTCs realizing
     * DataFlowComponentAction that are registered with any RTCs participating
     * in the context.
     *
     * @endif
     */
    virtual ReturnCode_t  set_rate(CORBA::Double rate)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RTコンポーネントをアクティブ化する
     *
     * Inactive 状態にあるRTコンポーネントをActive に遷移させ、
     * アクティブ化する。
     * この操作が呼ばれた結果、 on_activate が呼び出される。
     * 指定したRTコンポーネントが参加者リストに含まれない場合は、BAD_PARAMETERが			 * 返される。
     * 指定したRTコンポーネントの状態が Inactive 以外の場合は、
     * PRECONDITION_NOT_METが返される。
     *
     * @param comp アクティブ化対象RTコンポーネント
     *
     * @return 処理実行結果
     *
     * @else
     *
     * @brief Activate a RT-component
     *
     * The given participant RTC is Inactive and is therefore not being invoked
     * according to the execution context’s execution kind. This operation
     * shall cause the RTC to transition to the Active state such that it may
     * subsequently be invoked in this execution context.
     * The callback on_activate shall be called as a result of calling this
     * operation. This operation shall not return until the callback has
     * returned, and shall result in an error if the callback does.
     *
     * @endif
     */
    virtual ReturnCode_t activate_component(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RTコンポーネントを非アクティブ化する
     *
     * Inactive 状態にあるRTコンポーネントを非アクティブ化し、
     * Inactive に遷移させる。
     * この操作が呼ばれた結果、 on_deactivate が呼び出される。
     * 指定したRTコンポーネントが参加者リストに含まれない場合は、BAD_PARAMETERが			 * 返される。
     * 指定したRTコンポーネントの状態が Active 以外の場合は、
     * PRECONDITION_NOT_METが返される。
     *
     * @param comp 非アクティブ化対象RTコンポーネント
     *
     * @return 処理実行結果
     *
     * @else
     *
     * @brief Deactivate a RT-component
     *
     * The given RTC is Active in the execution context. Cause it to transition 
     * to the Inactive state such that it will not be subsequently invoked from
     * the context unless and until it is activated again.
     * The callback on_deactivate shall be called as a result of calling this
     * operation. This operation shall not return until the callback has 
     * returned, and shall result in an error if the callback does.
     *
     * @endif
     */
    virtual ReturnCode_t deactivate_component(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RTコンポーネントをリセットする
     *
     * Error 状態のRTコンポーネントの復帰を試みる。
     * この操作が呼ばれた結果、 on_reset が呼び出される。
     * 指定したRTコンポーネントが参加者リストに含まれない場合は、BAD_PARAMETERが
     * 返される。
     * 指定したRTコンポーネントの状態が Error 以外の場合は、PRECONDITION_NOT_MET
     * が返される。
     *
     * @param comp リセット対象RTコンポーネント
     *
     * @return 処理実行結果
     *
     * @else
     *
     * @brief Reset a RT-component
     *
     * Attempt to recover the RTC when it is in Error.
     * The ComponentAction::on_reset callback shall be invoked. This operation
     * shall not return until the callback has returned, and shall result in an
     * error if the callback does. If possible, the RTC developer should
     * implement that callback such that the RTC may be returned to a valid
     * state.
     *
     * @endif
     */
    virtual ReturnCode_t reset_component(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RTコンポーネントの状態を取得する
     *
     * 指定したRTコンポーネントの状態(LifeCycleState)を取得する。
     * 指定したRTコンポーネントが参加者リストに含まれない場合は、UNKNOWN_STATEが
     * 返される。
     *
     * @param comp 状態取得対象RTコンポーネント
     *
     * @return 現在の状態(LifeCycleState)
     *
     * @else
     *
     * @brief Get RT-component's state
     *
     * This operation shall report the LifeCycleState of the given participant
     * RTC.
     *
     * @endif
     */
    virtual LifeCycleState get_component_state(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionKind を取得する
     *
     * 本 ExecutionContext の ExecutionKind を取得する
     *
     * @return ExecutionKind
     *
     * @else
     *
     * @brief Get the ExecutionKind
     *
     * This operation shall report the execution kind of the execution context.
     *
     * @endif
     */
    virtual ExecutionKind get_kind()
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RTコンポーネントを追加する
     *
     * 指定したRTコンポーネントを参加者リストに追加する。
     * 追加されたRTコンポーネントは attach_context が呼ばれ、Inactive 状態に遷移
     * する。
     * 指定されたRTコンポーネントがnullの場合は、BAD_PARAMETER が返される。
     * 指定されたRTコンポーネントがDataFlowComponent以外の場合は、
     * BAD_PARAMETER が返される。
     *
     * @param comp 追加対象RTコンポーネント
     *
     * @return 処理実行結果
     *
     * @else
     *
     * @brief Add a RT-component
     *
     * The operation causes the given RTC to begin participating in the
     * execution context.
     * The newly added RTC will receive a call to 
     * LightweightRTComponent::attach_context and then enter the Inactive state.
     *
     * @endif
     */
    virtual ReturnCode_t add(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief RTコンポーネントを参加者リストから削除する
     *
     * 指定したRTコンポーネントを参加者リストから削除する。
     * 削除されたRTコンポーネントは detach_context が呼ばれる。
     * 指定されたRTコンポーネントが参加者リストに登録されていない場合は、
     * BAD_PARAMETER が返される。
     *
     * @param comp 削除対象RTコンポーネント
     *
     * @return 処理実行結果
     *
     * @else
     *
     * @brief Remove the RT-component from participant list
     *
     * This operation causes a participant RTC to stop participating in the
     * execution context.
     * The removed RTC will receive a call to
     * LightweightRTComponent::detach_context.
     *
     * @endif
     */
    virtual ReturnCode_t remove(LightweightRTObject_ptr comp)
      throw (CORBA::SystemException);
    
    /*!
     * @if jp
     * @brief ExecutionContextProfile を取得する
     *
     * 本 ExecutionContext のプロファイルを取得する。
     *
     * @return ExecutionContextProfile
     *
     * @else
     *
     * @brief Get the ExecutionContextProfile
     *
     * This operation provides a profile “descriptor” for the execution 
     * context.
     *
     * @endif
     */
    virtual ExecutionContextProfile* get_profile()
      throw (CORBA::SystemException);
    
  protected:
    //============================================================
    // DFPBase
    //============================================================
    typedef LifeCycleState ExecContextState;
    /***
	enum ExecContextState
	{
	INACTIVE_STATE,
	ACTIVE_STATE,
	ERROR_STATE,
	};
    */
    typedef StateHolder<ExecContextState> ECStates;
    
    /*!
     * @if jp
     * @class DFPBase
     * @brief DFPBase クラス
     *
     * 参加者リストに登録された DataFlowParticipant を管理するための抽象クラス。
     *
     * @since 0.4.0
     *
     * @else
     *
     * @endif
     */
    class DFPBase
    {
    public:
      
      /*!
       * @if jp
       * @brief コンストラクタ
       *
       * コンストラクタ
       *
       * @param id 所属する ExecutionContext のID
       *
       * @else
       * @brief Constructor
       * @endif
       */
      DFPBase(UniqueId id)
	: ec_id(id), m_sm(3)
      {
	m_sm.setListener(this);
	m_sm.setEntryAction (ACTIVE_STATE, &DFPBase::on_activated);
	m_sm.setDoAction    (ACTIVE_STATE, &DFPBase::on_execute);
	m_sm.setPostDoAction(ACTIVE_STATE, &DFPBase::on_state_update);
	m_sm.setExitAction  (ACTIVE_STATE, &DFPBase::on_deactivated);
	m_sm.setEntryAction (ERROR_STATE,  &DFPBase::on_aborting);
	m_sm.setDoAction    (ERROR_STATE,  &DFPBase::on_error);
	m_sm.setExitAction  (ERROR_STATE,  &DFPBase::on_reset);
	
	ECStates st;
	st.prev = INACTIVE_STATE;
	st.curr = INACTIVE_STATE;
	st.next = INACTIVE_STATE;
	m_sm.setStartState(st);
	m_sm.goTo(INACTIVE_STATE);
      }	
      
      /*!
       * @if jp
       * @brief デストラクタ
       *
       * デストラクタ
       *
       * @else
       * @brief Destructor
       * @endif
       */
      virtual ~DFPBase(){}
      
      /*!
       * @if jp
       * @brief ExecutionContext 実行開始時に呼ばれる純粋仮想関数
       *
       * 参加している ExecutionContext が実行を開始する時(Running状態へ遷移時)
       * に呼ばれる純粋仮想関数。
       *
       * @else
       *
       * @brief
       *
       * The given execution context, in which the RTC is participating, has 
       * transitioned from Stopped to Running.
       *
       * @endif
       */
      virtual void on_startup() = 0;
      
      /*!
       * @if jp
       * @brief ExecutionContext 停止時に呼ばれる純粋仮想関数
       *
       * 参加している ExecutionContext が実行を停止する時(Stopped状態へ遷移時)
       * に呼ばれる純粋仮想関数。
       *
       * @else
       *
       * @brief
       *
       * The given execution context, in which the RTC is participating, has 
       * transitioned from Running to Stopped.
       *
       * @endif
       */
      virtual void on_shutdown() = 0;
      
      /*!
       * @if jp
       * @brief RTコンポーネントがアクティブ化された時に呼ばれる純粋仮想関数
       *
       * 管理対象のRTコンポーネントがアクティブ化された時
       * (Active状態へ遷移時)に呼ばれる純粋仮想関数。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @brief
       *
       * The RTC has been activated in the given execution context.
       *
       * @endif
       */
      virtual void on_activated(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RTコンポーネントが非アクティブ化された時に呼ばれる純粋仮想関数
       *
       * 管理対象のRTコンポーネントが非アクティブ化された時
       * (Deactive状態へ遷移時)に呼ばれる純粋仮想関数。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @brief
       *
       * The RTC has been deactivated in the given execution context.
       *
       * @endif
       */
      virtual void on_deactivated(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RTコンポーネントでエラーが発生した時に呼ばれる純粋仮想関数
       *
       * 管理対象のRTコンポーネントにエラーが発生した時(Error状態へ遷移時)
       * に呼ばれる純粋仮想関数。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @brief
       *
       * The RTC is transitioning from the Active state to the Error state 
       * in some execution context.
       *
       * @endif
       */
      virtual void on_aborting(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RTコンポーネントがエラー状態の時に呼ばれる純粋仮想関数
       *
       * 管理対象のRTコンポーネントがエラー状態にいる間、 on_execute と
       * on_state_update に替わって定期的に呼び出される純粋仮想関数。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @brief
       *
       * If the RTC is in the Error state relative to some execution context
       * when it would otherwise be invoked from that context.
       * This operation shall be invoked in sorted order at the rate of the
       * context instead of DataFlowComponentAction::on_execute and 
       * on_state_update.The RTC is transitioning from the Active state to 
       * the Error state in some execution context.
       *
       * @endif
       */
      virtual void on_error(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RTコンポーネントをリセットする時に呼ばれる純粋仮想関数
       *
       * 管理対象のRTコンポーネントをリセットする際に呼ばれる純粋仮想関数。
       * この関数が正常に終了すると，RTCは Inactive 状態に復帰する。
       * この関数が正常に終了しなかった場合は， Error 状態に留まる。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @brief
       *
       * The RTC is in the Error state. An attempt is being made to recover it 
       * such that it can return to the Inactive state.
       * If the RTC was successfully recovered and can safely return to 
       * the Inactive state, this method shall complete with ReturnCode_t::OK.
       * Any other result shall indicate that the RTC should remain in the 
       * Error state.
       *
       * @endif
       */
      virtual void on_reset(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RTコンポーネント実行時に定期的に呼ばれる純粋仮想関数
       *
       * 管理対象のRTコンポーネントが Active 状態であるとともに、
       * ExecutionContext が Running 状態の場合に、設定された動作周期で定期的に
       * 呼び出される純粋仮想関数。
       * Two-Pass Execution の最初の実行で呼ばれる。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @brief
       *
       * This operation will be invoked periodically at the rate of the given
       * execution context as long as the following conditions hold:
       *  - The RTC is Active.
       *  - The given execution context is Running.
       * This callback occurs during the first execution pass.
       *
       * @endif
       */
      virtual void on_execute(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief RTコンポーネント実行時に定期的に呼ばれる純粋仮想関数
       *
       * 管理対象のRTコンポーネントが Active 状態であるとともに、
       * ExecutionContext が Running 状態の場合に、設定された動作周期で定期的に
       * 呼び出される純粋仮想関数。
       * Two-Pass Execution の２番目の実行で呼ばれる。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @brief
       *
       * This operation will be invoked periodically at the rate of the given
       * execution context as long as the following conditions hold:
       *  - The RTC is Active.
       *  - The given execution context is Running.
       * This callback occurs during the second execution pass.
       *
       * @endif
       */
      virtual void on_state_update(const ECStates& st) = 0;
      
      /*!
       * @if jp
       * @brief ExecutionContext の実行周期変更時に呼ばれる純粋仮想関数
       *
       * 参加している ExecutionContext の実行周期が変更となった場合に、
       * この変更を伝達するために呼び出される純粋仮想関数。
       *
       * @else
       *
       * @brief
       *
       * This operation is a notification that the rate of the indicated
       * execution context has changed.
       *
       * @endif
       */
      virtual void on_rate_changed() = 0;
      
      /*!
       * @if jp
       * @brief 状態遷移を実行するワーカーを取得する
       *
       * 管理対象RTコンポーネントの状態遷移を実行するワーカーを取得する。
       *
       * @return ワーカー
       *
       * @else
       *
       * @brief
       *
       * @endif
       */
      virtual void worker() {return m_sm.worker();}
      
      /*!
       * @if jp
       * @brief 現在の状態を取得する
       *
       * 管理対象RTコンポーネントの現在の状態を取得する。
       *
       * @return 現在状態
       *
       * @else
       *
       * @brief
       *
       * @endif
       */
      virtual ExecContextState get_state(){ return m_sm.getState();}
      
      /*!
       * @if jp
       * @brief 参加している ExecutionContext の ID
       * @else
       *
       * @endif
       */
      UniqueId ec_id;
      
      /*!
       * @if jp
       * @brief 管理対象RTコンポーネントのステートマシン
       * @else
       *
       * @endif
       */
      StateMachine<ExecContextState, DFPBase> m_sm;
    };
    
    //============================================================
    // DFP
    //============================================================
    /*!
     * @if jp
     * @class DFP
     * @brief DFP クラス
     *
     * 参加者リストに登録された DataFlowParticipant の関数を起動するための
     * テンプレートクラス。
     *
     * @param Object 管理対象コンポーネントの型
     *
     * @since 0.4.0
     *
     * @else
     *
     * @endif
     */
    template <class Object>
    class DFP
      : public DFPBase
    {
    public:
      /*!
       * @if jp
       * @brief デフォルトコンストラクタ
       *
       * デフォルトコンストラクタ
       *
       * @param obj 管理対象コンポーネント
       * @param id 所属する ExecutionContext のID
       *
       * @else
       * @brief Constructor
       * @endif
       */
      DFP(Object obj, UniqueId id)
	: DFPBase(id), m_obj(obj), m_active(true)
      {
      }
      
      /*!
       * @if jp
       * @brief ExecutionContext 実行開始時に呼ばれる関数
       *
       * 参加している ExecutionContext が実行を開始する時(Running状態へ遷移時)
       * に、管理対象コンポーネントの on_startup を呼びだす。
       *
       * @else
       *
       * @brief
       *
       * @endif
       */
      void on_startup()
      {
	m_obj->on_startup(ec_id);
      }
      
      /*!
       * @if jp
       * @brief ExecutionContext 停止時に呼ばれる関数
       *
       * 参加している ExecutionContext が実行を停止する時(Stopped状態へ遷移時)
       * に、管理対象コンポーネントの on_shutdown を呼びだす。
       *
       * @else
       *
       * @endif
       */
      void on_shutdown()
      {
	m_obj->on_shutdown(ec_id);
      }
      
      /*!
       * @if jp
       * @brief RTコンポーネントがアクティブ化された時に呼ばれる関数
       *
       * 管理対象のRTコンポーネントがアクティブ化された時(Active状態へ遷移時)
       * に、管理対象コンポーネントの on_activated を呼びだす。
       * 管理対象コンポーネントのアクティブ化が失敗した場合には、ステートマシン
       * を Error 状態に遷移させる。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @endif
       */
      void on_activated(const ECStates& st)
      {
	if (m_obj->on_activated(ec_id) != RTC::RTC_OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return;
	  }
	return;
      }
      
      /*!
       * @if jp
       * @brief RTコンポーネントが非アクティブ化された時に呼ばれる関数
       *
       * 管理対象のRTコンポーネントが非アクティブ化された時
       * (Deactive状態へ遷移時)に、管理対象コンポーネントの on_deactivated を
       * 呼びだす。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @endif
       */
      void on_deactivated(const ECStates& st)
      {
	m_obj->on_deactivated(ec_id);
      }
      
      /*!
       * @if jp
       * @brief RTコンポーネントでエラーが発生した時に呼ばれる関数
       *
       * 管理対象のRTコンポーネントにエラーが発生した時(Error状態へ遷移時)
       * に管理対象コンポーネントの on_aborting を呼びだす。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @brief
       *
       * @endif
       */
      void on_aborting(const ECStates& st)
      {
	m_obj->on_aborting(ec_id);
      }
      
      /*!
       * @if jp
       * @brief RTコンポーネントがエラー状態の時に呼ばれる関数
       *
       * 管理対象のRTコンポーネントがエラー状態にいる間、 
       * 管理対象コンポーネントの on_aborting を定期的に呼びだす。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @brief
       *
       * @endif
       */
      void on_error(const ECStates& st)
      {
	m_obj->on_error(ec_id);
      }
      
      /*!
       * @if jp
       * @brief RTコンポーネントをリセットする時に呼ばれる関数
       *
       * 管理対象のRTコンポーネントをリセットする際に、管理対象コンポーネント
       * の on_reset を呼びだす。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @endif
       */
      void on_reset(const ECStates& st)
      {
	if (m_obj->on_reset(ec_id) != RTC::RTC_OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return;
	  }
	return;
      }
      
      /*!
       * @if jp
       * @brief RTコンポーネント実行時に定期的に呼ばれる関数
       *
       * 管理対象のRTコンポーネントが Active 状態であるとともに、
       * ExecutionContext が Running 状態の場合に、設定された動作周期で定期的に
       * 管理対象コンポーネントの on_execute を呼びだす。
       * 関数の実行に失敗した場合(返値が RTC_OK 以外)、管理対象コンポーネントの
       * 状態を Error 状態に遷移させる。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @endif
       */
      void on_execute(const ECStates& st)
      {
	if (m_obj->on_execute(ec_id) != RTC::RTC_OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return;
	  }  
	return;
      }
      
      /*!
       * @if jp
       * @brief RTコンポーネント実行時に定期的に呼ばれる関数
       *
       * 管理対象のRTコンポーネントが Active 状態であるとともに、
       * ExecutionContext が Running 状態の場合に、設定された動作周期で定期的に
       * 管理対象コンポーネントの on_state_update を呼びだす。
       * 関数の実行に失敗した場合(返値が RTC_OK 以外)、管理対象コンポーネントの
       * 状態を Error 状態に遷移させる。
       *
       * @param st 対象RTコンポーネントの現在の状態
       *
       * @else
       *
       * @endif
       */
      void on_state_update(const ECStates& st)
      {
	if (m_obj->on_state_update(ec_id) != RTC::RTC_OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return;
	  }
	return;
      }
      
      /*!
       * @if jp
       * @brief ExecutionContext の実行周期変更時に呼ばれる関数
       *
       * 参加している ExecutionContext の実行周期が変更となった場合に、
       * 管理対象コンポーネントの on_rate_changed を呼びだす。
       *
       * @else
       *
       * @endif
       */
      void on_rate_changed()
      {
	m_obj->on_rate_changed(ec_id);
      }
      
      /*!
       * @if jp
       * @brief 管理対象コンポーネント
       * @else
       *
       * @endif
       */
      Object m_obj;
      
      /*!
       * @if jp
       * @brief 管理対象コンポーネントの動作状態フラグ
       * @else
       *
       * @endif
       */
      bool m_active;
    };
    
    /*!
     * @if jp
     * @brief コンポーネント管理用構造体
     * @else
     *
     * @endif
     */
    struct Comp
    {
      Comp(LightweightRTObject_ptr ref, DataFlowComponent_ptr dfp,
	   UniqueId id)
	: _ref(ref), _sm(dfp, id)
      {
      }
      Comp(const Comp& comp)
	: _ref(comp._ref), _sm(comp._sm.m_obj, comp._sm.ec_id)
      {
      }
      Comp& operator=(const Comp& comp)
      {
	_ref = comp._ref;
	_sm.m_obj = comp._sm.m_obj;
	_sm.ec_id = comp._sm.ec_id;
	return *this;
      }
      LightweightRTObject_var _ref;
      DFP<DataFlowComponent_var> _sm;
    };
    
    /*!
     * @if jp
     * @brief コンポーネント検索用ファンクタ
     * @else
     *
     * @endif
     */
    struct find_comp
    {
      LightweightRTObject_var m_comp;
      find_comp(LightweightRTObject_ptr comp) : m_comp(comp) {}
      bool operator()(Comp& comp)
      {
	return comp._ref->_is_equivalent(m_comp);
      }
    };
    
    /*!
     * @if jp
     * @brief on_startup 起動用ファンクタ
     * @else
     *
     * @endif
     */
    struct invoke_on_startup
    {
      void operator()(Comp& comp)
      {
	comp._sm.on_startup();
      }
    };
    
    /*!
     * @if jp
     * @brief on_shutdown 起動用ファンクタ
     * @else
     *
     * @endif
     */
    struct invoke_on_shutdown
    {
      void operator()(Comp& comp)
      {
	comp._sm.on_shutdown();
      }
    };
    
    /*!
     * @if jp
     * @brief on_rate_changed 起動用ファンクタ
     * @else
     *
     * @endif
     */
    struct invoke_on_rate_changed
    {
      void operator()(Comp& comp)
      {
	comp._sm.on_rate_changed();
      }
    };
    
    /*!
     * @if jp
     * @brief ワーカー実行用ファンクタ
     * @else
     *
     * @endif
     */
    struct invoke_worker
    {
      void operator()(Comp& comp)
      {
	comp._sm.worker();
      }
    };
    
    /*!
     * @if jp
     * @brief コンポーネントの参加者リスト
     * @else
     *
     * @endif
     */
    std::vector<Comp> m_comps;
    typedef std::vector<Comp>::iterator CompItr;
    
    /*!
     * @if jp
     * @brief ExecutionContext の実行状態
     * @else
     *
     * @endif
     */
    bool m_running;
    
    /*!
     * @if jp
     * @brief ExecutionContextProfile
     * @else
     *
     * @endif
     */
    ExecutionContextProfile m_profile;
    
    /*!
     * @if jp
     * @brief ExecutionContext の実行周期
     * @else
     *
     * @endif
     */
    long int m_usec;
    
    /*!
     * @if jp
     * @brief ExecutionContextService オブジェクトへの参照
     * @else
     *
     * @endif
     */
    ExecutionContextService_var m_ref;
    
    /*!
     * @if jp
     * @brief ExecutionContext 即時実行(wait無し実行)フラグ
     * @else
     *
     * @endif
     */
    bool m_nowait;
  }; // class PeriodicExecutionContext
}; // namespace RTC

extern "C"
{
  void PeriodicExecutionContextInit(RTC::Manager* manager);
};

#endif

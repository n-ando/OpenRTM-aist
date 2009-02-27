// -*- C++ -*-
/*!
 * @file ExecutionContext.h
 * @brief ExecutionContext class
 * @date $Date: 2007-01-21 13:43:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef ExecutionContext_h
#define ExecutionContext_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/SystemLogger.h>

namespace RTC
{
  /*!
   * @if jp
   *
   * @class ExecutionContextBase
   * @brief ExecutionContext base class
   *
   * ExecutionContext は RTC のビジネスロジックをそれを実行するスレッド制御
   * から分離することを可能にする。 コンテキストは論理的なスレッド制御に相当し
   * 実行時に RTC に対して提供される。コンテキストは種々のオペレーションを持ち
   * それ自身およびコンテキストに所属する RTC が持つ状態を問い合わせたり変更
   * したりすることができる。
   * こうした関係の分離は以下の二つの理由に拠り重要です。
   * <ul>
   * <li> 多くのコンポーネントは一つのノードもしくはプロセス上で密接に協調
   *      する可能性があります。 それぞれのコンポーネント自身がスレッド制御
   *      を持つ場合、スレッドそれ自身の数やスレッド相互を同期させるために、
   *      ミドルウエアはリアルタイムアプリケーションにおける、リアルタイム性や
   *      決定論的な要求を満たすことができない可能性があります。
   * <li> 一つのアプリケーションは異なる周期で実行される複数の独立したタスクを
   *      実行するかもしれません。たとえば、センサのサンプリングを早い周期で
   *      行いながら、ユーザインターフェースの更新を遅い周期で行うかもしれ
   *      ません。
   * </ul>
   *
   * <b> オーナーシップとコンテキストへの所属 </b><br>
   * 各 ExecutionContext は一つの RTC に所属しており、その RTC および、
   * その RTC が包含する RTC の実行を直接的または非直接的に行う。 
   * 一つ以上の ExecutionContext を持つ RTC は autonomous RTC と呼ばれる。
   * autonomous RTC およびそこに含まれるそのサブセットの RTC (これはアプリケー
   * ション開発者により定義される。) は ExecutionKind に従って、ミドルウエア
   * により実行される。ExecutionKind はそれぞれの RTC のオペレーションは、いつ
   * どういった順番で実行するかを規定する。これらの RTC はそのコンテキストに
   * 「所属」すると表現される。利用可能な ExecutionKind は以下で述べる。
   * 一般的には、RTCと ExecutionContext の関係は多対多であるかもしれない。
   * たとえば、複数の RTC が同一の ExecutionContext により実行されたり、
   * 一つの RTC が複数の ExecutionContext から実行されたりするかもしれない。
   * 複数のRTCが同一のコンテキストから実行される場合には、ExecutionContext を
   * スタートあるいはストップさせたりすることにより、それら全てのコンポーネント
   * のライフサイクル状態を遷移させる可能性がある。
   *
   * <b> Logical and Physical Threads </b><br>
   * ExecutionContext が論理的スレッド制御を表現しているものの、
   * それをどうやって具体的なスレッドにマッピングするかといった選択は、
   * アプリケーションデプロイメント環境に委ねられている。
   * 実装に際しては関連付けられるExecutionContextと具体的なスレッドを一対一
   * でマッピングしたり、一つのスレッドが複数の ExecutionContext に関連付け
   * られたりする可能性がある。
   * RTC が複数の ExecutionContext により実行される場合のコンカレンシー管理
   * は実装依存である。
   *
   * @else
   *
   * @class ExecutionContextBase
   * @brief ExecutionContext base class
   *
   * An ExecutionContext allows the business logic of an RTC to be decoupled
   * from the thread of control in which it is executed. The context represents
   * a logical thread of control and is provided to RTCs at runtime as an
   * argument to various operations, allowing them to query and modify their
   * own state, and that of other RTCs executing within the same context, in
   * the lifecycle.
   * This separation of concerns is important for two primary reasons:
   * <ul>
   * <li> Large number of components may collaborate tightly within a single
   *      node or process. If each component were to run within its own thread
   *      of control, the infrastructure may not be able to satisfy the
   *      timeliness and determinism requirements of real-time applications due
   *      to the large number of threads and the required synchronization
   *      between them.
   * <li> A single application may carry out a number of independent tasks that
   *      require different execution rates. For example, it may need to sample
   *      a sensor periodically at a very high rate and update a user
   *      interface at a much lower rate.
   * </ul>
   *
   * <b> Ownership and Participation </b><br>
   * Each execution context is owned by a single RTC and may be used to execute
   * that RTC and the RTCs contained within it, directly or indirectly. An RTC
   * that owns one or more execution contexts is known as an autonomous RTC.
   * An autonomous RTC and some subset of the RTCs within it (to be defined by
   * the application developer) shall be executed by the infrastructure
   * according to the context's execution kind, which defines when each RTC's
   * operations will be invoked when and in which order. These RTCs are said
   * to participate in the context. The available execution kinds are described
   * below.
   * The relationship between RTCs and execution contexts may be many-to-many
   * in the general case: multiple RTCs may be invoked from the same execution
   * context, and a single RTC may be invoked from multiple contexts.
   * In the case where multiple RTCs are invoked from the same context,
   * starting or stopping the context shall result in the corresponding
   * lifecycle transitions for all of those components.
   *
   * <b> Logical and Physical Threads </b><br>
   * Although an execution context represents a logical thread of control,
   * the choice of how it maps to a physical thread shall be left to the
   * application’s deployment environment. Implementations may elect to
   * associate contexts with threads with a one-to-one mapping, to serve
   * multiple contexts from a single thread, or by any other means. In the
   * case where a given RTC may be invoked from multiple contexts, concurrency
   * management is implementation-dependent.
   *
   * @endif
   */
  class ExecutionContextBase
    : public virtual POA_RTC::ExecutionContextService,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    /*!
     * @if jp
     * @brief コンストラクタ
     * @else
     * @brief Constructor
     * @endif
     */
    ExecutionContextBase(RTObject_ptr owner);


    /*!
     * @if jp
     * @brief デストラクタ
     * @else
     * @brief Destructor
     * @endif
     */
    virtual ~ExecutionContextBase() {};

    //============================================================
    // ExecutionContext interfaces
    //============================================================
    /*!
     * @if jp
     * @brief ExecutionContext が実行中かどうかのテスト
     *
     * <h3> Description </h3>
     * このオペレーションはこの ExecutionContext の実行状態を返す。
     *
     * <h3> Semantics </h3>
     * このコンテキストが Running 状態であれば、全てのアクティブな RTC の
     * 参加コンポーネントはコンテキストの ExecutionKind に従って実行される。
     *
     * @return 実行状態であれば true を返す。
     *
     * @else
     *
     * @brief Test for ExecutionContext running state
     *
     * <h3>Description</h3>
     * This operation shall return true if the context is in the Running state.
     *
     * <h3> Semantics </h3>
     * While the context is Running, all Active RTCs participating in the
     * context shall be executed according to the context's execution kind.
     *
     * @return If the ExecutionContext is running, it returns true.
     *
     * @endif
     */
    virtual CORBA::Boolean is_running();


    /*!
     * @if jp
     *
     * @brief ExecutionContext をスタートさせる
     *
     * <h3> Description </h3>
     *  ExecutionContext に Running 状態に遷移させるためのオペレーション。
     * 状態遷移が発生した場合、ComponentAction::on_startup が実行される。
     * (OMG RTC Specification section 2.2.2.5.2 を参照)
     *
     * <h3> Semantics </h3>
     * ExecutionContext に対する start および stop は繰り返し実行される。
     *
     * <h3> Constraints </h3>
     * @return このオペレーションは ExecutionContext が Stopped 状態にないとき
     *         実行されると、PRECONDITION_NOT_MET が返される。
     *
     * @else
     *
     * @brief Start the ExecutionContext
     *
     * <h3> Description </h3>
     * Request that the context enter the Running state. Once the state
     * transition occurs, the ComponentAction::on_startup operation
     * (see OMG RTC Specification section 2.2.2.5.2) will be invoked.
     *
     * <h3> Semantics </h3>
     * An execution context may be started and stopped multiple times.
     *
     * <h3> Constraints </h3>
     * @return This operation shall fail with PRECONDITION_NOT_MET if the
     *         context is not in the Stopped state.
     *
     * @endif
     */
    virtual ReturnCode_t start();


    /*!
     * @if jp
     *
     * @brief ExecutionContext をストップさせる
     *  
     * <h3> Description </h3>
     *  ExecutionContext に Stopped 状態に遷移させるためのオペレーション。
     * 状態遷移が発生した場合、ComponentAction::on_shutdown が実行される。
     * (OMG RTC Specification section 2.2.2.5.4 を参照)
     *
     * <h3> Semantics </h3>
     * ExecutionContext に対する start および stop は繰り返し実行される。
     *
     * <h3> Constraints </h3>
     * @return このオペレーションは ExecutionContext が Stopped 状態にないとき
     *         実行されると、PRECONDITION_NOT_MET が返される。
     *
     * @else
     * @brief Stop the ExecutionContext
     *
     * <h3> Description </h3>
     * Request that the context enter the Stopped state. Once the transition
     * occurs, the ComponentAction::on_shutdown operation
     * (see OMG RTC Specification section 2.2.2.5.4) will be invoked.
     *
     * <h3> Semantics </h3>
     * An execution context may be started and stopped multiple times.
     *
     * <h3> Constraints </h3>
     * @return This operation shall fail with PRECONDITION_NOT_MET if the
     *         context is not in the Stopped state.
     *
     * @endif
     */
    virtual ReturnCode_t stop();


    /*!
     * @if jp
     *
     * @brief 実行周期(Hz)を取得する
     *
     * <h3> Description </h3>
     * このオペレーションはこのコンテキストに参加しているアクティブなRTC
     * の実行される周期をHzで返す。
     *
     * <h3> Semantics </h3>
     * 実装においては PERIODIC 以外の ExecutionKind を持つある種の周期的
     * もしくは擬似周期的な処理を実装することも許されます。その場合には、
     * このオペレーションの結果は実装定義に従います。
     * もし、このExecutionContextが周期的処理を行わないコンテキストである場合、
     * このオペレーションは失敗します。
     *
     * <h3> Constraints </h3>
     *@return このExecutionContext の ExecutionKind が PERIODICであれば、
     *         0より大きい値を返す。
     *
     * @else
     *
     * @brief Get executionrate(Hz)
     *
     * <h3> Description </h3>
     * This operation shall return the rate (in hertz) at which its Active
     * participating RTCs are being invoked.
     *
     * <h3> Semantics </h3>
     * An implementation is permitted to perform some periodic or
     * quasi-periodic processing within an execution context with an
     * ExecutionKind other than PERIODIC. In such a case, the result of this
     * operation is implementation-defined.
     * If no periodic processing of any kind is taking place within the
     * context, this operation shall fail as described in section 2.2.1 above.
     *
     * <h3> Constraints </h3>
     * @return If the context has an ExecutionKind of PERIODIC, this operation
     *         shall return a rate greater than zero.
     *
     * @endif
     */
    virtual CORBA::Double get_rate();


    /*!
     * @if jp
     *
     * @brief 実行周期(Hz)を与える 
     *
     * <h3> Description </h3>
     * このオペレーションはこのコンテキストが持つアクティブなRTCを実行する
     * 周期を与える。
     *
     * <h3> Semantics </h3>
     * この ExecutionContext の ExecutionKind が PERIODIC である場合、
     * 実行周期の変更に伴い、この ExecutionContext に参加する RTC として
     * 登録されている DataFlowComponentAction を実装した RTC のオペレーション
     * on_rate_changed を実行する。
     * 実装においては PERIODIC 以外の ExecutionKind を持つある種の周期的
     * もしくは擬似周期的な処理を実装することも許されます。加えてその実装に
     * おいて周期を get_rate により取得できる場合には、もし与えられた周期が
     * 有効な周期であれば、このオペレーションは周期を設定するものとします。
     * もし、このExecutionContextが周期的処理を行わないコンテキストである場合、
     * このオペレーションは ReturnCode_t::UNSUPPORTED を返して失敗します。
     *
     * <h3> Constraints </h3>
     * @return 与えられる周期は0より大きくなければならず、そうでない場合
     *         このオペレーションは ReturnCode_t::BAD_PARAMETER を返す。
     *
     * @else
     *
     * @brief Set rate (Hz)
     *
     * <h3> Description </h3>
     * This operation shall set the rate (in hertz) at which this context's
     * Active participating RTCs are being called.
     *
     * <h3> Semantics </h3>
     * If the execution kind of the context is PERIODIC, a rate change shall
     * result in the invocation of on_rate_changed on any RTCs realizing
     * DataFlowComponentAction that are registered with any RTCs participating
     * in the context.
     * An implementation is permitted to perform some periodic or
     * quasi-periodic processing within an execution context with an
     * ExecutionKind other than PERIODIC. If such is the case, and the
     * implementation reports a rate from get_rate, this operation shall set
     * that rate successfully provided that the given rate is valid. If no
     * periodic processing of any kind is taking place within the context,
     * this operation shall fail with ReturnCode_t::UNSUPPORTED.
     *
     * <h3> Constraints </h3>
     * @return The given rate must be greater than zero. Otherwise, this
     *         operation shall fail with ReturnCode_t::BAD_PARAMETER.
     *
     * @endif
     */
    virtual ReturnCode_t set_rate(CORBA::Double rate);


    /*!
     * @if jp
     *
     * @brief コンポーネントをアクティブ化する
     *
     * <h3> Description </h3>
     * 与えられる RTC はこのコンテキストにおいて Inactive であり、従って
     * ExecutionContext の ExecutionKind に従って実行されていない。
     * このオペレーションによってこの RTC はこの ExecutionContext によって
     * 実行される Active 状態に遷移する。
     *
     * <h3> Constraints </h3>
     * <ul>
     * <li> ExecutionContext はそれ自身に参加しているコンポーネントしか Active
     *      化できないので、もし与えられたRTCがこのコンテキストに参加していな
     *      ければ、このオペレーションは BAD_PARAMETER を返して失敗する。
     * <li> Error 状態にある RTC は reset しなければ Active 化できない。
     *      もし与えられた RTC が Error 状態にいる場合、このオペレーションは
     *      PRECONDITION_NOT_MET を返して失敗する。
     * </ul>
     * @return OK, BAD_PARAMETER もしくは PRECONDITION_NOT_MET を返す。
     *
     * @else
     *
     * @brief Activate a component
     * 
     * <h3> Description </h3>
     * The given participant RTC is Inactive and is therefore not being invoked
     * according to the execution context's execution kind. This operation
     * shall cause the RTC to transition to the Active state such that it may
     * subsequently be invoked in this execution context.
     *
     * <h3> Constraints </h3>
     * <ul>
     * <li> An execution context can only activate its participant components.
     *      If the given RTC is not participating in the execution context,
     *      this operation shall fail with BAD_PARAMETER.
     * <li> An RTC that is in the Error state cannot be activated until after
     *      it has been reset. If the given RTC is in the Error state, this
     *      operation shall fail with PRECONDITION_NOT_MET.
     * </ul>
     * @return This operation returns OK, BAD_PARAMETER or PRECONDITION_NOT_MET
     *
     * @endif
     */
    virtual ReturnCode_t activate_component(LightweightRTObject_ptr comp);


    /*!
     * @if jp
     *
     * @brief コンポーネントを非アクティブ化する
     *
     * <h3> Description </h3>
     * 与えられる RTC はこのコンテキストの中で Active 状態である。
     * このオペレーションによってこの RTC は Inactive 状態に遷移する。
     * Inactive 状態では Active 化されるまで RTC は実行されない。
     *
     * <h3> Constraints </h3>
     * <ul>
     * <li> ExecutionContext は自身に所属するコンポーネントのみ非アクティブ化
     *      できる。もし、与えられた RTC がこの ExecutionContext に所属してい
     *      ない場合 BAD_PARAMETER を返して失敗する。
     * </ul>
     * @return OK, BAD_PARAMETER を返す。
     *
     * @else
     *
     * @brief Deactivate a component
     *
     * <h3> Description </h3>
     * The given RTC is Active in the execution context. Cause it to transition
     * to the Inactive state such that it will not be subsequently invoked from
     * the context unless and until it is activated again.
     *  
     * <h3> Constraints </h3>
     * <ul>
     * <li> An execution context can only deactivate its participant
     *      components. If the given RTC is not participating in the execution
     *      context, this operation shall fail with BAD_PARAMETER.
     * </ul>
     * @return This operation returns OK or BAD_PARAMETER.
     *
     * @endif
     */
    virtual ReturnCode_t deactivate_component(LightweightRTObject_ptr comp);

    /*!
     * @if jp
     *
     * @brief コンポーネントをリセットする
     *
     * <h3> Description </h3>
     * 与えられる RTC はこのコンテキストの中で Error または Active 状態である。
     * このオペレーションによってこの RTC は Inactive 状態に遷移する。
     * Inactive 状態では Active 化されるまで RTC は実行されない。
     *
     * <h3> Constraints </h3>
     * <ul>
     * <li> ExecutionContext は自身に所属するコンポーネントのみ非アクティブ化
     *      できる。もし、与えられた RTC がこの ExecutionContext に所属してい
     *      ない場合 BAD_PARAMETER を返して失敗する。
     * </ul>
     * @return OK, BAD_PARAMETER を返す。
     *
     * @else
     *
     * @brief Deactivate a component
     *
     * <h3> Description </h3>
     * The given RTC is Error or Active in the execution context. Cause it to
     * transition to the Inactive state such that it will not be subsequently
     * invoked from the context unless and until it is activated again.
     *  
     * <h3> Constraints </h3>
     * <ul>
     * <li> An execution context can only deactivate its participant
     *      components. If the given RTC is not participating in the execution
     *      context, this operation shall fail with BAD_PARAMETER.
     * </ul>
     * @return This operation returns OK or BAD_PARAMETER.
     *
     * @endif
     */
    virtual ReturnCode_t reset_component(LightweightRTObject_ptr comp);


    /*!
     * @if jp
     *
     * @brief コンポーネントの状態を取得する
     *
     * <h3> Description </h3>
     *このオペレーションは与えられた RTC の LifeCycleState を返す。
     *
     * <h3> Constraints </h3>
     * <ul>
     * <li> RTC は Alive状態でなければならない。
     * <li> 与えられる RTC は ExecutionContext に所属していなければならない。
     * </ul>
     * @return LifeCycleState::INACTIVE, ACTIVE, ERROR を返す。
     *
     * @else
     *
     * @brief Get component's state
     *
     * <h3> Description </h3>
     * This operation shall report the LifeCycleState of the given participant
     * RTC.
     *
     * <h3> Constraints </h3>
     * <ul>
     * <li> The given RTC must be Alive.
     * <li> The given RTC must be a participant in the target ExecutionContext.
     * <li> The LifeCycleState returned by this operation shall be one of
     *      LifeCycleState::INACTIVE, ACTIVE, or ERROR.
     * </ul>
     * @return The LifeCycleState returned by this operation shall be one of
     *         LifeCycleState::INACTIVE, ACTIVE, or ERROR.
     * @endif
     */
    virtual LifeCycleState get_component_state(LightweightRTObject_ptr comp);


    /*!
     * @if jp
     *
     * @brief ExecutionKind を取得する
     *
     * <h3> Description </h3>
     * このオペレーションは ExecutionContext の ExecutionKind を返す。
     *
     * <h3> ExecutionKind </h3>
     * ExecutionKind 列挙子は ExecutionContext に属する Execution の
     * セマンティクス (OMG RTC Specification section 2.3 を参照) を定義する。
     * <table>
     * <tr><td> PERIODIC </td>
     *     <td> このタイプの ExecutionContext に属する RTC は
     *          periodic sampled data セマンティクスに従って実行
     *          される。(OMG RTC Specification section 2.3.1 を参照)</td>
     * </tr>
     * <tr><td> EVENT_DRIVEN </td>
     *     <td> このタイプの ExecutionContext に属する RTC は
     *          stimulus response セマンティクスに従って実行される。
     *          (OMG RTC Specification section 2.3.2 を参照) </td>
     * </tr>
     * <tr><td> OTHER </td>
     *     <td> このタイプの ExecutionContext に属する RTC は
     *          その実行セマンティクスは実装者が任意に実装でき、
     *          仕様上はとくに定義されていない。</td>
     * </tr>
     * </table>
     *
     * @else
     *
     * @brief Get the ExecutionKind
     *
     * <h3> Description </h3>
     * This operation shall report the execution kind of the execution context.
     *
     * <h3> ExecutionKind </h3>
     * The ExecutionKind enumeration defines the execution semantics
     * (see OMG RTC Specification section 2.3) of the RTCs that participate
     * in an execution context.
     * <table>
     * <tr><td> PERIODIC </td>
     *     <td> The participant RTCs are executing according to
     *          periodic sampled data semantics
     *          (see OMG RTC Specification section 2.3.1). </td>
     * </tr>
     * <tr><td> EVENT_DRIVEN </td>
     *     <td>  The participant RTCs are executing according to
     *           stimulus response semantics
     *           (see OMG RTC Specification section 2.3.2).</td>
     * </tr>
     * <tr><td> OTHER </td>
     *     <td> The participant RTCs are executing according to some
     *          semantics not defined by this specification.</td>
     * </tr>
     * </table>
     * @endif
     */
    virtual ExecutionKind get_kind();


    /*!
     * @if jp
     *
     * @brief コンポーネントを追加する
     *
     * <h3> Description </h3>
     * このオペレーションは与えられたRTCをこのExecutionContextに所属させる。
     *
     * <h3> Semantics </h3>
     * 新たに追加された　RTC ははじめは　Inactive 状態にある。
     * ExecutionKind が PERIODIC ならば引数 index はこの RTC が実行される
     * 順番におけるソートされた位置を指定する。
     * それ以外では、実装依存であり無視されるかもしれない。
     *
     * <h3> Constraints </h3>
     * <ul>
     * <li> ExecutionKind が PERIODIC の場合, RTC は data flow participant
     *      (OMG RTC Specification section 2.3.1.2 を参照) でなければならない。
     *      それ以外は、このオペレーションは PRECONDITION_NOT_MET
     *      を返し失敗する。.
     * </ul>
     * @return OK or PRECONDITION_NOT_ME が返される
     *
     * @else
     *
     * @brief Add a component
     *
     * The operation causes the given RTC to begin participating in the
     * execution context.
     *
     * The newly added RTC will begin in the Inactive state.
     * If the ExecutionKind is PERIODIC, the index represents the sorted order
     * in which the RTC is to be executed. Otherwise, the meaning of the index
     * is implementation-defined and may be ignored.
     * <p>
     * <h3> Constraints </h3>
     * <ul>
     * <li> If the ExecutionKind is PERIODIC, the RTC must be a data flow
     *      participant (see OMG RTC Specification section 2.3.1.2).
     *      Otherwise, this operation will fail with PRECONDITION_NOT_MET.
     * </ul>
     * @return OK or PRECONDITION_NOT_ME would be returned.
     * </p>
     * @endif
     */
    virtual ReturnCode_t add_component(LightweightRTObject_ptr comp);

    /*!
     * @if jp
     *
     * @brief コンポーネントをコンポーネントリストから削除する
     * 
     * <h3> Description </h3>
     * このオペレーションは所属している RTC を所属から抹消する。
     * <b> Constraints </b>
     * <ul>
     * <li> もし与えられた RTC がこのコンテキストに参加していない場合には、
     *      このオペレーションは BAD_PARAMETER を返す。
     * <li> RTC をこの ExecutionContext の所属からはずす場合には、
     *      RTC は非アクティブ化しなければならない。
     *      与えられた RTC が ExecutionContext に所属しているものの、
     *      Active 状態にいる場合には、PRECONDITION_NOT_MET を返す。
     * </ul>
     *
     * @else
     *
     * @brief Remove the component from component list
     *
     * <h3> Description </h3>
     * This operation causes a participant RTC to stop participating in the
     * execution context.
     * 
     * <h3> Constraints </h3>
     * <ul>
     * <li> If the given RTC is not currently participating in the execution
     *      context, this operation shall fail with BAD_PARAMETER.
     * <li> An RTC must be deactivated before it can be removed from an
     *      execution context. If the given RTC is participating in the
     *      execution context but is still in the Active state, this operation
     *      shall fail with PRECONDITION_NOT_MET.
     * </ul>
     * @endif
     */			     
    virtual ReturnCode_t remove_component(LightweightRTObject_ptr comp);


    //============================================================
    // ExecutionContextAdmin interfaces
    //============================================================
    /*!
     * @if jp
     *
     * @brief ExecutionContextProfile を取得する
     *
     * <h3> Description </h3>
     * このオペレーションは ExecutionContext の Profile を取得する
     *
     * @else
     *
     * @brief Get the ExecutionContextProfile
     *
     * <h3> Description </h3>
     * This operation provides a profile descriptor for the execution context.
     *
     * @endif
     */
    virtual ExecutionContextProfile* get_profile();


  protected:
    Logger rtclog;
    ExecutionContextProfile m_profile;
    CORBA::Boolean m_running;

    template <class ObjRef>
    struct find_objref
    {
      find_objref(ObjRef ref) : m_ref(ref) {};
      bool operator()(ObjRef ref)
      {
	return ref->_is_equivalent(m_ref);
      }
      ObjRef m_ref;
    };
    /*
    {
                ExecutionKind kind;
                double rate;
                RTObject owner;
                RTCList participants;
                NVList properties;
        };
    */


  };

}; // namespace RTC

#endif // ExecutionContext_h 

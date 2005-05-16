// -*- C++ -*-
/*!
 * @file RtcBase.h
 * @brief RT component base class
 * @date $Date: 2005-05-16 06:02:49 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcBase.h,v 1.2 2005-05-16 06:02:49 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
 * Public release.
 *
 *
 */

#ifndef RtcBase_h
#define RtcBase_h

// CORBA header include
#include "rtm/RTC.h"

// STL includes
#include <list>
#include <string>
#include <algorithm>
#include <functional>

// ACE
#include <ace/Task.h>

// local includes 
#include "rtm/idl/RTCBaseSkel.h"
#include "rtm/idl/RTCBaseStub.h"
#include "rtm/RtcOutPort.h"
#include "rtm/RtcModuleProfile.h"
#include "rtm/RtcSystemLogger.h"

#define USLEEP(x) \
{ \
  ACE_Time_Value tv(0, x);\
  ACE_OS::sleep(tv);\
}

namespace RTM {
  // namespace
  using namespace std;
  
  
  class InPortBase;
  class OutPortBase;
  class RtcManager;
  
  static char* StateString[] =
	{
	  "RTC_UNKNOWN",
	  "RTC_BORN",
	  "RTC_INITIALIZING",
	  "RTC_READY",
	  "RTC_STARTING",
	  "RTC_ACTIVE",
	  "RTC_STOPPING",
	  "RTC_ABORTING",
	  "RTC_ERROR",
	  "RTC_FATAL_ERROR",
	  "RTC_EXITING",
	  "UNKNOWN"
	};

  /*!
   * @if jp
   * @brief RTComponent 状態型再宣言
   * @else
   * @brief RTComponent state re-declaration
   * @endif
   */
  typedef RTM::RTComponent::ComponentState ComponentState;
  
  const ComponentState RTC_UNKNOWN      = 0; //RTM::RTComponent::RTC_UNKNOWN;
  const ComponentState RTC_BORN         = 1; //RTM::RTComponent::RTC_BORN;
  const ComponentState RTC_INITIALIZING = 2; //RTM::RTComponent::RTC_INITIALIZING;
  const ComponentState RTC_READY        = 3; //RTM::RTComponent::RTC_READY;
  const ComponentState RTC_STARTING     = 4; //RTM::RTComponent::RTC_STARTING;
  const ComponentState RTC_ACTIVE       = 5; //RTM::RTComponent::RTC_ACTIVE;
  const ComponentState RTC_STOPPING     = 6; //RTM::RTComponent::RTC_STOPPING;
  const ComponentState RTC_ABORTING     = 7; //RTM::RTComponent::RTC_ABORTING;
  const ComponentState RTC_ERROR        = 8; //RTM::RTComponent::RTC_ERROR;
  const ComponentState RTC_FATAL_ERROR  = 9; //RTM::RTComponent::RTC_FATAL_ERROR;
  const ComponentState RTC_EXITING      = 10;//RTM::RTComponent::RTC_EXITING;

  typedef enum NamingPolicy {
	UNKNOWN = 0,
	LONGNAME_ENABLE = 1,
	ALIAS_ENABLE = 2
  };

  /*!
   * @if jp
   *
   * @class RtcBase
   *
   * @brief RTComponent 基底クラス
   *
   * RTComponent 開発者は新たに作成するコンポーネントのクラスをこのRtcBaseの
   * サブクラスとして定義しなければならない。
   * 新たに作成するコンポーネントにおいて、必要なアクティビティの状態に対応する
   * メソッド rtc_active_do() 等を適宜オーバーライドして、各状態にて行う処理を
   * そのメソッドに記述する。
   * rtc_xxx_entry(), rtc_xxx_exit() ではその状態に入るときと出るときに一度だけ
   * それらのメソッドが実行され、rtc_xxx_do() ではその状態にいる間中、そのメソ
   * ッドが周期実行される。
   * 各メソッド rtc_xxx_[entry|do|exit]() では戻り値に RTM_OK, RTM_ERR, 
   * RTM_WARNING, RTM_FATAL_ERR のいずれかを返す。
   * RTM_ERR を返すと ERROR 状態に、RTM_FATAL_ERR を返すと FATAL_ERROR 状態に
   * 移行する。その他の状態遷移についてはマニュアルを参照。
   * 
   * 新たに作成するコンポーネントのクラスでは、 InPort , OutPort とこれに
   * バインドされる InPort , OutPort の型に対応する変数を定義する。
   * コンポーネントのクラスのコンストラクタでは、これらの変数を初期化子を用いて
   * 初期化し、コンストラクタ内で registerInPort , registerOutPort を用いて
   * それぞれ InPort , OutPort として登録する必要がある。
   *
   * @else
   *
   * @class RtcBase
   *
   * @brief RT component base class.
   *
   * RT-component developer should derive this base class to create own RT
   * component class.
   * Procedure is as follows.
   *
   * In your RT-conponent class, you have to define input variable and output
   * variable. Input channel and output channel also should be defined as 
   * InPort<T> objects or OutPort<T> objects. These variables and channel
   * objects should be bound each other in the constructor.
   *
   * In the constructor of your component class, input channel objects and 
   * output channel objects have to make registration as CORBA objects using
   * registerInPort , registerOutPort method.
   *
   * @endif
   */
  class EXPORTS RtcBase  
	: public virtual POA_RTM::RTCBase, 
      public virtual PortableServer::RefCountServantBase,
      public ACE_Task<ACE_MT_SYNCH>
  {
  public:

	/*!
	 * @if jp
	 * @brief RtcBase クラスコンストラクタ
	 *
	 * RTComponent サーバント実装の基底クラス RtcBase のコンストラクタ。
	 * このコンストラクタを使用する場合、ユーザはORBへのポインタとPOAのポインタ
	 * あるいは、マネージャへのポインタを後でセットする必要がある。
	 *
	 * @else
	 *
	 * @brief A constructor of RtcBase class.
	 *
	 * Constructor of RtcBase which is RTComponent servant implementation
	 * base classes without arguments.
	 * If use this constructor, user have to set the ORB pointer and a POA
	 * pointer or a pointer to RtcManager.
	 *
	 * @endif
	 */
	RtcBase();
	
	/*!
	 * @if jp
	 * @brief RtcBase クラスコンストラクタ
	 *
	 * RTComponent サーバント実装の基底クラス RtcBase のコンストラクタ。
	 *
	 * ORB へのポインタとPOAへのポインタがすでに得られている場合には、この
	 * コンストラクタを使用することが出来る。
	 *
	 * @param orb ORB へのポインタ
	 * @param poa POA へのポインタ
	 *
	 * @else
	 *
	 * @brief A constructor of RtcBase class.
	 *
	 * If the ORB pointer and a POA pointer are already available, user can use
	 * this constructor.
	 *
	 * @param orb pointer to ORB
	 * @param poa pointer to POA
	 *
	 * @endif
	 */
	RtcBase(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);

	/*!
	 * @if jp
	 *
	 * @brief RtcBase クラスコンストラクタ
	 *
	 * 通常はマネージャを通してコンポーネントクラスをインスタンス化し、
	 * このコンストラクタを使用することを推奨する。
	 *
	 * @param manager コンポーネントマネージャ RtcManager へのポインタ
	 *
	 * @else
	 *
	 * @brief A constructor.
	 *
	 * @param manager pointer to component manager: RtcManager
	 * @endif
	 */
	RtcBase(RtcManager* manager);
	
	/*!
	 * @if jp
	 * 
	 * @brief RtcBase クラスデストラクタ
	 *
	 * @else
	 *
	 * @brief A destructor of RtcBase class.
	 *
	 * @endif
	 */
	virtual ~RtcBase();
	
	//============================================================
	//
	// <<< CORBA interfaces >>>
	//
	//============================================================
	
	//============================================================
	// State implementation functions 
	//============================================================
	/*
	 * 
	 *                                   __                      __
	 *                         _________V_ \          __________V_ \
	 *                        |           |/  (any)->|            |/
	 *                        |  Active   |          | FatalError |
	 *                        |___________|--,       |____________|
	 *                            A    |  ___|______      |
	 *                      ______|___ | |          |     |
	 *                     |          || | Aborting |     |
	 *                     | Starting || |__________|     |
	 *                     |__________||     |   __       |
	 *             ____________   |    |   __V__V_ \   ___V_____
	 *   _____    |            |<-+----+--|       |/  |         |    ___
	 *  (Start)-->|Initializing|  |    |  | Error |-->| Exiting |-->(End)
	 *   ~~~~~    |____________|--+----+->|_______|   |_________|    ~~~
	 *                A  |        | ___|______  A         A
	 *                |  |        ||          | |         |
	 *                |  |        || Stopping | |         |
	 *                |  |        ||__________| |         |
	 *                |  |        |    |        |         |
	 *                |  |     ___|____V__      |         |
	 *                |  `--->|           |-----'         |
	 *                `-------|   Ready   |               |
	 *                       /|___________|---------------'
	 *                       \__A
	 *
	 */
	
	//------------------------------------------------------------
	// Transition operation of component activity state
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] コンポーネントのアクティブ化
	 *
	 * コンポーネントの状態を READY から ACTIVE に遷移させる。
	 * このオペレーションを発行するとき、コンポーネントは READY 状態でなければ
	 * ならない。他の状態の場合には IllegalTransition 例外が発生する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Activate this components' activity
	 * 
	 * @endif
	 */
	virtual RtmRes rtc_start()
	  throw (CORBA::SystemException, RTM::RTComponent::IllegalTransition);
	
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] コンポーネントの非アクティブ化
	 *
	 * コンポーネントの状態を ACTIVE から READY に遷移させる。
	 * このオペレーションを発行するとき、コンポーネントは ACTIVE 状態でなければ
	 * ならない。他の状態の場合には IllegalTransition 例外が発生する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Stop this component's activity
	 * 
	 * @endif
	 */
	virtual RtmRes rtc_stop()
	  throw (CORBA::SystemException, RTM::RTComponent::IllegalTransition);
	
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] コンポーネントのリセット
	 *
	 * コンポーネントの状態を ERROR から INITIALIZE に遷移させる。
	 * INITIALIZE 後エラーがなければすぐに READY 状態に遷移する。
	 * このオペレーションを発行するとき、コンポーネントは ERROR 状態でなければ
	 * ならない。他の状態の場合には IllegalTransition 例外が発生する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Go to init() state from error() state
	 * 
	 * @endif
	 */
	virtual RtmRes rtc_reset()
	  throw (CORBA::SystemException, RTM::RTComponent::IllegalTransition);
	
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] コンポーネントのリセット
	 *
	 * コンポーネントの状態を EXITING に遷移させる。
	 * EXITING 状態に遷移したコンポーネントは二度と復帰することなく終了する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Go to term() state from anywhere
	 * 
	 * @endif
	 */
	virtual RtmRes rtc_exit()
	  throw (CORBA::SystemException, RTM::RTComponent::IllegalTransition);
	
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] コンポーネントの強制終了
	 *
	 * FATAL_ERROR 状態のコンポーネントを EXITING に遷移させる。
	 * EXITING 状態に遷移したコンポーネントは二度と復帰することなく終了する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Go to exiting() state from active() state 
	 * 
	 * @endif
	 */
	virtual RtmRes rtc_kill();
	
	//------------------------------------------------------------
	// Main activity
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * 
	 * @brief [CORBA interface] メインアクティビティのメソッド
	 *
	 * コンポーネントのアクティビティの本体はこのメソッドを周期実行することに
	 * より処理される。単体のコンポーネントでは内部的なスレッドによりこのメソ
	 * ッドを周期呼出することで処理を行っている。
	 * スレッドを停止させ、外部からこのオペレーションを呼び出すことにより、任
	 * 意のタイミングでアクティビティを実行することも出来る。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Main activity function. 
	 *
	 * Called from activity thread periodically.
	 * 
	 * @endif
	 */
	virtual RtmRes rtc_worker();
	
	
	// ** Steady state **
	//------------------------------------------------------------
	// Ready state methods
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: ready() メソッド
	 *
	 * READY 状態へ進入するときに1度だけ呼び出されるメソッド。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: ready() method.
	 *
	 * This method will be called once when component enter
	 * to Ready state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_ready_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] do: ready() メソッド.
	 *
	 * READY 状態にいる間周期実行されるメソッド。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] do: ready() method.
	 *
	 * This method will be called repeatedly when component state is Ready.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_ready_do()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] exit: ready() メソッド.
	 *
	 * READY 状態から出るときに1度だけ実行されるメソッド。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] exit: ready() method.
	 *
	 * This method will be called once when component exit from Ready state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_ready_exit()
	{USLEEP(1000); return RTM_OK;};
	
	
	//------------------------------------------------------------
	// Active state methods
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: active() メソッド.
	 *
	 * ACTIVE 状態に進入するときに1度だけ実行されるメソッド。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: active() method.
	 *
	 * This method will be called once when component enter to Active state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_active_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] do: active() メソッド.
	 *
	 * ACTIVE 状態に居る間周期実行されるメソッド。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] do: active() method.
	 *
	 * This method will be called repeatedly when component state is Active.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_active_do()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] exit: active() メソッド.
	 *
	 * ACTIVE 状態から出るときに1度だけ実行されるメソッド。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] exit: active() method.
	 *
	 * This method will be called once when component exit from Active state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_active_exit()
	{USLEEP(1000); return RTM_OK;};
	
	
	//------------------------------------------------------------
	// Error state methods
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: error() メソッド
	 *
	 * ERROR 状態へ進入するときに1度だけ呼び出されるメソッド。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: error() method.
	 *
	 * This method will be called once when component enter to Error state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_error_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] do: error() メソッド.
	 *
	 * ERROR 状態にいる間周期実行されるメソッド。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] do: ready() method.
	 *
	 * This method will be called repeatedly when component state is Error.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_error_do()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] exit: error() メソッド.
	 *
	 * ERROR 状態から出るときに1度だけ実行されるメソッド。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] exit: error() method.
	 *
	 * This method will be called once when component exit from Error state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_error_exit()
	{USLEEP(1000); return RTM_OK;};
	
	
	//------------------------------------------------------------
	// FatalError state methods
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: fatal() メソッド
	 *
	 * FATAL_ERROR 状態へ進入するときに1度だけ呼び出されるメソッド。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: fatal() method.
	 *
	 * This method will be called once when component enter to FATAL_ERROR
	 * state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_fatal_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] do: fatal() メソッド.
	 *
	 * FATAL_ERROR 状態にいる間周期実行されるメソッド。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] do: fatal() method.
	 *
	 * This method will be called repeatedly when component state is
	 * FATAL_ERROR state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_fatal_do()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] exit: fatal() メソッド.
	 *
	 * READY 状態から出るときに1度だけ実行されるメソッド。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] exit: fatal() method.
	 *
	 * This method will be called once when component exit from FATAL_ERROR
	 * state.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_fatal_exit()
	{USLEEP(1000); return RTM_OK;};
	//------------------------------------------------------------
	
	// ** Transient state **
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: init() メソッド
	 *
	 * INITIALIZING 状態へ進入するときに1度だけ呼び出されるメソッド。
	 * エラーがなければ READY 状態へ遷移する。
	 * 戻り値が RTM_ERR で ERROR 状態へ、 RTM_FATALERR で FATAL_ERROR 状態へ
	 * 遷移する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: ready() method.
	 *
	 * This method will be called and move to Ready/Error state immediately.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_init_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: starting() メソッド
	 *
	 * STARTING 状態へ進入するときに1度だけ呼び出されるメソッド。
	 * エラーがなければ ACTIVE 状態へ遷移する。
	 * 戻り値が RTM_ERR で ERROR 状態へ、 RTM_FATALERR で FATAL_ERROR 状態へ
	 * 遷移する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: starting() method.
	 *
	 * This method will be called and move to Active state immediately.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_starting_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: stopping() メソッド
	 *
	 * STOPPING 状態へ進入するときに1度だけ呼び出されるメソッド。
	 * エラーがなければ READY 状態へ遷移する。
	 * 戻り値が RTM_ERR で ERROR 状態へ、 RTM_FATALERR で FATAL_ERROR 状態へ
	 * 遷移する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: stopping() method.
	 *
	 * This method will be called and move to Ready state immediately.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_stopping_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: aborting() メソッド
	 *
	 * ABORTING 状態へ進入するときに1度だけ呼び出されるメソッド。
	 * エラーがなければ READY 状態へ遷移する。
	 * 戻り値が RTM_ERR で ERROR 状態へ、 RTM_FATALERR で FATAL_ERROR 状態へ
	 * 遷移する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: aborting() method.
	 *
	 * This method will be called and move to Error state immediately.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_aborting_entry()
	{USLEEP(1000); return RTM_OK;};
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] entry: exiting() メソッド
	 *
	 * EXITING 状態へ進入するときに1度だけ呼び出されるメソッド。
	 * エラーがなければ READY 状態へ遷移する。
	 * 戻り値が RTM_ERR で ERROR 状態へ、 RTM_FATALERR で FATAL_ERROR 状態へ
	 * 遷移する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] entry: exiting() method.
	 *
	 * This method will be called and terminate component.
	 *
	 * @endif
	 */
	virtual RtmRes rtc_exiting_entry()
	{USLEEP(1000); return RTM_OK;};
	
	
	//------------------------------------------------------------
	// Status handling
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] アクティビティステータスのOutPortの取得
	 *
	 * アクティビティステータスのOutPortのオブジェクトリファレンスを取得する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get activity status OutPort
	 *
	 * @endif
	 */
	virtual OutPort_ptr rtc_state();
	
	//------------------------------------------------------------
	// Get inports and outport object reference
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] InPortList の取得
	 *
	 * InPort のオブジェクトリファレンスのリストを取得する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Return input port object reference list
	 *
	 * @endif
	 */
	virtual InPortList* inports() ;

	/*!
	 * @if jp
	 * @brief [CORBA interface] InPort の取得
	 *
	 * InPort のオブジェクトリファレンスを取得する。
	 *
	 * @param name InPort 名
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Return input port object reference
	 *
	 * @param name InPort name
	 *
	 * @endif
	 */
	virtual InPort_ptr get_inport(const char* name)
	  throw (CORBA::SystemException, RTM::RTComponent::NoSuchName); 
	
	/*!
	 * @if jp
	 * @brief [CORBA interface] OutPortList の取得
	 *
	 * OutPort のオブジェクトリファレンスのリストを取得する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Return output port object reference list
	 *
	 * @endif
	 */
	virtual OutPortList* outports() ;

	/*!
	 * @if jp
	 * @brief [CORBA interface] OutPort の取得
	 *
	 * OutPort のオブジェクトリファレンスを取得する。
	 *
	 * @param name OutPort 名
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Return output port object reference
	 *
	 * @param name OutPort name
	 *
	 * @endif
	 */
	virtual OutPort_ptr get_outport(const char* name)
	  throw (CORBA::SystemException, RTM::RTComponent::NoSuchName);
	
	//------------------------------------------------------------
	// [CORBA interface] Getting component property
	//------------------------------------------------------------
	//  CORBA::Any* get_property(const char* name) {return NULL;};
	//  char* get_properties_xml() {return NULL;};
	//  virtual char* instance_name() {return "RtcBase0";}
	//  virtual char* class_name() {return "RtcBase";}

	/*!
	 * @if jp
	 * @brief [CORBA interface] instance_id の取得
	 *
	 * コンポーネントのインスタンスIDを取得する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get instance_id
	 *
	 * @endif
	 */
	virtual char* instance_id();

	/*!
	 * @if jp
	 * @brief [CORBA interface] implementation_id の取得
	 *
	 * コンポーネントのインプリメンテーションIDを取得する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get implementation_id
	 *
	 * @endif
	 */
    virtual char* implementation_id();

	/*!
	 * @if jp
	 * @brief [CORBA interface] description の取得
	 *
	 * コンポーネントの概要説明を取得する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get description
	 *
	 * @endif
	 */
    virtual char* description();

	/*!
	 * @if jp
	 * @brief [CORBA interface] version の取得
	 *
	 * コンポーネントのバージョンを取得する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get version
	 *
	 * @endif
	 */
    virtual char* version();

	/*!
	 * @if jp
	 * @brief [CORBA interface] maker の取得
	 *
	 * コンポーネントの作成者を取得する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get maker
	 *
	 * @endif
	 */
    virtual char* maker();

	/*!
	 * @if jp
	 * @brief [CORBA interface] category の取得
	 *
	 * コンポーネントのカテゴリを取得する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get category
	 *
	 * @endif
	 */
    virtual char* category();

	/*!
	 * @if jp
	 * @brief [CORBA interface] profile の取得
	 *
	 * コンポーネントのプロファイルを取得する。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] get profile
	 *
	 * @endif
	 */
	virtual RTCProfile* profile() ;
	//	virtual RTCConfiguration* configuration() ;

	
	
	//------------------------------------------------------------
	// [CORBA interface] composit component interfaces
	//
	// These interfaces are methods for RTCompositComponet
	// Almost all methods do nothing. Only rtc_components and 
	// rtc_get_componet methods return this component itself.
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief [CORBA interface] アクティビティスレッドのスタート
	 *
	 * コンポーネントアクティビティの内部スレッドをスタートさせる
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Start activity internal thread
	 *
	 * @endif
	 */
	virtual RtmRes rtc_start_thread();

	/*!
	 * @if jp
	 * @brief [CORBA interface] アクティビティスレッドのサスペンド
	 *
	 * コンポーネントアクティビティの内部スレッドをサスペンドさせる
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Suspend activity internal thread
	 *
	 * @endif
	 */
	virtual RtmRes rtc_suspend_thread();

	/*!
	 * @if jp
	 * @brief [CORBA interface] アクティビティスレッドのストップ
	 *
	 * コンポーネントアクティビティの内部スレッドをストップさせる
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Stop activity internal thread
	 *
	 * @endif
	 */
	virtual RtmRes rtc_stop_thread();

	/*!
	 * @if jp
	 * @brief [CORBA interface] 親コンポーネントをセットする
	 *
	 * 親コンポーネントのオブジェクトリファレンスをセットする。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Set parent component
	 *
	 * @endif
	 */
	virtual RtmRes rtc_set_parent(RTCBase_ptr comp);

	/*!
	 * @if jp
	 * @brief [CORBA interface] 子コンポーネントを追加する
	 *
	 * 子コンポーネントのオブジェクトリファレンスをセットする。
	 * 単体コンポーネントにおいてこのメソッドは未使用のため、RTM_ERR を返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Set child component
	 *
	 * @endif
	 */
	virtual RtmRes rtc_add_component(RTCBase_ptr comp)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] 子コンポーネントを削除する
	 *
	 * 子コンポーネントのオブジェクトリファレンスを削除する。
	 * 単体コンポーネントにおいてこのメソッドは未使用のため、RTM_ERR を返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Delete child component
	 *
	 * @endif
	 */
	virtual RtmRes rtc_delete_component(RTCBase_ptr comp)
	{return RTM_ERR;} ;

	/*!
	 * @if jp
	 * @brief [CORBA interface] 子コンポーネントの順序を入れ替える
	 *
	 * 2つの子コンポーネントをオブジェクトリファレンスを使用して順序を入れ替え
	 * る。
	 * 単体コンポーネントにおいてこのメソッドは未使用のため、RTM_ERR を返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Replace two child components
	 *
	 * @endif
	 */
	virtual RtmRes rtc_replace_component(RTCBase_ptr comp1, RTCBase_ptr comp2)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] 子コンポーネントの順序を入れ替える
	 *
	 * 2つの子コンポーネントの順序をコンポーネント名を指定して入れ替える。
	 * 単体コンポーネントにおいてこのメソッドは未使用のため、RTM_ERR を返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Replace two child components
	 *
	 * @endif
	 */
	virtual RtmRes rtc_replace_component_by_name(const char* name1, const char* name2)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] 子コンポーネントをリストとして取得する。
	 *
	 * 子コンポーネントのリストを取得する。
	 * 単体コンポーネントにおいては自分自身オブジェクトリファレンスを返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RTCBaseList* rtc_components()
	{
	  RTCBaseList_var myself = new RTCBaseList();
	  myself->length(1);

#ifdef ORB_IS_TAO
	  (*myself)[0] = RTM::RTCBase::_narrow(m_pPOA->servant_to_reference(this));
#else
	  myself[0] = RTM::RTCBase::_narrow(m_pPOA->servant_to_reference(this));
#endif
	  return myself._retn();
	};

	/*!
	 * @if jp
	 * @brief [CORBA interface] 子コンポーネントを名前を指定して取得
	 *
	 * 子コンポーネントを名前を指定してそのオブジェクトリファレンスを取得する。
	 * 単体コンポーネントにおいては自分自身オブジェクトリファレンスを返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RTCBase_ptr rtc_get_component(const char* name)
	{
	  return dynamic_cast<RTCBase_ptr>(m_pPOA->servant_to_reference(this));
	};

	/*!
	 * @if jp
	 * @brief [CORBA interface] InPortをアタッチする
	 *
	 * 子コンポーネントのInPortをこのコンポーネントのInPortにアタッチする。
	 * 単体コンポーネントにおいては自分自身オブジェクトリファレンスを返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_attach_inport(InPort_ptr in_port)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] InPortをアタッチする
	 *
	 * 子コンポーネントのInPort名を指定してコンポーネントのInPortにアタッチ
	 * する。
	 * 単体コンポーネントにおいては自分自身オブジェクトリファレンスを返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_attach_inport_by_name(RTCBase_ptr comp, const char* name)
	{return RTM_ERR;};


	/*!
	 * @if jp
	 * @brief [CORBA interface] InPortをデタッチする
	 *
	 * 子コンポーネントのInPortをこのコンポーネントのInPortからデタッチする。
	 * 単体コンポーネントにおいては RTM_ERR を返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_detatch_inport(InPort_ptr in_port)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] InPortをデタッチする
	 *
	 * 子コンポーネントのInPortを名前を指定してこのコンポーネントのInPortから
	 * デタッチする。
	 * 単体コンポーネントにおいては RTM_ERR を返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_detatch_inport_by_name(const char* name)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] OutPortをアタッチする
	 *
	 * 子コンポーネントのOutPortをこのコンポーネントのOutPortにアタッチする。
	 * 単体コンポーネントにおいては自分自身オブジェクトリファレンスを返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_attach_outport(OutPort_ptr out_port)
	{return RTM_ERR;} ;

	/*!
	 * @if jp
	 * @brief [CORBA interface] OutPortをアタッチする
	 *
	 * 子コンポーネントのOutPort名を指定してコンポーネントのInPortにアタッチ
	 * する。
	 * 単体コンポーネントにおいては自分自身オブジェクトリファレンスを返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_attach_outport_by_name(RTCBase_ptr comp,
											  const char* name)
	{return RTM_ERR;};

	/*!
	 * @if jp
	 * @brief [CORBA interface] OutPortをデタッチする
	 *
	 * 子コンポーネントのOutPortをこのコンポーネントのOutPortからデタッチする。
	 * 単体コンポーネントにおいては RTM_ERR を返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_detatch_outport(OutPort_ptr out_port)
	{return RTM_ERR;}

	/*!
	 * @if jp
	 * @brief [CORBA interface] OutPortをデタッチする
	 *
	 * 子コンポーネントのOutPortを名前を指定してこのコンポーネントのOutPortから
	 * デタッチする。
	 * 単体コンポーネントにおいては RTM_ERR を返す。
	 *
	 * @else
	 *
	 * @brief [CORBA interface] Get child components list
	 *
	 * @endif
	 */
	virtual RtmRes rtc_detatch_outport_by_name(const char* name)
	 {return RTM_ERR;};
	
	// end of CORBA interface definition
	//============================================================
	
	
	
	//============================================================
	//
	// <<< Local interfaces >>>
	//
	//============================================================
	
	/*!
	 * @if jp
	 * @brief ORB, POA のポインタを与えて初期化する
	 *
	 * コンポーネントにORBとPOAのポインタを与えてコンポーネントを初期化する。
	 *
	 * @param orb ORB へのポインタ
	 * @param poa POA へのポインタ
	 *
	 * @else
	 *
	 * @brief Initialize this component with ORB and POA pointer
	 *
	 * @param orb pointer to ORB
	 * @param poa pointer to POA
	 *
	 * @endif
	 */
	virtual void init_orb(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa);
	
	/*!
	 * @if jp
	 * @brief コンポーネントのアクティビティスレッドを生成する
	 *
	 * コンポーネントの内部アクティビティスレッドを生成し起動する。
	 * これは ACE_Task サービスクラスメソッドのオーバーライド。
	 *
	 * @param args 通常は0
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
	 * @brief コンポーネントのアクティビティスレッド関数
	 *
	 * コンポーネントの内部アクティビティスレッドの実行関数。
	 * これは ACE_Task サービスクラスメソッドのオーバーライド。
	 *
	 * @else
	 *
	 * @brief Create internal activity thread
	 *
	 * Run by a daemon thread to handle deferred processing.
	 * ACE_Task class method override.
	 *
	 * @endif
	 */	
	virtual int svc(void);
	

	/*!
	 * @if jp
	 * @brief コンポーネントのアクティビティスレッド終了関数
	 *
	 * コンポーネントの内部アクティビティスレッド終了時に呼ばれる。
	 * コンポーネントオブジェクトの非アクティブ化、マネージャへの通知を行う。
	 * これは ACE_Task サービスクラスメソッドのオーバーライド。
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

	/*!
	 * @if jp
	 *
	 * @brief コンポーネントステート取得
	 *
	 * コンポーネントの現在の状態を取得する。
	 *
	 * @else
	 *
	 * @brief Get current component state
	 *
	 * @endif
	 */
	virtual RTM::RTComponent::ComponentState getState();

	//============================================================
	// Component Property handling methods
	//============================================================
	// @brief Get component class name.

	/*!
	 * @if jp
	 *
	 * @brief ModuleProfile の初期化
	 *
	 * RtcModuleProfile クラスのインスタンスを渡して、コンポーネントの
	 * プロファイルを初期化する。
	 *
	 * @param RtcModuleProfSpec モジュールプロファイル
	 *
	 * @else
	 *
	 * @brief Initialize RtcModuleProfile
	 *
	 * @param RtcModuleProfile module profile
	 *
	 * @endif
	 */
	virtual void initModuleProfile(RtcModuleProfile prof);

	/*!
	 * @if jp
	 *
	 * @brief ModuleProfile の取得
	 *
	 * ModuleProfile を取得する。
	 *
	 * @else
	 *
	 * @brief Get RtcModuleProfile
	 *
	 * Get RtcModuleProfile
	 *
	 * @endif
	 */
	virtual RtcModuleProfile& getModuleProfile()
	{
	  return m_Profile;
	}
	/*
	virtual RtcComponentProfile& getProfile()
	{
	  return m_Profile;
	}
	*/
	/*
	virtual RtcConfiguration& getConfiguration()
	{
	  return m_Configuration;
	}
	*/
	/*!------------------------------------------------------------
	 * Set component name
	 *------------------------------------------------------------*/  
	/*!
	 * @if jp
	 *
	 * @brief コンポーネント名をセットする
	 *
	 * コンポーネントのモジュール名に引数で与えられる数字を付加した
	 * コンポーネント名を返す。
	 * ユーザはこのメソッドをオーバーライドして、コンポーネント名の命名
	 * 方法をカスタマイズすることが出来る。
	 *
	 * @param num コンポーネントのインスタンス番号
	 *
	 * @else
	 *
	 * @brief Set component name
	 *
	 * @param num instance number of this component
	 *
	 * @endif
	 */
	virtual string setComponentName(int num);

	//============================================================
	// Input port handling
	//============================================================
	/*!
	 * @if jp
	 *
	 * @brief InPort の登録
	 *
	 * InPort をコンポーネントに登録する。登録されたInPortは外部から
	 * 見えるようになる。
	 *
	 * @param in_ch InPort object of InPort<T>
	 *
	 * @else
	 *
	 * @brief Registration of input channel.
	 *
	 * Duplication of a name of input channel is not allowed.
	 * "false" will be returned when there is duplication of a name.
	 *
	 * @param in_ch Input channel object of InPort<T>
	 * @return true/false: "false" will be returned if registration goes wrong.
	 *
	 * @endif
	 */
	bool registerInPort(InPortBase& in_ch);

	/*!
	 * @if jp
	 *
	 * @brief InPort の登録
	 *
	 * InPort をコンポーネントに登録する。登録されたInPortは外部から
	 * 見えるようになる。
	 *
	 * @param in_ch InPort object of InPort<T>
	 *
	 * @else
	 *
	 * @brief Registration of input channel.
	 *
	 * Duplication of a name of input channel is not allowed.
	 * "false" will be returned when there is duplication of a name.
	 *
	 * @param in_ch Input channel object of InPort<T>
	 * @return true/false: "false" will be returned if registration goes wrong.
	 *
	 * @endif
	 */
	bool registerPort(InPortBase& in_ch)
	{
	  return registerInPort(in_ch);
	};
	
	/*!
	 * @if jp
	 *
	 * @brief InPort の登録解除
	 *
	 * 登録されている InPort の登録を解除する。
	 *
	 * @param in_ch InPort object of InPort<T>
	 *
	 * @else
	 *
	 * @brief Deletion of InPort
	 *
	 * "false" is returned when the object of the argument is not registered. 
	 *
	 * @param in_ch Input channel object of InPort<T>
	 * @return true/false: "false" will be returned if deletion goes wrong.
	 *
	 * @endif
	 */
	bool deleteInPort(InPortBase& in_ch);

	/*!
	 * @if jp
	 *
	 * @brief InPort の登録解除
	 *
	 * 登録されている InPort の登録を解除する。
	 *
	 * @param in_ch InPort object of InPort<T>
	 *
	 * @else
	 *
	 * @brief Deletion of InPort
	 *
	 * "false" is returned when the object of the argument is not registered. 
	 *
	 * @param in_ch Input channel object of InPort<T>
	 * @return true/false: "false" will be returned if deletion goes wrong.
	 *
	 * @endif
	 */
	bool deletePort(InPortBase& in_ch)
	{
	  return deleteInPort(in_ch);
	};
	
	/*!
	 * @if jp
	 *
	 * @brief InPort の登録解除
	 *
	 * 登録されている InPort の登録を名前を指定して解除する。
	 *
	 * @param ch_name InPort 名
	 *
	 * @else
	 *
	 * @brief Deletion of input channel by channel name.
	 *
	 * "false" is returned when the object of the argument is not registered. 
	 *
	 * @param ch_name Input channel name
	 * @return true/false: "false" will be returned if deletion goes wrong.
	 *
	 * @endif
	 */
	bool deleteInPortByName(const char* ch_name);

	/*!
	 * @if jp
	 *
	 * @brief 全ての InPort のデータ取り込み
	 *
	 * 全てのInPortに対して InPort::read() を実行。予めバインドされた変数に
	 * 最新の値が代入される。変数にバインドされていないInPortでは何も
	 * 起こらない。
	 *
	 * @else
	 *
	 * @brief Read all data to InPorts and bound variable
	 *
	 * Invoke InPort::read() to all registered InPorts.
	 *
	 * @endif
	 */	
	void readAllInPorts();


	/*!
	 * @if jp
	 *
	 * @brief 全ての InPort の終了処理
	 *
	 * 全てのInPortに対してオブジェクトの deactivate() を行う。
	 *
	 * @else
	 *
	 * @brief Finalize all InPorts
	 *
	 * Finalize all registered InPorts and deactivate as a CORBA objects.
	 *
	 * @endif
	 */	
	void finalizeInPorts();

	//============================================================
	// Output channel handling
	//============================================================
	/*!
	 * @if jp
	 *
	 * @brief OutPort の登録
	 *
	 * OutPort をコンポーネントに登録する。登録されたOutPortは外部から
	 * 見えるようになる。
	 *
	 * @param out_ch OutPort object of OutPort<T>
	 *
	 * @else
	 *
	 * @brief Registration of output channel
	 *
	 * Duplication of a name of output channel is not allowed.
	 * "false" will be returned when there is duplication of a name.
	 *
	 * @param out_ch Output channel object of OutPort<T>
	 * @return true/false: "false" will be returned if registration goes wrong.
	 *
	 * @endif
	 */
	bool registerOutPort(OutPortBase& out_ch);
	bool registerPort(OutPortBase& out_ch)
	{
	  return registerOutPort(out_ch);
	};
	
	/*!
	 * @if jp
	 *
	 * @brief OutPort の登録
	 *
	 * OutPort をコンポーネントに登録する。登録されたOutPortは外部から
	 * 見えるようになる。
	 *
	 * @param out_ch OutPort object of OutPort<T>
	 *
	 * @else
	 *
	 * @brief Deletion of output channel.
	 *
	 * "false" is returned when the object of the argument is not registered. 
	 *
	 * @param out_ch Output channel object of OutPort<T>
	 * @return true/false: "false" will be returned if deletion goes wrong.
	 *
	 * @endif
	 */
	bool deleteOutPort(OutPortBase& out_ch);

	/*!
	 * @if jp
	 *
	 * @brief OutPort の登録
	 *
	 * OutPort をコンポーネントに登録する。登録されたOutPortは外部から
	 * 見えるようになる。
	 *
	 * @param out_ch OutPort object of OutPort<T>
	 *
	 * @else
	 *
	 * @brief Deletion of output channel.
	 *
	 * "false" is returned when the object of the argument is not registered. 
	 *
	 * @param out_ch Output channel object of OutPort<T>
	 * @return true/false: "false" will be returned if deletion goes wrong.
	 *
	 * @endif
	 */
	bool deletePort(OutPortBase& out_ch)
	{
	  return deleteOutPort(out_ch);
	};
	
	/*!
	 * @if jp
	 *
	 * @brief OutPort の登録解除
	 *
	 * 登録されている OutPort の登録を名前を指定して解除する。
	 *
	 * @param ch_name OutPort 名
	 *
	 * @else
	 *
	 * @brief Deletion of output channel by channel name.
	 *
	 * "false" is returned when the object of the argument is not registered. 
	 *
	 * @param ch_name Output channel name
	 * @return true/false: "false" will be returned if deletion goes wrong.
	 *
	 * @endif
	 */
	bool deleteOutPortByName(const char* ch_name);

	/*!
	 * @if jp
	 *
	 * @brief 全ての OutPort のデータ書き出し
	 *
	 * 全てのOutPortに対して OutPort::write() を実行。予めバインドされた変数の
	 * 値をサブスクライバに書き出すためのバッファに書き込まれる。
	 * 変数にバインドされていないInPortでは何も起こらない。
	 *
	 * @else
	 *
	 * @brief Write all data to OutPorts from bound variables
	 *
	 * Invoke OutPort::write() to all registered OutPorts.
	 *
	 * @endif
	 */	
	void writeAllOutPorts();

	
	/*!
	 * @if jp
	 *
	 * @brief 全ての OutPort の終了処理
	 *
	 * 全てのOutPortに対して各サブスクライバを切断し、オブジェクトの
	 * deactivate() を行う。
	 *
	 * @else
	 *
	 * @brief Finalize all OutPorts
	 *
	 * Finalize all registered OutPorts and deactivate as a CORBA objects.
	 *
	 * @endif
	 */	
	void finalizeOutPorts();

	
	/*!
	 * @if jp
	 *
	 * @brief コンポーネント名の alias を登録
	 *
	 * コンポーネント名の alias を登録する。登録された alias はネーミングサーバ
	 * に登録される。
	 * 名前の付け方は コンテキストの区切りを "/"、 id と kind の区切りを "|"
	 * とする。コンテキスト Manipulator の下に自分自身を MyManipulator0 として
	 * bind したい場合には　"/Manipualtor/MyManipulator0|rtc" を文字列として
	 * 渡す。マネージャにより適切なタイミングでネーミングサーバに登録される。
	 *
	 * @param alias コンポーネント名の alias
	 *
	 * @else
	 *
	 * @brief Register alias of component name
	 *
	 * This method register alias of component name. Registered alias will
	 * bind to naming server.
	 * Context delimiter is "/", id/kind delimiter is "|".
	 * If you want to bind your component "MyManipulator0" under a context
	 * "Manipulator", you should give an char* argument 
	 * like "/Manipulator/MyManipulator|rtc".
	 * This component will be bound to naming server on this alias.
	 *
	 * @param alias An alias of this component name
	 *
	 * @endif
	 */
	void appendAlias(const char* alias);

	/*!
	 * @if jp
	 *
	 * @brief コンポーネント名の alias を登録
	 *
	 * コンポーネント名の alias を登録する。登録された alias はネーミングサーバ
	 * に登録される。
	 * 名前の付け方は コンテキストの区切りを "/"、 id と kind の区切りを "|"
	 * とする。コンテキスト Manipulator の下に自分自身を MyManipulator0 として
	 * bind したい場合には　"/Manipualtor/MyManipulator0|rtc" を文字列として
	 * 渡す。マネージャにより適切なタイミングでネーミングサーバに登録される。
	 *
	 * @param alias コンポーネント名の alias
	 *
	 * @else
	 *
	 * @brief Register alias of component name
	 *
	 * This method register alias of component name. Registered alias will
	 * bind to naming server.
	 * Context delimiter is "/", id/kind delimiter is "|".
	 * If you want to bind your component "MyManipulator0" under a context
	 * "Manipulator", you should give an char* argument 
	 * like "/Manipulator/MyManipulator|rtc".
	 * This component will be bound to naming server on this alias.
	 *
	 * @param alias An alias of this component name
	 *
	 * @endif
	 */
	void appendAlias(const std::string alias);

	/*!
	 * @if jp
	 *
	 * @brief コンポーネント名の alias を取得
	 *
	 * 登録されているコンポーネント名の alias を取得する。
	 *
	 * @else
	 *
	 * @brief Get registered aliases of component name
	 *
	 * @endif
	 */
	std::list<string> getAliases();

	void setNamingPolicy(NamingPolicy policy);
	NamingPolicy getNamingPolicy();
	bool isLongNameEnable();
	bool isAliasEnable();

	void forceExit();

	/*!
	 * @if jp
	 *
	 * @brief コンポーネントの終了処理
	 *
	 * 1.OutPortの終了処理+deactivate、2.InPortの終了処理+deactivate、
	 * 3.アクティビティの停止、4.コンポーネントのdeactivate
	 * 5. 
	 *
	 * @else
	 *
	 * @brief Get registered aliases of component name
	 *
	 * @endif
	 */
	void finalize();
  
	bool isThreadRunning();
	
	

	
  protected:
	/*!
	 * @if jp
	 * @brief ORB ポインタ変数
	 * @else
	 * @brief pointer to ORB
	 * @endif
	 */
	CORBA::ORB_ptr m_pORB;

	/*!
	 * @if jp
	 * @brief POA ポインタ変数
	 * @else
	 * @brief pointer to POA
	 * @endif
	 */
	PortableServer::POA_ptr m_pPOA;

	/*!
	 * @if jp
	 * @brief Manager ポインタ変数
	 * @else
	 * @brief pointer to Manager
	 * @endif
	 */
	RtcManager* m_pManager;

	/*!
	 * @if jp
	 * @brief 親コンポーネントのオブジェクトリファレンス
	 * @else
	 * @brief object reference to parent component
	 * @endif
	 */
	RTCBase_var m_Parent;

	/*!
	 * @if jp
	 * @brief アクティビティスレッド状態フラグ構造体
	 * @else
	 * @brief activity thread state structure
	 * @endif
	 */
	typedef enum ThreadStates {
	  UNKNOWN,
	  RUNNING,
	  SUSPEND,
	  STOP
	};
	class ThreadState
	{
	public:
	  ThreadState() : m_Flag(RUNNING){};
	  ThreadStates m_Flag;
	  ACE_Thread_Mutex m_Mutex;
	};
	/*!
	 * @if jp
	 * @brief アクティビティスレッド状態変数
	 * @else
	 * @brief activity thread state variable
	 * @endif
	 */
	ThreadState m_ThreadState;

	/*!
	 * @if jp
	 * @brief コンポーネント名比較 Fanctor クラス
	 * @else
	 * @brief Component name comparison fanctor class
	 * @endif
	 */
	class eq_name
	{
	public:
	  const string m_name;
	  eq_name(const char* name) : m_name(name){};
	  bool operator()(InPortBase* ch)
	  {
		string ch_name(ch->name());
		return m_name == ch_name;
	  };
	  bool operator()(OutPortBase* ch)
	  {
		string ch_name(ch->name());
		return m_name == ch_name;
	  };
	};

	/*!
	 * @if jp
	 * @brief アクティビティ状態変数クラス
	 * @else
	 * @brief activity state varible structure
	 * @endif
	 */
	struct ComponentStateMtx {
	public:
	  /*!
	   * @if jp
	   * @brief アクティビティ状態変数クラスコンストラクタ
	   * @else
	   * @brief activity state varible structure constructor
	   * @endif
	   */
	  ComponentStateMtx():_state(RTM::RTComponent::RTC_BORN){};

	  /*!
	   * @if jp
	   * @brief アクティビティ状態
	   * @else
	   * @brief activity state varible structure
	   * @endif
	   */
	  ComponentState _state;
	  
	  /*!
	   * @if jp
	   * @brief アクティビティ状態変数Mutex
	   * @else
	   * @brief activity state varible mutex
	   * @endif
	   */
	  ACE_Thread_Mutex _mutex;
	};

	/*!
	 * @if jp
	 * @brief アクティビティの現在状態変数
	 * @else
	 * @brief activity current state varible
	 * @endif
	 */
	ComponentStateMtx m_CurrentState;

	/*!
	 * @if jp
	 * @brief アクティビティの次状態変数
	 * @else
	 * @brief activity next state varible
	 * @endif
	 */
	ComponentStateMtx m_NextState;
	
	/*!
	 * @if jp
	 * @brief アクティビティ関数ポインタ宣言
	 * @else
	 * @brief activity function pointer definition
	 * @endif
	 */
	typedef RtmRes (RtcBase::*StateFunc)();
	
	//------------------------------------------------------------
	// Function pointer tables for state action functions.
	//------------------------------------------------------------
	/*!
	 * @if jp
	 * @brief アクティビティの exit 関数テーブル
	 * @else
	 * @brief exit function table of activity
	 * @endif
	 */
	StateFunc _exit_func[11];

	/*!
	 * @if jp
	 * @brief アクティビティの entry 関数テーブル
	 * @else
	 * @brief entry function table of activity
	 * @endif
	 */
	StateFunc _entry_func[11];

	/*!
	 * @if jp
	 * @brief アクティビティの do 関数テーブル
	 * @else
	 * @brief do function table of activity
	 * @endif
	 */
	StateFunc _do_func[11];
	
	//------------------------------------------------------------
	// State action functions
	//------------------------------------------------------------
	// 
	/*!
	 * @if jp
	 * @brief アクティビティエラーチェック関数
	 * @else
	 * @brief activity error check function
	 * @endif
	 */
	RtmRes _check_error(RtmRes result);

	/*!
	 * @if jp
	 * @brief アクティビティ用ダミー関数
	 * @else
	 * @brief dummy function for activity
	 * @endif
	 */
	RtmRes _nop(){return RTM_OK;}

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_init_entry 実行関数
	 * @else
	 * @brief rtc_init_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_initializing();

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_ready_entry 実行関数
	 * @else
	 * @brief rtc_ready_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_ready_entry();
	/*!
	 * @if jp
	 * @brief アクティビティ rtc_starting_entry 実行関数
	 * @else
	 * @brief rtc_starting_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_starting();
	/*!
	 * @if jp
	 * @brief アクティビティ rtc_active_entry 実行関数
	 * @else
	 * @brief rtc_active_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_active_entry();
	/*!
	 * @if jp
	 * @brief アクティビティ rtc_stippoing_entry 実行関数
	 * @else
	 * @brief rtc_stopping_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_stopping();
	/*!
	 * @if jp
	 * @brief アクティビティ rtc_aborting_entry 実行関数
	 * @else
	 * @brief rtc_aborting_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_aborting();

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_error_entry 実行関数
	 * @else
	 * @brief rtc_error_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_error_entry();

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_fatal_entry 実行関数
	 * @else
	 * @brief rtc_fatal_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_fatal_entry();

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_exiting_entry 実行関数
	 * @else
	 * @brief rtc_exiting_entry execution function for activity
	 * @endif
	 */
	RtmRes _rtc_exiting();

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_ready_do 実行関数
	 * @else
	 * @brief rtc_ready_do execution function for activity
	 * @endif
	 */
	RtmRes _rtc_ready();

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_active_do 実行関数
	 * @else
	 * @brief rtc_active_do execution function for activity
	 * @endif
	 */
	RtmRes _rtc_active();

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_error_do 実行関数
	 * @else
	 * @brief rtc_error_do execution function for activity
	 * @endif
	 */
	RtmRes _rtc_error();

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_fatal_do 実行関数
	 * @else
	 * @brief rtc_fatal_do execution function for activity
	 * @endif
	 */
	RtmRes _rtc_fatal();

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_ready_exit 実行関数
	 * @else
	 * @brief rtc_ready_exit execution function for activity
	 * @endif
	 */
	RtmRes _rtc_ready_exit();

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_active_exit 実行関数
	 * @else
	 * @brief rtc_active_exit execution function for activity
	 * @endif
	 */
	RtmRes _rtc_active_exit();

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_error_exit 実行関数
	 * @else
	 * @brief rtc_error_exit execution function for activity
	 * @endif
	 */
	RtmRes _rtc_error_exit();

	/*!
	 * @if jp
	 * @brief アクティビティ rtc_fatal_exit 実行関数
	 * @else
	 * @brief rtc_fatal_exit execution function for activity
	 * @endif
	 */
	RtmRes _rtc_fatal_exit();
	
	/*!
	 * @if jp
	 * @brief アクティビティ関数テーブルの初期化
	 * @else
	 * @brief initialize activity function table
	 * @endif
	 */
	void init_state_func_table();
	

	/*!
	 * @if jp
	 * @brief InPort リストイテレータ
	 * @else
	 * @brief InPort list iterator
	 * @endif
	 */
	typedef list<InPortBase*>::iterator InPorts_it;
	
	/*!
	 * @if jp
	 * @brief OutPort リストイテレータ
	 * @else
	 * @brief OutPort list iterator
	 * @endif
	 */
	typedef list<OutPortBase*>::iterator OutPorts_it;
	
	/*!
	 * @if jp
	 * @brief mutex 付き InPort リスト構造体
	 * @else
	 * @brief InPort list structure with mutex 
	 * @endif
	 */
	struct InPorts
	{
	  list<InPortBase*> m_List;
	  ACE_Thread_Mutex m_Mutex;
	};
	/*!
	 * @if jp
	 * @brief mutex 付き InPort リスト
	 * @else
	 * @brief InPort list with mutex 
	 * @endif
	 */
	InPorts m_InPorts;
	
	/*!
	 * @if jp
	 * @brief mutex 付き OutPort リスト構造体
	 * @else
	 * @brief OutPort list structure with mutex 
	 * @endif
	 */
	struct OutPorts
	{
	  list<OutPortBase*> m_List;
	  ACE_Thread_Mutex m_Mutex;
	};
	/*!
	 * @if jp
	 * @brief mutex 付き OutPort リスト
	 * @else
	 * @brief OutPort list with mutex
	 * @endif
	 */
	OutPorts m_OutPorts;
	
	//! Input port flag list
	//  list<const bool*> m_InFlags;
	
	/*!
	 * @if jp
	 * @brief アクティビティ状態変数
	 * @else
	 * @brief activity state variable
	 * @endif
	 */
	TimedState m_TimedState;
	/*!
	 * @if jp
	 * @brief アクティビティ状態OutPort
	 * @else
	 * @brief activity state OutPort
	 * @endif
	 */
	OutPortAny<TimedState> m_StatePort;									  

	/*!
	 * @if jp
	 * @brief コンポーネントプロファイル
	 * @else
	 * @brief component profile
	 * @endif
	 */
	RtcModuleProfile m_Profile;
	//	RtcManagerProfile m_ManagerProfile;
	//	RtcComponentProfile m_Profile;
	//	RtcConfiguration m_Configuration;

	/*!
	 * @if jp
	 * @brief コンポーネント名のalias
	 * @else
	 * @brief Aliases of component name
	 * @endif
	 */
	std::list<string> m_Alias;

	NamingPolicy m_NamingPolicy;

 	/*!
	 * @if jp
	 * @brief ロガー仲介バッファ
	 * @else
	 * @brief Logger mediation buffer
	 * @endif
	 */
	RtcMedLogbuf m_MedLogbuf;

 	/*!
	 * @if jp
	 * @brief ロガーストリーム
	 * @else
	 * @brief Logger stream
	 * @endif
	 */
	RtcLogStream rtcout;

  };

  //------------------------------------------------------------
  // RTComponent factory function type
  //------------------------------------------------------------

  class EXPORTS RtcManager;
	/*!
	 * @if jp
	 * @brief コンポーネントオブジェクトファクトリ関数宣言
	 * @else
	 * @brief component object factory function declaration
	 * @endif
	 */
  typedef RtcBase* (*RtcNewFunc)(RtcManager* manager);

	/*!
	 * @if jp
	 * @brief コンポーネントオブジェクト廃棄関数宣言
	 * @else
	 * @brief component object delete function declaration
	 * @endif
	 */
  typedef void (*RtcDeleteFunc)(RtcBase* rtc);

};  // end of namespace RTM


#endif // __RtcBase_h__

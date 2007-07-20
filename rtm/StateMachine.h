// -*- C++ -*-
/*!
 * @file StateMachine.h
 * @brief State machine template class
 * @date $Date: 2007-07-20 16:08:57 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: StateMachine.h,v 1.3.2.1 2007-07-20 16:08:57 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.3  2007/04/26 15:33:39  n-ando
 * The header include order was modified to define _REENTRANT before
 * including ace/config-lite.h in Linux systems.
 * In ace 5.4.7 or later, _REENTRANT flag should be defined explicitly.
 *
 * Revision 1.2  2007/01/09 15:26:53  n-ando
 * Now StateMachine does not need NOP function.
 * All null function pointer is checked and skipped.
 *
 * Revision 1.1  2006/10/26 08:55:53  n-ando
 * The first commitment.
 *
 *
 */

#ifndef StateMachine_h
#define StateMachine_h

#include <rtm/RTC.h>

#include <ace/Guard_T.h>
#include <ace/Thread_Mutex.h>

template <class State>
struct StateHolder
{
  State curr;
  State prev;
  State next;
};

/*!
 * @if jp
 *
 * @class StateMachine
 *
 * @brief 状態マシンクラス
 *
 * StateMachine クラスは状態マシンを実現するクラスである。
 *
 * 例: ActiveObjectは状態マシンを持つアクティブオブジェクトであるとする。
 * 状態は3状態 INACTIVE, ACTIVE, ERROR あり、各状態でのEntryやExit動作を
 * 定義したいとすると、以下のように実現される。
 * <pre>
 * class ActiveObject 
 * {  
 * public: 
 *   enum MyState { INACTIVE, ACTIVE, ERROR }; 
 *   typedef States<MyState> MyStates; 
 *  
 *   ActiveObject() 
 *     : m_sm(3) 
 *   { 
 *     m_sm.setNOP(&ActiveObject::nullAction); 
 *     m_sm.setListener(this); 
 *  
 *     m_sm.setExitAction(NACTIVE, &ActiveObject::inactiveExit); 
 *       : 
 *     m_sm.setPostDoAction(ERROR, &ActiveObject::errorPostDo); 
 *     m_sm.setTransitionAction(&ActiveObject:tratransitionnsition); 
 *   }; 
 *  
 *   bool nullAction(MyStates st) {}; 
 *   bool inactiveExit(MyStates st) {}; 
 *     : 
 *   bool errorPostDo(MyStates st) {}; 
 *   bool transition(MyStates st) {}; 
 *  
 * private: 
 *   StateMachine<MyState, bool, ActiveObject> m_sm; 
 * }; 
 * </pre>
 * 状態を持たせたいクラスは以下の条件を満たすように実装しなければならない。
 * <ol>
 * <li> enum で状態を定義
 * <li> StateMachine のテンプレート引数は、<br>
 *   <状態の型(MyState), アクション関数の戻り値(bool), 当該オブジェクトの型>
 * <li> StateMachine のコンストラクタ引数は状態の数
 * <li> 以下のアクション関数を(Return _function_name_(States)) の関数として設定
 * <ol>
 *  <li> 何もしない関数を必ず定義し、setNOP で与えなければならない
 *  <li> 各状態毎に, set(Entry|PreDo|Do|PostDo|Exit)Action でアクションを設定
 *  <li> 状態遷移時のアクションを setTransitionAction() で設定。
 * </ol>
 * <li> 遷移時のアクションは、与えられた現在状態、次状態、前状態を元に、
 *   ユーザが実装しなければならない。
 * <li> 状態の変更は goTo() で、状態のチェックは isIn(state) で行う。
 * <li> goTo()は次状態を強制的にセットする関数であり、遷移の可否は、
 *   ユーザが現在状態を取得し判断するロジックを実装しなければならない。
 * </ol>
 *
 * このクラスは、一つの状態に対して、
 * <ul>
 * <li> Entry action
 * <li> PreDo action
 * <li> Do action
 * <li> PostDo action
 * <li> Exit action
 * </ul>
 * 5つのアクションが定義することができる。
 * Transition action はあらゆる状態間遷移で呼び出されるアクションで、
 * その振る舞いはユーザが定義しなければならない。
 * 
 * このクラスは以下のようなタイミングで各アクションが実行される。
 *
 * <ul>
 * <li> 状態が変更され(A->B)状態が遷移する場合 <br>
 * (A:Exit)->|(状態更新:A->B)->(B:Entry)->(B:PreDo)->(B:Do)->(B:PostDo)
 *
 * <li> 状態が変更されず、B状態を維持する場合 (|はステップの区切りを表す)<br>
 * (B(n-1):PostDo)->|(B(n):PreDo)->(B(n):Do)->(B(n):PostDo)->|(B(n+1):PreDo)<br>
 * PreDo, Do, PostDo が繰り返し実行される。
 *
 * <li> 自己遷移する場合 <br>
 * (B(n-1):PostDo)->(B(n-1):Exit)->|(B(n):Entry)->(B(n):PreDo) <br>
 * 一旦 Exit が呼ばれた後、Entry が実行され、以降は前項と同じ動作をする。
 * </ul>
 * @else
 *
 * @brief
 *
 * @endif
 */
template <class State, class Result,
	  class Listener,
	  class States = StateHolder<State>, 
	  class Callback = Result (Listener::*)(const States& states)
	  >
class StateMachine
{
public:
  /*!
   * @if jp
   * @brief コンストラクタ
   * @else
   * @brief Constructor
   * @endif
   */
  StateMachine(int num_of_state)
    : m_num(num_of_state),
      m_entry (new Callback[m_num]),
      m_predo (new Callback[m_num]),
      m_do    (new Callback[m_num]),
      m_postdo(new Callback[m_num]),
      m_exit  (new Callback[m_num])
  {
    setNullFunc(m_entry,  NULL);
    setNullFunc(m_do,     NULL);
    setNullFunc(m_exit,   NULL);
    setNullFunc(m_predo,  NULL);
    setNullFunc(m_postdo, NULL);
    m_transit = NULL;
  };


  /*!
   * @if jp
   * @brief NOP関数を登録する
   * @else
   * @brief Set NOP function
   * @endif
   */
  void setNOP(Callback call_back)
  {
    setNullFunc(m_entry,  call_back);
    setNullFunc(m_do,     call_back);
    setNullFunc(m_exit,   call_back);
    setNullFunc(m_predo,  call_back);
    setNullFunc(m_postdo, call_back);
    m_transit = call_back;
  }


  /*!
   * @if jp
   * @brief Listener オブジェクトを登録する
   * @else
   * @brief Set Listener Object
   * @endif
   */
  void setListener(Listener* listener)
  {
    m_listener = listener;
  }


  /*!
   * @if jp
   * @brief Entry action 関数を登録する
   * @else
   * @brief Set Entry action function
   * @endif
   */
  bool setEntryAction(State state, Callback call_back)
  {
    m_entry[state] = call_back;
    return true;
  }


  /*!
   * @if jp
   * @brief PreDo action 関数を登録する
   * @else
   * @brief Set PreDo action function
   * @endif
   */
  bool setPreDoAction(State state, Callback call_back)
  {
    m_predo[state] = call_back;
    return true;
  }


  /*!
   * @if jp
   * @brief Do action 関数を登録する
   * @else
   * @brief Set Do action function
   * @endif
   */
  bool setDoAction(State state, Callback call_back)
  {
    m_do[state] = call_back;
    return true;
    
  }


  /*!
   * @if jp
   * @brief Post action 関数を登録する
   * @else
   * @brief Set Post action function
   * @endif
   */
  bool setPostDoAction(State state, Callback call_back)
  {
    m_postdo[state] = call_back;
    return true;
  }


  /*!
   * @if jp
   * @brief Exit action 関数を登録する
   * @else
   * @brief Set Exit action function
   * @endif
   */
  bool setExitAction(State state, Callback call_back)
  {
    m_exit[state] = call_back;
    return true;
  }


  /*!
   * @if jp
   * @brief State transition action 関数を登録する
   * @else
   * @brief Set state transition action function
   * @endif
   */
  bool setTransitionAction(Callback call_back)
  {
    m_transit = call_back;
    return true;
  }


  /*!
   * @if jp
   * @brief 初期状態をセットする
   * @else
   * @brief Set Exit action function
   * @endif
   */
  void setStartState(States states)
  {
    m_states.curr = states.curr;
    m_states.prev = states.prev;
    m_states.next = states.next;
  }


  /*!
   * @if jp
   * @brief 状態を取得する
   * @else
   * @brief Get state machine's status
   * @endif
   */
  States getStates()
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    return m_states;
  }
  
  State getState()
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    return m_states.curr;
  }
  

  /*!
   * @if jp
   * @brief 現在状態を確認
   * @else
   * @brief Evaluate current status
   * @endif
   */
  bool isIn(State state)
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    return m_states.curr == state ? true : false;
  }


  /*!
   * @if jp
   * @brief 状態を変更
   * @else
   * @brief Change status
   * @endif
   */
  void goTo(State state)
  {
    ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
    m_states.next = state;
    if (m_states.curr == state)
      {
	m_selftrans  = true;
      }
  }


  /*!
   * @if jp
   * @brief 駆動関数
   * @else
   * @brief Worker function
   * @endif
   */
  Result worker()
  {
    Result res = RTC::RTC_OK;
    States state;
    bool selftrans;

    { // lock
      ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
      state = m_states;
      selftrans = m_selftrans;
      m_selftrans = false;
    }

    // Entry アクション
    // 前回から状態が変わった
    // もしくは自己遷移が行われたのでEntryアクションを行う
    if ((state.prev != state.curr) || selftrans)
      {
	// Entry アクションを実行
	if (m_entry[state.curr] != NULL)
	  res = (m_listener->*m_entry[state.curr])(state);
      }

    // この区間では状態の変更を感知しない。
    // ただし状態変数 m_states は外部から変更される可能性がある。
    // Do アクション判定にはローカル変数を使う。

    // Do アクション
    if (state.curr == state.next)
      {
	if (m_predo[state.curr] != NULL)
	  res = (m_listener->*m_predo [state.curr])(state);
	if (m_do[state.curr] != NULL)
	  res = (m_listener->*m_do    [state.curr])(state);
	if (m_postdo[state.curr] != NULL)
	  res = (m_listener->*m_postdo[state.curr])(state);
      }

    // この区間では次の状態が変更されているかもしれない。
    // 状態は m_states.next に反映されている。
    // lock
    {
      ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
      // 状態のコピー
      state.next = m_states.next;
      selftrans = m_selftrans;
    }

    // Exit アクション
    if ((state.curr != state.next) || selftrans)
      {
	// Exit action of pre-state
	if (m_exit[state.curr] != NULL)
	  res = (m_listener->*m_exit[state.curr])(state);
	if (m_transit != NULL)
	  res = (m_listener->*m_transit)(state);
      }

    {
      ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);
      // 状態を更新
      m_states.prev = m_states.curr;
      m_states.curr = m_states.next;
    }

    return res;
  }

protected:
  void setNullFunc(Callback* s, Callback nullfunc)
  {
    for (int i = 0; i < m_num; ++i) s[i] = nullfunc;
  }


  int m_num;
  Listener* m_listener;
  Callback* m_entry;
  Callback* m_predo;
  Callback* m_do;
  Callback* m_postdo;
  Callback* m_exit;
  Callback  m_transit;

  States m_states;
  bool m_selftrans;
  ACE_Thread_Mutex m_mutex;
};

#endif // StateMachine_h

// -*- C++ -*-
/*!
 * @file PeriodicExecutionContext.h
 * @brief PeriodicExecutionContext class
 * @date $Date: 2007-01-21 10:27:00 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: PeriodicExecutionContext.h,v 1.2 2007-01-21 10:27:00 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2007/01/09 15:29:35  n-ando
 * PeriodicExecutionContext class
 *
 */

#ifndef PeriodicExecutionContext_h
#define PeriodicExecutionContext_h

#include <rtm/idl/RTCSkel.h>
#include <rtm/StateMachine.h>

// ACE
#include <ace/Task.h>
#include <vector>
#include <iostream>

namespace RTC
{

  class PeriodicExecutionContext
    : public virtual POA_RTC::ExecutionContextService,
      public virtual PortableServer::RefCountServantBase,
      public ACE_Task<ACE_MT_SYNCH>
  {
  public:
    PeriodicExecutionContext(DataFlowComponent_ptr owner, double rate = 0.0);
    virtual ~PeriodicExecutionContext();
    
    ExecutionContextService_ptr getRef() {return m_ref;}

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


    //============================================================
    // ExecutionContext
    //============================================================
    
    virtual CORBA::Boolean is_running();

    virtual ReturnCode_t start();
    virtual ReturnCode_t stop();

    virtual CORBA::Double get_rate();
    virtual ReturnCode_t  set_rate(CORBA::Double rate);

    virtual ReturnCode_t activate_component(LightweightRTObject_ptr comp);
    virtual ReturnCode_t deactivate_component(LightweightRTObject_ptr comp);
    virtual ReturnCode_t reset_component(LightweightRTObject_ptr comp);

    virtual LifeCycleState get_component_state(LightweightRTObject_ptr comp);
    virtual ExecutionKind get_kind();
    virtual ReturnCode_t add(LightweightRTObject_ptr comp);
    virtual ReturnCode_t remove(LightweightRTObject_ptr comp);

    virtual ExecutionContextProfile* get_profile();

  
  protected:
    //============================================================
    // DFPBase
    //============================================================
    typedef LifeCycleState ExecContextState;
    /*
    enum ExecContextState
      {
	INACTIVE_STATE,
	ACTIVE_STATE,
	ERROR_STATE,
      };
    */
    typedef StateHolder<ExecContextState> ECStates;
    
    class DFPBase
    {
    public:

      DFPBase(UniqueId id)
	: ec_id(id), m_sm(3)
      {
	m_sm.setListener(this);
	m_sm.setEntryAction (ACTIVE_STATE,
			     &DFPBase::on_activated);
	m_sm.setDoAction    (ACTIVE_STATE,
			     &DFPBase::on_execute);
	m_sm.setPostDoAction(ACTIVE_STATE,
			     &DFPBase::on_state_update);
	m_sm.setExitAction  (ACTIVE_STATE,
			     &DFPBase::on_deactivated);
	m_sm.setEntryAction (ERROR_STATE,
			     &DFPBase::on_aborting);
	m_sm.setDoAction    (ERROR_STATE,
			     &DFPBase::on_error);
	m_sm.setExitAction  (ERROR_STATE,
			     &DFPBase::on_reset);

	ECStates st;
	st.prev = INACTIVE_STATE;
	st.curr = INACTIVE_STATE;
	st.next = INACTIVE_STATE;
	m_sm.setStartState(st);
	m_sm.goTo(INACTIVE_STATE);
      }	
      virtual ~DFPBase(){}
      virtual ReturnCode_t on_startup() = 0;
      virtual ReturnCode_t on_shutdown() = 0;

      virtual ReturnCode_t on_activated(const ECStates& st) = 0;
      virtual ReturnCode_t on_deactivated(const ECStates& st) = 0;
      virtual ReturnCode_t on_aborting(const ECStates& st) = 0;
      virtual ReturnCode_t on_error(const ECStates& st) = 0;
      virtual ReturnCode_t on_reset(const ECStates& st) = 0;
      virtual ReturnCode_t on_execute(const ECStates& st) = 0;
      virtual ReturnCode_t on_state_update(const ECStates& st) = 0;

      virtual ReturnCode_t on_rate_changed() = 0;
      virtual ReturnCode_t worker() {return m_sm.worker();}
      virtual ExecContextState get_state(){ return m_sm.getState();}
      UniqueId ec_id;
      StateMachine<ExecContextState, ReturnCode_t, DFPBase> m_sm;
    };


    //============================================================
    // DFP
    //============================================================
    template <class Object>
    class DFP
      : public DFPBase
    {
    public:
      DFP(Object obj, UniqueId id)
	: DFPBase(id), m_obj(obj), m_active(true)
      {
	
      }
      ReturnCode_t on_startup()
      {
	return m_obj->on_startup(ec_id);
      }
      ReturnCode_t on_shutdown()
      {
	return m_obj->on_shutdown(ec_id);
      }

      ReturnCode_t on_activated(const ECStates& st)
      {
	if (m_obj->on_activated(ec_id) != RTC::OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return RTC::ERROR;
	  }
	return RTC::OK;
      }
      ReturnCode_t on_deactivated(const ECStates& st)
      {
	if (m_obj->on_deactivated(ec_id) != RTC::OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return RTC::ERROR;
	  }
	return RTC::OK;
      }

      ReturnCode_t on_aborting(const ECStates& st)
      {
	return m_obj->on_aborting(ec_id);
      }

      ReturnCode_t on_error(const ECStates& st)
      {
	return m_obj->on_error(ec_id);
      }

      ReturnCode_t on_reset(const ECStates& st)
      {
	if (m_obj->on_reset(ec_id) != RTC::OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return RTC::ERROR;
	  }
	return RTC::OK;
      }

      ReturnCode_t on_execute(const ECStates& st)
      {
	if (m_obj->on_execute(ec_id) != RTC::OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return RTC::ERROR;
	  }  
	return RTC::OK;
      }

      ReturnCode_t on_state_update(const ECStates& st)
      {
	if (m_obj->on_state_update(ec_id) != RTC::OK)
	  {
	    m_sm.goTo(ERROR_STATE);
	    return RTC::ERROR;
	  }
	return RTC::OK;
      }

      ReturnCode_t on_rate_changed()
      {
	return m_obj->on_rate_changed(ec_id);
      }

      Object m_obj;
      bool m_active;
    };

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



    struct find_comp
    {
      LightweightRTObject_var m_comp;
      find_comp(LightweightRTObject_ptr comp) : m_comp(comp) {}
      bool operator()(Comp& comp)
      {
	return comp._ref->_is_equivalent(m_comp);
      }
    };


    struct invoke_on_startup
    {
      void operator()(Comp& comp)
      {
	comp._sm.on_startup();
      }
    };

    struct invoke_on_shutdown
    {
      void operator()(Comp& comp)
      {
	comp._sm.on_shutdown();
      }
    };

    struct invoke_on_rate_changed
    {
      void operator()(Comp& comp)
      {
	comp._sm.on_rate_changed();
      }
    };

    struct invoke_worker
    {
      void operator()(Comp& comp)
      {
	comp._sm.worker();
      }
    };

    std::vector<Comp> m_comps;
    typedef std::vector<Comp>::iterator CompItr;
    bool m_running;
    ExecutionContextProfile m_profile;
    long int m_usec;
    ExecutionContextService_var m_ref;

  
  }; // class PeriodicExecutionContext
}; // namespace RTC

#endif

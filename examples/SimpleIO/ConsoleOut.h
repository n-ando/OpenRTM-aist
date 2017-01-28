/// -*- C++ -*-
/*!
 * @file  ConsoleOut.h
 * @brief Console output component
 * @date  $Date: 2008-02-29 04:55:03 $
 *
 * $Id$
 */

#ifndef CONSOLEOUT_H
#define CONSOLEOUT_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/ConnectorListener.h>
#include <rtm/Macho.h>
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include <iostream>
// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;
using namespace std;
class ConsoleOut;

namespace Example {

	////////////////////////////////////////////////////////
	// State declarations

	// Machine's top state
	TOPSTATE(Top) {
		// Top state variables (visible to all substates)
		struct Box {
			Box() : data(0) {}
			long data;
		};

		STATE(Top)

		// Machine's event protocol
		virtual void event1(int i) {}
		virtual void event2(long l) {}

	private:
		// special actions
		void entry();
		void exit();
		void init();
		void init(int);
	};

	// A superstate
	SUBSTATE(Super, Top) {
		STATE(Super)

		// This state has history
		HISTORY()

	private:
		// Entry and exit actions of state
		void entry();
		void exit();
	};

	// A substate
	SUBSTATE(StateA, Super) {
		// State variables
		struct Box {
			Box() : data(0) {}
			int data;
		};

		STATE(StateA)

		// Event handler
		void event1(int i);

	private:
		void entry();
		void init(int);
		void exit();
	};

	// A substate
	SUBSTATE(StateB, Super) {
		STATE(StateB)

		void event2(long l);

	private:
		void entry();
		void exit();
	};
};

class DataListener
  : public ConnectorDataListenerT<RTC::TimedLong>
{
  USE_CONNLISTENER_STATUS;
public:
  DataListener(const char* name) : m_name(name) {}
  virtual ~DataListener()
  {
    std::cout << "dtor of " << m_name << std::endl;
  }

  virtual ReturnCode operator()(ConnectorInfo& info,
                          TimedLong& data)
  {
    std::cout << "------------------------------"   << std::endl;
    std::cout << "Data Listener: " << m_name       << std::endl;
    std::cout << "Profile::name: " << info.name    << std::endl;
    std::cout << "Profile::id:   " << info.id      << std::endl;
//    std::cout << "Profile::properties: "            << std::endl;
//    std::cout << info.properties;
//    std::cout                                       << std::endl;
    std::cout << "Data:          " << data.data    << std::endl;
    std::cout << "------------------------------"   << std::endl;
    return NO_CHANGE;
  };
  std::string m_name;
};


class ConnListener
  : public ConnectorListener
{
  USE_CONNLISTENER_STATUS;
public:
  ConnListener(const char* name) : m_name(name) {}
  virtual ~ConnListener()
  {
    std::cout << "dtor of " << m_name << std::endl;
  }

  virtual ReturnCode operator()(ConnectorInfo& info)
  {
    std::cout << "------------------------------"   << std::endl;
    std::cout << "Connector Listener: " << m_name       << std::endl;
    std::cout << "Profile::name:      " << info.name    << std::endl;
    std::cout << "Profile::id:        " << info.id      << std::endl;
    std::cout << "Profile::properties: "            << std::endl;
    std::cout << info.properties;
    std::cout                                       << std::endl;
    std::cout << "------------------------------"   << std::endl;
    return NO_CHANGE;
  };
  std::string m_name;
};


class ConsoleOut
  : public RTC::DataFlowComponentBase
{
 public:
  ConsoleOut(RTC::Manager* manager);
  ~ConsoleOut();

  // The initialize action (on CREATED->ALIVE transition)
  // formaer rtc_init_entry() 
  virtual RTC::ReturnCode_t onInitialize();

  // The finalize action (on ALIVE->END transition)
  // formaer rtc_exiting_entry()
  // virtual RTC::ReturnCode_t onFinalize();

  // The startup action when ExecutionContext startup
  // former rtc_starting_entry()
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  // The shutdown action when ExecutionContext stop
  // former rtc_stopping_entry()
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  // The activated action (Active state entry action)
  // former rtc_active_entry()
  // virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  // The deactivated action (Active state exit action)
  // former rtc_active_exit()
  // virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  // The execution action that is invoked periodically
  // former rtc_active_do()
  virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  // The aborting action when main logic error occurred.
  // former rtc_aborting_entry()
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  // The error action in ERROR state
  // former rtc_error_do()
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  // The reset action that is invoked resetting
  // This is same but different the former rtc_init_entry()
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  // The state update action that is invoked after onExecute() action
  // no corresponding operation exists in OpenRTm-aist-0.2.0
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  // The action that is invoked when execution context's rate is changed
  // no corresponding operation exists in OpenRTm-aist-0.2.0
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);

  CORBA::Long getInPortValue() { return m_in.data; }
 protected:
  // DataInPort declaration
  // <rtc-template block="inport_declare">
  TimedLong m_in;
  InPort<TimedLong> m_inIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

  Macho::Machine<Example::Top> m_machine;

 private:

};



//namespace Example {
//
//  ////////////////////////////////////////////////////////
//  // State declarations
//  
//  // Machine's top state
//  TOPSTATE(Top) {
//    // Top state variables (visible to all substates)
//    struct Box {
//      Box() : comp(0), data(0) {}
//      ConsoleOut* comp;
//      long data;
//    };
//    
//    STATE(Top)
//      
//    // Machine's event protocol
//    virtual void event1(int i, ConsoleOut* c) {}
//    virtual void event2(long l, ConsoleOut* c) {}
//    
//  private:
//    // special actions
//    void entry();
//    void exit();
//    void init();
//    void init(int i);
//  };
//  
//  // A superstate
//  SUBSTATE(Super, Top) {
//    STATE(Super)
//    
//    // This state has history
//    HISTORY()
//    
//  private:
//    // Entry and exit actions of state
//    void entry();
//    void exit();
//  };
//
//  // A substate
//  SUBSTATE(StateA, Super) {
//    // State variables
//    struct Box {
//      Box() : data(0) {}
//      int data;
//    };
//    
//    STATE(StateA)
//
//    // Event handler
//    virtual void event1(int i, ConsoleOut* c);
//
//  private:
//    void entry();
//    void init(int i, ConsoleOut* c);
//    void exit();
//  };
//  
//  // A substate
//  SUBSTATE(StateB, Super) {
//    STATE(StateB)
//      
//    virtual void event2(long l, ConsoleOut* c);
//    
//  private:
//    void entry();
//    void exit();
//  };
//  
//  ////////////////////////////////////////////////////////
//  // Event handler implementations
//  
//  // Top state
//  void Top::entry() { std::cout << "Top::entry" <<std::endl; }
//  void Top::exit() { std::cout << "Top::exit" <<std::endl; }
//  void Top::init() {
//    // Initialize state with box
//    setState<StateA>(44);
//  }
//  void Top::init(int i) {
//    box().data = i;
//    //    box().comp = c;
//    init();
//  }
//  
//  // Super state
//  void Super::entry() { std::cout << "Super::entry" << std::endl; }
//  void Super::exit() { std::cout << "Super::exit" << std::endl; }
//  
//  // StateA state
//  void StateA::entry() { std::cout << "StateA::entry" << std::endl; }
//  void StateA::init(int i, ConsoleOut* c)
//  {
//    std::cout << "StateA::init " << i << std::endl;
//  }
//  void StateA::exit()
//  {
//    std::cout << "In StateA" << std::endl;
//    std::cout << "box().data:  " << TOP::box().data << std::endl;
//    std::cout << "comp's data: " << TOP::box().comp->getInPortValue() << std::endl;
//    std::cout << "StateA::exit" <<std::endl;
//  }
//  void StateA::event1(int i, ConsoleOut* c)
//  {
//    box().data = i;
//    std::cout << "StateA::box().data: " << TOP::box().data << std::endl;
//    setState<StateB>(i, c);
//  }
//  
//  // StateB state
//  void StateB::entry() { std::cout << "StateB::entry" << std::endl; }
//  void StateB::exit()
//  {
//    std::cout << "In StateB" << std::endl;
//    std::cout << "box().data:  " << TOP::box().data << std::endl;
//    std::cout << "comp's data: " << TOP::box().comp->getInPortValue() << std::endl;
//    std::cout << "StateB::exit" << std::endl;
//  }
//
//  void StateB::event2(long l, ConsoleOut* c) {
//    Top::box().data = l;
//    std::cout << "Top::box().data: " << TOP::box().data << std::endl;
//    setState<StateA>(l, c);
//  }
//  
//} // namespace Example


extern "C"
{
  DLL_EXPORT void ConsoleOutInit(RTC::Manager* manager);
};

#endif // CONSOLEOUT_H

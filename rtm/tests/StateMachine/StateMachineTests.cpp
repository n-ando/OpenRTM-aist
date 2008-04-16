// -*- C++ -*-
/*!
 * @file   StateMachineTests.cpp
 * @brief  StateMachine test class
 * @date   $Date: 2007-01-12 14:56:19 $
 * @author Shinji Kurihara
 *         Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 08:26:03  n-ando
 * TestSuites are devided into each directory.
 *
 * Revision 1.2  2006/11/02 12:27:09  kurihara
 *
 * StateMachineTest is modified by kurihara.
 *
 * Revision 1.1  2006/10/26 08:56:56  n-ando
 * The first commitment.
 */

#ifndef StateMachine_cpp
#define StateMachine_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/StateMachine.h>

/*!
 * @class StateMachineTests class
 * @brief StateMachine test
 */
namespace StateMachineTests
{
  using namespace std;

  class StateClass
  {
  public:
    enum MyState
      {
	CREATED,
	INACTIVE,
	ACTIVE,
	ERROR
      };
    
    typedef StateHolder<MyState> MyStates;
    
    StateClass()
      : m_fsm(4)
    {
      MyStates st;
      m_fsm.setListener(this);
//      m_fsm.setNOP(&StateClass::nullFunc);
      m_fsm.setTransitionAction(&StateClass::transitionAction);
      
      m_fsm.setEntryAction (CREATED, &StateClass::createdEntry);
      //    m_fsm.setPreDoAction (CREATED, &StateClass::createdPreDo);
      m_fsm.setDoAction    (CREATED, &StateClass::createdDo);
      m_fsm.setPostDoAction(CREATED, &StateClass::createdPostDo);
      m_fsm.setExitAction  (CREATED, &StateClass::createdExit);
      
      m_fsm.setEntryAction (INACTIVE, &StateClass::inactiveEntry);
      m_fsm.setPreDoAction (INACTIVE, &StateClass::inactivePreDo);
      m_fsm.setDoAction    (INACTIVE, &StateClass::inactiveDo);
      m_fsm.setPostDoAction(INACTIVE, &StateClass::inactivePostDo);
      m_fsm.setExitAction  (INACTIVE, &StateClass::inactiveExit);
      
      m_fsm.setEntryAction (ACTIVE, &StateClass::activeEntry);
      m_fsm.setPreDoAction (ACTIVE, &StateClass::activePreDo);
      m_fsm.setDoAction    (ACTIVE, &StateClass::activeDo);
      m_fsm.setPostDoAction(ACTIVE, &StateClass::activePostDo);
      m_fsm.setExitAction  (ACTIVE, &StateClass::activeExit);
      
      m_fsm.setEntryAction (ERROR, &StateClass::errorEntry);
      m_fsm.setPreDoAction (ERROR, &StateClass::errorPreDo);
      m_fsm.setDoAction    (ERROR, &StateClass::errorDo);
      m_fsm.setPostDoAction(ERROR, &StateClass::errorPostDo);
      m_fsm.setExitAction  (ERROR, &StateClass::errorExit);
      
      //    st.prev = CREATED;
      //    st.curr = CREATED;
      //    st.next = CREATED;
      st.prev = ERROR;
      st.curr = ERROR;
      st.next = ERROR;
      MyStates getst;
      
      m_fsm.setStartState(st);
      getst = m_fsm.getStates();
      cout << "prev: " << getst.prev << " curr: " << getst.curr << " next: " << getst.next << endl;
      m_fsm.goTo(CREATED);
      
      i = 0;
      
    }
    
    
    void work()
    {
          for (int i = 0; i < 20; i++)
            {
      m_fsm.worker();
      	cout << endl;
	sleep(1);
            }
    }
    
    int transitionAction(const MyStates& state)
    {
      std::cout << "Transition state prev: " << m_fsm.getStates().prev << " curr: " << m_fsm.getStates().curr << " next: " << m_fsm.getStates().next << std::endl;
      return true;
    }
    
    int createdEntry(const MyStates& state)
    {
      // createdDoでgoTo()が呼ばれている場合、ここでのgoTo()は無効
      m_fsm.goTo(ERROR); 
      std::cout << "Created:Entry" << std::endl;
      return true;
    }
    
    /*
      int createdPreDo(const MyStates& state)
      {
      // createdDoでgoTo()が呼ばれている場合、ここでのgoTo()は無効
      m_fsm.goTo(ERROR); 
      std::cout << "Created:PreDo" << std::endl;
      return true;
      }
    */
    
    int createdDo(const MyStates& state)
    {
      m_fsm.goTo(INACTIVE);
      std::cout << "Created:Do" << std::endl;
      if (!m_fsm.isIn(CREATED))
	cout << "Error: createDo" << endl;
      return true;
    }
    
    int createdPostDo(const MyStates& state)
    {
      std::cout << "Created:PostDo" << std::endl;
      return true;
    }
    
    int createdExit(const MyStates& state)
    {
      std::cout << "Created:Exit" << std::endl;
      return true;
    }
    
    int inactiveEntry(const MyStates& state)
    {
      std::cout << "Inactive:Entry" << std::endl;
      return true;
    }
    
    int inactivePreDo(const MyStates& state)
    {
      std::cout << "Inactive:PreDo" << std::endl;
      return true;
    }
    
    int inactiveDo(const MyStates& state)
    {
      std::cout << "Inactive:Do" << std::endl;
      if (!m_fsm.isIn(INACTIVE))
	cout << "Error: inactiveDo" << endl;
      if (i >= 3) i = 0, m_fsm.goTo(ACTIVE);
      ++i;
      return true;
    }
    
    int inactivePostDo(const MyStates& state)
    {
      std::cout << "Inactive:PostDo" << std::endl;
      return true;
    }
    
    int inactiveExit(const MyStates& state)
    {
      std::cout << "Inactive:Exit" << std::endl;
      return true;
    }
    
    int activeEntry(const MyStates& state)
    {
      std::cout << "Active:Entry" << std::endl;
      return true;
    }
    
    int activePreDo(const MyStates& state)
    {
      std::cout << "Active:PreDo" << std::endl;
      return true;
    }
    
    int activeDo(const MyStates& state)
    {
      std::cout << "Active:Do" << std::endl;
      if (!m_fsm.isIn(ACTIVE))
	cout << "Error: activeDo" << endl;
      if (i == 3) m_fsm.goTo(ACTIVE);
      if (i >= 10) i = 0, m_fsm.goTo(ERROR);
      ++i;
      return true;
    }
    
    int activePostDo(const MyStates& state)
    {
      std::cout << "Active:PostDo" << std::endl;
      return true;
    }
    
    int activeExit(const MyStates& state)
    {
      std::cout << "Active:Exit" << std::endl;
      return true;
    }
    
    int errorEntry(const MyStates& state)
    {
      std::cout << "Error:Entry" << std::endl;
      return true;
    }
    
    int errorPreDo(const MyStates& state)
    {
      std::cout << "Error:PreDo" << std::endl;
      return true;
    }
    
    int errorDo(const MyStates& state)
    {
      std::cout << "Error:Do" << std::endl;
      if (!m_fsm.isIn(ERROR))
	cout << "Error: errorDo" << endl;
      if (i >= 5) i = 0, m_fsm.goTo(CREATED);
      ++i;
      return true;
    }
    
    int errorPostDo(const MyStates& state)
    {
      std::cout << "Error:PostDo" << std::endl;
      return true;
    }
    
    int errorExit(const MyStates& state)
    {
      std::cout << "Error:Exit" << std::endl;
      return true;
    }
    
    int nullFunc(const MyStates& state)
    {
      // createdPreDoを宣言していないため、CREATED状態でのPreDo action時にはここが呼ばれる。
      cout << "nullfunc" << endl;
      return true;
    }
    
    
  protected:
    
    int i;
    StateMachine<MyState, int, StateClass> m_fsm;
  };
  
  
  class StateMachineTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(StateMachineTests);
    CPPUNIT_TEST(test_statemachine);
    CPPUNIT_TEST_SUITE_END();
    
  private:
    
  public:
    
    /*!
     * @brief Constructor
     */
    StateMachineTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~StateMachineTests()
    {
    }
    
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
    
    void test_statemachine()
    {
      StateClass s;
      s.work();
    }
  };
}; // namespace StateMachine

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(StateMachineTests::StateMachineTests);

#ifdef LOCAL_MAIN
int main(int argc, char* argv[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  CppUnit::Outputter* outputter = 
    new CppUnit::TextOutputter(&runner.result(), std::cout);
  runner.setOutputter(outputter);
  bool retcode = runner.run();
  return !retcode;
}
#endif // MAIN
#endif // StateMachine_cpp

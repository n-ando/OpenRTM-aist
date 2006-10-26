// -*- C++ -*-
/*!
 * @file StringUtilTests.cpp
 * @brief StringUtil test class
 * @date $Date: 2006-10-26 08:56:56 $
 * @author Shinji Kurihara
 * $Id: StateMachineTests.cpp,v 1.1 2006-10-26 08:56:56 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/10/23 07:38:37  n-ando
 * Some fixes for split() tests.
 *
 * Revision 1.1  2006/10/23 06:10:17  kurihara
 *
 * test program for StringUtil class.
 *
 *
 */

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include "../StateMachine.h"

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
    m_fsm.setListener(this);
    m_fsm.setNOP(&StateClass::nullFunc);
    m_fsm.setEntryAction(CREATED, &StateClass::createdEntry);
    m_fsm.setDoAction   (CREATED, &StateClass::createdDo);
    m_fsm.setExitAction (CREATED, &StateClass::createdExit);

    m_fsm.setEntryAction(INACTIVE, &StateClass::inactiveEntry);
    m_fsm.setDoAction   (INACTIVE, &StateClass::inactiveDo);
    m_fsm.setExitAction (INACTIVE, &StateClass::inactiveExit);

    m_fsm.setEntryAction(ACTIVE, &StateClass::activeEntry);
    m_fsm.setDoAction   (ACTIVE, &StateClass::activeDo);
    m_fsm.setExitAction (ACTIVE, &StateClass::activeExit);

    m_fsm.setEntryAction(ERROR, &StateClass::errorEntry);
    m_fsm.setDoAction   (ERROR, &StateClass::errorDo);
    m_fsm.setExitAction (ERROR, &StateClass::errorExit);

    MyStates st;
    st.prev = CREATED;
    st.curr = CREATED;
    st.next = CREATED;
    m_fsm.setStartState(st);
    m_fsm.goTo(CREATED);

  }

  void work()
  {
    for (int i = 0; i < 100; i++)
      {
	m_fsm.worker();
	usleep(100000);
      }
  }

  int createdEntry(const MyStates& state)
  {
    std::cout << "Created:Entry" << std::endl;
    return true;
  }
  int createdDo(const MyStates& state)
  {
    m_fsm.goTo(INACTIVE);
    std::cout << "Created:Do" << std::endl;
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
  int inactiveDo(const MyStates& state)
  {
    std::cout << "Inactive:Do" << std::endl;
    if (i >= 3) i = 0, m_fsm.goTo(ACTIVE);
    ++i;
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
  int activeDo(const MyStates& state)
  {
    std::cout << "Active:Do" << std::endl;
    if (i == 3) m_fsm.goTo(ACTIVE);
    if (i >= 10) i = 0, m_fsm.goTo(ERROR);
    ++i;
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
  int errorDo(const MyStates& state)
  {
    std::cout << "Error:Do" << std::endl;
    if (i >= 5) i = 0, m_fsm.goTo(CREATED);
    ++i;
    return true;
  }
  int errorExit(const MyStates& state)
  {
    std::cout << "Error:Exit" << std::endl;
    return true;
  }

  int nullFunc(const MyStates& state)
  {
    return true;
  }


protected:

  int i;
  StateMachine<MyState, int, StateClass> m_fsm;
};


// XXX をテストする [3]
class StateMachineTest
  : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(StateMachineTest);
  CPPUNIT_TEST(test_statemachine);
  CPPUNIT_TEST_SUITE_END();
  
public:
  
  /*
   * コンストラクタ/デストラクタ [7]
   */
  StateMachineTest()
  {
  }
  
  ~StateMachineTest()
  {
  }
  
  /*
   * 初期化/後始末 [8]
   */
  virtual void setUp()
  {
  }
  
  virtual void tearDown()
  { 
  }


  void test_statemachine()
  {
    StateClass s;
    s.work();
  }

};


/*
 * register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(StateMachineTest);




int main(int argc, char* argv[])
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    CppUnit::Outputter* outputter = 
      new CppUnit::TextOutputter(&runner.result(), std::cout);
    runner.setOutputter(outputter);
   
    return runner.run();
}

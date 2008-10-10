// -*- C++ -*-
/*!
 * @file   ConditionTests.cpp
 * @brief  Condition test class
 * @date   $Date$ 
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$ 
 *
 */

/*
 * $Log$
 *
 */

#ifndef Condition_cpp
#define Condition_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/Condition.h>
#include <coil/Mutex.h>
#include <coil/Task.h>

/*!
 * @class ConditionTests class
 * @brief Condition test
 */
namespace Condition
{
  static int ConditionStatus;

/*!
 *  @brief 試験用タスク。起動するとwaitして、起こされると生成時に渡された値をConditionStatusに加算する。
 */
  class ConditionCheckTask : public coil::Task
  {
  public:
    ConditionCheckTask() : id(0) { }
    ConditionCheckTask(coil::Mutex & aMutex, coil::Condition<coil::Mutex> & aCondition, int anId)
        : mutex(&aMutex), cond(&aCondition), id(anId) {
//        std::cout << "Task(" << id << ") created." << std::endl;
        }
    ~ConditionCheckTask() { };
    virtual int svc()
    {
//      std::cout << "Ready to Add " << id << " to ConditionStatus(" << ConditionStatus << ")" << std::endl;
      mutex->lock();
      cond->wait();
      ConditionStatus += id;
      mutex->unlock();
//      std::cout << "Added " << id << " to ConditionStatus(" << ConditionStatus << ")" << std::endl;
      return ConditionStatus;
    }
    /*!
     *  @brief 結果情報のConditionStatusをクリアする
     */
    static void resteStatus() { ConditionStatus =  0; }
    /*!
     *  @brief 結果情報のConditionStatusの現在値を返す
     */
    static int getStatus() { return ConditionStatus; }
  private:
//    static int status;  // <- undefined reference
    coil::Mutex * mutex;
    coil::Condition<coil::Mutex> * cond;
    int id;
  };  // class ConditionCheckTask

  class ConditionTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(ConditionTests);
    CPPUNIT_TEST(test_Condition_wait_and_signal);
    CPPUNIT_TEST(test_Condition_wait_and_broadcast);
    CPPUNIT_TEST(test_Condition_wait_with_time);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    coil::Mutex * mu;

  public:
    /*!
     * @brief Constructor
     */
    ConditionTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~ConditionTests()
    {
    }
 
		
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      mu = new coil::Mutex;
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
      delete mu;
    }
  
    /* test case */

    /*!
     *  @brief wati with time.
     */
    void test_Condition_wait_and_signal()
    {
      coil::Mutex mu1;
      coil::Condition<coil::Mutex> cond1(mu1);
      coil::Mutex mu2;
      coil::Condition<coil::Mutex> cond2(mu2);
      int id1(0x02);
      int id2(0x08);

      ConditionCheckTask::resteStatus();
      ConditionCheckTask cct1(mu1, cond1, id1);
      ConditionCheckTask cct2(mu1, cond1, id2);

      cct1.activate();
      cct2.activate();

      CPPUNIT_ASSERT_EQUAL(0x00, ConditionCheckTask::getStatus());

      mu1.lock();
      cond1.signal();
      mu1.unlock();

      mu1.lock();
      cond1.signal();
      mu1.unlock();

      mu2.lock();
      cond2.wait(1);
      mu2.unlock();
      CPPUNIT_ASSERT_EQUAL(id1 + id2, ConditionCheckTask::getStatus());
    }

    /*!
     *  @brief wati with time.
     */
    void test_Condition_wait_and_broadcast()
    {
      coil::Condition<coil::Mutex> cd(*mu);
      coil::Mutex mu2;
      coil::Condition<coil::Mutex> cond2(mu2);

      ConditionCheckTask::resteStatus();
      ConditionCheckTask cct6(*mu, cd, 0x20);
      ConditionCheckTask cct5(*mu, cd, 0x10);
      ConditionCheckTask cct4(*mu, cd, 0x08);
      ConditionCheckTask cct3(*mu, cd, 0x04);
      ConditionCheckTask cct2(*mu, cd, 0x02);
      ConditionCheckTask cct1(*mu, cd, 0x01);

      cct6.activate();
      cct5.activate();
      cct4.activate();
      cct3.activate();
      cct2.activate();
      cct1.activate();

      CPPUNIT_ASSERT_EQUAL(0, ConditionCheckTask::getStatus());

      mu2.lock();
      cond2.wait(0, 300000000);
      mu2.unlock();

      mu->lock();
      cd.broadcast();
      mu->unlock();

      mu2.lock();
      cond2.wait(1);
      mu2.unlock();

//      std::cout << "Status is : " << ConditionCheckTask::getStatus() << std::endl;
      CPPUNIT_ASSERT_EQUAL(0x3f, ConditionCheckTask::getStatus());

      CPPUNIT_ASSERT(true);
    }
  
    /*!
     *  @brief wati with time.
     */
    void test_Condition_wait_with_time()
    {
      int waitSec(2);
      coil::Condition<coil::Mutex> cd(*mu);
//      std::cout << "Before wait " << waitSec << " sec." << std::endl << std::flush;
      mu->lock();
      int result = cd.wait(waitSec);
      mu->unlock();
//      std::cout << " After wait (result:" << result << ")" << std::endl;
      
      CPPUNIT_ASSERT(true);
    }

  };
}; // namespace Condition

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(Condition::ConditionTests);

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
#endif // Condition_cpp

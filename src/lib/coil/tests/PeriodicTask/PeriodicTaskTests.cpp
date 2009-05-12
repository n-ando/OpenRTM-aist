// -*- C++ -*-
/*!
 * @file   PeriodicTaskTests.cpp
 * @brief  PeriodicTask test class
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

#ifndef PeriodicTask_cpp
#define PeriodicTask_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/Time.h>
#include <coil/PeriodicTask.h>

#include <sstream>

  class Logger
  {
  public:
    void log(const std::string& msg)
    {
      m_log.push_back(msg);
    }
		
    int countLog(const std::string& msg)
    {
      int count = 0;
      for (int i = 0; i < (int) m_log.size(); ++i)
	{
	  if (m_log[i] == msg) ++count;
	}
      return count;
    }
		
    void clearLog()
    {
        m_log.clear();
    }
  private:
    std::vector<std::string> m_log;
  };
	
class A
{
public:
  int mysvc()
  {
    static int cnt;
    std::cout << "mysvc(): " << cnt << std::endl;
    ++cnt;
    coil::sleep(coil::TimeValue(0, 10000));
    return 0;
  }
    int mysvc2()
    {
      if (m_logger != NULL) 
      {
          m_logger->log("mysvc2");
      }
      return 0;
    }

    static void setLogger(Logger* logger)
    {
      m_logger = logger;
    }

private:
    static Logger* m_logger;
};
  Logger* A::m_logger = NULL;

/*!
 * @class PeriodicTaskTests class
 * @brief PeriodicTask test
 */
namespace PeriodicTask
{
  class PeriodicTaskTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PeriodicTaskTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST(test_setTask);
    CPPUNIT_TEST(test_setPeriodic);
    CPPUNIT_TEST(test_signal);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    PeriodicTaskTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~PeriodicTaskTests()
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
  
    /* test case */
    void test_case0()
    {
      A a;
      coil::PeriodicTask p;
      p.setTask(&a, &A::mysvc);
      p.setPeriod(0.05);
      p.executionMeasure(true);
      p.executionMeasureCount(1);
      p.periodicMeasure(true);
      p.periodicMeasureCount(1);
      p.activate();

      for (int i(0); i < 10; ++i)
        {
          coil::sleep(1);
          std::cout << "i: " << i << std::endl;
          coil::TimeMeasure::Statistics estat = p.getExecStat();
          coil::TimeMeasure::Statistics pstat = p.getPeriodStat();
          
          std::cout << "estat max:  " << estat.max_interval << std::endl;
          std::cout << "estat min:  " << estat.min_interval << std::endl;
          std::cout << "estat mean: " << estat.mean_interval << std::endl;
          std::cout << "estat sdev: " << estat.std_deviation << std::endl;
          
          std::cout << "pstat max:  " << pstat.max_interval << std::endl;
          std::cout << "pstat min:  " << pstat.min_interval << std::endl;
          std::cout << "pstat mean: " << pstat.mean_interval << std::endl;
          std::cout << "pstat sdev: " << pstat.std_deviation << std::endl;

          if (i == 1)
            {
              p.suspend();
              std::cout << "suspended: " << i << std::endl;
            }
          else if (i == 5)
            {
              p.resume();
              std::cout << "resumed: " << i << std::endl;
            }
          else if (i == 3)
            {
              std::cout << "signal: " << i << std::endl;
              p.signal();
              coil::usleep(200000);
              p.signal();
              coil::usleep(200000);
            }

        }

      p.finalize();
     
      

    }
    /*!
     *
     */
    void test_setTask()
    {

      A a;
      coil::PeriodicTask p;
      CPPUNIT_ASSERT(p.setTask(&a, &A::mysvc2));

      Logger logger;
      a.setLogger(&logger);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("mysvc2"));
      p.activate();
      coil::usleep(5);
      p.finalize();
      coil::usleep(5);
      CPPUNIT_ASSERT(1<logger.countLog("mysvc2"));


    }
    /*!
     *
     */
    void test_setPeriodic()
    {
      std::ostringstream ss;
      A a;
      coil::PeriodicTask p;

      Logger logger;
      a.setLogger(&logger);

      p.setTask(&a, &A::mysvc2);
      p.setPeriod(0.05);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("mysvc2"));
      p.activate();
      coil::usleep(100000);
      p.suspend();
      coil::usleep(50000);

//      std::cout<<logger.countLog("mysvc2")<<std::endl;
      CPPUNIT_ASSERT(4>logger.countLog("mysvc2"));
      CPPUNIT_ASSERT(0<logger.countLog("mysvc2"));

      logger.clearLog();

      p.setPeriod(0.01);
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("mysvc2"));
      p.resume();
      coil::usleep(100000);
      p.suspend();
      coil::usleep(10000);
//      std::cout<<logger.countLog("mysvc2")<<std::endl;
      CPPUNIT_ASSERT(12>logger.countLog("mysvc2"));
      CPPUNIT_ASSERT(8<logger.countLog("mysvc2"));

      logger.clearLog();

      coil::TimeValue tm(0,50000);
      p.setPeriod(tm);
      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("mysvc2"));
      p.resume();
      coil::usleep(100000);
      p.finalize();
      coil::usleep(50000);
//      std::cout<<logger.countLog("mysvc2")<<std::endl;
      CPPUNIT_ASSERT(4>logger.countLog("mysvc2"));
      CPPUNIT_ASSERT(0<logger.countLog("mysvc2"));

    }
    /*!
     *
     */
    void test_signal()
    {
      A a;
      coil::PeriodicTask p;

      Logger logger;
      a.setLogger(&logger);

      p.setTask(&a, &A::mysvc2);
      p.setPeriod(0.05);

      CPPUNIT_ASSERT_EQUAL(0, logger.countLog("mysvc2"));
      p.activate();
      coil::usleep(200000);
      p.suspend();

      int count;
      count = logger.countLog("mysvc2");
      coil::usleep(200000);
      CPPUNIT_ASSERT(count == logger.countLog("mysvc2"));

      p.signal();
      coil::usleep(200000);
      CPPUNIT_ASSERT(count+1 == logger.countLog("mysvc2"));
      p.signal();
      coil::usleep(200000);
      CPPUNIT_ASSERT(count+2 == logger.countLog("mysvc2"));

      logger.clearLog();
      p.resume();
      coil::usleep(200000);
      p.suspend();
      coil::usleep(200000);
      CPPUNIT_ASSERT(6>logger.countLog("mysvc2"));
      CPPUNIT_ASSERT(2<logger.countLog("mysvc2"));

      p.finalize();
      coil::usleep(200000);

    }
  };
}; // namespace PeriodicTask

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PeriodicTask::PeriodicTaskTests);

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
#endif // PeriodicTask_cpp

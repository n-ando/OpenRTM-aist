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
};

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

        }

      p.finalize();
     
      

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

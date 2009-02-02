// -*- C++ -*-
/*!
 * @file   TimeMeasureTests.cpp
 * @brief  TimeMeasure test class
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

#ifndef TimeMeasure_cpp
#define TimeMeasure_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <coil/TimeMeasure.h>

/*!
 * @class TimeMeasureTests class
 * @brief TimeMeasure test
 */
namespace TimeMeasure
{
  class TimeMeasureTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(TimeMeasureTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    TimeMeasureTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~TimeMeasureTests()
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
      coil::TimeMeasure tm;
      for (int i(0); i < 100; ++i)
        {
          tm.tick();
          //          sleep(1);
          usleep(30000);
          tm.tack();
        }
      double maxi, mini, mean, stdev;
      tm.getStatistics(maxi, mini, mean, stdev);
      std::cout << "max interval : " << maxi << " [sec]" << std::endl;
      std::cout << "min interval : " << mini << " [sec]" << std::endl;
      std::cout << "mean interval: " << mean << " [sec]" << std::endl;
      std::cout << "stddev       : " << stdev<< " [sec]" << std::endl;
    }
  };
}; // namespace TimeMeasure

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(TimeMeasure::TimeMeasureTests);

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
#endif // TimeMeasure_cpp

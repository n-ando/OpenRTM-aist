// -*- C++ -*-
/*!
 * @file   PublisherNewTests.cpp
 * @brief  PublisherNew test class
 * @date   $Date: 2006-12-18 06:51:43 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: PublisherNewTests.cpp,v 1.1 2006-12-18 06:51:43 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef PublisherNew_cpp
#define PublisherNew_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/Properties.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherNew.h>


/*!
 * @class PublisherNewTests class
 * @brief PublisherNew test
 */
namespace PublisherNew
{
  class TestConsumer
    : public RTC::InPortConsumer
  {
  public:
    TestConsumer() : RTC::InPortConsumer() {};
    virtual ~TestConsumer(){};
    virtual void push()
    {
      gettimeofday(&m_tm, NULL);
      //      std::cout << "push():   " << m_tm.tv_usec << std::endl;
    }
    timeval m_tm;
  };

  class PublisherNewTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PublisherNewTests);
    CPPUNIT_TEST(test_update);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    RTC::PublisherNew* m_publisher;
    TestConsumer m_consumer;
    RTC::Properties m_properties;
  public:
  
    /*!
     * @brief Constructor
     */
    PublisherNewTests()
    {
      m_publisher = new RTC::PublisherNew(m_consumer, m_properties);
    }
    
    /*!
     * @brief Destructor
     */
    ~PublisherNewTests()
    {
      delete m_publisher;
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
#define CNTNUM 100
#define DEBUG

    /* test case */
    void test_update()
    {
      usleep(100000);
      double total(0);
      for (int i = 0; i < CNTNUM; ++i)
	{
	  timeval tm;
	  gettimeofday(&tm, NULL);
	  //	  std::cout << "update(): " << tm.tv_usec << std::endl;
	  m_publisher->update();
	  long int interval;
	  interval = (m_consumer.m_tm.tv_sec - tm.tv_sec) * 1000000
	    + (m_consumer.m_tm.tv_usec - tm.tv_usec);
	  total += interval;
#ifdef DEBUG
	  std::cout << "update() - push(): " << interval << " [us]" << std::endl;
#endif

	  usleep(1000);
	}
      double mean;
      mean = total/CNTNUM;
      CPPUNIT_ASSERT(mean < 20);
    }
  };
}; // namespace PublisherNew

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PublisherNew::PublisherNewTests);

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
#endif // PublisherNew_cpp

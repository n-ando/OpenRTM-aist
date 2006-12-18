// -*- C++ -*-
/*!
 * @file   PublisherFactoryTests.cpp
 * @brief  PublisherFactory test class
 * @date   $Date: 2006-12-18 06:50:59 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: PublisherFactoryTests.cpp,v 1.1 2006-12-18 06:50:59 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef PublisherFactory_cpp
#define PublisherFactory_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <rtm/Properties.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherFactory.h>
#include <rtm/PublisherNew.h>
#include <rtm/PublisherPeriodic.h>
#include <rtm/PublisherFlush.h>

/*!
 * @class PublisherFactoryTests class
 * @brief PublisherFactory test
 */
namespace PublisherFactory
{
  class TestConsumer
    : public RTC::InPortConsumer
  {
  public:
    TestConsumer() : RTC::InPortConsumer() {};
    virtual ~TestConsumer(){};
    virtual void push()
    {
      timeval tm;
      gettimeofday(&tm, NULL);
      interval = (tm.tv_sec - m_tm.tv_sec) * 1000000
	+ (tm.tv_usec - m_tm.tv_usec);
      //      std::cout << "period: " << interval << std::endl;
      m_tm = tm;
    }
    timeval m_tm;
    long int interval;
  };
  
  class PublisherFactoryTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PublisherFactoryTests);
    CPPUNIT_TEST(test_new);
    CPPUNIT_TEST(test_periodic);
    CPPUNIT_TEST(test_flush);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    RTC::PublisherFactory m_factory;
    RTC::PublisherBase* m_publisher;
    TestConsumer m_consumer;
    RTC::Properties m_properties;
  public:
  
    /*!
     * @brief Constructor
     */
    PublisherFactoryTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~PublisherFactoryTests()
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
#define CNTNUM 100
#define DEBUG

    /* test case */
    void test_new()
    {
      m_publisher = m_factory.create("New", &m_consumer, m_properties);

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

      delete m_publisher;
    }

    void test_periodic()
    {
      m_properties.setProperty("dataport.push_interval", "100.0");
      m_publisher = m_factory.create("Periodic", &m_consumer, m_properties);

      sleep(2);
      for (int i = 0; i < 100; ++i)
	{
	  m_publisher->update();
	  //std::cout << m_consumer.interval << std::endl;
	  CPPUNIT_ASSERT(m_consumer.interval < 13000 &&
			 m_consumer.interval >  7000);
	  usleep(10000);
	}

      delete m_publisher;
    }

    void test_flush()
    {
      m_publisher = m_factory.create("Flush", &m_consumer, m_properties);
      
      long int interval0, interval1;
      for (int i = 0; i < 100; ++i)
	{
	  timeval tm0, tm1;
	  gettimeofday(&tm0, NULL);
	  m_publisher->update();
	  gettimeofday(&tm1, NULL);

	  interval0 = (m_consumer.m_tm.tv_sec - tm0.tv_sec) * 1000000
	    + (m_consumer.m_tm.tv_usec - tm0.tv_usec);
	  interval1 = (tm1.tv_sec - m_consumer.m_tm.tv_sec) * 1000000
	    + (tm1.tv_usec - m_consumer.m_tm.tv_usec);
#ifdef DEBUG
	  std::cout << "update() - push(): " << interval0 << std::endl;
	  std::cout << "push() - return  : " << interval1 << std::endl;
#endif
	  usleep(1000);
	  CPPUNIT_ASSERT(interval0 < 15);
	  CPPUNIT_ASSERT(interval1 < 15);
	}

      delete m_publisher;
    }
  };
}; // namespace PublisherFactory

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PublisherFactory::PublisherFactoryTests);

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
#endif // PublisherFactory_cpp

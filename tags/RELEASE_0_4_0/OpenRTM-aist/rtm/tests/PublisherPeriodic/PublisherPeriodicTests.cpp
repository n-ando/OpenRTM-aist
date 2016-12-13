// -*- C++ -*-
/*!
 * @file   PublisherPeriodicTests.cpp
 * @brief  PublisherPeriodic test class
 * @date   $Date: 2007-01-12 14:54:45 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: PublisherPeriodicTests.cpp,v 1.2 2007-01-12 14:54:45 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/12/18 06:51:55  n-ando
 * The first commitment.
 *
 *
 */

#ifndef PublisherPeriodic_cpp
#define PublisherPeriodic_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <iostream>
#include <rtm/Properties.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherPeriodic.h>


/*!
 * @class PublisherPeriodicTests class
 * @brief PublisherPeriodic test
 */
namespace PublisherPeriodic
{
  class TestConsumer
    : public RTC::InPortConsumer
  {
  public:
    TestConsumer() : RTC::InPortConsumer()
    {
    };
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
	virtual RTC::InPortConsumer* clone() const
	{
	  return new TestConsumer();
	}
	virtual bool subscribeInterface(const SDOPackage::NVList&)
	{
	  return true;
	}
	virtual void unsubscribeInterface(const SDOPackage::NVList&)
	{
	  return;
	}
	
    timeval m_tm;
    long int interval;
  };

  class PublisherPeriodicTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PublisherPeriodicTests);
    CPPUNIT_TEST(test_update);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    RTC::PublisherPeriodic* m_publisher;
    TestConsumer m_consumer;
    RTC::Properties m_properties;
  public:
  
    /*!
     * @brief Constructor
     */
    PublisherPeriodicTests()
    {
      m_properties.setProperty("dataport.push_interval", "100.0");
      m_publisher = new RTC::PublisherPeriodic(&m_consumer, m_properties);
    }
    
    /*!
     * @brief Destructor
     */
    ~PublisherPeriodicTests()
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
  
    /* test case */
    void test_update()
    {
      sleep(2);
      for (int i = 0; i < 100; ++i)
	{
	  m_publisher->update();
	  //std::cout << m_consumer.interval << std::endl;
	  CPPUNIT_ASSERT(m_consumer.interval < 13000 &&
			 m_consumer.interval >  7000);
	  usleep(10000);
	}
    }
  };
}; // namespace PublisherPeriodic

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PublisherPeriodic::PublisherPeriodicTests);

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
#endif // PublisherPeriodic_cpp

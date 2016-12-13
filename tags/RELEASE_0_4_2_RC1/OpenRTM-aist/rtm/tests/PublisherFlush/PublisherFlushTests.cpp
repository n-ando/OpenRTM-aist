// -*- C++ -*-
/*!
 * @file   PublisherFlushTests.cpp
 * @brief  PublisherFlush test class
 * @date   $Date: 2007-01-12 14:54:32 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: PublisherFlushTests.cpp,v 1.2 2007-01-12 14:54:32 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/12/18 06:51:31  n-ando
 * The first commitment.
 *
 *
 */

#ifndef PublisherFlush_cpp
#define PublisherFlush_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/Properties.h>
#include <rtm/InPortConsumer.h>
#include <rtm/PublisherFlush.h>

/*!
 * @class PublisherFlushTests class
 * @brief PublisherFlush test
 */
namespace PublisherFlush
{
  class TestConsumer
    : public RTC::InPortConsumer
  {
  public:
    //    TestConsumer() : RTC::InPortConsumer() {};
    //    virtual ~TestConsumer(){};
    virtual void push()
    {
      gettimeofday(&m_tm, NULL);
      // std::cout << "push():   " << tm.tv_usec << std::endl;
      // std::cout << "push():" << std::endl;
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
  };
  
  class PublisherFlushTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(PublisherFlushTests);
    CPPUNIT_TEST(test_update);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    RTC::PublisherFlush* m_publisher;
    TestConsumer m_consumer;
    RTC::Properties m_properties;
  public:
  
    /*!
     * @brief Constructor
     */
    PublisherFlushTests()
    {
      m_publisher = new RTC::PublisherFlush(&m_consumer, m_properties);
    }
    
    /*!
     * @brief Destructor
     */
    ~PublisherFlushTests()
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
	  CPPUNIT_ASSERT(interval0 < 10);
	  CPPUNIT_ASSERT(interval1 < 10);
	}
    }
  };
}; // namespace PublisherFlush

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(PublisherFlush::PublisherFlushTests);

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
#endif // PublisherFlush_cpp

// -*- C++ -*-
/*!
 * @file   OutPortTests.cpp
 * @brief  OutPort test class
 * @date   $Date: 2006-12-02 18:52:54 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/29 04:26:28  n-ando
 * CppUnit tests for OutPort.
 *
 *
 */

#ifndef OutPort_cpp
#define OutPort_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/OutPort.h>
#include <rtm/BufferBase.h>

#define WTIMEOUT_USEC 1000000
#define USEC_PER_SEC 1000000
//#define DEBUG
/*!
 * @class OutPortTests class
 * @brief OutPort test
 */
namespace OutPort
{
  template <class DataType>
  class FullBuffer
    : public RTC::NullBuffer<DataType>
  {
  public:
    FullBuffer(long int length){};
    virtual bool isFull() const
    {
      return true;
    }
  };

  template <class DataType>
  class OnOverflow
    : public RTC::OnOverflow<DataType>
  {
  public:
    virtual void operator()(const DataType& value)
    {
      data = value;
    }
    DataType data;
  };
  class OutPortTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OutPortTests);
    CPPUNIT_TEST(test_wr);
    CPPUNIT_TEST(test_write_timeout);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    OutPortTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~OutPortTests()
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
    void test_wr()
    {
      double value;
      RTC::OutPort<double>* outp;
      outp = new RTC::OutPort<double>("OutPort", value, 8);

      for (int i = 0; i < 100; ++i)
	{
	  value = i * 3.14159265;
	  if (outp->write(value))
	    ;
	  else
	    CPPUNIT_ASSERT(false);

	  double dvar;
	  if (outp->read(dvar))
	    CPPUNIT_ASSERT(dvar == value);
	  else
	    CPPUNIT_ASSERT(false);
	}
    }
    void test_write_timeout()
    {
      double value;
      RTC::OutPort<double, FullBuffer>* outp;
      outp = new RTC::OutPort<double, FullBuffer>("OutPort", value, 8);

      outp->setWriteBlock(true);
      outp->setWriteTimeout(WTIMEOUT_USEC);

      OnOverflow<double> ofcb;

      outp->setOnOverflow(&ofcb);

      timeval tm_cur, tm_pre;
      gettimeofday(&tm_pre, NULL);

      for (int i = 0; i < 10; ++i)
	{
	  value = i * 3.14159265;


	  if (outp->write(value))
	    CPPUNIT_ASSERT(false);
	  else
	    CPPUNIT_ASSERT(ofcb.data == value);

	  gettimeofday(&tm_cur, NULL);
	  long int sec (tm_cur.tv_sec  - tm_pre.tv_sec);
	  long int usec(tm_cur.tv_usec - tm_pre.tv_usec);
	  double interval;
	  interval = (double) sec + (double) usec / USEC_PER_SEC;
	  tm_pre = tm_cur;
#ifdef DEBUG
	  std::cout << "Timeout: " << interval << "[sec]" << std::endl;
	  /*	  std::cout << (double)WTIMEOUT_USEC/USEC_PER_SEC << " " <<
	    interval << " " <<
	    0.1 * WTIMEOUT_USEC/USEC_PER_SEC << std::endl;
	  */
#endif

	  CPPUNIT_ASSERT_DOUBLES_EQUAL((double)WTIMEOUT_USEC/USEC_PER_SEC,
				       interval,
				       0.1 * WTIMEOUT_USEC/USEC_PER_SEC);
	}
    }
  };
}; // namespace OutPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OutPort::OutPortTests);

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
#endif // OutPort_cpp

// -*- C++ -*-
/*!
 * @file   RingBufferTests.cpp
 * @brief  RingBuffer test class
 * @date   $Date: 2006-11-27 08:37:03 $
 * @author Shinji Kurihara
 *         Noriaki Ando <n-ando@aist.go.jp>
 * 
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RingBufferTests.cpp,v 1.1 2006-11-27 08:37:03 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RingBuffer_cpp
#define RingBuffer_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/RingBuffer.h>

/*!
 * @class RingBufferTests class
 * @brief RingBuffer test
 */
namespace RingBuffer
{
  using namespace RTC;
  using namespace std;
  
  class RingBufferTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(RingBufferTests);
    CPPUNIT_TEST(test_put);
    CPPUNIT_TEST(test_get_new);
    CPPUNIT_TEST(test_get_new_rlist);
    CPPUNIT_TEST(test_get_new_list);
    CPPUNIT_TEST(test_get_new_len);
    CPPUNIT_TEST(test_get_old);
    CPPUNIT_TEST(test_get_back);
    CPPUNIT_TEST(test_get_front);
    CPPUNIT_TEST(test_buff_length);
    CPPUNIT_TEST(test_is_new);
    CPPUNIT_TEST_SUITE_END();
    
  private:
    typedef RingBuffer<double> RBuffer;
    RBuffer* m_prb;
    int m_length;
  public:
    
    /*!
     * @brief Constructor
     */
    RingBufferTests()
    {
      m_length = 5;
    }
    
    /*!
     * @brief Destructor
     */
    ~RingBufferTests()
    {
    }
    
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      double initval = 0.0;
      m_prb = new RBuffer(5, initval);
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
      delete m_prb;
    }
    /*!
     * @brief tests for
     */
    void test_put() {
      for (int i = 0; i < m_length; i++)
	m_prb->put(i+1);
    }
    
    
    /*!
     * @brief tests for
     */
    void test_get_new() {}
    
    
    /*!
     * @brief tests for
     */
    void test_get_new_rlist() {}
    
    
    /*!
     * @brief tests for
     */
    void test_get_new_list() {}
    
    
    /*!
     * @brief tests for
     */
    void test_get_new_len() {}
    
    
    /*!
     * @brief tests for
     */
    void test_get_old() {}
    
    
    /*!
     * @brief tests for
     */
    void test_get_back() {}
    
    
    /*!
     * @brief tests for
     */
    void test_get_front() {}
    
    
    /*!
     * @brief tests for
     */
    void test_buff_length() {}
    
    
    /*!
     * @brief tests for
     */
    void test_is_new() {}
    
  };
}; // namespace RingBuffer

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(RingBuffer::RingBufferTests);

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
#endif // RingBuffer_cpp

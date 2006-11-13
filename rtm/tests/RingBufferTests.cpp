// -*- C++ -*-
/*!
 * @file 
 * @brief test class
 * @date $Date: 2006-11-13 09:14:26 $
 * @author Shinji Kurihara
 * $Id: RingBufferTests.cpp,v 1.1 2006-11-13 09:14:26 kurihara Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 */

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include "../RingBuffer.h"

using namespace RTC;
using namespace std;


// RingBuffer クラスのテスト
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
  RingBuffer<double> *m_prb;
  int m_length;
public:
  
  /*!
   * @brief コンストラクタ
   */
  RingBufferTests()
  {
    m_length = 5;
  }


  /*!
   * @brief デストラクタ
   */
  ~RingBufferTests()
  {
  }
  
  /*!
   * @brief 初期化
   */
  virtual void setUp()
  {
    double initval = 0.0;
    m_prb = new RingBuffer<double>(m_length, initval);
  }
  

  /*!
   * @brief 後始処理
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


/*!
 * @brief register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(RingBufferTests);



int main(int argc, char* argv[])
{
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    CppUnit::Outputter* outputter = 
      new CppUnit::TextOutputter(&runner.result(), std::cout);
    runner.setOutputter(outputter);
   
    return runner.run();
}

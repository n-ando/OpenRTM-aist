// -*- C++ -*-
/*!
 * @file   RingBufferTests.cpp
 * @brief  RingBuffer test class
 * @date   $Date: 2006-12-02 18:53:08 $
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
 * $Id$
 *
 */

#ifndef RingBuffer_cpp
#define RingBuffer_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <string>
#include <sstream>
#include <rtm/RingBuffer.h>

//#define DEBUG
#define ITNUM 1025
/*!
 * @class RingBufferTests class
 * @brief RingBuffer test
 */
namespace RingBuffer
{
  class RingBufferTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(RingBufferTests);
    CPPUNIT_TEST(test_init_double);
    CPPUNIT_TEST(test_init_string);
    CPPUNIT_TEST(test_wr_double);
    CPPUNIT_TEST(test_wr_string);
    CPPUNIT_TEST(test_wr_double_s);
    CPPUNIT_TEST(test_wr_string_s);
    CPPUNIT_TEST(test_isnew_double);
    CPPUNIT_TEST(test_isnew_string);
    /*
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
    */
    CPPUNIT_TEST_SUITE_END();
    
  private:
    RTC::RingBuffer<double>* m_double;
    RTC::RingBuffer<std::string>* m_string;
    RTC::RingBuffer<double>* m_double_s;
    RTC::RingBuffer<std::string>* m_string_s;
    
  public:
    
    /*!
     * @brief Constructor
     */
    RingBufferTests()
    {

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
      m_double = new RTC::RingBuffer<double>(17);
      m_string = new RTC::RingBuffer<std::string>(17);
      m_double_s = new RTC::RingBuffer<double>(2);
      m_string_s = new RTC::RingBuffer<std::string>(2);
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }

    void test_init_double()
    {
      // 初期化前なので isNew() == false のはず
      CPPUNIT_ASSERT(!m_double->isNew());

      double data(3.14159265);
      m_double->init(data);

      // 初期化後なので isNew() == true のはず
      CPPUNIT_ASSERT(m_double->isNew());

      double dvar;
      m_double->read(dvar);
      CPPUNIT_ASSERT(data == dvar);

      // read()後なので isNew() == false のはず
      CPPUNIT_ASSERT(!m_double->isNew());
    }

    void test_init_string()
    {
      // 初期化前なので isNew() == false のはず
      CPPUNIT_ASSERT(!m_string->isNew());

      std::string data("3.14159265");
      m_string->init(data);


      // 初期化後なので isNew() == true のはず
      CPPUNIT_ASSERT(m_string->isNew());

      std::string dvar;
      m_string->read(dvar);
      CPPUNIT_ASSERT(data == dvar);

      // read()後なので isNew() == false のはず
      CPPUNIT_ASSERT(!m_string->isNew());
    }

    /*!
     * @brief RingBuffer<double> のwrite/read テスト
     */
    void test_wr_double()
    {
      for (int i = 0; i < ITNUM; ++i)
	{
	  if (m_double->write(i))
	    ;
	  else
	    CPPUNIT_ASSERT(false);

	  double dvar;
	  if (m_double->read(dvar))
	    {
#ifdef DEBUG
	      std::cout << i << "\t" << dvar << std::endl;
#endif
	      CPPUNIT_ASSERT((double)i == dvar);
	    }
	  else
	    {
	      CPPUNIT_ASSERT(false);
	    }
	}
    }

    /*!
     * @brief RingBuffer<string> のwrite/read テスト
     */
    void test_wr_string()
    {
      for (int i = 0; i < ITNUM; ++i)
	{
	  std::stringstream str_stream;
	  str_stream << "Hogehoge" << i;
	  if (m_string->write(str_stream.str()))
	    ;
	  else
	    CPPUNIT_ASSERT(false);

	  std::string strvar;
	  if (m_string->read(strvar))
	    {
#ifdef DEBUG
	      std::cout << str_stream.str() << "\t" << strvar << std::endl;
#endif
	      CPPUNIT_ASSERT(strvar == str_stream.str());	    
	    }
	  else
	    {
	    }
	}
    }
    
    /*!
     * @brief RingBuffer<double>(ダブルバッファ) のwrite/read テスト
     */
    void test_wr_double_s()
    {
      for (int i = 0; i < ITNUM; ++i)
	{
	  if (m_double_s->write(i))
	    ;
	  else
	    CPPUNIT_ASSERT(false);

	  double dvar;
	  if (m_double_s->read(dvar))
	    {
#ifdef DEBUG
	      std::cout << i << "\t" << dvar << std::endl;
#endif
	      CPPUNIT_ASSERT((double)i == dvar);
	    }
	  else
	    {
	      CPPUNIT_ASSERT(false);
	    }
	}
    }

    /*!
     * @brief RingBuffer<string>(ダブルバッファ) のwrite/read テスト
     */
    void test_wr_string_s()
    {
      for (int i = 0; i < ITNUM; ++i)
	{
	  std::stringstream str_stream;
	  str_stream << "Hogehoge" << i;
	  if (m_string_s->write(str_stream.str()))
	    ;
	  else
	    CPPUNIT_ASSERT(false);

	  std::string strvar;
	  if (m_string_s->read(strvar))
	    {
#ifdef DEBUG
	      std::cout << str_stream.str() << "\t" << strvar << std::endl;
#endif
	      CPPUNIT_ASSERT(strvar == str_stream.str());	    
	    }
	  else
	    {
	    }
	}
    }
    
    
    /*!
     * @brief isNew() のテスト
     */
    void test_isnew_double()
    {
      for (long int i = 0; i < ITNUM; ++i)
	{
	  double data;
	  data = (double)i * 3.14159265;
	  m_double->write(data);
	  if ((i % 13) == 0)
	    {
	      double dvar;
	      if (m_double->isNew())
		m_double->read(dvar);
	      else
		CPPUNIT_ASSERT(false);
	      CPPUNIT_ASSERT(data == dvar);
	    }

	  if ((i % 7) == 0)
	    {
	      double dvar;
	      m_double->read(dvar);
	      CPPUNIT_ASSERT(data == dvar);

	      // isNew() == false のはず
	      if (m_double->isNew())
		CPPUNIT_ASSERT(false);
	      m_double->read(dvar);
	      CPPUNIT_ASSERT(data == dvar);

	      // isNew() == false のはず
	      if (m_double->isNew())
		CPPUNIT_ASSERT(false);
	      m_double->read(dvar);
	      CPPUNIT_ASSERT(data == dvar);
	    }
	}	      
    }
    

    /*!
     * @brief isNew() のテスト
     */
    void test_isnew_string()
    {
      for (long int i = 0; i < ITNUM; ++i)
	{
	  std::stringstream strstr;
	  strstr << "HogeHoge" << i;
	  m_string->write(strstr.str());
	  if ((i % 13) == 0)
	    {
	      std::string strvar;
	      if (m_string->isNew())
		m_string->read(strvar);
	      else
		CPPUNIT_ASSERT(false);
	      CPPUNIT_ASSERT(strstr.str() == strvar);
	    }

	  if ((i % 7) == 0)
	    {
	      std::string strvar;
	      m_string->read(strvar);
	      CPPUNIT_ASSERT(strstr.str() == strvar);

	      // isNew() == false のはず
	      if (m_string->isNew())
		CPPUNIT_ASSERT(false);
	      m_string->read(strvar);
	      CPPUNIT_ASSERT(strstr.str() == strvar);

	      // isNew() == false のはず
	      if (m_double->isNew())
		CPPUNIT_ASSERT(false);
	      m_string->read(strvar);
	      CPPUNIT_ASSERT(strstr.str() == strvar);
	    }
	}	      
    }
    
    
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

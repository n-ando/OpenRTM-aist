// -*- C++ -*-
/*!
 * @file   NullBufferTests.cpp
 * @brief  NullBuffer test class
 * @date   $Date: 2006-12-02 18:54:50 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

#ifndef NullBuffer_cpp
#define NullBuffer_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <iostream>
#include <rtm/BufferBase.h>

/*!
 * @class NullBufferTests class
 * @brief NullBuffer test
 */
namespace NullBuffer
{
  struct Data
  {
    int    int_data;
    double double_data;
  };

  template <class DataType>
  class MyBuffer
    : public RTC::NullBuffer<DataType>
  {
  public:
    virtual void put(const DataType& data)
    {
      RTC::NullBuffer<DataType>::put(data);
    }

    virtual const DataType& get()
    {
      return RTC::NullBuffer<DataType>::get();
    }

    virtual DataType& getRef()
    {
      return RTC::NullBuffer<DataType>::getRef();
    }
  };

  class NullBufferTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(NullBufferTests);
    CPPUNIT_TEST(test_wr_int);
    CPPUNIT_TEST(test_wr_char);
    CPPUNIT_TEST(test_wr_struct);
    CPPUNIT_TEST(test_isfull);
    CPPUNIT_TEST(test_isempty);
    CPPUNIT_TEST(test_pg_int);
    CPPUNIT_TEST(test_pg_char);
    CPPUNIT_TEST(test_put_struct);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    RTC::BufferBase<int>*  m_intBuf;
    RTC::BufferBase<char>* m_charBuf;
    RTC::BufferBase<Data>* m_dataBuf;
  public:
  
    /*!
     * @brief Constructor
     */
    NullBufferTests()
    {
      m_intBuf  = new MyBuffer<int>();
      m_charBuf = new MyBuffer<char>();
      m_dataBuf = new MyBuffer<Data>();
    }
    
    /*!
     * @brief Destructor
     */
    ~NullBufferTests()
    {
      delete m_intBuf;
      delete m_charBuf;
      delete m_dataBuf;
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
    void test_wr_int()
    {
      for (int i = 0; i < 100; ++i)
	{
	  if (m_intBuf->write(i))
	    ;
	  else
	    CPPUNIT_ASSERT(false);

	  int intvar;
	  if (m_intBuf->read(intvar))
	    ;
	  else
	    CPPUNIT_ASSERT(i == intvar);
	}
    }

    void test_wr_char()
    {
      for (int i = 0; i < 100; ++i)
	{
	  if (m_charBuf->write(i))
	    ;
	  else
	    CPPUNIT_ASSERT(false);

	  char charvar;
	  if (m_charBuf->read(charvar))
	    CPPUNIT_ASSERT(i == charvar);
	  else
	    CPPUNIT_ASSERT(false);
	}
    }

    void test_wr_struct()
    {
      for (int i = 0; i < 100; ++i)
	{
	  Data data;
	  data.int_data = i;
	  data.double_data = i / 3.141592653589793238462643383279;

	  if (m_dataBuf->write(data))
	    ;
	  else
	    CPPUNIT_ASSERT(false);

	  Data dvar;
	  if (m_dataBuf->read(dvar))
	    {
	      CPPUNIT_ASSERT(data.int_data == dvar.int_data);
	      CPPUNIT_ASSERT(data.double_data == dvar.double_data);
     // std::cout << dvar.int_data << "\t" << dvar.double_data << std::endl;
	    }
	  else
	    CPPUNIT_ASSERT(false);
	} 
    }

    void test_isfull()
    {
      CPPUNIT_ASSERT(!m_intBuf->isFull());
      CPPUNIT_ASSERT(!m_charBuf->isFull());
      CPPUNIT_ASSERT(!m_dataBuf->isFull());
    }


    void test_isempty()
    {
      CPPUNIT_ASSERT(!m_intBuf->isEmpty());
      CPPUNIT_ASSERT(!m_charBuf->isEmpty());
      CPPUNIT_ASSERT(!m_dataBuf->isEmpty());
    }

    void test_pg_int()
    {
      for (int i = 0; i < 100; ++i)
	{
	  dynamic_cast<MyBuffer<int>*>(m_intBuf)->put(i);
	  CPPUNIT_ASSERT(i == dynamic_cast<MyBuffer<int>*>(m_intBuf)->get());
	}
    }

    void test_pg_char()
    {
      for (int i = 0; i < 100; ++i)
	{
	  dynamic_cast<MyBuffer<char>*>(m_charBuf)->put(i);
	  CPPUNIT_ASSERT(i == dynamic_cast<MyBuffer<char>*>(m_charBuf)->get());
	}
    }

    void test_put_struct()
    {
      for (int i = 0; i < 100; ++i)
	{
	  Data data;
	  data.int_data = i;
	  data.double_data = i / 3.141592653589793238462643383279;

	  dynamic_cast<MyBuffer<Data>*>(m_dataBuf)->put(data);

	  CPPUNIT_ASSERT(data.int_data
            == dynamic_cast<MyBuffer<Data>*>(m_dataBuf)->get().int_data);
	  CPPUNIT_ASSERT(data.double_data
            == dynamic_cast<MyBuffer<Data>*>(m_dataBuf)->get().double_data);
     // std::cout << dvar.int_data << "\t" << dvar.double_data << std::endl;
	} 
    }


  };
}; // namespace NullBuffer

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(NullBuffer::NullBufferTests);

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
#endif // NullBuffer_cpp

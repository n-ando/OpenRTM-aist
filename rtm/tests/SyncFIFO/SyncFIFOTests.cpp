// -*- C++ -*-
/*!
 * @file   SyncFIFOTests.cpp
 * @brief  SyncFIFO test class
 * @date   $Date: 2007-09-19 02:37:05 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

#ifndef SyncFIFO_cpp
#define SyncFIFO_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <SyncFIFO.h>
#include <vector>
/*!
 * @class SyncFIFOTests class
 * @brief SyncFIFO test
 */
#define IBUF_LEN 23
#define DBUF_LEN 65
#define VBUF_LEN 44
namespace SyncFIFO
{
  class SyncFIFOTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(SyncFIFOTests);
    CPPUNIT_TEST(test_init);
    CPPUNIT_TEST(test_length);
    CPPUNIT_TEST(test_readable);
    CPPUNIT_TEST(test_writable);
    CPPUNIT_TEST(test_setbuffer);
    CPPUNIT_TEST(test_putn);
    CPPUNIT_TEST_SUITE_END();
    struct TimedIntVector
    {
      long time;
      std::vector<int> data;
    };
  
  private:
    RTC::SyncFIFO<int> m_ibuf;
    RTC::SyncFIFO<double> m_dbuf;
    RTC::SyncFIFO<TimedIntVector> m_vbuf;
  public:
  
    /*!
     * @brief Constructor
     */
    SyncFIFOTests()
      : m_ibuf(IBUF_LEN), m_dbuf(DBUF_LEN), m_vbuf(VBUF_LEN)
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~SyncFIFOTests()
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
    void test_init()
    {
      m_ibuf.init(7);
      m_dbuf.init(9.876);

      CPPUNIT_ASSERT(m_ibuf.readable() == (IBUF_LEN - 1));
      CPPUNIT_ASSERT(m_dbuf.readable() == (DBUF_LEN - 1));

      for (int i(0), len(m_ibuf.readable()); i < len; ++i)
	{
	  int data;
	  CPPUNIT_ASSERT(m_ibuf.read(data) == true);
	  CPPUNIT_ASSERT(data == 7);
	}

      for (int i(0), len(m_dbuf.readable()); i < len; ++i)
	{
	  double data;
	  CPPUNIT_ASSERT(m_dbuf.read(data));
	  CPPUNIT_ASSERT(data == 9.876);
	}

      CPPUNIT_ASSERT(m_ibuf.readable() == 0);
      CPPUNIT_ASSERT(m_dbuf.readable() == 0);

    }

    void test_length()
    {
      CPPUNIT_ASSERT(m_ibuf.length() == IBUF_LEN);
      CPPUNIT_ASSERT(m_dbuf.length() == DBUF_LEN);
      CPPUNIT_ASSERT(m_vbuf.length() == VBUF_LEN);
    }

    void test_readable()
    {
      CPPUNIT_ASSERT(m_ibuf.readable() == 0);
      CPPUNIT_ASSERT(m_dbuf.readable() == 0);
      CPPUNIT_ASSERT(m_vbuf.readable() == 0);

      m_ibuf.write(1);
      m_dbuf.write(3.14);
      TimedIntVector iv;
      iv.time = 100000;
      iv.data.push_back(1);
      iv.data.push_back(2);
      iv.data.push_back(3);
      iv.data.push_back(4);
      m_vbuf.write(iv);

      CPPUNIT_ASSERT(m_ibuf.readable() == 1);
      CPPUNIT_ASSERT(m_dbuf.readable() == 1);
      CPPUNIT_ASSERT(m_vbuf.readable() == 1);
    }

    void test_writable()
    {
      CPPUNIT_ASSERT(m_ibuf.writable() == (IBUF_LEN - 1));
      CPPUNIT_ASSERT(m_dbuf.writable() == (DBUF_LEN - 1));
      CPPUNIT_ASSERT(m_vbuf.writable() == (VBUF_LEN - 1));

      m_ibuf.write(1);
      m_dbuf.write(3.14);
      TimedIntVector iv;
      iv.time = 100000;
      iv.data.push_back(1);
      iv.data.push_back(2);
      iv.data.push_back(3);
      iv.data.push_back(4);
      m_vbuf.write(iv);

      CPPUNIT_ASSERT(m_ibuf.writable() == (IBUF_LEN - 2));
      CPPUNIT_ASSERT(m_dbuf.writable() == (DBUF_LEN - 2));
      CPPUNIT_ASSERT(m_vbuf.writable() == (VBUF_LEN - 2));
    }

    void test_setbuffer()
    {
      int ibuf[6];
      double dbuf[6];

      m_ibuf.setBuffer(ibuf, 6);
      m_dbuf.setBuffer(dbuf, 6);

      CPPUNIT_ASSERT(m_ibuf.length() == 6);
      CPPUNIT_ASSERT(m_dbuf.length() == 6);

      for (int i(0); i < 1000; ++i)
	{
	  m_ibuf.write(i);
	  m_dbuf.write(i * 3.14);

	  int idata;
	  CPPUNIT_ASSERT(m_ibuf.read(idata) == true);
	  CPPUNIT_ASSERT(ibuf[i % 6] == idata);

	  double ddata;
	  CPPUNIT_ASSERT(m_dbuf.read(ddata) == true);
	  CPPUNIT_ASSERT(dbuf[i % 6] == ddata);
	}
    }


    void test_putn()
    {
      for (int j(0); j < 1000; ++j)
	{
	  CPPUNIT_ASSERT(m_ibuf.writable() == (IBUF_LEN - 1));
	  CPPUNIT_ASSERT(m_dbuf.writable() == (DBUF_LEN - 1));
	  
	  CPPUNIT_ASSERT(m_ibuf.readable() == 0);
	  CPPUNIT_ASSERT(m_dbuf.readable() == 0);
	  
	  int ibuf[6] = {1, 2, 3, 4, 5, 6};
	  double dbuf[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
	  
	  m_ibuf.putn(ibuf, 6);
	  m_dbuf.putn(dbuf, 6);
	  
	  CPPUNIT_ASSERT(m_ibuf.readable() == 6);
	  CPPUNIT_ASSERT(m_dbuf.readable() == 6);
	  
	  int ibuf2[6];
	  double dbuf2[6];
	  
	  m_ibuf.getn(ibuf2, 6);
	  m_dbuf.getn(dbuf2, 6);
	  
	  for (int i(0); i < 6; ++i)
	    {
	      CPPUNIT_ASSERT(ibuf[i] == ibuf2[i]);
	      CPPUNIT_ASSERT(dbuf[i] == dbuf2[i]);
	    }
	}
    }

  };
}; // namespace SyncFIFO

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(SyncFIFO::SyncFIFOTests);

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
#endif // SyncFIFO_cpp

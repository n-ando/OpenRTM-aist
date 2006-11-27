// -*- C++ -*-
/*!
 * @file   InPortTests.cpp
 * @brief  InPort test class
 * @date   $Date: 2006-11-27 08:32:39 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 *
 * Copyright (C) 2006
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: InPortTests.cpp,v 1.1 2006-11-27 08:32:39 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef InPort_cpp
#define InPort_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <fstream>
#include <string>

#include <rtm/InPort.h>

/*!
 * @class InPortTests class
 * @brief InPort test
 */
namespace InPort
{
  class InPortTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(InPortTests);
    CPPUNIT_TEST(test_put);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    typedef RTC::InPort<int> InPortInt;
    InPortInt* m_pInport;
    int m_value;

  public:
  
    /*!
     * @brief Constructor
     */
    InPortTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~InPortTests()
    {
    }


    class OnWrite
      : public RTC::InPort<int>::OnWrite
    {
      void operator()(const int& value)
      {
	std::cout << "put(): " << value << std::endl;
      };
    };

    class OnWriteConvert
      : public RTC::InPort<int>::OnWriteConvert
    {
      int operator()(const int& value)
      {
	return value * value * value;
      };
    };
    
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      m_pInport = new InPortInt("int", m_value);
      m_pInport->setOnWrite(new OnWrite());
      m_pInport->setOnWriteConvert(new OnWriteConvert());
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    {
      delete m_pInport; 
    }
  
    /* tests for void registerObject(Object* obj) */
    void test_put()
    {
      for (int i = 0; i < 100; ++i)
	{
	  //	std::cout << i << std::endl;
	  m_pInport->write(i);
	  std::cout << m_pInport->read() << std::endl;
	}
    }
  };
}; // namespace InPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(InPort::InPortTests);

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
#endif // InPort_cpp

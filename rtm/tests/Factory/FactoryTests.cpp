// -*- C++ -*-
/*!
 * @file   FactoryTests.cpp
 * @brief  Factory test class
 * @date   $Date: 2007-01-12 14:50:35 $
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

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 08:31:38  n-ando
 * TestSuites are devided into each directory.
 *
 *
 */

#ifndef Factory_cpp
#define Factory_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

//#include <rtm/Factory.h>
//#include <rtm/Manager.h>

namespace RTC
{
  class RtcBase
  {
  };
};

/*!
 * @class FactoryTests class
 * @brief Factory test
 */
namespace Factory
{
  using namespace std;

  /*
  class Sample
    : public RTC::RtcBase
  {
  public:
    Sample() {};
  };
  
  
  extern "C"
  {
    RTC::RtcBase* SampleNew(RTC::Manager* manager)
    {
      return new Sample();
    }
    
    
    void SampleDelete(RTC::RtcBase* p)
    {
      delete (Sample *)p;
      return;
    }
    
    
    //  void SampleInit(Manager* manager)
    //  {
    //	RtcModuleProfile profile(sample_spec);
    //	manager->registerComponent(profile, SampleNew, SampleDelete);
    //  }
  };
  */  
  class FactoryTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(FactoryTests);
    CPPUNIT_TEST(test_create);
    CPPUNIT_TEST(test_destroy);
    CPPUNIT_TEST_SUITE_END();
  
  private:
	//    RTC::FactoryCXX*  m_pFC;
  public:
  
    /*!
     * @brief Constructor
     */
    FactoryTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~FactoryTests()
    {
    }
  
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
	  //      RTC::Properties profile;
	  //      m_pFC = new RTC::FactoryCXX(profile, SampleNew, SampleDelete);
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    {
	  //      delete m_pFC; 
    }
  
    /* tests for RtcBase* create(Manager* mgr) */
    void test_create()
	{
      CPPUNIT_FAIL("test");
    }
    
    
    /* tests for RtcBase* create(Manager* mgr) */
    void test_destroy()
	{
      CPPUNIT_FAIL("test");
    }
  };
}; // namespace Factory

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(Factory::FactoryTests);

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
#endif // Factory_cpp

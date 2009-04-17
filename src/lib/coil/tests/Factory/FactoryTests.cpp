// -*- C++ -*-
/*!
 * @file   FactoryTests.cpp
 * @brief  Factory test class
 * @date   $Date$ 
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$ 
 *
 */

/*
 * $Log$
 *
 */

#ifndef Factory_cpp
#define Factory_cpp

#include <string>

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/Factory.h>

class Base
{
public:
  virtual ~Base(){}
  virtual std::string name() = 0;
};

class A
  : public Base
{
public:
  virtual std::string name()
  {
    return "A";
  }
};

class B
  : public Base
{
public:
  virtual std::string name()
  {
    return "B";
  }
};

/*!
 * @class FactoryTests class
 * @brief Factory test
 */
namespace Factory
{
  class FactoryTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(FactoryTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    coil::Factory<Base> m_factory;
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
    }
    
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    { 
    }
  
    /* test case */
    void test_case0()
    {
      std::string Astr("A");
      std::string Bstr("B");
      m_factory.addFactory("A",
                           coil::Creator<Base, A>,
                           coil::Destructor<Base, A>);
      m_factory.addFactory("B",
                           coil::Creator<Base, B>,
                           coil::Destructor<Base, B>);

      for (int i(0); i < 1000; ++i)
        {
          Base* a = m_factory.createObject("A");
          CPPUNIT_ASSERT(a->name() == "A");

          Base* b = m_factory.createObject("B");
          CPPUNIT_ASSERT(b->name() == "B");
          
          m_factory.deleteObject(a);
          CPPUNIT_ASSERT(a == 0);

          m_factory.deleteObject(b);
          CPPUNIT_ASSERT(b == 0);
        }
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

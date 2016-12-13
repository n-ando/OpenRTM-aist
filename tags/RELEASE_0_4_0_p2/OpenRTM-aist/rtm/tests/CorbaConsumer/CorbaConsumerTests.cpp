// -*- C++ -*-
/*!
 * @file   CorbaConsumerTests.cpp
 * @brief  CorbaConsumer test class
 * @date   $Date: 2007-01-12 14:48:30 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: CorbaConsumerTests.cpp,v 1.2 2007-01-12 14:48:30 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.1  2006/11/27 08:30:48  n-ando
 * TestSuites are devided into each directory.
 *
 *
 */

#ifndef CorbaConsumer_cpp
#define CorbaConsumer_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/config_rtc.h>
#include "HelloSkel.h"
#include <rtm/CorbaConsumer.h>

/*!
 * @class CorbaConsumerTests class
 * @brief CorbaConsumer test
 */
namespace CorbaConsumer
{
  class hello_impl
    : virtual public POA_hello,
      virtual public PortableServer::RefCountServantBase
  {
  public:
    hello_impl(){};
    virtual ~hello_impl(){};
    
    void hello_world()
    {
      std::cout << "hello world" << std::endl;
    }
  };

  class CorbaConsumerTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(CorbaConsumerTests);
    CPPUNIT_TEST(test_consumer);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;

  public:
  
    /*!
     * @brief Constructor
     */
    CorbaConsumerTests()
    {
      int argc(0);
      char** argv(NULL);
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
			    m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();
    }
    
    /*!
     * @brief Destructor
     */
    ~CorbaConsumerTests()
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
    
    void test_consumer()
    {
      hello_impl* pHello = new hello_impl();
      
      PortableServer::ServantBase* servant;
      
      servant = pHello;
      
      PortableServer::ObjectId_var oid;
      oid = m_pPOA->activate_object(servant);
      
      RTC::CorbaConsumer<hello> cons;
      cons.setObject(m_pPOA->id_to_reference(oid));
      cons._ptr()->hello_world();
    }
  };
}; // namespace CorbaConsumer

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(CorbaConsumer::CorbaConsumerTests);

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
#endif // CorbaConsumer_cpp

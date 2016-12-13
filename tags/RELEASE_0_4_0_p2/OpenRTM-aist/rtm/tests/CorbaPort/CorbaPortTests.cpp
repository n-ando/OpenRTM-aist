// -*- C++ -*-
/*!
 * @file   CorbaPortTests.cpp
 * @brief  CorbaPort test class
 * @date   $Date: 2007-01-04 00:50:38 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: CorbaPortTests.cpp,v 1.1 2007-01-04 00:50:38 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef CorbaPort_cpp
#define CorbaPort_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/CorbaPort.h>
#include <rtm/CorbaConsumer.h>

#include "MyServiceSkel.h"

class MyService_impl
  : public virtual POA_MyService,
    public virtual PortableServer::RefCountServantBase
{
public:
  virtual ~MyService_impl(){};
  void setName(const char* name) { m_name = name; }
  char* name(){ return "MyService"; }
  void hello_world() { std::cout << m_name << ": Hello, World!!!" << std::endl; }
  void print_msg(const char* msg) { std::cout << m_name << ": " << msg << std::endl; }
  std::string m_name;
};


/*!
 * @class CorbaPortTests class
 * @brief CorbaPort test
 */
namespace CorbaPort
{
  class CorbaPortTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(CorbaPortTests);
    CPPUNIT_TEST(test_ifprofile);
    CPPUNIT_TEST(test_connect);
    CPPUNIT_TEST(test_disconnect);
    CPPUNIT_TEST_SUITE_END();
  
  private:
    RTC::CorbaPort* m_port0;
    RTC::Port_var m_port0ref;
    MyService_impl m_mysvc0;
    RTC::CorbaConsumer<MyService> m_cons0;

    RTC::CorbaPort* m_port1;
    RTC::Port_var m_port1ref;
    MyService_impl m_mysvc1;
    RTC::CorbaConsumer<MyService> m_cons1;
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
  public:
  
    /*!
     * @brief Constructor
     */
    CorbaPortTests()
    {
      int argc(0);
      char** argv(NULL);
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
	         m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();

      m_port0 = new RTC::CorbaPort("port0");
      m_port1 = new RTC::CorbaPort("port1");

      m_port0ref = m_port0->getPortRef();
      m_port1ref = m_port1->getPortRef();

      m_mysvc0.setName("MyService0 in Port0");
      m_port0->registerProvider("MyService0", "Generic", m_mysvc0);
      m_port0->registerConsumer("MyService1", "Generic", m_cons0 );

      m_mysvc1.setName("MyService1 in Port1");
      m_port1->registerProvider("MyService1", "Generic", m_mysvc1);
      m_port1->registerConsumer("MyService0", "Generic", m_cons1 );
    }
    
    /*!
     * @brief Destructor
     */
    ~CorbaPortTests()
    {
      try
	{
	  m_pPOA->destroy(false, false);
	  m_pPOA->the_POAManager()->deactivate(false, false);
	  m_pORB->destroy(); 
	}
      catch (...)
	{
	  ; // do nothing
	}
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
    void test_ifprofile()
    {
      RTC::PortProfile* prof0;
      prof0 = m_port0ref->get_port_profile();

      std::cout << "port0.name:" << prof0->name << std::endl;

      CORBA::ULong len0(prof0->interfaces.length());
      RTC::PortInterfaceProfileList& iflist0(prof0->interfaces);
      for (CORBA::ULong i = 0; i < len0; ++i)
	{
	  std::cout << "port0.if" << i << ".instance_name:"
		    << iflist0[i].instance_name << std::endl;
	  std::cout << "port0.if" << i << ".type_name:"
		    << iflist0[i].type_name << std::endl;
	  std::cout <<  "port0.if" << i << ".polarity:"
		    << ((iflist0[i].polarity == RTC::PROVIDED)
			? "PROVIDED" : "REQUIRED") << std::endl;
	}

      RTC::PortProfile* prof1;
      prof1 = m_port1ref->get_port_profile();

      std::cout << "port1.name:" << prof1->name << std::endl;

      CORBA::ULong len1(prof1->interfaces.length());
      RTC::PortInterfaceProfileList& iflist1(prof1->interfaces);
      for (CORBA::ULong i = 0; i < len1; ++i)
	{
	  std::cout << "port1.if" << i << ".instance_name:"
		    << iflist1[i].instance_name << std::endl;
	  std::cout << "port1.if" << i << ".type_name:"
		    << iflist1[i].type_name << std::endl;
	  std::cout <<  "port1.if" << i << ".polarity:"
		    << ((iflist1[i].polarity == RTC::PROVIDED)
			? "PROVIDED" : "REQUIRED") << std::endl;
	}

    }

    void test_connect()
    {
      RTC::ConnectorProfile prof;
      prof.connector_id = "";
      prof.name = CORBA::string_dup("connector0");
      prof.ports.length(2);
      prof.ports[0] = m_port0ref;
      prof.ports[1] = m_port1ref;

      m_port0ref->connect(prof);

      std::cout << prof.connector_id << std::endl;

      std::cout << "Consumer0: " << m_cons0->name() << std::endl;
      m_cons0->hello_world();
      m_cons0->print_msg("hogehoge");

      std::cout << "Consumer1: " << m_cons1->name() << std::endl;
      m_cons1->hello_world();
      m_cons1->print_msg("hogehoge");

    }

    void test_disconnect()
    {
      RTC::ConnectorProfile prof;
      prof.connector_id = "";
      prof.name = CORBA::string_dup("connector0");
      prof.ports.length(2);
      prof.ports[0] = m_port0ref;
      prof.ports[1] = m_port1ref;

      RTC::ReturnCode_t retval;
      retval = m_port0ref->connect(prof);
      std::cout << "retval: " << retval << std::endl;

      std::cout << prof.connector_id << std::endl;

      RTC::ConnectorProfileList* proflist;

      proflist = m_port0ref->get_connector_profiles();

      std::cout << "conn proflist len: " << proflist->length() << std::endl;

      std::cout << m_cons0->name() << std::endl;
      m_cons0->hello_world();
      m_cons0->print_msg("hogehoge");

      m_port0ref->disconnect(prof.connector_id);

      try
	{
	  CPPUNIT_ASSERT(CORBA::is_nil(m_cons0._ptr()));
	  std::cout << m_cons0->name() << std::endl;
	  m_cons0->hello_world();
	  m_cons0->print_msg("hogehoge");
	  CPPUNIT_ASSERT(false);
	}
      catch (...)
	{
	  std::cout << "Properly disconnected" << std::endl;
	}

    }




  };
}; // namespace CorbaPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(CorbaPort::CorbaPortTests);

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
#endif // CorbaPort_cpp

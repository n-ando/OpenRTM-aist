// -*- C++ -*-
/*!
 * @file   CorbaObjectManagerTests.cpp
 * @brief  CorbaObjectManager test class
 * @date   $Date: 2008/04/25 07:28:29 $
 *
 * $Id: CorbaObjectManagerTests.cpp,v 1.1 2008/04/25 07:28:29 arafune Exp $
 *
 */

/*
 * $Log: CorbaObjectManagerTests.cpp,v $
 * Revision 1.1  2008/04/25 07:28:29  arafune
 * The first commitment.
 *
 * Revision 1.1  2008/04/24 08:49:57  arafune
 * The first commitment.
 *
 */

#ifndef CorbaObjectManager_cpp
#define CorbaObjectManager_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/RTC.h>
#include <rtm/PeriodicExecutionContext.h>
#include <rtm/CorbaObjectManager.h>

/*!
 * @class CorbaObjectManagerTests class
 * @brief CorbaObjectManager test
 */
namespace CorbaObjectManager
{
  class RTObjectMock
    : public RTC::RTObject_impl
  {
  public:
    RTObjectMock(CORBA::ORB_ptr orb, PortableServer::POA_ptr poa)
      : RTC::RTObject_impl(orb, poa)
    {
    }
  };

  class CorbaObjectManagerTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(CorbaObjectManagerTests);
    CPPUNIT_TEST(test_activate_and_deactivate);
    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
	
  public:
    /*!
     * @brief Constructor
     */
    CorbaObjectManagerTests()
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
    virtual ~CorbaObjectManagerTests()
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
		
    /*!
     * @brief activate()とdeactivate()のテスト
     * 
     * - RTObjectを正常にアクティブ化できるか？
     * - RTObjectを正常に非アクティブ化できるか？
     */
    void test_activate_and_deactivate()
    {

      RTC::CorbaObjectManager objMgr(m_pORB, m_pPOA);
			
      // RTObjectをアクティブ化する
      RTObjectMock* rto = new RTObjectMock(m_pORB, m_pPOA);
      objMgr.activate(rto);

      // RTObjectに参照が設定されているか確認することでアクティブ化の成功を確認する
      RTC::RTObject_ptr rtoRef = rto->getObjRef();
      CPPUNIT_ASSERT(! CORBA::is_nil(rtoRef));
      rtoRef->get_sdo_id();
			
      // 非アクティブ化する
      objMgr.deactivate(rto);
      // 参照を用いてCORBAインタフェースにアクセスし、参照無効により意図どおり失敗することを確認する
      try
	{
	  rtoRef->get_sdo_id();
	  CPPUNIT_FAIL("Failed to deactivate.");
	}
      catch (...) {
	// expected
      }
    }
		
  };
}; // namespace CorbaObjectManager

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(CorbaObjectManager::CorbaObjectManagerTests);

#ifdef LOCAL_MAIN
int main(int argc, char* argv[])
{

  FORMAT format = TEXT_OUT;
  int target = 0;
  std::string xsl;
  std::string ns;
  std::string fname;
  std::ofstream ofs;

  int i(1);
  while (i < argc)
    {
      std::string arg(argv[i]);
      std::string next_arg;
      if (i + 1 < argc) next_arg = argv[i + 1];
      else              next_arg = "";

      if (arg == "--text") { format = TEXT_OUT; break; }
      if (arg == "--xml")
	{
	  if (next_arg == "")
	    {
	      fname = argv[0];
	      fname += ".xml";
	    }
	  else
	    {
	      fname = next_arg;
	    }
	  format = XML_OUT;
	  ofs.open(fname.c_str());
	}
      if ( arg == "--compiler"  ) { format = COMPILER_OUT; break; }
      if ( arg == "--cerr"      ) { target = 1; break; }
      if ( arg == "--xsl"       )
	{
	  if (next_arg == "") xsl = "default.xsl"; 
	  else                xsl = next_arg;
	}
      if ( arg == "--namespace" )
	{
	  if (next_arg == "")
	    {
	      std::cerr << "no namespace specified" << std::endl;
	      exit(1); 
	    }
	  else
	    {
	      xsl = next_arg;
	    }
	}
      ++i;
    }
  CppUnit::TextUi::TestRunner runner;
  if ( ns.empty() )
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  else
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry(ns).makeTest());
  CppUnit::Outputter* outputter = 0;
  std::ostream* stream = target ? &std::cerr : &std::cout;
  switch ( format )
    {
    case TEXT_OUT :
      outputter = new CppUnit::TextOutputter(&runner.result(),*stream);
      break;
    case XML_OUT :
      std::cout << "XML_OUT" << std::endl;
      outputter = new CppUnit::XmlOutputter(&runner.result(),
					    ofs, "shift_jis");
      static_cast<CppUnit::XmlOutputter*>(outputter)->setStyleSheet(xsl);
      break;
    case COMPILER_OUT :
      outputter = new CppUnit::CompilerOutputter(&runner.result(),*stream);
      break;
    }
  runner.setOutputter(outputter);
  runner.run();
  return 0; // runner.run() ? 0 : 1;
}
#endif // MAIN
#endif // CorbaObjectManager_cpp

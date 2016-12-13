// -*- C++ -*-
/*!
 * @file   InPortCorbaCdrProviderTests.cpp
 * @brief  InPortCorbaCdrProvider test class
 * @date   $Date: 2008/02/21 07:36:39 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: InPortCorbaCdrProviderTests.cpp 1007 2008-10-31 01:35:29Z fsi-katami $
 *
 */

/*
 * $Log: InPortCorbaCdrProviderTests.cpp,v $
 *
 *
 */

#ifndef InPortCorbaCdrProvider_cpp
#define InPortCorbaCdrProvider_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/RTC.h>
#include <rtm/Typename.h>
#include <rtm/InPortCorbaCdrProvider.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/PortAdmin.h>
#include <rtm/CORBA_SeqUtil.h>

/*!
 * @class InPortCorbaCdrProviderTests class
 * @brief InPortCorbaCdrProvider test
 */
namespace InPortCorbaCdrProvider
{
  /*!
   * 
   * 
   */
  class InPortCorbaCdrProviderMock
    : public RTC::InPortCorbaCdrProvider
  {
  public:
      /*!
       * 
       * 
       */
      InPortCorbaCdrProviderMock(void)
      {
      }
      /*!
       * 
       * 
       */
      virtual ~InPortCorbaCdrProviderMock()
      {
      }
      /*!
       *  確認用 
       * 
       */
      SDOPackage::NVList get_m_properties()
      {
          return m_properties;
      }
  };
  class InPortCorbaCdrProviderTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(InPortCorbaCdrProviderTests);

    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;

  public:
	
    /*!
     * @brief Constructor
     */
    InPortCorbaCdrProviderTests()
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
    ~InPortCorbaCdrProviderTests()
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
     * @brief 
     * 
     */
    void test_case0()
    {
        //
        //
        //
        InPortCorbaCdrProviderMock provider;
        CORBA::Long index;

        //IOR をプロぺティに追加することを確認
        index = NVUtil::find_index(provider.get_m_properties(),"dataport.corba_cdr.inport_ior");
        CPPUNIT_ASSERT(0<=index);

        //ref をプロぺティに追加することを確認
        index = NVUtil::find_index(provider.get_m_properties(),"dataport.corba_cdr.inport_ref");
        CPPUNIT_ASSERT(0<=index);

          // 未実装関数のため省略
          //provideri.init();

        ::OpenRTM::PortStatus ret;
        ::OpenRTM::CdrData data;
        CORBA_SeqUtil::push_back(data,0);

        ret = provider.put(data);      
        CPPUNIT_ASSERT_EQUAL(::OpenRTM::PORT_ERROR,ret);

        RTC::CdrBufferBase* buffer;
        buffer = RTC::CdrBufferFactory::instance().createObject("ring_buffer");
        provider.setBuffer(buffer);

        ret = provider.put(data);      
        CPPUNIT_ASSERT_EQUAL(::OpenRTM::PORT_OK,ret);
        CORBA_SeqUtil::push_back(data,1);
        CORBA_SeqUtil::push_back(data,2);
        CORBA_SeqUtil::push_back(data,3);
        CORBA_SeqUtil::push_back(data,4);
        CORBA_SeqUtil::push_back(data,5);
        CORBA_SeqUtil::push_back(data,6);
        ret = provider.put(data);      
        CPPUNIT_ASSERT_EQUAL(::OpenRTM::PORT_OK,ret);
        CORBA_SeqUtil::push_back(data,7);

        ret = provider.put(data);      
        CPPUNIT_ASSERT_EQUAL(::OpenRTM::PORT_OK,ret);
        ret = provider.put(data);      
        CPPUNIT_ASSERT_EQUAL(::OpenRTM::PORT_OK,ret);
        ret = provider.put(data);      
        CPPUNIT_ASSERT_EQUAL(::OpenRTM::PORT_OK,ret);
        ret = provider.put(data);      
        CPPUNIT_ASSERT_EQUAL(::OpenRTM::PORT_OK,ret);
        ret = provider.put(data);      
        CPPUNIT_ASSERT_EQUAL(::OpenRTM::PORT_OK,ret);
        ret = provider.put(data);      
        CPPUNIT_ASSERT_EQUAL(::OpenRTM::PORT_OK,ret);
        ret = provider.put(data);      
        CPPUNIT_ASSERT_EQUAL(::OpenRTM::BUFFER_FULL,ret);
    }
    
  };
}; // namespace OutPortBase

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(InPortCorbaCdrProvider::InPortCorbaCdrProviderTests);

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
#endif // OutPortBase_cpp

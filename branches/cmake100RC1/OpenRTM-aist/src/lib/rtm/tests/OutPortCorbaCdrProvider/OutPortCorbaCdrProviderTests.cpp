// -*- C++ -*-
/*!
 * @file   OutPortCorbaCdrProviderTests.cpp
 * @brief  OutPortCorbaCdrProvider test class
 * @date   $Date: 2008/02/21 07:36:39 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: OutPortCorbaCdrProviderTests.cpp 1007 2008-10-31 01:35:29Z fsi-katami $
 *
 */

/*
 * $Log: OutPortCorbaCdrProviderTests.cpp,v $
 *
 *
 */

#ifndef OutPortCorbaCdrProvider_cpp
#define OutPortCorbaCdrProvider_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/DataPortSkel.h>
#include <rtm/RTC.h>
#include <rtm/Typename.h>
#include <rtm/OutPortCorbaCdrProvider.h>
#include <rtm/OutPortCorbaCdrConsumer.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/PortAdmin.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <rtm/DataPortStatus.h>

/*!
 * @class OutPortCorbaCdrProviderTests class
 * @brief OutPortCorbaCdrProvider test
 */
namespace OutPortCorbaCdrProvider
{
  /*!
   * 
   * 
   */
  class OutPortCorbaCdrProviderMock
    : public RTC::OutPortCorbaCdrProvider
  {
  public:
      /*!
       * 
       * 
       */
      OutPortCorbaCdrProviderMock(void)
      {
      }
      /*!
       * 
       * 
       */
      virtual ~OutPortCorbaCdrProviderMock()
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
  class OutPortCorbaCdrProviderTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OutPortCorbaCdrProviderTests);

    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;

  public:
	
    /*!
     * @brief Constructor
     */
    OutPortCorbaCdrProviderTests()
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
    ~OutPortCorbaCdrProviderTests()
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
        OutPortCorbaCdrProviderMock provider;

        int index;
        //IOR をプロぺティに追加することを確認
        index = NVUtil::find_index(provider.get_m_properties(),
                                   "dataport.corba_cdr.outport_ior");
        CPPUNIT_ASSERT(0<=index);

        //ref をプロぺティに追加することを確認
        index = NVUtil::find_index(provider.get_m_properties(),
                                   "dataport.corba_cdr.outport_ref");
        CPPUNIT_ASSERT(0<=index);


        //init() は未実装関数のため省略
        //provider.init();

         
        RTC::CdrBufferBase* buffer;
        buffer = RTC::CdrBufferFactory::instance().createObject("ring_buffer");

        ::OpenRTM::PortStatus retcode;

        ::OpenRTM::CdrData_var cdr_data;

        // buffer がない状態でコール(unkown error)
        retcode = provider.get(cdr_data.out());
        CPPUNIT_ASSERT_EQUAL((::OpenRTM::PortStatus)5, retcode);
        
        provider.setBuffer(buffer);

        //データなしの状態でコール(empty)
        retcode = provider.get(cdr_data);
        CPPUNIT_ASSERT_EQUAL((::OpenRTM::PortStatus)3, retcode);

        int testdata[8] = { 12,34,56,78,90,23,45 };
        ::OpenRTM::CdrData cdr_d;
        for(int ic(0);ic<8;++ic)
        {
            CORBA_SeqUtil::push_back(cdr_d,testdata[ic]);
        }
        cdrMemoryStream cdr;
        cdr.put_octet_array(&cdr_d[0], cdr_d.length());
        buffer->write(cdr);


        retcode = provider.get(cdr_data);
        CPPUNIT_ASSERT_EQUAL((::OpenRTM::PortStatus)0, retcode);


        SDOPackage::NVList list = provider.get_m_properties();
        index = NVUtil::find_index(list,
                                   "dataport.corba_cdr.outport_ior");

        const char* ior;
        if (list[index].value >>= ior)
        {
            CORBA::Object_ptr var = m_pORB->string_to_object(ior);
            PortableServer::Servant ser = m_pPOA->reference_to_servant(var);
	    m_pPOA->deactivate_object(*m_pPOA->servant_to_id(ser));
        }
            
    }
    
  };
}; // namespace OutPortBase

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OutPortCorbaCdrProvider::OutPortCorbaCdrProviderTests);

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

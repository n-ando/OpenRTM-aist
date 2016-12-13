// -*- C++ -*-
/*!
 * @file   InPortCorbaCdrConsumerTests.cpp
 * @brief  InPortCorbaCdrConsumer test class
 * @date   $Date: 2008/02/21 07:36:39 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id: InPortCorbaCdrConsumerTests.cpp 1007 2008-10-31 01:35:29Z fsi-katami $
 *
 */

/*
 * $Log: InPortCorbaCdrConsumerTests.cpp,v $
 *
 *
 */

#ifndef InPortCorbaCdrConsumer_cpp
#define InPortCorbaCdrConsumer_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/DataPortSkel.h>
#include <rtm/RTC.h>
#include <rtm/Typename.h>
#include <rtm/InPortCorbaCdrConsumer.h>
#include <rtm/InPortCorbaCdrProvider.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/PortAdmin.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>

/*!
 * @class InPortCorbaCdrConsumerTests class
 * @brief InPortCorbaCdrConsumer test
 */
namespace InPortCorbaCdrConsumer
{
  /*!
   * 
   * 
   */
  class InPortCorbaCdrConsumerMock
    : public RTC::InPortCorbaCdrConsumer
  {
  public:
      /*!
       * 
       * 
       */
      InPortCorbaCdrConsumerMock(void)
      {
      }
      /*!
       * 
       * 
       */
      virtual ~InPortCorbaCdrConsumerMock()
      {
      }
      /*!
       *  確認用 
       * 
       */
      CORBA::Object_var get_m_objre()
      {
          return m_objref;
      }
  };
  class InPortCorbaCdrConsumerTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(InPortCorbaCdrConsumerTests);

    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
	
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;

  public:
	
    /*!
     * @brief Constructor
     */
    InPortCorbaCdrConsumerTests()
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
    ~InPortCorbaCdrConsumerTests()
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
        InPortCorbaCdrConsumerMock consumer;

        RTC::ConnectorProfile prof;
        bool ret;
        int testdata[8] = { 12,34,56,78,90,23,45, };

        ret = consumer.subscribeInterface(prof.properties);
        //ior を設定していないのでfalseとなることを確認する。
        CPPUNIT_ASSERT_EQUAL(false, ret);

        RTC::InPortCorbaCdrProvider provider;

        CORBA_SeqUtil::push_back(prof.properties,
                                 NVUtil::newNV("dataport.interface_type",
                                               "corba_cdr"));
        provider.publishInterface(prof.properties);

        ret = consumer.subscribeInterface(prof.properties);
        CPPUNIT_ASSERT_EQUAL(true, ret);

        cdrMemoryStream indata;
        indata.setByteSwapFlag(true);
        ::RTC::DataPortStatus::Enum retcode;

        ::OpenRTM::CdrData cdr_data;
        for(int ic(0);ic<8;++ic)
        {
            CORBA_SeqUtil::push_back(cdr_data,testdata[ic]);
        }
        indata.put_octet_array(&cdr_data[0], cdr_data.length());
         

        //provider 側の buffer がない状態でコール(error)
        retcode = consumer.put(indata);
        CPPUNIT_ASSERT_EQUAL((::RTC::DataPortStatus::Enum)1, retcode);
std::cout<<"1"<<std::endl;

        RTC::CdrBufferBase* buffer;
        buffer = RTC::CdrBufferFactory::instance().createObject("ring_buffer");
        provider.setBuffer(buffer);

std::cout<<"2"<<std::endl;
        for(int ic(0);ic<8;++ic)
        {
            retcode = consumer.put(indata);
            CPPUNIT_ASSERT_EQUAL((::RTC::DataPortStatus::Enum)0, retcode);
         }

std::cout<<"3"<<std::endl;
        //full の状態でコール(full)
        retcode = consumer.put(indata);
        CPPUNIT_ASSERT_EQUAL((::RTC::DataPortStatus::Enum)2, retcode);


        for(int icc(0);icc<8;++icc)
        {
            cdrMemoryStream cdr;
            buffer->read(cdr);

            CORBA::ULong inlen = cdr.bufSize();
            CPPUNIT_ASSERT_EQUAL(8,(int)inlen);

            CORBA::Octet oct[8];
            cdr.get_octet_array (oct, 8);
            for(int ic(0);ic<(int)inlen;++ic)
            {
                CPPUNIT_ASSERT_EQUAL(testdata[ic],(int)oct[ic]);
            }
        }

std::cout<<"4"<<std::endl;
        CPPUNIT_ASSERT(!CORBA::is_nil(consumer.get_m_objre()));
        consumer.unsubscribeInterface(prof.properties);
        CPPUNIT_ASSERT(CORBA::is_nil(consumer.get_m_objre()));

        int index;
        index = NVUtil::find_index(prof.properties,
                                   "dataport.corba_cdr.inport_ior");

         const char* ior;
         if (prof.properties[index].value >>= ior)
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
CPPUNIT_TEST_SUITE_REGISTRATION(InPortCorbaCdrConsumer::InPortCorbaCdrConsumerTests);

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

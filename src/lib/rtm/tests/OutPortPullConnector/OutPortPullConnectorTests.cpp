// -*- C++ -*-
/*!
 * @file   OutPortPullConnectorTests.cpp
 * @brief  OutPortPullConnector test class
 * @date   $Date: 2008/03/13 13:12:25 $
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
 * $Id: InPortTests.cpp 817 2008-08-06 02:54:26Z n-ando $
 *
 */


#ifndef OutPortPullConnector_cpp
#define OutPortPullConnector_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/Properties.h>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/DataPortSkel.h>
#include <rtm/Typename.h>
#include <rtm/OutPortPullConnector.h>
#include <rtm/CdrBufferBase.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/NVUtil.h>
#include <rtm/ConnectorBase.h>
#include <rtm/DataPortStatus.h>
#include <rtm/InPortBase.h>
#include <rtm/InPortConsumer.h>
#include <rtm/OutPortBase.h>
#include <rtm/PortAdmin.h>
#include <rtm/CorbaConsumer.h>
#include <rtm/PublisherBase.h>

/*!
 * @class OutPortPullConnectorTests class
 * @brief OutPortPullConnector test
 */
namespace OutPortPullConnector
{
  /*!
   * 
   * 
   *
   */
  class Logger
  {
  public:
    void log(const std::string& msg)
    {
      m_log.push_back(msg);
    }

    int countLog(const std::string& msg)
    {
      int count = 0;
      for (int i = 0; i < (int) m_log.size(); ++i)
        {
          if (m_log[i] == msg) ++count;
        }
     return count;
    }
		
  private:
    std::vector<std::string> m_log;
  };
  /*!
   * 
   * 
   *
   */
  template <class DataType>
  class RingBufferMock
    : public RTC::BufferBase<DataType>
  {
  public:
    BUFFERSTATUS_ENUM
      RingBufferMock(long int length = 8)
      {
          m_logger = NULL;
          logger.log("RingBufferMock::Constructor");
          m_read_return_value = BUFFER_OK;
      }
      virtual ~RingBufferMock(void)
      {
      }
  
    
      /*!
       *
       *
       */
      void set_read_return_value(::RTC::BufferStatus::Enum value)
      {
          m_read_return_value = value;
      }
      /*!
       *
       *
       */
      virtual void init(const coil::Properties& prop)
      {
      }
      /*!
       *
       *
       */
      virtual size_t length(void) const
      {
          return 0;
      }
      /*!
       *
       *
       */
      virtual ReturnCode length(size_t n)
      {
          return ::RTC::BufferStatus::BUFFER_OK; //BUFFER_OK;
      }
      /*!
       *
       *
       */
      virtual ReturnCode reset()
      {
          return ::RTC::BufferStatus::BUFFER_OK; //BUFFER_OK;
      }
      /*!
       *
       *
       */
      virtual DataType* wptr(long int n = 0)
      {
          return &m_data;
      }
      /*!
       *
       *
       */
      virtual ReturnCode advanceWptr(long int n = 1)
      {
          return ::RTC::BufferStatus::BUFFER_OK; //BUFFER_OK;
      }
      /*!
       *
       *
       */
      virtual ReturnCode put(const DataType& value)
      {
          return ::RTC::BufferStatus::BUFFER_OK; //BUFFER_OK;
      }
      /*!
       *
       *
       */
      virtual ReturnCode write(const DataType& value,
                               long int sec = -1, long int nsec = -1)
      {
          return ::RTC::BufferStatus::BUFFER_OK; //BUFFER_OK;
      }
      /*!
       *
       *
       */
      virtual size_t writable() const
      {
          return 0;
      }
      /*!
       *
       *
       */
      virtual bool full(void) const
      {
          return true;
      }
      /*!
       *
       *
       */
      virtual DataType* rptr(long int n = 0)
      {
          return &m_data;
      }
      /*!
       *
       *
       */
      virtual ReturnCode advanceRptr(long int n = 1)
      {
          return ::RTC::BufferStatus::BUFFER_OK; //BUFFER_OK;
      }
      /*!
       *
       *
       */
      virtual ReturnCode get(DataType& value)
      {
          return ::RTC::BufferStatus::BUFFER_OK; //BUFFER_OK;
      }
      /*!
       *
       *
       */
      virtual DataType&  get()
      {
          return m_data;
      }
      /*!
       *
       *
       */
      virtual ReturnCode read(DataType& value,
                              long int sec = -1, long int nsec = -1)
      {
          if (m_logger != NULL)
          {
              m_logger->log("RingBufferMock::read");
          }
          logger.log("RingBufferMock::read");
          return m_read_return_value; //BUFFER_OK;
      }
      /*!
       *
       *
       */
      virtual size_t readable() const
      {
          return 0;
      }
      /*!
       *
       *
       */
      virtual bool empty(void) const
      {
          return true;
      }
      /*!
       *
       *
       */
      void setLogger(Logger* logger)
      {
          m_logger = logger;
      }

      static Logger logger;
  private:
      DataType m_data;
      std::vector<DataType> m_buffer;
      Logger* m_logger;
      ::RTC::BufferStatus::Enum m_read_return_value;
  };
  template <class DataType>
  Logger RingBufferMock<DataType>::logger;
  typedef RingBufferMock<cdrMemoryStream> CdrRingBufferMock;
  /*!
   * 
   * 
   *
   */
  class OutPortCorbaCdrProviderMock
    : public RTC::OutPortProvider,
      public virtual ::POA_OpenRTM::OutPortCdr,
      public virtual PortableServer::RefCountServantBase
  {

  public:
      OutPortCorbaCdrProviderMock(void)
       {
          m_logger = NULL;
       }
      virtual ~OutPortCorbaCdrProviderMock(void)
      {
      }
      /*!
       *
       *
       */
      void init(coil::Properties& prop)
      {
          if (m_logger != NULL)
          {
              m_logger->log("OutPortCorbaCdrProviderMock::init");
          }
      }
      /*!
       *
       *
       */
      virtual ::OpenRTM::PortStatus get(::OpenRTM::CdrData_out data)
      {
          return ::OpenRTM::PORT_OK;
      }
      /*!
       *
       *
       */
      RTC::InPortConsumer::ReturnCode put(const cdrMemoryStream& data)
      {
          return PORT_OK;
      }
      /*!
       *
       *
       */
      void publishInterfaceProfile(SDOPackage::NVList& properties)
      {
          return;
      }

      /*!
       *
       *
       */
      bool subscribeInterface(const SDOPackage::NVList& properties)
      {
    
          return true;;
      }
  
      /*!
       *
       *
       */
      void unsubscribeInterface(const SDOPackage::NVList& properties)
      {
      }
  
  
      /*!
       *
       *
       */
      void setLogger(Logger* logger)
      {
          m_logger = logger;
      }
  private:
    Logger* m_logger;

  };

  class OutPortPullConnectorTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OutPortPullConnectorTests);

    CPPUNIT_TEST(test_OutPortPullConnector);
    CPPUNIT_TEST(test_write);
    CPPUNIT_TEST(test_disconnect_getBuffer);
//    CPPUNIT_TEST(test_activate_deactivate);

    CPPUNIT_TEST_SUITE_END();
		
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;


  public:
	
    /*!
     * @brief Constructor
     */
    OutPortPullConnectorTests()
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
    ~OutPortPullConnectorTests()
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
     * @brief Constructorのテスト
     * 
     */
    void test_OutPortPullConnector()
    {
        CdrRingBufferMock* pbuffer = new CdrRingBufferMock();

        RTC::ConnectorProfile prof;
        CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.interface_type",
					     "corba_cdr"));
        CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.dataflow_type",
					     "push"));
        CORBA_SeqUtil::push_back(prof.properties,
	  		       NVUtil::newNV("dataport.subscription_type",
					     "new"));
        // prop: [port.outport].
        coil::Properties prop;
        {
            coil::Properties conn_prop;
            NVUtil::copyToProperties(conn_prop, prof.properties);
            prop << conn_prop.getNode("dataport"); // marge ConnectorProfile
        }
        OutPortCorbaCdrProviderMock*provider = new OutPortCorbaCdrProviderMock();
        Logger logger;
        provider->setLogger(&logger);
        RTC::ConnectorBase::Profile profile_new(prof.name,
                                   prof.connector_id,
                                   CORBA_SeqUtil::refToVstring(prof.ports),
                                   prop); 
        RTC::OutPortConnector* connector(0);
        connector = new RTC::OutPortPullConnector(profile_new, provider, pbuffer);

        //consumerはデストラクタでdeleteされる。
        delete connector;

        //subscription_type が未設定の場合は
        //Flush が起動することを確認する。
        CORBA_SeqUtil::push_back(prof.properties,
	  		       NVUtil::newNV("dataport.subscription_type",
					     ""));
        // prop: [port.outport].
        {
            coil::Properties conn_prop;
            NVUtil::copyToProperties(conn_prop, prof.properties);
            prop << conn_prop.getNode("dataport"); // marge ConnectorProfile
        }
        RTC::ConnectorBase::Profile profile_flush(prof.name,
                                   prof.connector_id,
                                   CORBA_SeqUtil::refToVstring(prof.ports),
                                   prop); 
        connector = new RTC::OutPortPullConnector(profile_flush, provider);

        //consumerはデストラクタでdeleteされる。
        delete connector;
        
/*
        //provider を与えない場合は例外を投げることを確認する。
        RTC::OutPortConnector* connector_err(0);
        try {
            RTC::ConnectorProfile prof_err;
            // prop: [port.outport].
            {
                coil::Properties conn_prop;
                NVUtil::copyToProperties(conn_prop, prof_err.properties);
                prop << conn_prop.getNode("dataport"); // marge ConnectorProfile
            }
            RTC::ConnectorBase::Profile profile_err(prof_err.name,
                                    prof_err.connector_id,
                                    CORBA_SeqUtil::refToVstring(prof_err.ports),
                                    prop); 
            connector_err = new RTC::OutPortPullConnector(profile_err, NULL);
            CPPUNIT_FAIL("The exception was not thrown. ");
        }
        catch(std::bad_alloc& e)
        {
        }
        catch(...)
        {
            CPPUNIT_FAIL("The exception not intended was thrown .");
        }
        delete connector_err;
*/
    }
    /*!
     * @brief writeのテスト
     * 
     */
    void test_write()
    {
        CdrRingBufferMock* pbuffer = new CdrRingBufferMock();
        RTC::ConnectorProfile prof;
        CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.interface_type",
					     "corba_cdr"));
        CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.dataflow_type",
					     "push"));
        CORBA_SeqUtil::push_back(prof.properties,
	  		       NVUtil::newNV("dataport.subscription_type",
					     "new"));
        // prop: [port.outport].
        coil::Properties prop;
        {
            coil::Properties conn_prop;
            NVUtil::copyToProperties(conn_prop, prof.properties);
            prop << conn_prop.getNode("dataport"); // marge ConnectorProfile
        }
        OutPortCorbaCdrProviderMock*provider = new OutPortCorbaCdrProviderMock();
        Logger logger;
        provider->setLogger(&logger);
        RTC::ConnectorBase::Profile profile_new(prof.name,
                                   prof.connector_id,
                                   CORBA_SeqUtil::refToVstring(prof.ports),
                                   prop); 
        RTC::OutPortConnector* connector(0);
        connector = new RTC::OutPortPullConnector(profile_new, provider, pbuffer);
        cdrMemoryStream cdr;
        12345 >>= cdr;
        connector->write(cdr);

        delete connector;

    }
    /*!
     * @brief disconnectのテスト
     * 
     */
    void test_disconnect_getBuffer()
    {
        CdrRingBufferMock* pbuffer = new CdrRingBufferMock();
        RTC::ConnectorProfile prof;
        CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.interface_type",
					     "corba_cdr"));
        CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.dataflow_type",
					     "push"));
        CORBA_SeqUtil::push_back(prof.properties,
	  		       NVUtil::newNV("dataport.subscription_type",
					     "new"));
        // prop: [port.outport].
        coil::Properties prop;
        {
            coil::Properties conn_prop;
            NVUtil::copyToProperties(conn_prop, prof.properties);
            prop << conn_prop.getNode("dataport"); // marge ConnectorProfile
        }
        OutPortCorbaCdrProviderMock*provider = new OutPortCorbaCdrProviderMock();
        Logger logger;
        provider->setLogger(&logger);
        RTC::ConnectorBase::Profile profile_new(prof.name,
                                   prof.connector_id,
                                   CORBA_SeqUtil::refToVstring(prof.ports),
                                   prop); 
        RTC::OutPortConnector* connector(0);
        connector = new RTC::OutPortPullConnector(profile_new, provider, pbuffer);
        CPPUNIT_ASSERT(pbuffer==connector->getBuffer());
        connector->disconnect();
//        CPPUNIT_ASSERT(!connector->getBuffer());

    }
    /*!
     * @brief activate のテスト
     * 
     */
    void test_activate_deactivate()
    {
        CdrRingBufferMock* pbuffer = new CdrRingBufferMock();
        RTC::ConnectorProfile prof;
        CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.interface_type",
					     "corba_cdr"));
        CORBA_SeqUtil::push_back(prof.properties,
			       NVUtil::newNV("dataport.dataflow_type",
					     "push"));
        CORBA_SeqUtil::push_back(prof.properties,
	  		       NVUtil::newNV("dataport.subscription_type",
					     "new"));
        // prop: [port.outport].
        coil::Properties prop;
        {
            coil::Properties conn_prop;
            NVUtil::copyToProperties(conn_prop, prof.properties);
            prop << conn_prop.getNode("dataport"); // marge ConnectorProfile
        }
        OutPortCorbaCdrProviderMock*provider = new OutPortCorbaCdrProviderMock();
        Logger logger;
        provider->setLogger(&logger);
        RTC::ConnectorBase::Profile profile_new(prof.name,
                                   prof.connector_id,
                                   CORBA_SeqUtil::refToVstring(prof.ports),
                                   prop); 
        RTC::OutPortConnector* connector(0);
        connector = new RTC::OutPortPullConnector(profile_new, provider, pbuffer);
        connector->activate();

        connector = new RTC::OutPortPullConnector(profile_new, provider, pbuffer);
        delete connector;
    }
  };
}; // namespace OutPortPullConnector

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OutPortPullConnector::OutPortPullConnectorTests);

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
#endif // InPort_cpp

// -*- C++ -*-
/*!
 * @file   OutPortPushConnectorTests.cpp
 * @brief  OutPortPushConnector test class
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


#ifndef OutPortPushConnector_cpp
#define OutPortPushConnector_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/Properties.h>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/DataPortSkel.h>
#include <rtm/Typename.h>
#include <rtm/OutPortPushConnector.h>
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
 * @class OutPortPushConnectorTests class
 * @brief OutPortPushConnector test
 */
namespace OutPortPushConnector
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
  class InPortCorbaCdrConsumerMock
    : public RTC::InPortConsumer,
      public RTC::CorbaConsumer< ::OpenRTM::InPortCdr >
  {

  public:
      InPortCorbaCdrConsumerMock(void)
       {
          m_logger = NULL;
       }
      virtual ~InPortCorbaCdrConsumerMock(void)
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
              m_logger->log("InPortCorbaCdrConsumerMock::init");
          }
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
  /*!
   * 
   * 
   *
   */
  class PublisherFlushMock
    : public RTC::PublisherBase
  {
  public:
      PublisherFlushMock()
      {
          m_logger = NULL;
      }
      ~PublisherFlushMock()
      {
      }
      /*!
       *
       *
       */
      RTC::PublisherBase::ReturnCode write(const cdrMemoryStream& data,
                                           unsigned long sec,
                                           unsigned long usec)
      {
          return PORT_OK;
      }
      /*!
       *
       *
       */
      bool isActive()
      {
          return true;
      }

      /*!
       *
       *
       */
      RTC::PublisherBase::ReturnCode activate()
      {
          return PORT_OK;
      }

      /*!
       *
       *
       */
      RTC::PublisherBase::ReturnCode deactivate()
      {
          return PORT_OK;
      }
      /*!
       *
       *
       */
      RTC::PublisherBase::ReturnCode init(coil::Properties& prop)
      {
          return PORT_OK;
      }
      /*!
       *
       *
       */
      RTC::PublisherBase::ReturnCode setConsumer(RTC::InPortConsumer* consumer)
      {
          if (m_logger != NULL)
          {
              m_logger->log("setConsumer");
          }
          logger.log("setConsumer");
          return PORT_OK;
      }

      /*!
       *
       *
       */
      RTC::PublisherBase::ReturnCode setBuffer(RTC::CdrBufferBase* buffer)
      {
          if (m_logger != NULL)
          {
              m_logger->log("setBuffer");
              if(buffer == NULL)
              {
                  m_logger->log("buffer NG");
              }
              else
              {
                  m_logger->log("buffer OK");
              }
          }
          logger.log("setBuffer");
          if(buffer == NULL)
          {
              logger.log("buffer NG");
          }
          else
          {
              logger.log("buffer OK");
          }
          return PORT_OK;
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
    Logger* m_logger;
  };
  Logger PublisherFlushMock::logger;
  /*!
   * 
   * 
   *
   */
  class PublisherNewMock
    : public RTC::PublisherBase
  {
  public:
      PublisherNewMock()
      {
          m_logger = NULL;
      }
      ~PublisherNewMock()
      {
      }
      /*!
       *
       *
       */
      RTC::PublisherBase::ReturnCode write(const cdrMemoryStream& data,
                                           unsigned long sec,
                                           unsigned long usec)
      {
          return PORT_OK;
      }
      /*!
       *
       *
       */
      bool isActive()
      {
          return true;
      }

      /*!
       *
       *
       */
      RTC::PublisherBase::ReturnCode activate()
      {
          return PORT_OK;
      }

      /*!
       *
       *
       */
      RTC::PublisherBase::ReturnCode deactivate()
      {
          return PORT_OK;
      }

      /*!
       *
       *
       */
      RTC::PublisherBase::ReturnCode init(coil::Properties& prop)
      {
          return PORT_OK;
      }

      /*!
       *
       *
       */
      RTC::PublisherBase::ReturnCode setConsumer(RTC::InPortConsumer* consumer)
      {
          if (m_logger != NULL)
          {
              m_logger->log("setConsumer");
          }
          logger.log("setConsumer");
          return PORT_OK;
      }

      /*!
       *
       *
       */
      PublisherBase::ReturnCode setBuffer(RTC::CdrBufferBase* buffer)
      {
          if (m_logger != NULL)
          {
              m_logger->log("setBuffer");
              if(buffer == NULL)
              {
                  m_logger->log("buffer NG");
              }
              else
              {
                  m_logger->log("buffer OK");
              }
          }
          logger.log("setBuffer");
          if(buffer == NULL)
          {
              logger.log("buffer NG");
          }
          else
          {
              logger.log("buffer OK");
          }
          return PORT_OK;
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
    Logger* m_logger;
  };
  Logger PublisherNewMock::logger;

  class OutPortPushConnectorTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(OutPortPushConnectorTests);
    CPPUNIT_TEST(test_OutPortPushConnector);
    CPPUNIT_TEST_SUITE_END();
		
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;


  public:
	
    /*!
     * @brief Constructor
     */
    OutPortPushConnectorTests()
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
    ~OutPortPushConnectorTests()
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
    void test_OutPortPushConnector()
    {
        ::RTC::PublisherFactory::
        instance().addFactory("flush",
                              ::coil::Creator< ::RTC::PublisherBase,
                                               PublisherFlushMock>,
                              ::coil::Destructor< ::RTC::PublisherBase,
                                                  PublisherFlushMock>);
        ::RTC::PublisherFactory::
        instance().addFactory("new",
                              ::coil::Creator< ::RTC::PublisherBase,
                                               PublisherNewMock>,
                              ::coil::Destructor< ::RTC::PublisherBase,
                                                  PublisherNewMock>);
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
        InPortCorbaCdrConsumerMock*consumer = new InPortCorbaCdrConsumerMock();
        Logger logger;
        consumer->setLogger(&logger);
        RTC::ConnectorBase::Profile profile_new(prof.name,
                                   prof.connector_id,
                                   CORBA_SeqUtil::refToVstring(prof.ports),
                                   prop); 
        RTC::OutPortConnector* connector(0);
        CPPUNIT_ASSERT_EQUAL(0, 
                           logger.countLog("InPortCorbaCdrConsumerMock::init"));
        CPPUNIT_ASSERT_EQUAL(0, 
                             PublisherNewMock::logger.countLog("setBuffer"));
        CPPUNIT_ASSERT_EQUAL(0, 
                             PublisherNewMock::logger.countLog("buffer OK"));
        CPPUNIT_ASSERT_EQUAL(0, 
                             PublisherNewMock::logger.countLog("setConsumer"));
        connector = new RTC::OutPortPushConnector(profile_new, consumer);
        CPPUNIT_ASSERT_EQUAL(1, 
                           logger.countLog("InPortCorbaCdrConsumerMock::init"));
        CPPUNIT_ASSERT_EQUAL(1, 
                             PublisherNewMock::logger.countLog("setBuffer"));
        CPPUNIT_ASSERT_EQUAL(1, 
                             PublisherNewMock::logger.countLog("buffer OK"));
        CPPUNIT_ASSERT_EQUAL(1, 
                             PublisherNewMock::logger.countLog("setConsumer"));


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
        CPPUNIT_ASSERT_EQUAL(1, 
                           logger.countLog("InPortCorbaCdrConsumerMock::init"));
        CPPUNIT_ASSERT_EQUAL(0, 
                             PublisherFlushMock::logger.countLog("setBuffer"));
        CPPUNIT_ASSERT_EQUAL(0, 
                             PublisherFlushMock::logger.countLog("buffer OK"));
        CPPUNIT_ASSERT_EQUAL(0, 
                             PublisherFlushMock::logger.countLog("setConsumer"));
        connector = new RTC::OutPortPushConnector(profile_flush, consumer);
        CPPUNIT_ASSERT_EQUAL(2, 
                           logger.countLog("InPortCorbaCdrConsumerMock::init"));
        CPPUNIT_ASSERT_EQUAL(1, 
                             PublisherFlushMock::logger.countLog("setBuffer"));
        CPPUNIT_ASSERT_EQUAL(1, 
                             PublisherFlushMock::logger.countLog("buffer OK"));
        CPPUNIT_ASSERT_EQUAL(1, 
                             PublisherFlushMock::logger.countLog("setConsumer"));

        //consumerはデストラクタでdeleteされる。
        delete connector;
        
    }
		
  };
}; // namespace InPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(OutPortPushConnector::OutPortPushConnectorTests);

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

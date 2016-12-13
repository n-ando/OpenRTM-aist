// -*- C++ -*-
/*!
 * @file   DataOutPortTests.cpp
 * @brief  DataOutPort test class
 * @date   $Date: 2008/03/04 08:43:24 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$
 *
 */

/*
 * $Log: DataOutPortTests.cpp,v $
 * Revision 1.2  2008/03/04 08:43:24  arafune
 * Remove some tests and added some new tests.
 *
 * Revision 1.1  2007/12/20 07:50:18  arafune
 * *** empty log message ***
 *
 * Revision 1.2  2007/01/12 14:49:56  n-ando
 * The constructor signature of DataOutPort was changed.
 *
 * Revision 1.1  2006/11/27 08:31:03  n-ando
 * TestSuites are devided into each directory.
 *
 *
 */

#ifndef DataOutPort_cpp
#define DataOutPort_cpp

#include <iostream>

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <idl/BasicDataTypeSkel.h>
#include <idl/RTCSkel.h>
#include <coil/stringutil.h>
#include <rtm/OutPort.h>
#include <rtm/DataOutPort.h>

/*!
 * @class DataOutPortTests class
 * @brief DataOutPort test
 */
namespace DataOutPort
{
  template <class DataType, template <class DataType> class Buffer>
  class DataOutPortMock
    : public RTC::DataOutPort
  {
  public:
    DataOutPortMock(
		    const char* name,
		    RTC::OutPort<DataType, Buffer>& outport,
		    coil::Properties& prop)
      : RTC::DataOutPort(name, outport, prop)
    {
    }
		
    // public override for test
    virtual RTC::ReturnCode_t publishInterfaces_public(
						       RTC::ConnectorProfile& connector_profile)
    {
      return RTC::DataOutPort::publishInterfaces(connector_profile);
    }
		
    // public override for test
    virtual RTC::ReturnCode_t subscribeInterfaces_public(
							 const RTC::ConnectorProfile& connector_profile)
    {
      return RTC::DataOutPort::subscribeInterfaces(connector_profile);
    }
		
    // public override for test
    virtual void unsubscribeInterfaces_public(
					      const RTC::ConnectorProfile& connector_profile)
    {
      RTC::DataOutPort::unsubscribeInterfaces(connector_profile);
    }
		
  };
	
  class InPortAnyMock
    : public virtual POA_RTC::InPortAny,
      public virtual PortableServer::RefCountServantBase
  {
  public:
    InPortAnyMock() : m_calledCount(0) {}
    virtual void put(const CORBA::Any& data) { ++m_calledCount; }
    int getCalledCount() const { return m_calledCount; }
		
  private:
    int m_calledCount;
  };
	
  class DataOutPortTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(DataOutPortTests);
    CPPUNIT_TEST(test_get_port_profile);
    CPPUNIT_TEST(test_publishInterfaces_CORBA_Any);
    //		CPPUNIT_TEST(test_publishInterfaces_TCP_Any); // OutPortTcpProvider実装途中につき、テストをコメントアウト
    CPPUNIT_TEST(test_subscribeInterfaces_CORBA_Any);
    CPPUNIT_TEST(test_unsubscribeInterfaces_CORBA_Any);
    CPPUNIT_TEST_SUITE_END();
		
  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
		
  public:
	
    /*!
     * @brief Constructor
     */
    DataOutPortTests()
    {
    }
		
    /*!
     * @brief Destructor
     */
    ~DataOutPortTests()
    {
    }
		
    /*!
     * @brief Test initialization
     */
    virtual void setUp()
    {
      int argc = 0;
      char** argv = 0;
			
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
					    m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();

      usleep(100000);
    }
		
    /*!
     * @brief Test finalization
     */
    virtual void tearDown()
    {
      // if (m_pORB != 0) {
      // m_pORB->destroy();
      // m_pORB = 0;
      // }
    }
		
    /*!
     * @brief get_port_profile()メソッドのテスト
     * 
     * - PortProfileの名称を正しく取得できるか？
     * - "port.port_type"プロパティは正しく取得されるか？
     * - "dataport.data_type"プロパティは正しく取得されるか？
     * - "dataport.interface_type"プロパティは正しく取得されるか？
     * - "dataport.subscription_type"プロパティは正しく取得されるか？
     */
    void test_get_port_profile()
    {
      // DataOutPortを生成する
      RTC::TimedFloat outPortBindValue;
      RTC::OutPort<RTC::TimedFloat>* pOutPort =
	new RTC::OutPort<RTC::TimedFloat>("name of OutPort", outPortBindValue); // will be deleted automatically
			
      coil::Properties dataOutPortProps;
      RTC::DataOutPort* pDataOutPort =
	new RTC::DataOutPort("name of DataOutPort", *pOutPort, dataOutPortProps); // will be deleted automatically
			
      // PortProfileを取得する
      RTC::PortProfile* pPortProfile = pDataOutPort->get_port_profile();
			
      // - PortProfileの名称が正しく取得されるか？
      CPPUNIT_ASSERT_EQUAL(std::string("name of DataOutPort"),
			   std::string(pPortProfile->name));
				
      // "port.port_type"プロパティは正しく取得されるか？
      CPPUNIT_ASSERT_EQUAL(std::string("DataOutPort"),
			   NVUtil::toString(pPortProfile->properties, "port.port_type"));
			
      // "dataport.data_type"プロパティは正しく取得されるか？
      CPPUNIT_ASSERT_EQUAL(std::string("TimedFloat"),
			   NVUtil::toString(pPortProfile->properties, "dataport.data_type"));
			
      // "dataport.interface_type"プロパティは正しく取得されるか？
      // OutPortCorbaProvider --> CORBA_Any
      // OutPortTcpSockProvider --> TCP_Any
      CPPUNIT_ASSERT_EQUIVALENT("CORBA_Any",
				NVUtil::toString(pPortProfile->properties, "dataport.interface_type"));
			
      // "dataport.subscription_type"プロパティは正しく取得されるか？
      CPPUNIT_ASSERT_EQUIVALENT("Flush, New, Periodic",
				NVUtil::toString(pPortProfile->properties, "dataport.subscription_type"));
//      delete pDataOutPort;
//      delete pOutPort;
    }
		
    /*!
     * @brief インタフェースタイプがCORBA_Anyの場合の、publisherInterfaces()メソッドのテスト
     * 
     * - "dataport.corba_any.outport_ref"プロパティを取得できるか？
     */
    void test_publishInterfaces_CORBA_Any()
    {
      // DataOutPortを生成する
      RTC::TimedFloat outPortBindValue;
      RTC::OutPort<RTC::TimedFloat>* pOutPort =
	new RTC::OutPort<RTC::TimedFloat>("name of OutPort", outPortBindValue); // will be deleted automatically
			
      coil::Properties dataOutPortProps;
      DataOutPortMock<RTC::TimedFloat, RTC::RingBuffer>* pDataOutPort =
	new DataOutPortMock<RTC::TimedFloat, RTC::RingBuffer>(
							      "name of DataOutPort", *pOutPort, dataOutPortProps); // will be deleted automatically
			
      // CORBA_Any, Push, Newの組合せを指定してpublisherInterfaces()を呼出す
      RTC::ConnectorProfile connProf;
      connProf.connector_id = "id";
      connProf.name = CORBA::string_dup("name");
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.interface_type", "CORBA_Any"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.dataflow_type", "Push"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.subscription_type", "New"));
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK,
			   pDataOutPort->publishInterfaces_public(connProf));
			
      // "dataport.corba_any.outport_ref"プロパティを取得できるか？
      RTC::OutPortAnyRef outPortAnyRef;
      NVUtil::find(connProf.properties,
		   "dataport.corba_any.outport_ref") >>= outPortAnyRef;
      CPPUNIT_ASSERT(! CORBA::is_nil(outPortAnyRef));
//      delete pDataOutPort;
//      delete pOutPort;
    }

    /*!
     * @brief インタフェースタイプがTCP_Anyの場合の、publisherInterfaces()メソッドのテスト
     * 
     * - "dataport.tcp_any.outport_addr"プロパティを取得できるか？
     */
    void test_publishInterfaces_TCP_Any()
    {
      // DataOutPortを生成する
      RTC::TimedFloat outPortBindValue;
      RTC::OutPort<RTC::TimedFloat>* pOutPort =
	new RTC::OutPort<RTC::TimedFloat>("name of OutPort", outPortBindValue); // will be deleted automatically
			
      coil::Properties dataOutPortProps;
      DataOutPortMock<RTC::TimedFloat, RTC::RingBuffer>* pDataOutPort =
	new DataOutPortMock<RTC::TimedFloat, RTC::RingBuffer>(
							      "name of DataOutPort", *pOutPort, dataOutPortProps); // will be deleted automatically
			
      // TCP_Any, Pull, Periodicの組合せを指定してpublisherInterfaces()を呼出す
      RTC::ConnectorProfile connProf;
      connProf.connector_id = "id";
      connProf.name = CORBA::string_dup("name");
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.interface_type", "TCP_Any"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.dataflow_type", "Pull"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.subscription_type", "Periodic"));
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK,
			   pDataOutPort->publishInterfaces_public(connProf));
			
      // "dataport.tcp_any.outport_addr"プロパティを取得できるか？
      CORBA::Long index = NVUtil::find_index(
					     connProf.properties, "dataport.tcp_any.outport_addr");
      CPPUNIT_ASSERT(index > 0);
//      delete pDataOutPort;
//      delete pOutPort;
    }

    /*!
     * @brief インタフェースタイプがCORBA_Any型の場合の、subscribeInterfaces()メソッドのテスト
     * 
     * - subscribeInterfaces()呼出により、InPortAny側へ正しく接続できるか？
     */
    void test_subscribeInterfaces_CORBA_Any()
    {
      // DataOutPortを生成する
      RTC::TimedFloat outPortBindValue;
      RTC::OutPort<RTC::TimedFloat>* pOutPort =
	new RTC::OutPort<RTC::TimedFloat>("name of OutPort", outPortBindValue); // will be deleted automatically
			
      coil::Properties dataOutPortProps;
      DataOutPortMock<RTC::TimedFloat, RTC::RingBuffer>* pDataOutPort =
	new DataOutPortMock<RTC::TimedFloat, RTC::RingBuffer>(
							      "name of DataOutPort", *pOutPort, dataOutPortProps); // will be deleted automatically
			
      // ConnectorProfileに、接続に必要となるプロパティをセットする
      RTC::ConnectorProfile connProf;
      connProf.connector_id = "id";
      connProf.name = CORBA::string_dup("name");
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.interface_type", "CORBA_Any"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.dataflow_type", "Push"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.subscription_type", "New"));
      InPortAnyMock* pInPortAny = new InPortAnyMock();
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.corba_any.inport_ref",
					     RTC::InPortAny::_duplicate(pInPortAny->_this())));
			
      // subscribeInterfaces()メソッドを呼び出す
      // （これによりDataOutPortがInPortAnyへの参照を取得して、接続が完了する）
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK,
			   pDataOutPort->subscribeInterfaces_public(connProf));
			
      // データ送信を行い、InPortAnyMock::put()側に到達したことをチェックすることで、接続の成功を確認する
      RTC::TimedFloat value;
      value.data = 1.0;
      CPPUNIT_ASSERT(pOutPort->write(value));
      CPPUNIT_ASSERT_EQUAL(1, pInPortAny->getCalledCount());
//      delete pDataOutPort;
//      delete pOutPort;
    }

    /*!
     * @brief インタフェースタイプがCORBA_Anyの場合の、unsubscribeInterfaces()メソッドのテスト
     * 
     * - いったん接続成功した後にunsubscribeInterfaces()を呼び出すことで、切断が成功するか？
     */
    void test_unsubscribeInterfaces_CORBA_Any()
    {
      // DataOutPortを生成する
      RTC::TimedFloat outPortBindValue;
      RTC::OutPort<RTC::TimedFloat>* pOutPort =
	new RTC::OutPort<RTC::TimedFloat>("name of OutPort", outPortBindValue); // will be deleted automatically
			
      coil::Properties dataOutPortProps;
      DataOutPortMock<RTC::TimedFloat, RTC::RingBuffer>* pDataOutPort =
	new DataOutPortMock<RTC::TimedFloat, RTC::RingBuffer>(
							      "name of DataOutPort", *pOutPort, dataOutPortProps); // will be deleted automatically
			
      // ConnectorProfileに、接続に必要となるプロパティをセットする
      RTC::ConnectorProfile connProf;
      connProf.connector_id = "id";
      connProf.name = CORBA::string_dup("name");
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.interface_type", "CORBA_Any"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.dataflow_type", "Push"));
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.subscription_type", "New"));
      InPortAnyMock* pInPortAny = new InPortAnyMock();
      CORBA_SeqUtil::push_back(connProf.properties,
			       NVUtil::newNV("dataport.corba_any.inport_ref",
					     RTC::InPortAny::_duplicate(pInPortAny->_this())));
			
      // subscribeInterfaces()メソッドを呼び出す
      // （これによりDataOutPortがInPortAnyへの参照を取得して、接続が完了する）
      CPPUNIT_ASSERT_EQUAL(RTC::RTC_OK,
			   pDataOutPort->subscribeInterfaces_public(connProf));
			
      // データ送信を行い、InPortAnyMock::put()側に到達したことをチェックすることで、接続の成功を確認する
      RTC::TimedFloat value;
      value.data = 1.0;
      CPPUNIT_ASSERT(pOutPort->write(value));
      CPPUNIT_ASSERT_EQUAL(1, pInPortAny->getCalledCount());
			
      // （接続が成功した後で、）unsubscribeInterfacesを呼出す
      pDataOutPort->unsubscribeInterfaces_public(connProf);

      // 再度データ送信を行うが、InPortAnyMock::put()側に到達しないことをチェックすることで、切断の成功を確認する
      value.data = 2.0;
      CPPUNIT_ASSERT(pOutPort->write(value));
      CPPUNIT_ASSERT_EQUAL(1, pInPortAny->getCalledCount()); // カウント数が変化していないはず
//      delete pDataOutPort;
//      delete pOutPort;
    }
		
  private:
		
    void CPPUNIT_ASSERT_EQUIVALENT(const std::string& lhs, const std::string& rhs)
    {
      std::vector<std::string> lhsValues = coil::split(lhs, ",");
      std::vector<std::string> rhsValues = coil::split(rhs, ",");
			
      // 要素数が異なれば、中身を見るまでもなく同一ではないと判定できる
      if (lhsValues.size() != rhsValues.size())
	{
	  CPPUNIT_ASSERT_EQUAL(lhs, rhs);
	}
			
      // 要素数は同じなので、中身を逐一比較する
      sort(lhsValues.begin(), lhsValues.end());
      sort(rhsValues.begin(), rhsValues.end());
      std::vector<std::string>::size_type size = lhsValues.size();
      for (std::vector<std::string>::size_type i = 0; i < size; ++i)
	{
	  if (lhsValues[i] != rhsValues[i])
	    {
	      CPPUNIT_ASSERT_EQUAL(lhs, rhs);
	    }
	}
			
      // ここまでたどり着いたのであれば、同一と判定される
      return;
    }
		
  };
}; // namespace DataOutPort

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(DataOutPort::DataOutPortTests);

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
#endif // DataOutPort_cpp

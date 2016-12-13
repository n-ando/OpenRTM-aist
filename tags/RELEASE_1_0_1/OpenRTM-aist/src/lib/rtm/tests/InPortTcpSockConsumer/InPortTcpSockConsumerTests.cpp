// -*- C++ -*-

/*
 * $Log: InPortTcpSockConsumerTests.cpp,v $
 * Revision 1.1  2008/04/02 11:02:53  arafune
 * The first commitment.
 *
 * Revision 1.1  2008/02/28 10:00:29  arafune
 * The first commitment.
 *
 *
 *
 */

#ifndef InPortTcpSockConsumer_cpp
#define InPortTcpSockConsumer_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <rtm/config_rtc.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/DataPortSkel.h>
#include <rtm/idl/SDOPackageSkel.h>
#include <rtm/CORBA_SeqUtil.h>
#include <rtm/RingBuffer.h>
#include <rtm/TcpSockServer.h>	
#include <rtm/InPortTcpSockConsumer.h>
#include <rtm/NVUtil.h>

/*!
 * @class InPortTcpSockConsumerTests class
 * @brief InPortTcpSockConsumer test
 */
namespace InPortTcpSockConsumer
{
  class InPortTcpSockConsumerTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(InPortTcpSockConsumerTests);
    CPPUNIT_TEST(test_subscribeInterfaces);
    CPPUNIT_TEST(test_unsubscribeInterfaces);
    CPPUNIT_TEST(test_push);
    CPPUNIT_TEST(test_copy_constructor);
    CPPUNIT_TEST(test_clone);
    CPPUNIT_TEST(test_substitute_operator);
    CPPUNIT_TEST_SUITE_END();

  private:
    CORBA::ORB_ptr m_pORB;
    PortableServer::POA_ptr m_pPOA;
	
  public:
	
    /*!
     * @brief Constructor
     */
    InPortTcpSockConsumerTests()
    {
      int argc = 0;
      char** argv = 0;
			
      m_pORB = CORBA::ORB_init(argc, argv);
      m_pPOA = PortableServer::POA::_narrow(
					    m_pORB->resolve_initial_references("RootPOA"));
      m_pPOA->the_POAManager()->activate();
    }
		
    /*!
     * @brief Destructor
     */
    ~InPortTcpSockConsumerTests()
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
     * @brief subscribeInterfaces()メソッドのテスト
     * 
     * - テスト用の接続情報を元に、Consumerに正しくsubscribeさせることができるか？
     */
    void test_subscribeInterfaces()
    {
      // TCPサーバを生成し、起動させる
      RTC::RingBuffer<float> serverBuffer(2);
      RTC::Properties serverProps;
      RTC::TcpServer<float>* pTcpServer
	= new RTC::TcpServer<float>(serverBuffer, serverProps);
      pTcpServer->open(0);
			
      std::string hostName = pTcpServer->getHostName();
      std::string portNumber = otos(pTcpServer->getPortNumber());
      std::string serverAddr = hostName + ":" + portNumber;
			
      // InPortTcpSockConsumerを生成する
      RTC::RingBuffer<float> consumerBuffer(2);
      RTC::Properties consumerProps;
      RTC::InPortTcpSockConsumer<float> consumer(consumerBuffer, consumerProps);

      // テスト用の疑似接続情報を作成して、Consumerにsubscribeさせる（＝サーバに接続させる）
      SDOPackage::NVList properties;
      CORBA_SeqUtil::push_back(properties,
			       NVUtil::newNV("dataport.dataflow_type", "Push"));
      CORBA_SeqUtil::push_back(properties,
			       NVUtil::newNV("dataport.tcp_any.inport_addr", serverAddr.c_str()));
      CPPUNIT_ASSERT(consumer.subscribeInterface(properties));
    }

    /*!
     * @brief unsubscribeInterfaces()メソッドのテスト
     * 
     * - テスト用の接続情報を元に、Consumerに正しくsubscribeさせた後に、正しくunsubscribeさせることができるか？
     */
    void test_unsubscribeInterfaces()
    {
      // TCPサーバを生成し、起動させる
      RTC::RingBuffer<float> serverBuffer(2);
      RTC::Properties serverProps;
      RTC::TcpServer<float>* pTcpServer
	= new RTC::TcpServer<float>(serverBuffer, serverProps);
      pTcpServer->open(0);
			
      std::string hostName = pTcpServer->getHostName();
      std::string portNumber = otos(pTcpServer->getPortNumber());
      std::string serverAddr = hostName + ":" + portNumber;
			
      // InPortTcpSockConsumerを生成する
      RTC::RingBuffer<float> consumerBuffer(2);
      RTC::Properties consumerProps;
      RTC::InPortTcpSockConsumer<float> consumer(consumerBuffer, consumerProps);

      // テスト用の疑似接続情報を作成して、Consumerにsubscribeさせる（＝サーバに接続させる）
      SDOPackage::NVList properties;
      CORBA_SeqUtil::push_back(properties,
			       NVUtil::newNV("dataport.dataflow_type", "Push"));
      CORBA_SeqUtil::push_back(properties,
			       NVUtil::newNV("dataport.tcp_any.inport_addr", serverAddr.c_str()));
      CPPUNIT_ASSERT(consumer.subscribeInterface(properties));
			
      // unsubscribeさせる
      consumer.unsubscribeInterface(properties);

      // バッファにデータを書き込んで、push()メソッドで送出を試みる（実際は送出されないはず）
      float writeValue = 3.14159;
      consumerBuffer.write(writeValue);
      consumer.push();
      // sleep(1); // 受信待ち時間。ただし、1 [sec]で足りる保証はない。

      // サーバ側のバッファからデータを読み取り、送出したデータと一致しないことを確認する
      float readValue;
      serverBuffer.read(readValue);
      CPPUNIT_ASSERT(writeValue != readValue);
    }
		
    /*!
     * @brief push()メソッドのテスト
     * 
     * - バッファに書き込んでおいたデータが、push()メソッド呼出によってサーバ側へ正しく送出されるか？
     */
    void test_push()
    {
      // TCPサーバを生成し、起動させる
      RTC::RingBuffer<float> serverBuffer(2);
      RTC::Properties serverProps;
      RTC::TcpServer<float>* pTcpServer
	= new RTC::TcpServer<float>(serverBuffer, serverProps);
      pTcpServer->open(0);
			
      std::string hostName = pTcpServer->getHostName();
      std::string portNumber = otos(pTcpServer->getPortNumber());
      std::string serverAddr = hostName + ":" + portNumber;
			
      // InPortTcpSockConsumerを生成する
      RTC::RingBuffer<float> consumerBuffer(2);
      RTC::Properties consumerProps;
      RTC::InPortTcpSockConsumer<float> consumer(consumerBuffer, consumerProps);

      // テスト用の疑似接続情報を作成して、Consumerにsubscribeさせる（＝サーバに接続させる）
      SDOPackage::NVList properties;
      CORBA_SeqUtil::push_back(properties,
			       NVUtil::newNV("dataport.dataflow_type", "Push"));
      CORBA_SeqUtil::push_back(properties,
			       NVUtil::newNV("dataport.tcp_any.inport_addr", serverAddr.c_str()));
      CPPUNIT_ASSERT(consumer.subscribeInterface(properties));

      // バッファにデータを書き込んで、push()メソッドで送出させる
      float writeValue = 3.14159;
      consumerBuffer.write(writeValue);
      consumer.push();
      // sleep(1); // 受信待ち時間。ただし、1 [sec]で足りる保証はない。

      // サーバ側のバッファからデータを読み取り、送出したデータと一致することを確認する			
      float readValue;
      serverBuffer.read(readValue);
      CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
    }
		
    /*!
     * @brief コピーコンストラクタのテスト
     * 
     * - 正しく新たなInPortTcpSockConsumerのインスタンスをコピー生成できるか？
     */
    void test_copy_constructor()
    {
      // TCPサーバを生成し、起動させる
      RTC::RingBuffer<float> serverBuffer(2);
      RTC::Properties serverProps;
      RTC::TcpServer<float>* pTcpServer
	= new RTC::TcpServer<float>(serverBuffer, serverProps);
      pTcpServer->open(0);
			
      std::string hostName = pTcpServer->getHostName();
      std::string portNumber = otos(pTcpServer->getPortNumber());
      std::string serverAddr = hostName + ":" + portNumber;

      // InPortTcpSockConsumerを生成する
      RTC::RingBuffer<float> consumerBuffer(2);
      RTC::Properties consumerProps;
      RTC::InPortTcpSockConsumer<float> consumer(consumerBuffer, consumerProps);

      // 生成したInPortTcpSockConsumerを元にして、別のInPortTcpSockConsumerをコピー生成する
      RTC::InPortTcpSockConsumer<float> consumerNew(consumer);

      // バッファにデータを書き込んで、コピー生成したConsumerを用いてpush()メソッドで送出させる
      float writeValue = 3.14159;
      consumerBuffer.write(writeValue);
      consumerNew.push();
      //sleep(1); // 受信待ち時間。ただし、1 [sec]で足りる保証はない。

      // サーバ側のバッファからデータを読み取り、送出したデータと一致することを確認する			
      float readValue;
      serverBuffer.read(readValue);
      CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
    }
		
    /*!
     * @brief 代入演算子（operator=）のテスト
     * 
     * - 正しくInPortTcpSockConsumerのインスタンスを代入できるか？
     */
    void test_substitute_operator()
    {
      // TCPサーバを生成し、起動させる
      RTC::RingBuffer<float> serverBuffer(2);
      RTC::Properties serverProps;
      RTC::TcpServer<float>* pTcpServer
	= new RTC::TcpServer<float>(serverBuffer, serverProps);
      pTcpServer->open(0);
			
      std::string hostName = pTcpServer->getHostName();
      std::string portNumber = otos(pTcpServer->getPortNumber());
      std::string serverAddr = hostName + ":" + portNumber;

      // InPortTcpSockConsumerを生成する
      RTC::RingBuffer<float> consumerBuffer(2);
      RTC::Properties consumerProps;
      RTC::InPortTcpSockConsumer<float> consumer(consumerBuffer, consumerProps);

      // 生成したInPortCorbaConsumerを元にして、別のInPortCorbaConsumerを代入生成する
      RTC::RingBuffer<float> dummyBuffer(123);
      RTC::Properties dummyProps;
      RTC::InPortTcpSockConsumer<float> consumerNew(dummyBuffer, dummyProps);
      consumerNew = consumer;

      // バッファにデータを書き込んで、代入生成したConsumerを用いてpush()メソッドで送出させる
      float writeValue = 3.14159;
      consumerBuffer.write(writeValue);
      consumerNew.push();
      // sleep(1); // 受信待ち時間。ただし、1 [sec]で足りる保証はない。

      // サーバ側のバッファからデータを読み取り、送出したデータと一致することを確認する			
      float readValue;
      serverBuffer.read(readValue);
      CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
    }

    /*!
     * @brief clone()メソッドのテスト
     * 
     * - 正しくInPortTcpSockConsumerのインスタンスを複製できるか？
     */
    void test_clone()
    {
      // TCPサーバを生成し、起動させる
      RTC::RingBuffer<float> serverBuffer(2);
      RTC::Properties serverProps;
      RTC::TcpServer<float>* pTcpServer
	= new RTC::TcpServer<float>(serverBuffer, serverProps);
      pTcpServer->open(0);
			
      std::string hostName = pTcpServer->getHostName();
      std::string portNumber = otos(pTcpServer->getPortNumber());
      std::string serverAddr = hostName + ":" + portNumber;

      // InPortTcpSockConsumerを生成する
      RTC::RingBuffer<float> consumerBuffer(2);
      RTC::Properties consumerProps;
      RTC::InPortTcpSockConsumer<float> consumer(consumerBuffer, consumerProps);

      // 生成したInPortTcpSockConsumerを元にして、別のInPortTcpSockConsumerをclone生成する
      std::auto_ptr<RTC::InPortTcpSockConsumer<float> > pConsumerNew(consumer.clone());

      // バッファにデータを書き込んで、コピー生成したConsumerを用いてpush()メソッドで送出させる
      float writeValue = 3.14159;
      consumerBuffer.write(writeValue);
      pConsumerNew->push();
      // sleep(1); // 受信待ち時間。ただし、1 [sec]で足りる保証はない。

      // サーバ側のバッファからデータを読み取り、送出したデータと一致することを確認する			
      float readValue;
      serverBuffer.read(readValue);
      CPPUNIT_ASSERT_EQUAL(writeValue, readValue);
    }
		
  };
}; // namespace InPortTcpSockConsumer

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(InPortTcpSockConsumer::InPortTcpSockConsumerTests);

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
#endif // InPortTcpSockConsumer_cpp

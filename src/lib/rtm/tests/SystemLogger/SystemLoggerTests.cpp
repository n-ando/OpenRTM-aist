// -*- C++ -*-
/*!
 * @file   SystemLoggerTests.cpp
 * @brief  SystemLogger test class
 * @date   $Date: 2008/05/12 03:58:45 $
 *
 * $Id: SystemLoggerTests.cpp,v 1.2 2008/05/12 03:58:45 arafune Exp $
 *
 */

/*
 * $Log: SystemLoggerTests.cpp,v $
 * Revision 1.2  2008/05/12 03:58:45  arafune
 * Added some tests.
 * Rearranged tests in a different order.
 *
 * Revision 1.1  2008/05/09 12:01:44  arafune
 * The first commitment.
 *
 *
 */

#ifndef SystemLoggerTests_cpp
#define SystemLoggerTests_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/Task.h>
#include <coil/DynamicLib.h>

#include <rtm/SystemLogger.h>
#include <coil/TimeMeasure.h>

/*!
 * @class SystemLoggerTests class
 * @brief SystemLogger test
 */
namespace Tests
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
  class LogOutCreator
    : public coil::Task
  {
  public:
    LogOutCreator(const char* name, coil::LogStreamBuffer *streambuf)
      : m_name(name),
        rtclog(streambuf)
    {
        rtclog.setName(m_name.c_str());
        rtclog.setDateFormat("%b %d %H:%M:%S");
        rtclog.setLevel("PARANOID");
        rtclog.enableLock();
    }
    ~LogOutCreator()
    {
        rtclog.disableLock();
    }
    virtual int svc()
    {
      coil::TimeMeasure tm;
      for (int i(0); i < 100; ++i)
        {
          double r(rand() / (double)RAND_MAX * 100.0);
          tm.tick();
          std::string str = coil::sprintf("svc() %03d %6.2f",  i, r);
          RTC_TRACE((str.c_str()));
          tm.tack();
          coil::usleep((int)r);
        }
      return 0;
    }
  private:
  protected:
    std::string m_name;
    RTC::Logger rtclog;
  };
  /*!
   * 
   * 
   *
   */
  class SystemLoggerTests
    : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(SystemLoggerTests);
    CPPUNIT_TEST(test_case0);
    CPPUNIT_TEST_SUITE_END();
	
	
  private:

  protected:
	
  public:
    /*!
     * @brief Constructor
     */
    SystemLoggerTests()
    {
    }
		    
    /*!
     * @brief Destructor
     */
    virtual ~SystemLoggerTests()
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
     *
     * 
     *
     */
    void test_case0(void)
    {

        coil::LogStreamBuffer logger;
        std::stringstream s0;

        logger.addStream(s0.rdbuf());
        RTC::Logger rtclog(&logger);
        rtclog.setLevel("PARANOID");
        rtclog.setName("LoggerTests");
//        rtclog.setDateFormat("%b %d %H:%M:%S");
        rtclog.setDateFormat("");
        rtclog.enableLock();

        RTC_LOG(::RTC::Logger::RTL_DEBUG,("tests"));
        CPPUNIT_ASSERT_EQUAL(std::string(" DEBUG: LoggerTests: tests\n"),
                             s0.str());
    }

  };
}; // namespace Tests

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(Tests::SystemLoggerTests);

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
#endif // SystemLoggerTests_cpp

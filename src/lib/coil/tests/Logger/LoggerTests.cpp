// -*- C++ -*-
/*!
 * @file   LoggerTests.cpp
 * @brief  Logger test class
 * @date   $Date$ 
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * $Id$ 
 *
 */

/*
 * $Log$
 *
 */

#ifndef Logger_cpp
#define Logger_cpp

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>

#include <coil/Logger.h>
#include <coil/Task.h>
#include <coil/TimeMeasure.h>
#include <coil/stringutil.h>
#include <string>

class LogCreator
  : public coil::Task
{
public:
  LogCreator(const char* name, std::basic_streambuf<char>* streambuf)
    : m_name(name),
      m_out(streambuf)
      //      logger(name)
  {
  }

  virtual int svc()
  {
    coil::TimeMeasure tm;
    for (int i(0); i < 100; ++i)
      {
        double r(rand() / (double)RAND_MAX * 100.0);
        tm.tick();
        m_out << coil::sprintf("%s %03d %6.2f", m_name.c_str(), i, r) << std::endl;
        tm.tack();
        usleep((int)r);
      }

    double max, min, mean, stddev;
    tm.getStatistics(max, min, mean, stddev);
    std::cout << m_name << std::endl;
    printf("max   : %04.2f [us]\n", max * 1000000);
    printf("min   : %04.2f [us]\n", min * 1000000);
    printf("mean  : %04.2f [us]\n", mean * 1000000);
    printf("stddev: %04.2f [us]\n", stddev * 1000000);
    return 0;
  }

private:
  std::string m_name;
  std::basic_ostream<char> m_out;
};


enum LogLevel
  {
    SILENT,
    INFO,
    ERROR,
    PARANOID
  };

class LogOut
  : public coil::LogStream
{
  

public:
  LogOut(::coil::LogStream::streambuf_type* streambuf)
    : ::coil::LogStream(streambuf)
  {
  }
  virtual ~LogOut(){}

  virtual std::string& prefix(std::string& prefix, int level)
  {
    if (level < SILENT || level > PARANOID) level = SILENT;
    const char* level_str[] =
      {
        "SILENT   ",
        "INFO     ",
        "ERROR    ",
        "PARANOID "
      };
    prefix = getFmtDate() + level_str[level];
    return prefix;
  }

protected:
  std::string getFmtDate()
  {
    const int maxsize = 256;
    char buf[maxsize];

    time_t timer;
    struct tm* date;
    
    timer = time(NULL);
    date = localtime(&timer);
    strftime(buf, maxsize, "%b %d %H:%M:%S ", date);
    
    return std::string(buf);
  }
};


/*!
 * @class LoggerTests class
 * @brief Logger test
 */
namespace Logger
{
  class LoggerTests
   : public CppUnit::TestFixture
  {
    CPPUNIT_TEST_SUITE(LoggerTests);
    CPPUNIT_TEST(test_log_streambuf);
    CPPUNIT_TEST(test_log_stream);
    CPPUNIT_TEST_SUITE_END();
  
  private:
  
  public:
  
    /*!
     * @brief Constructor
     */
    LoggerTests()
    {
    }
    
    /*!
     * @brief Destructor
     */
    ~LoggerTests()
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
  
    /* test case */
    void test_log_streambuf()
    {
      coil::LogStreamBuffer logger;

      std::stringstream s0;
      std::stringstream s1;
      std::stringstream s2;

      logger.addStream(s0.rdbuf());
      logger.addStream(s1.rdbuf());
      logger.addStream(s2.rdbuf());

      LogCreator l0("log0", &logger);
      LogCreator l1("log1", &logger);
      LogCreator l2("log2", &logger);
      LogCreator l3("log3", &logger);

      l0.activate();
      l1.activate();
      l2.activate();
      l3.activate();

      l0.wait();
      l1.wait();
      l2.wait();
      l3.wait();

      std::ofstream f0("log0.log");
      std::ofstream f1("log1.log");
      std::ofstream f2("log2.log");
      f0 << s0.str() << std::endl;
      f1 << s1.str() << std::endl;
      f2 << s2.str() << std::endl;
      f0.close();
      f1.close();
      f2.close();
      CPPUNIT_ASSERT(s0.str() == s1.str());
      CPPUNIT_ASSERT(s1.str() == s2.str());


      std::string s;
      getline(s0, s);
      size_t len(s.size());

      while (getline(s0, s))
        {
          CPPUNIT_ASSERT(len == s.size());
        }
    }

    void test_log_stream()
    {
      coil::LogStreamBuffer logbuf;
      std::stringstream s0;
      logbuf.addStream(s0.rdbuf());
      logbuf.addStream(std::cout.rdbuf());

      LogOut log(&logbuf);
      log.setLevel(PARANOID);
      std::cout << std::endl;
      log.log(SILENT) << coil::sprintf("This is silent message.") << std::endl;
      log.log(INFO) << coil::sprintf("This is info message.") << std::endl;
      log.log(ERROR) << coil::sprintf("This is error message.") << std::endl;
      log.log(PARANOID) << coil::sprintf("This is paranoid message.") << std::endl;

      std::cout << std::endl;
      log.setLevel(INFO);
      log.log(SILENT) << coil::sprintf("This is silent message.") << std::endl;
      log.log(INFO) << coil::sprintf("This is info message.") << std::endl;
      log.log(ERROR) << coil::sprintf("This is error message.") << std::endl;
      log.log(PARANOID) << coil::sprintf("This is paranoid message.") << std::endl;

      std::cout << std::endl;
      log.setLevel(SILENT);
      log.log(SILENT) << coil::sprintf("This is silent message.") << std::endl;
      log.log(INFO) << coil::sprintf("This is info message.") << std::endl;
      log.log(ERROR) << coil::sprintf("This is error message.") << std::endl;
      log.log(PARANOID) << coil::sprintf("This is paranoid message.") << std::endl;

    }

  };
}; // namespace Logger

/*
 * Register test suite
 */
CPPUNIT_TEST_SUITE_REGISTRATION(Logger::LoggerTests);

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
#endif // Logger_cpp

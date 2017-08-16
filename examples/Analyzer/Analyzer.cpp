// -*- C++ -*-
/*!
 * @file  Analyzer.cpp
 * @brief Clock Analyzer Component
 * @date $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * $Id$
 */

#include "Analyzer.h"

// Module specification
// <rtc-template block="module_spec">
static const char* analyzer_spec[] =
  {
    "implementation_id", "Analyzer",
    "type_name",         "Analyzer",
    "description",       "Clock Analyzer Component",
    "version",           "1.0.0",
    "vendor",            "AIST",
    "category",          "Test",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.outputfile", "test.dat",
	"conf.default.datalength", "10",
	"conf.default.sleep_time", "0.1",
	"conf.default.mode", "const",
	"conf.default.maxsize", "10000000",

    // Widget
    "conf.__widget__.outputfile", "text",
	"conf.__widget__.datalength", "text",
	"conf.__widget__.sleep_time", "text",
	"conf.__widget__.mode", "radio",
	"conf.__widget__.maxsize", "text",
    // Constraints

    "conf.__type__.outputfile", "string",
	"conf.__type__.datalength", "long",
	"conf.__type__.sleep_time", "double",
	"conf.__type__.mode", "string",
	"conf.__type__.maxsize", "long",

    ""
  };
// </rtc-template>



DataListener::DataListener(Analyzer *comp) : m_comp(comp)
{

}

DataListener::~DataListener()
{

}




/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Analyzer::Analyzer(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in),
    m_outOut("out", m_out),
    data_size(0)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Analyzer::~Analyzer()
{
}



RTC::ReturnCode_t Analyzer::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  m_inIn.addConnectorDataListener(ON_BUFFER_WRITE,new DataListener(this));
  
  // Set OutPort buffer
  addOutPort("out", m_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("outputfile", m_outputfile, "test.dat");
  bindParameter("datalength", m_datalength, "10");
  bindParameter("sleep_time", m_sleep_time, "0.1");
  bindParameter("mode", m_mode, "const");
  bindParameter("maxsize", m_maxsize, "10000000");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Analyzer::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Analyzer::onActivated(RTC::UniqueId ec_id)
{
	data_size = 0;
	m_fs.open(m_outputfile.c_str(), std::ios::out);
	if (!m_fs)
	{
		return RTC::RTC_ERROR;
	}
  return RTC::RTC_OK;
}



RTC::ReturnCode_t Analyzer::onDeactivated(RTC::UniqueId ec_id)
{
	if (m_fs)
	{
		m_fs.close();
	}
  return RTC::RTC_OK;
}



RTC::ReturnCode_t Analyzer::onExecute(RTC::UniqueId ec_id)
{
	//static int ds = 0;
	//ds += 10000;
	coil::TimeValue start(coil::gettimeofday());
	setTimestamp(m_out);
	//m_out.data.length(m_datalength+ds);
	if(m_mode == "const")
	{
		m_out.data.length(m_datalength);
	}
	else
	{
		data_size += m_datalength;
		if(data_size > m_maxsize)
		{
			return RTC::RTC_ERROR;
		}
		m_out.data.length(data_size);
	}
	

	//coil::sleep(coil::TimeValue(m_sleep_time));
	{
		coil::Guard<coil::Mutex> guard(m_mu);
		m_datalist.push_back(m_out);
		//setTimestamp(m_datalist[m_datalist.size()-1]);
		//m_out.tm.sec = m_datalist[m_datalist.size()-1].tm.sec;
		//m_out.tm.nsec = m_datalist[m_datalist.size()-1].tm.nsec;
	}
	//std::cout << "Analyzer: " << &m_out << std::endl;
	//std::cout << "Analyzer: " << m_out.tm.sec << "\t" << m_out.tm.nsec << std::endl;
	coil::TimeValue end(coil::gettimeofday());
	double diff = (double)(end - start);
	//std::cout << "Analyzer: " << m_sleep_time - diff << std::endl;
	if(diff < m_sleep_time)
	{
		coil::sleep(coil::TimeValue(m_sleep_time - diff));
	}
	
	//coil::TimeValue start1(coil::gettimeofday());
	//coil::sleep(coil::TimeValue(0.3));
	//coil::TimeValue end1(coil::gettimeofday());
	//std::cout << "Analyzer: " << (double)(end1 - start1) << std::endl;
	//std::cout << "Analyzer: " << m_sleep_time - (double)(end - start) << std::endl;

	m_outOut.write();


  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Analyzer::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Analyzer::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


void Analyzer::writeData(const RTC::TimedOctetSeq &data)
{
	//std::cout << "writeData" << std::endl;
	coil::Guard<coil::Mutex> guard(m_mu);
	for (std::vector<TimedOctetSeq>::iterator itr = m_datalist.begin(); itr != m_datalist.end(); ) {
		//std::cout << "writeData: " << data.tm.sec << "\t" << data.tm.nsec << std::endl;
		//std::cout << "writeData2: " << (*itr).tm.sec << "\t" << (*itr).tm.nsec << std::endl;
		if (data.tm.nsec == (*itr).tm.nsec && data.tm.sec == (*itr).tm.sec)
		{
			coil::TimeValue end(coil::gettimeofday());
			coil::TimeValue start(data.tm.sec, data.tm.nsec/1000);
			
			double diff = (double)(end - start);
			std::cout << diff << std::endl;
			m_fs << data.data.length() << "\t" << diff << std::endl;
			itr = m_datalist.erase(itr);
		}
		else
		{
			++itr;
		}
	}
	
}


extern "C"
{
 
  void AnalyzerInit(RTC::Manager* manager)
  {
    coil::Properties profile(analyzer_spec);
    manager->registerFactory(profile,
                             RTC::Create<Analyzer>,
                             RTC::Delete<Analyzer>);
  }
  
};



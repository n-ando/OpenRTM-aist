// -*- C++ -*-
/*!
 * @file  Analyzer.h
 * @brief Clock Analyzer Component
 * @date  $Date$
 *
 * @author 宮本　信彦　n-miyamoto@aist.go.jp
 * 産業技術総合研究所　ロボットイノベーション研究センター
 * ロボットソフトウエアプラットフォーム研究チーム
 *
 * $Id$
 */

#ifndef ANALYZER_H
#define ANALYZER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <vector>
#include <fstream>

using namespace RTC;


class Analyzer;






/*!
 * @class Analyzer
 * @brief Clock Analyzer Component
 *
 * 時間計測用RTC
 *
 */
class Analyzer
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  Analyzer(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~Analyzer() override;

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onInitialize() override;

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id) override;

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id) override;

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id) override;

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);
   void writeData(const RTC::TimedOctetSeq &data);

 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 出力ファイル名
   * - Name: outputfile outputfile
   * - DefaultValue: test_callback.dat
   */
  std::string m_outputfile;
  /*!
   * 出力ファイル名
   * - Name: outputwritefile outputwritefile
   * - DefaultValue: test_writefunc.dat
   */
  std::string m_outputwritefile;
  /*!
  * データ長さ
  * - Name: datalength datalength
  * - DefaultValue: 10
  */
  int m_datalength;
  /*!
  * 内部で待機する時間
  * - Name: sleep_time sleep_time
  * - DefaultValue: 0.01
  */
  std::chrono::microseconds m_sleep_time;
  /*!
  * 通信データ量を一定値(const)にするか、徐々に増加する値(increase)にするかの設定
  * - Name: mode mode
  * - DefaultValue: const
  */
  std::string m_mode;
  /*!
  * 通信データ量を徐々に増やすモードの場合最大データサイズ
  * これを超えるとエラー状態に遷移
  * - Name: maxsize maxsize
  * - DefaultValue: 10000000
  */
  long m_maxsize;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedOctetSeq m_in;
  /*!
   * インポートにデータが入力された時間をファイルに記録
   */
  InPort<RTC::TimedOctetSeq> m_inIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedOctetSeq m_out;
  /*!
   * アウトポートからデータを出力した時間をファイルに記録
   */
  OutPort<RTC::TimedOctetSeq> m_outOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

  

 private:
	 std::ofstream m_fs;
   std::ofstream m_fsw;
	 std::vector<RTC::Time> m_datalist;
	 std::mutex m_mu;
	 int m_data_size;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};

class DataListener
	: public ConnectorDataListenerT<RTC::TimedOctetSeq>
{
	USE_CONNLISTENER_STATUS;
public:
	DataListener(Analyzer *comp);
	~DataListener() override;

	ReturnCode operator()(ConnectorInfo&  /*info*/,
		TimedOctetSeq& data) override
	{
		m_comp->writeData(data);
		return NO_CHANGE;
	}
	Analyzer *m_comp;

};


extern "C"
{
  DLL_EXPORT void AnalyzerInit(RTC::Manager* manager);
}

#endif // ANALYZER_H

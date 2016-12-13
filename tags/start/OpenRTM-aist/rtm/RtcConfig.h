// -*- C++ -*-
/*!
 * @file RtcConfig.h
 * @brief RtcConfig class
 * @date $Date: 2005-05-12 09:06:18 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: RtcConfig.h,v 1.1.1.1 2005-05-12 09:06:18 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */

#ifndef RtcConfig_h
#define RtcConfig_h

#include <string>
#include <map>
#include <vector>
#include <list>
#include <fstream>
#include "rtm/RTC.h"


namespace RTM
{
  
  using namespace std;
  
#ifdef ORB_IS_OMNIORB
  static const char* config_map[][3] = 
	{{"IIOPAddrPort", "-ORBendPoint", "giop:tcp:"},
	 {"", "", ""},
	 {"NameServer", "-ORBInitRef", "NameService=corbaname::"},
	 {0,0,0}};
#endif // omniORB
  
#ifdef ORB_IS_MICO
  static const char* config_map[][3] = 
	{{"NameServer", "-ORBNamingAddr", ""},
	 {"IIOPAddrPort", "-ORBIIOPAddr", "inet:"},
	 {"", "", ""},
	 {0,0,0}};
#endif // MICO
  
  static const char* config_file_path[] = 
	{"./rtc.conf",
	 "/etc/rtc.conf",
	 "/etc/rtc/rtc.conf",
	 "/usr/local/etc/rtc.conf",
	 NULL};
  
  static const char* config_file_env = "RTC_CONFIG";

  /*!
   * @if jp
   *
   * @class RtcConfig
   *
   * @brief RtcManager コンフィギュレーションクラス
   * 
   * コンフィギュレーションファイルを読み込み RtcManager のコンフィギュレーシ
   * ョンを行う。
   *
   * @else
   *
   * @class RtcConfig
   *
   * @brief Rtcmanager configuration class
   *
   * Read configuration information from rtc.conf configuration file 
   * for RtcManager.
   *
   * @endif
   */
  class RtcConfig
  {
  public:
	/*!
	 * @if jp
	 *
	 * @brief RtcConfig クラスコンストラクタ
	 *
	 * RtcConfig クラスのコンストラクタ。
	 *
	 * @else
	 *
	 * @brief RtcConfig class constructor
	 *
	 * A constructor of RtcConfig.
	 *
	 * @endif
	 */
	RtcConfig(): m_DebugMode(false){};

	/*!
	 * @if jp
	 *
	 * @brief RtcConfig クラスコンストラクタ
	 *
	 * RtcConfig クラスのコンストラクタ。
	 *
	 * @param argc コマンドライン引数の数
	 * @param argv コマンドライン引数の配列
	 *
	 * @else
	 *
	 * @brief RtcConfig class constructor
	 *
	 * A constructor of RtcConfig.
	 *
	 * @param argc number of command line arguments
	 * @param argv sequence of command line arguments
	 *
	 * @endif
	 */
	RtcConfig(int argc, char** argv);

	/*!
	 * @if jp
	 *
	 * @brief RtcConfig クラスデストラクタ
	 *
	 * @else
	 *
	 * @brief RtcConfig class destructor
	 *
	 * @endif
	 */
	virtual ~RtcConfig();
	
	/*!
	 * @if jp
	 *
	 * @brief RtcConfig クラスの初期化
	 *
	 * RtcConfig クラスをコマンドライン引数で初期化する
	 *
	 * @param argc コマンドライン引数の数
	 * @param argv コマンドライン引数の配列
	 *
	 * @else
	 *
	 * @brief Initialize RtcConfig class
	 *
	 * Initialize RtcConfig with command line arguments.
	 *
	 * @param argc number of command line arguments
	 * @param argv sequence of command line arguments
	 *
	 * @endif
	 */
	bool initConfig(int argc, char** argv);
	
	/*!
	 * @if jp
	 *
	 * @brief ORB_init() に渡す引数を取得する
	 *
	 * コンフィギュレーションファイルから得たコンフィギュレーション情報の内
	 * ORB の初期化に必要な情報を ORB_init() に渡す引数として取得する。
	 *
	 * @else
	 *
	 * @brief Get arguments to give ORB_init()
	 *
	 * Get configuration information to give to ORB_init() given by 
	 * configuration file as a sequence data.
	 *
	 * @endif
	 */
	char** getOrbInitArgv() const
	{
	  //	  for (int i = 0; i < m_Argc; i++) cerr << m_Argv[i] << endl;
	  return m_Argv;
	};
	
	/*!
	 * @if jp
	 *
	 * @brief ORB_init() に渡す引数の数を取得する
	 *
	 * ORB_init() に渡す引数の数を取得する。
	 *
	 * @else
	 *
	 * @brief Get number of arguments to give ORB_init()
	 *
	 * Get number of argument to give ORB_init().
	 *
	 * @endif
	 */
	int getOrbInitArgc() const {return m_Argc;};
	
	/*!
	 * @if jp
	 *
	 * @brief ネームサーバ名を取得
	 *
	 * コンフィギュレーションファイルから得たネームサーバ名を取得する。
	 *
	 * @else
	 *
	 * @brief Get name of CORBA name server
	 *
	 * Get name of CORBA name server gived by configuration file.
	 *
	 * @endif
	 */
	string getNameServer() const {return m_NameServer;};
	
	/*!
	 * @if jp
	 *
	 * @brief コンポーネントロードパスを取得
	 *
	 * コンフィギュレーションファイルから得たコンポーネントロードパスを
	 * 取得する。
	 *
	 * @else
	 *
	 * @brief Get component load path
	 *
	 * Get component load path gived by configuration file.
	 *
	 * @endif
	 */
	list<string>& getComponentLoadPath() {return m_ComponentLoadPath;};
	
	/*!
	 * @if jp
	 * @brief 現在の実行ファイル名を取得
	 * @else
	 * @brief Get current executable name
	 * @endif
	 */
	string getBinName() const {return m_BinName;};
	
	/*!
	 * @if jp
	 * @brief 現在のOS名を取得
	 * @else
	 * @brief Get current OS name
	 * @endif
	 */
	string getOSname() const {return m_OSname;};
	
	/*!
	 * @if jp
	 * @brief 現在のhost名を取得
	 * @else
	 * @brief Get current host name
	 * @endif
	 */
	string getHostname() const {return m_Hostname;};
	
	/*!
	 * @if jp
	 * @brief 現在の OS release level を取得
	 * @else
	 * @brief Get current OS release level
	 * @endif
	 */
	string getOSrelease() const {return m_OSrelease;};
	
	/*!
	 * @if jp
	 * @brief 現在の OS version を取得
	 * @else
	 * @brief Get current OS version
	 * @endif
	 */
	string getOSversion() const {return m_OSversion;};
	
	/*!
	 * @if jp
	 * @brief 現在の machien architecture を取得
	 * @else
	 * @brief Get current machine architecture
	 * @endif
	 */
	string getArch() const {return m_Arch;};
	
	/*!
	 * @if jp
	 * @brief 現在のプロセスIDを取得
	 * @else
	 * @brief Get current process id
	 * @endif
	 */
	string getPid() const {return m_Pid;};

	string getLogFileName();
	string getErrorLogFileName();
	int getLogLevel();
	int getLogLock();
	std::string getLogTimeFormat();
	
  protected:
	/*!
	 * @if jp
	 * @brief コマンドライン引数をパースする
	 * @else
	 * @brief Parse command line arguments
	 * @endif
	 */
	bool parseCommandArgs(int argc, char** argv);
	
	/*!
	 * @if jp
	 * @brief コンフィギュレーションファイルをデフォルトパスから探す
	 * @else
	 * @brief Find configuration file from default given path
	 * @endif
	 */
	bool findConfigFile();
	
	/*!
	 * @if jp
	 * @brief コンフィギュレーションファイルをパースする
	 * @else
	 * @brief Parse configuration file
	 * @endif
	 */
	bool parseConfigFile();
	
	/*!
	 * @if jp
	 * @brief システム情報を取得する
	 * @else
	 * @brief Get system information
	 * @endif
	 */
	bool collectSysInfo();
	
	/*!
	 * @if jp
	 * @brief ヘルプを表示する
	 * @else
	 * @brief Print usage
	 * @endif
	 */
	void printUsage(char* arg);
	
	/*!
	 * @if jp
	 * @brief 引数形式を変換する
	 * @else
	 * @brief Convert command line argument from std::list to char**
	 * @endif
	 */
	void argsToArgv();

	/*!
	 * @if jp
	 * @brief ファイル存在チェック
	 * @else
	 * @brief Check file existance
	 * @endif
	 */
	bool fileExist(const char *filename);
	/*!
	 * @if jp
	 * @brief 文字列の分割
	 * @else
	 * @brief Split string with delimter
	 * @endif
	 */
	bool split(const string& input, const string& delimiter, list<string>& results);
  private:
	/*!
	 * @if jp
	 * @brief 実行ファイル名
	 * @else
	 * @brief Current executable name
	 * @endif
	 */
	string m_BinName;
	string m_ArgConfigFile;
	string m_ConfigFile;
	map<string, string> m_Config;
	vector<string> m_Args;
	char** m_Argv;
	int m_Argc;
	string m_NameServer;
	std::list<string> m_ComponentLoadPath;
	string m_OSname;
	string m_Hostname;
	string m_OSrelease;
	string m_OSversion;
	string m_Arch;
	string m_Pid;
	bool m_DebugMode;
  };
  
}; // end of namespace RTM

#endif // end of __RtcConfig_h__

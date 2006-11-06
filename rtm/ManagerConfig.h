// -*- C++ -*-
/*!
 * @file ManagerConfig.h
 * @brief RTC manager configuration
 * @date $Date: 2006-11-06 01:26:28 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ManagerConfig.h,v 1.3 2006-11-06 01:26:28 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.2  2006/10/23 08:38:23  n-ando
 * To get Property after "init()" calling, getConfig() was added.
 *
 * Revision 1.1  2006/10/17 10:21:38  n-ando
 * The first commitment.
 *
 *
 */


#ifndef ManagerConfig_h
#define ManagerConfig_h

#include <rtm/Properties.h>


namespace RTC
{

  
  /*!
   * @if jp
   *
   * @class ManagerConfig
   * @brief Manager configuration クラス
   *
   * Manager のコンフィギュレーションを行う、コマンドライン引数を受け取り、
   * (あるいは引数なしで)インスタンス化される。、Manager のプロパティの前設定
   * を行い
   *
   * 設定(ファイル)の指定の強さは以下のとおりである。
   * 上がもっとも強く、下がもっとも弱い。
   * <OL>
   * <LI>コマンドラインオプション "-f"
   * <LI>環境変数 "RTC_MANAGER_CONFIG"
   * <LI>デフォルト設定ファイル "./rtc.conf"
   * <LI>デフォルト設定ファイル "/etc/rtc.conf"
   * <LI>デフォルト設定ファイル "/etc/rtc/rtc.conf"
   * <LI>デフォルト設定ファイル "/usr/local/etc/rtc.conf"
   * <LI>デフォルト設定ファイル "/usr/local/etc/rtc/rtc.conf"
   * <LI>埋め込みコンフィギュレーション値
   *</OL>
   * ただし、コマンドラインオプション "-d" が指定された場合は、
   * (たとえ -f で設定ファイルを指定しても)埋め込みコンフィギュレーション値
   * が使用される。
   *
   * @else
   *
   * @brief
   *
   * @endif
   */
  class ManagerConfig
  {
  public:
    // The list of default configuration file path.
    static const char* config_file_path[];
    
    // Environment value to specify configuration file
    static const char* config_file_env;


    /*!
     * @if jp
     *
     * @brief ManagerConfig コンストラクタ
     *
     * 何もしないコンストラクタ。
     *
     * @else
     *
     * @brief ManagerConfig constructor
     *
     * Do nothing. 
     *
     * @endif
     */
    ManagerConfig();


    /*!
     * @if jp
     *
     * @brief ManagerConfig コンストラクタ
     *
     * 与えられた引数により初期化も同時にするコンストラクタ。
     *
     * @param argc コマンドライン引数の数
     * @param argv コマンドライン引数
     *
     * @else
     *
     * @brief ManagerConfig constructor
     *
     * The constructor that performs initialization at the same time with
     * given arguments.
     *
     * @param argc The number of command line arguments
     * @param argv The command line arguments
     *
     * @endif
     */
    ManagerConfig(int argc, char** argv);


    /*!
     * @if jp
     *
     * @brief ManagerConfig デストラクタ
     *
     * @else
     *
     * @brief ManagerConfig destructor
     *
     * @endif
     */
    virtual ~ManagerConfig();
    

    /*!
     * @if jp
     *
     * @brief 初期化
     *
     * デフォルトサーチパスからコンフィギュレーションファイルを探し初期化
     * を行うとともにプロパティを返す。サーチパスにコンフィギュレーション
     * ファイルが存在しない場合、デフォルトのコンフィギュレーションを
     * 返す。
     *
     * @return 初期化された Property 値
     *
     * @else
     *
     * @brief Initialization
     *
     * This operation searches the configuration file from default search path,
     * and initialize and return default properties.
     * If there is no configuration file in the default search path,
     * default configuration statically defined is used.
     *
     * @return Initialized Property value.
     *
     * @endif
     */
    Properties init();


    /*!
     * @if jp
     *
     * @brief 初期化
     *
     * コマンドライン引数を与えて初期化する。コマンドラインオプションは
     * 以下のものが使用可能である。
     *
     * -f file   : コンフィギュレーションファイルを指定する。<br>
     * -l module : ロードするモジュールを指定する。<br>
     * -o options: その他オプションを指定する。。<br>
     * -d        : デフォルトのコンフィギュレーションを使う。<br>
     *
     * @else
     *
     * @brief Initialization
     *
     * Initialize with command line options. The following command options
     * are available.
     *
     * -f file   : Specify a configuration file. <br>
     * -l module : Specify modules to be loaded at the beginning. <br>
     * -o options: Other options. <br>
     * -d        : Use default static configuration. <br>
     *
     * @endif
     */
    Properties init(int argc, char** argv);


    /*!
     * @if jp
     *
     * @brief コンフィギュレーションを取得する
     *
     * コンフィギュレーションを取得する。init()呼び出し前に呼ぶと、
     * 静的に定義されたデフォルトのコンフィギュレーションを返す。
     * init() 呼び出し後に呼ぶと、コマンドライン引数、環境変数等に
     * 基づいた初期化されたコンフィギュレーションを返す。
     *
     * @else
     *
     * @brief Get configuration value.
     *
     * This operation returns default configuration statically defined,
     * when before calling init() function. When after calling init() function,
     * this operation returns initialized configuration value according to
     * command option, environment value and so on.
     *
     * @endif
     */
    Properties getConfig() const;

  protected:
    /*!
     * @if jp
     *
     * @brief コマンド引数をパースする
     *
     * -f file   : コンフィギュレーションファイルを指定する。<br>
     * -l module : ロードするモジュールを指定する。。<br>
     * -o options: その他オプションを指定する。。<br>
     * -d        : デフォルトのコンフィギュレーションを使う。<br>
     *
     * @else
     *
     * @brief Parse command arguments
     *
     * -f file   : Specify a configuration file. <br>
     * -l module : Specify modules to be loaded at the beginning. <br>
     * -o options: Other options. <br>
     * -d        : Use default static configuration. <br>
     *
     * @endif
     */
    void parseArgs(int argc, char** argv);
    
    
    /*!
     * @if jp
     *
     * @brief Configuration file を探す
     *
     * Configuration file の優先順位
     *
     * コマンドオプション指定＞環境変数＞デフォルトファイル＞デフォルト設定
     *
     * デフォルト強制オプション(-d): デフォルトファイルがあっても無視して
     *                               デフォルト設定を使う
     *
     *
     * @else
     *
     * @brief Find configuration file
     *
     * @endif
     */
    bool findConfigFile();

    
    /*!
     * @if jp
     *
     * @brief システム情報をセットする
     *
     * システム情報を取得しプロパティにセットする。設定されるキーは以下の通り。
     * manager.os.name    : OS名
     * manager.os.release : OSリリース名
     * maanger.os.version : OSバージョン名
     * manager.os.arch    : OSアーキテクチャ
     * manager.os.hostname: ホスト名
     * manager.pid        : プロセスID
     * 
     * @else
     * 
     * @brief Set system information
     * 
     * Get the following system info and set them to Manager's properties.
     * manager.os.name    : OS name
     * manager.os.release : OS release name
     * maanger.os.version : OS version
     * manager.os.arch    : OS architecture
     * manager.os.hostname: Hostname
     * manager.pid        : process ID
     *
     * @endif
     */
    void setSystemInformation(Properties& prop);


    /*!
     * @if jp
     * @brief ファイルが存在するかどうか確かめる
     * @else
     * @brief Check file existance
     * @endif
     */
    bool fileExist(const std::string& filename);

    std::string m_configFile;
    Properties m_properties;
   
    
  };
  
}; // namespace RTC  
  
  
#endif // ManagerConfig_h
  

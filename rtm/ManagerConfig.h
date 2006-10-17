// -*- C++ -*-
/*!
 * @file ManagerConfig.h
 * @brief RTC manager configuration
 * @date $Date: 2006-10-17 10:21:38 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2005
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ManagerConfig.h,v 1.1 2006-10-17 10:21:38 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 *
 */


#ifndef ManagerConfig_h
#define ManagerConfig_h

#include <rtm/Properties.h>


namespace RTC
{
  // The list of default configuration file path.
  static const char* config_file_path[] = 
    {
      "./rtc.conf",
      "/etc/rtc.conf",
      "/etc/rtc/rtc.conf",
      "/usr/local/etc/rtc.conf",
      "/usr/local/etc/rtc/rtc.conf",
      NULL
    };
  
  // Environment value to specify configuration file
  static const char* config_file_env = "RTC_MANAGER_CONFIG";
  
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
    /*!
     * @if jp
     *
     * @brief ManagerConfig コンストラクタ
     *
     * @else
     *
     * @brief ManagerConfig constructor
     *
     * @endif
     */
    ManagerConfig();
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
     * @brief ManagerConfig デストラクタ
     *
     * @else
     *
     * @brief ManagerConfig destructor
     *
     * @endif
     */
    Properties init();
    Properties init(int argc, char** argv);

  protected:
    /*!
     * @if jp
     *
     * @brief コマンド引数をパースする
     *
     * -f file   : コンフィギュレーションファイルを指定する。
     * -l module : ロードするモジュールを指定する。
     * -o options: その他オプションを指定する。
     * -d        : デフォルトのコンフィギュレーションを使う
     *
     * @else
     *
     * @brief Parse command arguments
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
   
    
  };
  
}; // namespace RTC  
  
  
#endif // ManagerConfig_h
  

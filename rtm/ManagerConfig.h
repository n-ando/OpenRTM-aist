// -*- C++ -*-
/*!
 * @file ManagerConfig.h
 * @brief RTC manager configuration
 * @date $Date: 2007-12-31 03:08:04 $
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2003-2008
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id: ManagerConfig.h,v 1.4.2.1 2007-12-31 03:08:04 n-ando Exp $
 *
 */

/*
 * $Log: not supported by cvs2svn $
 * Revision 1.4  2007/04/13 18:02:28  n-ando
 * Some configuration properties handling processes were changed.
 *
 * Revision 1.3  2006/11/06 01:26:28  n-ando
 * Some trivial fixes.
 *
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
   * (あるいは引数なしで)インスタンス化される。
   * コマンドライン引数で指定された設定ファイル、環境変数などから Manager の
   * プロパティ情報を設定する。
   *
   * 各設定の優先度は以下のとおりである。
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
   * @since 0.4.0
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
    /*!
     * @if jp
     * @brief Manager コンフィギュレーションのデフォルト・ファイル・パス
     * @else
     * @endif
     */
    static const char* config_file_path[];
    
    // Environment value to specify configuration file
    /*!
     * @if jp
     * @brief デフォルト・コンフィギュレーションのファイル・パスを識別する
     *        環境変数
     * @else
     * @endif
     */
    static const char* config_file_env;
    
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ。(何もしない)
     *
     * @else
     *
     * @brief constructor
     *
     * Do nothing. 
     *
     * @endif
     */
    ManagerConfig();
    
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * 与えられた引数によりコンフィギュレーション情報の初期化を行う。
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
     * @brief デストラクタ
     *
     * @else
     *
     * @brief destructor
     *
     * @endif
     */
    virtual ~ManagerConfig();
    
    /*!
     * @if jp
     *
     * @brief 初期化
     *
     * コマンドライン引数に応じて初期化を実行する。コマンドラインオプションは
     * 以下のものが使用可能である。
     *
     * -f file   : コンフィギュレーションファイルを指定する。<br>
     * -l module : ロードするモジュールを指定する。(未実装)<br>
     * -o options: その他オプションを指定する。(未実装)<br>
     * -d        : デフォルトのコンフィギュレーションを使う。(未実装)<br>
     *
     * @param argc コマンドライン引数の数
     * @param argv コマンドライン引数
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
    void init(int argc, char** argv);
    
    /*!
     * @if jp
     * @brief Configuration 情報を Property に設定する
     * 
     * Manager のConfiguration 情報を指定された Property に設定する。
     *
     * @param prop Configuration 設定対象 Property
     * 
     * @else
     * @brief Apply configuration results to Property
     * @endif
     */
    void configure(Properties& prop);
    
    /*!
     * @if jp
     *
     * @brief コンフィギュレーションを取得する
     *
     * コンフィギュレーションを取得する。init()呼び出し前に呼ぶと、
     * 静的に定義されたデフォルトのコンフィギュレーションを返す。
     * init() 呼び出し後に呼ぶと、コマンドライン引数、環境変数等に
     * 基づいた初期化されたコンフィギュレーションを返す。
     * (未実装)
     *
     * @return Manager のコンフィギュレーション情報
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
     * -l module : ロードするモジュールを指定する。(未実装)<br>
     * -o options: その他オプションを指定する。(未実装)<br>
     * -d        : デフォルトのコンフィギュレーションを使う。(未実装)<br>
     *
     * @param argc コマンドライン引数の数
     * @param argv コマンドライン引数
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
     * @brief Configuration file の検索
     *
     * Configuration file を検索し、設定する。
     * 既に Configuration file が設定済みの場合は、ファイルの存在確認を行う。
     *
     * Configuration file の優先順位
     * コマンドオプション指定＞環境変数＞デフォルトファイル＞デフォルト設定
     *
     * デフォルト強制オプション(-d): デフォルトファイルがあっても無視して
     *                               デフォルト設定を使う
     *
     * @return Configuration file 検索結果
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
     * @brief システム情報を設定する
     *
     * システム情報を取得しプロパティにセットする。設定されるキーは以下の通り。
     * manager.os.name    : OS名
     * manager.os.release : OSリリース名
     * maanger.os.version : OSバージョン名
     * manager.os.arch    : OSアーキテクチャ
     * manager.os.hostname: ホスト名
     * manager.pid        : プロセスID
     * 
     * @param prop システム情報を設定したプロパティ
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
     * @brief ファイルの存在確認
     *
     * 指定されたファイルが存在するか確認する。
     *
     * @param filename 確認対象ファイル名称
     *
     * @return 対象ファイル確認結果(存在する場合にtrue)
     *
     * @else
     * @brief Check file existance
     * @endif
     */
    bool fileExist(const std::string& filename);
    
    /*!
     * @if jp
     * @brief Manager コンフィギュレーション・ファイルのパス
     * @else
     * @endif
     */
    std::string m_configFile;
  };
}; // namespace RTC  
#endif // ManagerConfig_h

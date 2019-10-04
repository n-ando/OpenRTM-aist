// -*- C++ -*-
/*!
 * @file OS_win32.h
 * @brief OS class
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_OS_H
#define COIL_OS_H

#include <Windows.h>
#include <process.h>
#include <WinBase.h>
#include <string>

extern "C"
{
  extern char *optarg;
};

namespace coil
{

#define COIL_UTSNAME_LENGTH 65
  struct utsname
  {
    char sysname[COIL_UTSNAME_LENGTH];
    char nodename[COIL_UTSNAME_LENGTH];
    char release[COIL_UTSNAME_LENGTH];
    char version[COIL_UTSNAME_LENGTH];
    char machine[COIL_UTSNAME_LENGTH];
  };

  class osversion
  {
  public:
      osversion();
      osversion(const osversion& obj);

      osversion(DWORD majar_version,DWORD minor_version);
      DWORD major;
      DWORD minor;
  };

  /*!
  * @if jp
  *
  * @brief RtlGetVersion APIによりOSの情報取得
  * RtlGetVersion関数によりOSのメジャーバージョン、マイナーバージョン、
  * ビルドナンバー、サービスパックの情報を取得する
  * RtlGetVersion関数アドレス取得失敗、OSの情報取得失敗の場合は-1を返す
  * この関数はrtlgetinfo関数で使用するためのものであり、基本的に外部からは使用しない
  *
  *
  * @param name 構造体名称
  *
  * @return 0: 成功, -1: 失敗
  *
  * @else
  *
  * @brief Obtain OS information using RtlGetVersion API
  * Get major version, minor version, build number, service pack information of OS by RtlGetVersion function
  * RtlGetVersion function Returns -1 in the case of address acquisition failure, OS information acquisition failure.
  *
  * @param name Name of structure
  *
  * @return 0: Successful, -1: failed
  *
  * @endif
  */
  bool rtlgetinfo(utsname* name);

  /*!
   * @if jp
   *
   * @brief システム情報取得
   *
   * システム情報を構造体に設定して返す。
   * OSのバージョンはRtlGetVersionにより取得する
   * RtlGetVersionはRTL_OSVERSIONINFOWにOSのメジャーバージョン、
   * マイナーバージョン、ビルドナンバー、サービスパックの情報などを格納する
   * ただし、ライブラリ(ntdll.dll)が存在せず利用できない場合は
   * VerifyVersionInfoによるバージョン比較を行う。
   * VerifyVersionInfoは設定したOSのバージョンと指定のバージョンを比較する関数である。
   * VerifyVersionInfoを使う場合はビルドナンバーは設定されない
   *
   * @param name 構造体名称
   *
   * @return 0: 成功, -1: 失敗
   *
   * @else
   *
   * @brief Get System information
   *
   * Return a system information to a structure.
   * Set system information to structure and return it.
   * Obtain version of OS by RtlGetVersion function.
   * RtlGetVersion function stores the major version, minor version, build number, service pack information etc of OS in RTL_OSVERSIONINFOW.
   * However, if the library (ntdll.dll) does not exist and can not be used, version comparison by VerifyVersionInfo function is performed.
   * VerifyVersionInfo function is a function to compare the version of the specified OS with the specified version.
   * When using VerifyVersionInfo function, the build number is not set.
   *
   * @param name Name of structure
   *
   * @return 0: Successful, -1: failed
   *
   * @endif
   */
  int uname(utsname* name);

  /*!
   * @if jp
   *
   * @brief 呼び出し元プロセスのプロセスID取得
   *
   * 呼び出し元プロセスのプロセスIDを返す。
   *
   * @return プロセスID
   *
   * @else
   *
   * @brief Get process ID of the caller process
   *
   * Return a process ID of the caller process.
   *
   * @return Process ID
   *
   * @endif
   */
  using pid_t = int;
  pid_t getpid();

  /*!
   * @if jp
   *
   * @brief 呼び出し元プロセスの親プロセスのプロセスID取得
   *
   * 呼び出し元プロセスの親プロセスのプロセスIDを返す。
   *
   * @return 0
   *
   * @else
   *
   * @brief Get process ID of the parent process
   *
   * Return a process ID of the parent process.
   *
   * @return 0
   *
   * @endif
   */
  pid_t getppid();

  /*!
   * @if jp
   *
   * @brief 環境変数取得
   *
   * 環境変数を返す。
   *
   * @param name 環境変数名称
   *
   * @return 環境変数の値(NULL: 該当なし)
   *
   * @else
   *
   * @brief Get environment variable
   *
   * Return a environment variable.
   *
   * @param name Name of environment variable
   *
   * @return Value of environment variable(NULL: nonexistent)
   *
   * @endif
   */
  bool getenv(const char* name, std::string &env);

  /*!
   * @if jp
   *
   * @class GetOpt
   * @brief GetOpt クラス
   *
   * @else
   *
   * @class GetOpt
   * @brief GetOpt class
   *
   * @endif
   */
  class GetOpt
  {
  public:
    /*!
     * @if jp
     *
     * @brief コンストラクタ
     *
     * コンストラクタ。
     *
     * @param name オブジェクト名
     *
     * @else
     *
     * @brief Constructor
     *
     * Constructor
     *
     * @param name Object name
     *
     * @endif
     */
    GetOpt(int argc, char* const argv[], const char* opt, int flag);

    /*!
     * @if jp
     *
     * @brief デストラクタ
     *
     * デストラクタ。
     *
     * @else
     *
     * @brief Destructor
     *
     * Destructor
     *
     * @endif
     */
    ~GetOpt();

    /*!
     * @if jp
     *
     * @brief コマンドライン引数解析
     *
     * コマンドライン引数を解析する。
     *
     * @return 解析結果
     *
     * @else
     *
     * @brief Parses the command line arguments
     *
     * Parses the command line arguments.
     *
     * @return Result of parses.
     *
     * @endif
     */
    int operator()();

    char* optarg;     //! オプション引数
    int optind;       //! 処理対象引数
    int opterr;       //! エラー表示 0:抑止、1:表示
    int optopt;       //! オプション文字が足りない時、多い時にセットされる

  private:
    int m_argc;
    char* const * m_argv;
    const char* m_opt;
  };

} // namespace coil

#endif  // COIL_OS_H

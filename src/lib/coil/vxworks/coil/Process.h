// -*- C++ -*-
/*!
 * @file  Process.h
 * @brief Process handling functions
 * @date  $Date$
 * @author Nobuhiko Miyamoto <n-miyamoto@aist.go.jp>
 *
 * Copyright (C) 2017
 *     Nobuhiko Miyamoto
 *     Robot Innovation Research Center
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_PROCESS_H
#define COIL_PROCESS_H

#include <stdlib.h>
#include <unistd.h>

#include <coil/stringutil.h>

namespace coil
{

  /*!
   * @if jp
   * @brief プロセスを起動する
   *
   * プロセスを起動する。引数には起動するファイル名を与える。実行ファイ
   * ルは環境変数 PATH に設定されたコマンドサーチパス内から検索され、見
   * つかればコマンドが起動される。プロセスの起動が成功すれば 0、失敗す
   * れば -1 を返す。
   *
   * @param command 起動する実行ファイルのフルパス
   * @return 0: 成功, -1: 失敗
   *
   * @else
   * @brief Launching a process
   *
   * This function launches a process. The argument is command file
   * name be launched. The command will be searched according to the
   * environment variable PATH of command search path. 0 will be
   * returned if launching process is successful, and -1 will be
   * returned if it is failed.
   * 
   * @param command full path string to a command to be executed.
   * @return 0: successful, -1: failed
   *
   * @endif
   */
  int launch_shell(std::string command);

  int daemon(int nochdir, int noclose);

  int create_process(std::string command, std::vector<std::string> &out);

} // namespace coil
#endif // COIL_PROCESS_H

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

#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <coil/stringutil.h>

namespace coil
{

  /*!
   * @if jp
   * @brief プロセスを起動する
   * @else
   * @brief Launching a process
   * @endif
   */
  int launch_shell(std::string command)
  {

    return -1;
  }

  int daemon(int nochdir, int noclose)
  {
    return -1;
  }


}; // namespace coil
#endif // COIL_PROCESS_H

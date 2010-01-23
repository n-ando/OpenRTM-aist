// -*- C++ -*-
/*!
 * @file  Process.h
 * @brief Process handling functions
 * @date  $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2010
 *     Noriaki Ando
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
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
#include <libgen.h>
#include <signal.h>
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
    signal(SIGCHLD, SIG_IGN);
    pid_t pid;
    if((pid = fork()) < 0 )
      { // fork failed
        return -1; 
      }
    
    if (pid == 0) // I'm child process
      {
        coil::vstring vstr(::coil::split(command, " "));
        char* const * argv = ::coil::toArgv(vstr);

        execvp(vstr.front().c_str(), argv);
        return -1;
      }
    return 0;
  }
}; // namespace coil
#endif // COIL_PROCESS_H

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

#include <coil/Process.h>
#include <coil/File.h>
#include <coil/stringutil.h>

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <libgen.h>
#include <csignal>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>


namespace coil
{

  /*!
   * @if jp
   * @brief ¥×¥í¥»¥¹¤òµ¯Æ°¤¹¤ë
   * @else
   * @brief Launching a process
   * @endif
   */
  int launch_shell(const std::string& command)
  {
    signal(SIGCHLD, SIG_IGN);

    pid_t pid;
    if ((pid = fork()) < 0 )
      {  // fork failed
        return -1;
      }

    if (pid == 0)  // I'm child process
      {
        setsid();

        coil::vstring vstr(::coil::split(command, " "));
        char* const * argv = ::coil::toArgv(vstr);

        execvp(vstr.front().c_str(), argv);

        return -1;
      }
    return 0;
  }

  int daemon(int nochdir, int noclose)
  {
    return ::daemon(nochdir, noclose);
  }

  int create_process(const std::string& command, std::vector<std::string> &out)
  {
    FILE* fd;
    out.clear();
    if ((fd = popen(command.c_str(), "r")) == nullptr)
      {
        return -1;
      }
    do
      {
        char str[512];
        fgets(str, 512, fd);
        std::string line(str);
        if (!line.empty())
          {
            line.erase(line.size() - 1);
          }
        out.push_back(line);
      } while (feof(fd) == 0);
    
    (void) pclose(fd);
    return 0;
  }

} // namespace coil

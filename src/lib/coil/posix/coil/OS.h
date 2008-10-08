// -*- C++ -*-
/*!
 * @file Task.cpp
 * @brief Task class
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

#include <string>
#include <sys/utsname.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>

extern "C"
{
  extern char *optarg;
};

namespace coil
{
  typedef ::utsname utsname;
  inline int uname(utsname* name)
  {
    return ::uname(name);
  }

  typedef ::pid_t pid_t;
  inline pid_t getpid()
  {
    return ::getpid();
  }
  inline pid_t getppid()
  {
    return ::getppid();
  }

  inline char* getenv(const char *name)
  {
    return ::getenv(name);
  }


  /* Global Variables for getopt() */

  class GetOpt
  {
  public:
    GetOpt(int argc, char* const argv[], const char* opt, int flag)
      : m_argc(argc), m_argv(argv), m_opt(opt), m_flag(flag), optind(1), opterr(1), optopt(0)
    {
      this->optarg = ::optarg;
      ::optind = 1;
    }

    ~GetOpt()
    {
      ::optind = 1;
    }

    int operator()()
    {
      ::opterr = opterr;
      ::optind = optind;

      int result = getopt(m_argc, m_argv, m_opt);

      optarg = ::optarg;
      optind = ::optind;
      optopt = ::optopt;

      return result;
    }
    char* optarg;     //! オプション引数
    int optind;       //! 処理対象引数
    int opterr;       //! エラー表示 0:抑止、1:表示
    int optopt;       //! オプション文字が足りない時、多い時にセットされる

  private:
    int m_argc;
    char* const * m_argv;
    const char* m_opt;
    int m_flag;
  };
    
};

#endif // COIL_OS_H

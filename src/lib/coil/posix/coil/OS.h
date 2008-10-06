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


  class GetOpt
  {
  public:
    GetOpt(int argc, char* const argv[], const char* opt, int flag)
      : m_argc(argc), m_argv(argv), m_opt(opt), m_flag(flag)
    {
      this->optarg = ::optarg;
    }

    int operator()()
    {
      return getopt(m_argc, m_argv, m_opt);
    }
    char* optarg;
  private:
    int m_argc;
    char* const * m_argv;
    const char* m_opt;
    int m_flag;
  };
    
};

#endif // COIL_OS_H

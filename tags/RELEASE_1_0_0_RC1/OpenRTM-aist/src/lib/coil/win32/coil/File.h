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

#ifndef COIL_FILE_H
#define COIL_FILE_H

#include <coil/config_coil.h>
#include <memory>

namespace coil
{
  const unsigned int MaxPathLength(1024);

  /*!
  *  @note like ACE.
  */
  inline char* dirname(char* path)
  {
    static char return_dirname[MaxPathLength + 1];
//    const char delimiter('\\');
    const char delimiter('/');
    const char *p = std::strrchr(path, delimiter);
    if (p)
    {
      size_t len = p - path + 1;
      if (len > (sizeof(return_dirname) / sizeof(char)))
      {
        len = sizeof(return_dirname) / sizeof(char);
      }
      std::strncpy(return_dirname, path, len);
    } else {
      return_dirname[0] = '.';
      return_dirname[1] = '\0';
    }
    return return_dirname;
  }

  inline char* basename(const char* path)
  {
//    const char delimiter('\\');
    const char delimiter('/');
    const char *p = std::strrchr(path, delimiter);
    const char *q = (p) ? p + 1 : path ;

    return (char *)q;
  }
};

#endif // COIL_FILE_H

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
  inline std::string dirname(char* path)
  {
    char return_dirname[MaxPathLength + 1];

    size_t len = strlen(path);
    if (len > (sizeof(return_dirname) / sizeof(char)))
    {
      len = sizeof(return_dirname) / sizeof(char);
    }
    std::strncpy(return_dirname, path, len);
    return_dirname[len] = '\0';

    const char delimiter('/');
    char *p = std::strrchr(return_dirname, delimiter);

    std::string dir_name;
    if (p)
    {
      if(p != return_dirname)
      {
        if(*(p+1) == '\0')
        {
           *p = '\0';
           dir_name = dirname(return_dirname);
        }
        else
        {
           *p = '\0';
           dir_name = return_dirname;
        }
      }
      else 
      {
        *(p+1) = '\0';
        dir_name = return_dirname;
      }
    }
    else
    {
      dir_name = ".";
    }
    return dir_name;
  }

  inline std::string basename(const char* path)
  {
    char p[MaxPathLength + 1];

    size_t len = strlen(path);
    if (len > (sizeof(p) / sizeof(char)))
    {
      len = sizeof(p) / sizeof(char);
    }
    std::strncpy(p, path, len);
    p[len] = '\0';

    const char delimiter('/');
    char *pdelimiter = std::strrchr(p, delimiter);

    std::string base_name(p);
    if (pdelimiter)
    {
      if(pdelimiter != p)
      {
        if(*(pdelimiter+1) == '\0')
        {
          *pdelimiter = '\0';
          base_name = basename(p);
        }
        else
        {
          pdelimiter++;
          base_name = pdelimiter;
        }
      }
      else
      {
        if(*(pdelimiter+1) != '\0')
        {
          pdelimiter++;
          base_name = pdelimiter;
        }
        else
        {
          base_name = pdelimiter;
        }

      }
    }
    return base_name;
  }
};

#endif // COIL_FILE_H

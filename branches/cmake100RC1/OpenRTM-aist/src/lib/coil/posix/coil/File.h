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

#include <libgen.h>
#include <coil/config_coil.h>
#include <memory>


namespace coil
{

  inline std::string dirname(char* path)
  {
    char path_name[strlen(path)+1];
    strcpy(path_name, path);
    std::string dir_name = ::dirname(path);
    return dir_name;
  }

  inline std::string basename(const char* path)
  {
    char path_name[strlen(path)+1];
    strcpy(path_name, path);
    std::string base_name = ::basename(path_name);
    return base_name;
  }
};

#endif // COIL_FILE_H

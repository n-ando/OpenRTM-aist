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

  inline char* dirname(char* path)
  {
    return ::dirname(path);
  }

  inline char* basename(const char* path)
  {
    char p[strlen(path)+1];
    strncpy(p, path, strlen(path));
    return ::basename(p);
  }
};

#endif // COIL_FILE_H
